#-*-makefile-*-

TARGETS = \
    InitJPG.o

all All: $(TARGETS)

################################################################################
INCPATH = -I/usr/local/include
CFLAGS = +DD32 $(DEBUGFLAGS) $(INCPATH)


SRCS = \
	InitJPG.c

OBJS = $(SRCS:.c=.o)

.SUFFIXES:	.c

.c.o:	
	cc -c $< $(CFLAGS)
