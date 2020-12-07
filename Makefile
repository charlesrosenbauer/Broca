all:
	clang -O3 *.c

debug:
	clang -O2 -g *.c