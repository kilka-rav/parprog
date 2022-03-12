Tasks for parallel programming using MPI
Compile:
mpicc <name>.c -o name
In file <name>.sh you should specify the queue system.
Run:
qsub <name>.sh
Your results are stored in special files
Info about processes:
qstat
