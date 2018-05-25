all : zeepkist

zeepkist.o : zeepkist.c zeepkist.h
	cc -c zeepkist.c zeepkist.h

zeepkist : zeepkist.o
	cc zeepkist.c -o zeepkist  -lGL -lglut -lGLU -lm -lglut -lm
