#!/bin/bash

#PBS -l walltime=00:01:00,nodes=1:ppn=4
#PBS -N my_job
#PBS -q batch

cd $PBS_O_WORKDIR
mpirun --hostfile $PBS_NODEFILE -np 4 ./a.out 
