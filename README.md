# Sort-Merge-Join
Implementation of optimized sort-merge join algorithm in C++.

## Q3: Sort-merge Join Algorithms
Consider the following relations:
> Dept (did (integer), dname (string), budget (double), managerid (integer))

> Emp (eid (integer), ename (string), age (integer), salary (double))

Fields of types integer, double, and string occupy 4, 8, and 40 bytes, respectively. <br>
Each block can fit at most one tuple of an input relation. <br>
There are at most 22 blocks available to the join algorithm in the main memory. <br>
Implement the optimized sort-merge join algorithm for Dept ./Dept.managerid=Emp.eid Emp in C++.
+ Each input relation is stored in a separate CSV file, i.e., each tuple is in a separate line and fields of each record are separated by commas.
+ The result of the join must be stored in a new CSV file. The files that store relations Dept and Emp are Dept.csv and Emp.csv, respectively.
+ Your program must assume that the input files are in the current working directory, i.e., the one from which your program is running.
+ The program must store the result in a new CSV file with the name join.csv in the current
working directory.
__________________________________________________________________________________________________________________________________________________

## To run the Algorithm
1. Add your Emp.csv and Dept.csv to source directory
2. Run:
```
> g++ -o out sortMergeJoin.cpp
> out.exe
```
3. Required Join is implemented and the file is stored in source directory.
4. empSorted and deptSorted are also saved for different algorithms like multiwaySort.
__________________________________________________________________________________________________________________________________________________
Oregon State University, Winter 2021 (CS540)
