
HOME=$HOME

SRC_ROOT=$HOME/lab/sva/cheri/cheribsd
#SRC_ROOT=$HOME/cheri/cheribsd

cd / 	
find  $SRC_ROOT/                                                                \
	-path "$SRC_ROOT/include/asm-*" ! -path "$SRC_ROOT/include/asm-i386*" -prune -o \
	-path "$SRC_ROOT/sys/arm*" -prune -o             \
	-path "$SRC_ROOT/sys/arm64*" -prune -o             \
	-path "$SRC_ROOT/sys/i386*" -prune -o             \
	-path "$SRC_ROOT/sys/powerpc*" -prune -o             \
	-path "$SRC_ROOT/sys/sparc64*" -prune -o             \
	-path "$SRC_ROOT/contrib*" -prune -o             \
        -name "*.[chxsS]" -print >$SRC_ROOT/.cscope/cscope.files


#	-path "$SRC_ROOT/sys/riscv*" -prune -o             \
#	-path "$SRC_ROOT/sys/amd64*" -prune -o             \


# regenerate the database

cd $SRC_ROOT/.cscope && cscope -b -q -k

