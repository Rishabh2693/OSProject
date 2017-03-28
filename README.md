# OSProject

Performance Measurement 

The aim of the project is to measure the Operational as well as Memory overheads of a system, along with the overheads due to the 
associated measurements. 

The Operational overheads that have been tested for are: 
1. Procedure Call Overhead 
2. System Call Overhead 
3. Task Creation Time (through kernel threads and forks) 
4. Context Switch Time 

The Memory Overhead tested included: 
1. Page Fault time 
2. Memory Access Time
3. RAM Bandwidth The Measurement Overheads are: Loop Overheads, Time Overhead

The measurements for performance testing has been implemented through C programming and the compilation for the codes involved 
have been done using gnu gcc.  The experiments have been run on Dell Inspiron. Its machine description has been described in the
next section. 

RUNNING THE CODE
1. Go into the folder with the name of the overhead you want to calculate.
2. Compile the C file in the folder and execute the compiled code.
