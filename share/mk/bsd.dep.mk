# $FreeBSD$
#
# The include file <bsd.dep.mk> handles Makefile dependencies.
#
#
# +++ variables +++
#
# CTAGS		A tags file generation program [gtags]
#
# CTAGSFLAGS	Options for ctags(1) [not set]
#
# DEPENDFILE	dependencies file [.depend]
#
# GTAGSFLAGS	Options for gtags(1) [-o]
#
# HTAGSFLAGS	Options for htags(1) [not set]
#
# MKDEP		Options for ${MKDEPCMD} [not set]
#
# MKDEPCMD	Makefile dependency list program [mkdep]
#
# SRCS          List of source files (c, c++, assembler)
#
# DPSRCS	List of source files which are needed for generating
#		dependencies, ${SRCS} are always part of it.
#
# +++ targets +++
#
#	cleandepend:
#		Remove depend and tags file
#
#	depend:
#		Make the dependencies for the source files, and store
#		them in the file ${DEPENDFILE}.
#
#	tags:
#		In "ctags" mode, create a tags file for the source files.
#		In "gtags" mode, create a (GLOBAL) gtags file for the
#		source files.  If HTML is defined, htags(1) is also run
#		after gtags(1).

.if !target(__<bsd.init.mk>__)
.error bsd.dep.mk cannot be included directly.
.endif

CTAGS?=		gtags
CTAGSFLAGS?=
GTAGSFLAGS?=	-o
HTAGSFLAGS?=

# XXX-BD: Is _MKDEPCC:= in head, but we need to expand in the target
_MKDEPCC=	${CC.${.IMPSRC:T}:U${CC}:N${CCACHE_BIN}}
# XXX: DEPFLAGS can come out once Makefile.inc1 properly passes down
# CXXFLAGS.
.if !empty(DEPFLAGS)
_MKDEPCC+=	${DEPFLAGS}
.endif
MKDEPCMD?=	CC='${_MKDEPCC}' mkdep
DEPENDFILE?=	.depend
.MAKE.DEPENDFILE= ${DEPENDFILE}
DEPENDFILES=	${DEPENDFILE}

# Keep `tags' here, before SRCS are mangled below for `depend'.
.if !target(tags) && defined(SRCS) && !defined(NO_TAGS)
tags: ${SRCS}
.if ${CTAGS:T} == "gtags"
	@cd ${.CURDIR} && ${CTAGS} ${GTAGSFLAGS} ${.OBJDIR}
.if defined(HTML)
	@cd ${.CURDIR} && htags ${HTAGSFLAGS} -d ${.OBJDIR} ${.OBJDIR}
.endif
.else
	@${CTAGS} ${CTAGSFLAGS} -f /dev/stdout \
	    ${.ALLSRC:N*.h} | sed "s;${.CURDIR}/;;" > ${.TARGET}
.endif
.endif

.if defined(SRCS)
CLEANFILES?=

.if ${MK_FAST_DEPEND} == "yes" || !exists(${.OBJDIR}/${DEPENDFILE})
.for _S in ${SRCS:N*.[dhly]}
${_S:R}.o: ${_S}
.endfor
.endif

# Lexical analyzers
.for _LSRC in ${SRCS:M*.l:N*/*}
.for _LC in ${_LSRC:R}.c
${_LC}: ${_LSRC}
	${LEX} ${LFLAGS} -o${.TARGET} ${.ALLSRC}
.if ${MK_FAST_DEPEND} == "yes" || !exists(${.OBJDIR}/${DEPENDFILE})
${_LC:R}.o: ${_LC}
.endif
SRCS:=	${SRCS:S/${_LSRC}/${_LC}/}
CLEANFILES+= ${_LC}
.endfor
.endfor

# Yacc grammars
.for _YSRC in ${SRCS:M*.y:N*/*}
.for _YC in ${_YSRC:R}.c
SRCS:=	${SRCS:S/${_YSRC}/${_YC}/}
CLEANFILES+= ${_YC}
.if !empty(YFLAGS:M-d) && !empty(SRCS:My.tab.h)
.ORDER: ${_YC} y.tab.h
${_YC} y.tab.h: ${_YSRC}
	${YACC} ${YFLAGS} ${.ALLSRC}
	cp y.tab.c ${_YC}
CLEANFILES+= y.tab.c y.tab.h
.elif !empty(YFLAGS:M-d)
.for _YH in ${_YC:R}.h
${_YH}: ${_YC}
${_YC}: ${_YSRC}
	${YACC} ${YFLAGS} -o ${_YC} ${.ALLSRC}
