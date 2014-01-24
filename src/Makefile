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

mpi: mpitest.c grid.h grid.c field.h mesh.h mesh.c
	$(MPICC) -g -Wall -c grid.c -o grid.o
	$(MPICC) -g -Wall -c mesh.c -o mesh.o
	$(MPICC) -g -Wall -c mpitest.c -o mpitest.o
	$(MPICC) -g -Wall -o mpitest mpitest.o grid.o mesh.o -lm
	
prmt: mesh.h mesh.c permut.c
	$(MPICC) -g -Wall -c mesh.c -o mesh.o
	$(MPICC) -g -Wall -c permut.c -o permut.o
	$(MPICC) -g -Wall -o permut permut.o mesh.o -lm
	
smpl: simplex.c mesh.h mesh.c
	$(MPICC) -g -Wall -c mesh.c -o mesh.o
	$(MPICC) -g -Wall -c simplex.c -o simplex.o
	$(MPICC) -g -Wall -o simplex simplex.o mesh.o -lm
	
cfdseq: grid.h grid.h gridfile.c function.h function.c
	$(MPICC) -g -Wall -c grid.c -o grid.o
	$(MPICC) -g -Wall -c gridfile.c -o gridfile.o
	$(MPICC) -g -Wall -c function.c -o function.o
	$(MPICC) -g -Wall -o cfdseq gridfile.o grid.o function.o -lm

clean:
	$(RM) main.o cfd

clcfdseq:
	$(RM) grid.o gridfile.o *~ cfdseq

