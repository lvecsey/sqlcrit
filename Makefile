
CC=gcc

CFLAGS=-O3 -Wall -g -pg

all : sqlcrit

sqlcrit : LIBS+=-lsqlite3

sqlcrit : critbit.o sqlcrit.o
	$(CC) -o $@ $(CFLAGS) $^ $(LDFLAGS) $(LIBS)

sqlcrit-fastcgi : LIBS+=-lfcgi

sqlcrit-fastcgi : critbit.o replace_plus.o fill_critbit.o sqlcrit-fastcgi.o
	$(CC) -o $@ $(CFLAGS) $^ $(LDFLAGS) $(LIBS)
