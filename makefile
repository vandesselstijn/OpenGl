all : zeepkist

zeepkist.o : zeepkist.c
	cc -c zeepkist.c

zeepkist : zeepkist.o
	cc zeepkist.c -o zeepkist -LGL -lglut -lm
