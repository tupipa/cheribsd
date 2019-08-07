# $FreeBSD$

SRCDIR=	${.CURDIR}/../cheritest
.PATH:	${SRCDIR}

PROG=	cheriabitest

CHERIABI_TESTS=	yes
CHERI_C_TESTS=	yes

.include	<${SRCDIR}/Makefile>

# Lele: save assembly file for manual inspection
# with =obj and no -Wno-error: will get unused variable warning to error
# with =obj and -Wno-error: will get clang crash on clang_purecap_capret.i
# CFLAGS+= -save-temps=obj -Wno-error
# CFLAGS+= -save-temps -Wno-error



