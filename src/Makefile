# Compilation makefile

MPICPP = mpic++
MPICC = mpicc
CPP = g++
CC = gcc
CLANG = clang++
R = R
RM = rm
MAKE = make
CPPFLAGS = -std=c++11 -fopenmp
CCFLAGS = -std=c11

all: main.c
	$(CC) -g -Wall $(CCFLAGS) main.c -o cfd
# 	$(CPP) $(CPPFLAGS) main.c -o cfd
#	$(MPICPP) $(CPPFLAGS) main.c -o cfd

clean:
	$(RM) main.o cfd

clcfdseq:
	$(RM) grid.o gridfile.o *~ cfdseq