SRCS+=	${_YH}
CLEANFILES+= ${_YH}
.endfor
.else
${_YC}: ${_YSRC}
	${YACC} ${YFLAGS} -o ${_YC} ${.ALLSRC}
.endif
.if ${MK_FAST_DEPEND} == "yes" || !exists(${.OBJDIR}/${DEPENDFILE})
${_YC:R}.o: ${_YC}
.endif
.endfor
.endfor

# DTrace probe definitions
.if ${SRCS:M*.d}
CFLAGS+=	-I${.OBJDIR}
.endif
.for _DSRC in ${SRCS:M*.d:N*/*}
.for _D in ${_DSRC:R}
SRCS+=	${_D}.h
${_D}.h: ${_DSRC}
	${DTRACE} ${DTRACEFLAGS} -h -s ${.ALLSRC}
SRCS:=	${SRCS:S/^${_DSRC}$//}
OBJS+=	${_D}.o
CLEANFILES+= ${_D}.h ${_D}.o
${_D}.o: ${_DSRC} ${OBJS:S/^${_D}.o$//}
	@rm -f ${.TARGET}
	${DTRACE} ${DTRACEFLAGS} -G -o ${.TARGET} -s ${.ALLSRC:N*.h}
.if defined(LIB)
CLEANFILES+= ${_D}.So ${_D}.po
${_D}.So: ${_DSRC} ${SOBJS:S/^${_D}.So$//}
	@rm -f ${.TARGET}
	${DTRACE} ${DTRACEFLAGS} -G -o ${.TARGET} -s ${.ALLSRC:N*.h}
${_D}.po: ${_DSRC} ${POBJS:S/^${_D}.po$//}
	@rm -f ${.TARGET}
	${DTRACE} ${DTRACEFLAGS} -G -o ${.TARGET} -s ${.ALLSRC:N*.h}
.endif
.endfor
.endfor


.if ${MK_FAST_DEPEND} == "yes" && \
    (${.MAKE.MODE:Mmeta} == "" || ${.MAKE.MODE:Mnofilemon} != "")
DEPENDFILES+=	${DEPENDFILE}.*
DEPEND_MP?=	-MP
# Handle OBJS=../somefile.o hacks.  Just replace '/' rather than use :T to
# avoid collisions.
DEPEND_FILTER=	C,/,_,g
DEPEND_CFLAGS+=	-MD ${DEPEND_MP} -MF${DEPENDFILE}.${.TARGET:${DEPEND_FILTER}}
DEPEND_CFLAGS+=	-MT${.TARGET}
.if defined(.PARSEDIR)
# Only add in DEPEND_CFLAGS for CFLAGS on files we expect from DEPENDOBJS
# as those are the only ones we will include.
DEPEND_CFLAGS_CONDITION= !empty(DEPENDOBJS:M${.TARGET:${DEPEND_FILTER}})
CFLAGS+=	${${DEPEND_CFLAGS_CONDITION}:?${DEPEND_CFLAGS}:}
.else
CFLAGS+=	${DEPEND_CFLAGS}
.endif
DEPENDSRCS=	${SRCS:M*.[cSC]} ${SRCS:M*.cxx} ${SRCS:M*.cpp} ${SRCS:M*.cc}
.if !empty(DEPENDSRCS)
DEPENDOBJS+=	${DEPENDSRCS:R:S,$,.o,}
.endif
DEPENDFILES_OBJS=	${DEPENDOBJS:O:u:${DEPEND_FILTER}:C/^/${DEPENDFILE}./}
.if ${.MAKEFLAGS:M-V} == ""
.for __depend_obj in ${DEPENDFILES_OBJS}
.sinclude "${__depend_obj}"
.endfor
.endif
.endif	# ${MK_FAST_DEPEND} == "yes"
.endif	# defined(SRCS)

.if ${MK_DIRDEPS_BUILD} == "yes"
.include <meta.autodep.mk>
# this depend: bypasses that below
# the dependency helps when bootstrapping
depend: beforedepend ${DPSRCS} ${SRCS} afterdepend
beforedepend:
afterdepend: beforedepend
.endif

.if !target(depend)
.if defined(SRCS)
depend: beforedepend ${DEPENDFILE} afterdepend

# Tell bmake not to look for generated files via .PATH
.NOPATH: ${DEPENDFILE} ${DEPENDFILES_OBJS}

.if ${MK_FAST_DEPEND} == "no"
# Capture -include from CFLAGS.
# This could be simpler with bmake :tW but needs to support fmake for MFC.
_CFLAGS_INCLUDES= ${CFLAGS:Q:S/\\ /,/g:C/-include,/-include%/g:C/,/ /g:M-include*:C/%/ /g}
_CXXFLAGS_INCLUDES= ${CXXFLAGS:Q:S/\\ /,/g:C/-include,/-include%/g:C/,/ /g:M-include*:C/%/ /g}
# XXX: Temporary hack to workaround .depend files not tracking -include
.if !empty(_CFLAGS_INCLUDES)
${OBJS} ${POBJS} ${SOBJS}: ${_CFLAGS_INCLUDES:M*.h}
.endif
.if !empty(_CXXFLAGS_INCLUDES)
${OBJS} ${POBJS} ${SOBJS}: ${_CXXFLAGS_INCLUDES:M*.h}
.endif

# Different types of sources are compiled with slightly different flags.
# Split up the sources, and filter out headers and non-applicable flags.
MKDEP_CFLAGS=	${CFLAGS:M-nostdinc*} ${CFLAGS:M-[BIDU]*} ${CFLAGS:M-std=*} \
		${CFLAGS:M-ansi} ${_CFLAGS_INCLUDES}
MKDEP_CXXFLAGS=	${CXXFLAGS:M-nostdinc*} ${CXXFLAGS:M-[BIDU]*} \
		${CXXFLAGS:M-std=*} ${CXXFLAGS:M-ansi} ${CXXFLAGS:M-stdlib=*} \
		${_CXXFLAGS_INCLUDES}
.endif	# ${MK_FAST_DEPEND} == "no"

DPSRCS+= ${SRCS}
DPFILES+=	${DPSRCS:M*.[cS]:S/.c$/.dep_c/:S/.S$/.dep_S/} \
		${DPSRCS:M*.cc:S/.cc$/.dep_cc/} \
		${DPSRCS:M*.C:S/.C$/.dep_C/} \
		${DPSRCS:M*.cpp:S/.cpp$/.dep_cpp/} \
		${DPSRCS:M*.cxx:S/.cxx$/.dep_cxx/}
.SUFFIXES:	.dep_c .dep_S .dep_cc .dep_C .dep_cpp .dep_cxx
.c.dep_c .S.dep_S: ${DPSRCS}
	${MKDEPCMD} -f ${.TARGET} ${MKDEP} ${MKDEP_CFLAGS} ${.IMPSRC}
.cc.dep_cc .C.dep_C .cpp.dep_cpp .cxx.dep_cxx: ${DPSRCS}
	${MKDEPCMD} -f ${.TARGET} ${MKDEP} ${MKDEP_CXXFLAGS} ${.IMPSRC}

.if ${MK_FAST_DEPEND} == "no"
${DEPENDFILE}: ${DPFILES}
	cat ${.ALLSRC} > ${DEPENDFILE}
.else
${DEPENDFILE}: ${DPSRCS}
	: > ${.TARGET}
.endif	# ${MK_FAST_DEPEND} == "no"
.if target(_EXTRADEPEND)
_EXTRADEPEND: .USE
${DEPENDFILE}: _EXTRADEPEND
.endif

.ORDER: ${DEPENDFILE} afterdepend
.else
depend: beforedepend afterdepend
.endif
.if !target(beforedepend)
beforedepend:
.else
.ORDER: beforedepend ${DEPENDFILE}
.ORDER: beforedepend afterdepend
.endif
.if !target(afterdepend)
afterdepend:
.endif
.endif

.if !target(cleandepend)
cleandepend:
.if defined(SRCS)
.if ${CTAGS:T} == "gtags"
	rm -f ${DEPENDFILES} GPATH GRTAGS GSYMS GTAGS
.if defined(HTML)
	rm -rf HTML
.endif
.else
	rm -f ${DEPENDFILES} tags
.endif
.endif
.endif

.if !target(checkdpadd) && (defined(DPADD) || defined(LDADD))
_LDADD_FROM_DPADD=	${DPADD:R:T:C;^lib(.*)$;-l\1;g}
# Ignore -Wl,--start-group/-Wl,--end-group as it might be required in the
# LDADD list due to unresolved symbols
_LDADD_CANONICALIZED=	${LDADD:N:R:T:C;^lib(.*)$;-l\1;g:N-Wl,--[es]*-group}
checkdpadd:
.if ${_LDADD_FROM_DPADD} != ${_LDADD_CANONICALIZED}
	@echo ${.CURDIR}
	@echo "DPADD -> ${_LDADD_FROM_DPADD}"
	@echo "LDADD -> ${_LDADD_CANONICALIZED}"
.endif
.endif
