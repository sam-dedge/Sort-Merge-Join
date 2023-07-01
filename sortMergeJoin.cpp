#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <math.h>
#include <cstdio>

using namespace std;

const int M = 22;
int passNum = 0;

typedef struct EmpBlock {
    int eid;
    string ename;
    int age;
    double salary;
    EmpBlock *nextEmp;
    //int empEntry;
}empBlock;

typedef struct DeptBlock {
    int did;
    string dname;
    double budget;
    int managerid;
    DeptBlock *nextDept;
    //int deptEntry;
}deptBlock;

typedef struct JoinTuple {
    int did;
    string dname;
    double budget;
    int managerid;
    int eid;
    string ename;
    int age;
    double salary;
    JoinTuple *nextJoinTuple;
    //int deptEntry;
} joinTuple;

bool eidSort(empBlock a, empBlock b) {
    return a.eid < b.eid;
}

bool didSort(deptBlock a, deptBlock b) {
    return a.managerid < b.managerid;
}

bool empMinRecord(empBlock a, empBlock b) {
    return a.eid < b.eid;
}

bool deptMinRecord(deptBlock a, deptBlock b) {
    return a.managerid < b.managerid;
}

void deleteRuns(int numberOfRuns, int delPassNum, string delType) {
    // Delete Code
    //cout << "In Delete - delPassNum = " << delPassNum << endl;
    for(int k=0; k<numberOfRuns; k++) {
        string toDel = delType + to_string(delPassNum) + "run" + to_string(k+1) + ".txt";
        std::remove(toDel.c_str());
    }
}

int readEmp() {
    std::array<empBlock, 22> record;
    //Block temp;

    // Read File
    fstream fin;
    fin.open("Emp.csv");

    string line, word;
    std::vector<string> tuple;

    int runNum = 1;
    int i=0;

    // PASS 0
    while (getline(fin, line, '\n') && passNum == 0 ) {

        stringstream ss(line);

        tuple.clear();
        while(getline(ss, word, ',')) {
            tuple.push_back(word);
        }

        // Weird representation of double? Why? Affects anything?
        /*if(stoi(tuple[0]) == 253754){
            cout << "HERE - " << tuple[3] << "   " << stoi(tuple[3]);
            int x = stoi(tuple[3]);
            double d = (double) x;
            double db = 999999+1;
            cout << "Double Check d - " << d << endl;
            cout << "Double Check db - " << db << endl;
        }*/

        // Fill block with record in tuple
        record[i].eid = stoi(tuple[0]);
        record[i].ename = tuple[1];
        record[i].age = stoi(tuple[2]);
        record[i].salary = stod(tuple[3]);

        //cout << record[i].ename << endl;
        i++;

        //Writes after Memory is full as Memory available = M (global)
        if(i>=M || fin.eof()) {
            sort(record.begin(), record.end(), eidSort);

            // Writing sorted record[1..M] into run file
            string filename = "emp" + to_string(passNum) + "run" + to_string(runNum) + ".txt";
            std::ofstream outFile(filename);
            for (const auto &r : record){
                if(r.eid == 0)
                    continue;
                outFile << r.eid << "," << r.ename << "," << r.age << "," << r.salary << "\n";
            }
            runNum++;
            i = 0;

            //cout << "After Sorting... 2nd Rec: " << record[1].ename << "   " << record[1].eid << endl;

            // Resets record by putting NULL or 0 in record[1..M]
            memset(record.begin(), '\0', sizeof(record));

            outFile.close();
        }

    }

    int j=0;
    while(j<22) {
        if(record[j].eid == 0)
            record[j].eid = 999999999;
        j++;
    }

    if(fin.eof() && record[0].ename != ""){

        sort(record.begin(), record.end(), eidSort);
        //cout << "After Sorting... 18th Rec: " << record[5].ename << "   " << record[1].eid << endl;

        string filename = "emp" + to_string(passNum) + "run" + to_string(runNum) + ".txt";
        std::ofstream outFile(filename);
        for (const auto &r : record){
            if(r.eid == 0)
                continue;
            outFile << r.eid << "," << r.ename << "," << r.age << "," << r.salary << "\n";

        }

        runNum++;
        i = 0;

        //cout << "After Sorting... 2nd Rec: " << record[1].ename << "   " << record[1].eid << endl;
        memset(record.begin(), '\0', sizeof(record));

        outFile.close();
    }

    passNum++;
    fin.close();
    return runNum-1;

}

int readDept() {
    std::array<deptBlock, 22> record;
    //Block temp;

    // Read File
    fstream fin;
    fin.open("Dept.csv");

    string line, word;
    std::vector<string> tuple;

    int runNum = 1;
    int i=0;

    // PASS 0
    while (getline(fin, line, '\n') && passNum == 0 ) {

        stringstream ss(line);
        //cout << line << endl;
        tuple.clear();
        while(getline(ss, word, ',')) {
            tuple.push_back(word);
        }

        // Fill block with record in tuple
        record[i].did = stoi(tuple[0]);
        record[i].dname = tuple[1];
        record[i].budget = stod(tuple[2]);
        record[i].managerid = stoi(tuple[3]);

        //cout << record[i].ename << endl;
        i++;

        //Writes after Memory is full as Memory available = M (global)
        if(i>=M || fin.eof()) {
            sort(record.begin(), record.end(), didSort);

            // Writing sorted record[1..M] into run file
            string filename = "dept" + to_string(passNum) + "run" + to_string(runNum) + ".txt";
            std::ofstream outFile(filename);
            for (const auto &r : record){
                if(r.did == 0)
                    continue;
                outFile << r.did << "," << r.dname << "," << r.budget << "," << r.managerid << "\n";
            }
            runNum++;
            i = 0;

            //cout << "After Sorting... 2nd Rec: " << record[1].ename << "   " << record[1].eid << endl;

            // Resets record by putting NULL or 0 in record[1..M]
            memset(record.begin(), '\0', sizeof(record));

            outFile.close();
        }

    }
    //cout << "Record 0: " << record[0].dname << "   " << record[0].did << endl;

    int j=0;
    while(j<22) {
        if(record[j].dname == "")
            record[j].managerid = 999999999;
        j++;
    }

    //cout << "Record 17: " << record[17].dname << "   " << record[17].managerid << endl;
    //cout << "Record 20: " << record[0].dname << "   " << record[20].managerid << endl;
    if(fin.eof() && record[0].dname != ""){

        sort(record.begin(), record.end(), didSort);
        //cout << "After Sorting... 5th Rec: " << record[0].dname << "   " << record[5].dname << endl;

        string filename = "dept" + to_string(passNum) + "run" + to_string(runNum) + ".txt";
        std::ofstream outFile(filename);
        for (const auto &r : record){
            if(r.managerid == 999999999)
                continue;
            outFile << r.did << "," << r.dname << "," << r.budget << "," << r.managerid << "\n";

        }

        runNum++;
        i = 0;

        //cout << "After Sorting... 2nd Rec: " << record[1].dname << "   " << record[1].did << endl;
        memset(record.begin(), '\0', sizeof(record));

        outFile.close();
    }

    passNum++;
    fin.close();
    //cout << "\nEnd of read " << runNum << endl;
    return runNum-1;
}

int passIthEmp(int numOfRuns, int maxPasses) {
    cout << "-------Ongoing-------" << endl;
    cout << "Pass Number: " << passNum << "\t" << "Runs to Merge: " << numOfRuns << endl;
    cout << "...\n" << ".....\n" << "........." << endl;
    int runsLeftToMerge = numOfRuns;

    int mergePointers;
    if(numOfRuns>=M)
        mergePointers = M-1;
    else
        mergePointers = runsLeftToMerge;

    fstream fin[mergePointers];

    //cout << "Here2 Merger Pointer = " << mergePointers << endl;
    std::array<empBlock, 21> record;
    empBlock outBuf;
    std::vector<string> tuple;
    string line, word;

    //cout << record[1].ename;
    //cout << "\n\nMerge Pointers = " << mergePointers << endl;

    int runNum=0; // J = New number of Runs of Pass i+1
    // When i = mergePointers, Values are initialized again and

    int k=0;
    while(k<22) {
        if(record[k].eid == 0)
            record[k].eid = 999999999;
        k++;
    }

    for(int i=0, j=1; i<=mergePointers && mergePointers >= 1; i++, j++) {

        if(i != mergePointers) {
            //cout << "Record in IF of EMP Merge step: ";
            string filename;
            filename = "emp" + to_string(passNum-1) + "run" + to_string(j) + ".txt";
            fin[i].open(filename);

            //cout << "Here3" << "  " << runNum << "   " << i << "  " << mergePointers << endl;
            //cout << &fin[i] << endl;

            getline(fin[i], line, '\n');
            stringstream ss(line);
            //cout << "Here4" << "   " << line;
            tuple.clear();
            while(getline(ss, word, ',')) {
                tuple.push_back(word);
            }

            record[i].eid = stoi(tuple[0]);
            record[i].ename = tuple[1];
            record[i].age = stoi(tuple[2]);
            record[i].salary = stod(tuple[3]);
            //cout << "Here" << i << "  " << record[i].eid << "   " << record[i].ename << endl;
            //cout << "Record: " << record[i].eid << "  " << record[i].ename << endl;
        }
        else {
            //cout << "Record in Merge step: " << record[1].eid << "  " << record[1].eid << endl;
            //cout << "-----------------Sorted Run----------------" << j << "  " << mergePointers << endl;
            string outFilename;
            if(maxPasses == passNum)
                outFilename = "empSorted.csv";
            else
                outFilename = "emp" + to_string(passNum) + "run" + to_string(j) + ".txt";
            //cout << outFilename << endl;

            ofstream outFile;
            outFile.open(outFilename, ios::app);

            while(true) {

                empBlock *ptr = std::min_element(record.begin(), record.end(), empMinRecord);
                // Block outBuf contains smallest tuple
                outBuf = *ptr;
                //cout << "Here   " << outBuf.eid << "  " << record[0].eid << endl;
                if(outBuf.eid == 999999999) {
                    //cout << "Break Reason - minEid = " << outBuf.eid << endl;
                    break;
                }

                //cout << "Here  " << outBuf.eid << endl;
                int index = ptr - record.begin();

                if(fin[index].eof()) {
                    memset(&record[index], '\0', sizeof(empBlock));
                    // Arbitrarily long number to avoid collision with empMinRecord.
                    record[index].eid = 999999999;
                    continue;
                }
                else
                    getline(fin[index], line, '\n');

                //cout << line << endl;
                stringstream ss(line);
                tuple.clear();
                while(getline(ss, word, ',')) {
                    tuple.push_back(word);
                }
                record[index].eid = stoi(tuple[0]);
                record[index].ename = tuple[1];
                record[index].age = stoi(tuple[2]);
                record[index].salary = stod(tuple[3]);

                //  ---------TURN to OutputFile---------
                // Appends to EOF
                outFile << outBuf.eid << "," << outBuf.ename << "," << outBuf.age << "," << outBuf.salary << "\n";

                // cout << "outBuf: " << outBuf.eid << "   " << outBuf.ename << endl;
                //cout << "Record at 8: " << record[8].ename << "  " << index;
            }

            //cout << "Here2   " << mergePointers << endl;

            // New Initialising
            outFile.close();

            // i will be initialized to 0 after getting incremented after this iteration of loop
            i = -1;

            for(int k=0; k<mergePointers; k++)
                fin[k].close();
            runsLeftToMerge = runsLeftToMerge - mergePointers;
            if(runsLeftToMerge>=M)
                mergePointers = M-1;
            else
                mergePointers = runsLeftToMerge;

            memset(&record, '\0', sizeof(record));
            for(int k=0; k<22; k++)
                record[k].eid = 999999999;

            j--; //The next continue statement skips one run file

            //cout << "RUN   J : " << runNum << "   " << j;
            runNum = j;
        }

    }

    cout << "End of Pass Num " << passNum << " with # of Runs Created = " << runNum << endl;
    //deleteRuns(numOfRuns , passNum-1 , "emp");
    passNum++;
    return runNum; // Returns number of Runs created for that pass

}

int passIthDept(int numOfRuns, int maxPasses) {
    cout << "-------Ongoing-------" << endl;
    cout << "Pass Number: " << passNum << "\t" << "Runs to Merge: " << numOfRuns << endl;
    cout << "...\n" << ".....\n" << "........." << endl;
    int runsLeftToMerge = numOfRuns;

    int mergePointers;
    if(numOfRuns>=M)
        mergePointers = M-1;
    else
        mergePointers = runsLeftToMerge;

    fstream fin[mergePointers];

    //cout << "Here2 Merger Pointer = " << mergePointers << endl << endl;
    std::array<deptBlock, 21> record;
    deptBlock outBuf;
    std::vector<string> tuple;
    string line, word;

    //cout << record[1].ename;
    //cout << "\n\nMerge Pointers = " << mergePointers << endl;

    int runNum=0; // J = New number of Runs of Pass i+1
    // When i = mergePointers, Values are initialized again and

    int k=0;
    while(k<22) {
        if(record[k].dname == "")
            record[k].managerid = 999999999;
        k++;
    }

    for(int i=0, j=1; i<=mergePointers && mergePointers >= 1; i++, j++) {

        if(i != mergePointers) {
            //cout << "Record in IF of DEPT Merge step: " << record[1].dname << "  " << record[1].managerid << endl;
            string filename;
            filename = "dept" + to_string(passNum-1) + "run" + to_string(j) + ".txt";
            fin[i].open(filename);

            //cout << "Here3" << "  " << runNum << "   " << i << "  " << mergePointers << endl;
            //cout << &fin[i] << endl;

            getline(fin[i], line, '\n');
            stringstream ss(line);
            //cout << "Here4" << "   " << line;
            tuple.clear();
            while(getline(ss, word, ',')) {
                tuple.push_back(word);
            }

            record[i].did = stoi(tuple[0]);
            record[i].dname = tuple[1];
            record[i].budget = stod(tuple[2]);
            record[i].managerid = stoi(tuple[3]);
            //cout << "Here" << i << "  " << record[i].eid << "   " << record[i].ename << endl;
            //cout << "Record: " << record[i].did << "  " << record[i].dname << endl;
        }
        else {
            //cout << "Record in Merge step: " << record[18].managerid << "  " << record[0].managerid << endl;
            //cout << "-----------------Sorted Run----------------" << j << "  " << mergePointers << endl;
            string outFilename;
            if(maxPasses == passNum)
                outFilename = "deptSorted.csv";
            else
                outFilename = "dept" + to_string(passNum) + "run" + to_string(j) + ".txt";
            //cout << outFilename << endl;

            ofstream outFile;
            outFile.open(outFilename, ios::app);
            //cout << "Here   " << outFilename << endl;

            while(true) {

                deptBlock *ptr = std::min_element(record.begin(), record.end(), deptMinRecord);
                // Block outBuf contains smallest tuple
                outBuf = *ptr;


                if(outBuf.dname == "" || outBuf.managerid == 999999999) {
                    //cout << "Break Reason - minEid = " << outBuf.managerid << endl;
                    break;
                }

                //cout << "Here  " << outBuf.eid << endl;
                int index = ptr - record.begin();
                //cout << "Here   " << outBuf.managerid << "  " << outBuf.dname <<"   " << index<< endl;

                if(fin[index].eof()) {
                    memset(&record[index], '\0', sizeof(empBlock));
                    // Arbitrarily long number to avoid collision with empMinRecord.
                    record[index].managerid = 999999999;
                    continue;
                }
                else
                    getline(fin[index], line, '\n');

                //cout << line << endl;
                stringstream ss(line);
                tuple.clear();
                while(getline(ss, word, ',')) {
                    tuple.push_back(word);
                }
                record[index].did = stoi(tuple[0]);
                record[index].dname = tuple[1];
                record[index].budget = stod(tuple[2]);
                record[index].managerid = stoi(tuple[3]);

                //  ---------TURN to OutputFile---------
                // Appends to EOF
                outFile << outBuf.did << "," << outBuf.dname << "," << outBuf.budget << "," << outBuf.managerid << "\n";

                // cout << "outBuf: " << outBuf.eid << "   " << outBuf.ename << endl;
                //cout << "Record at 8: " << record[8].ename << "  " << index;
            }

            //cout << "Here2   " << mergePointers << endl;

            // New Initialising
            outFile.close();

            // i will be initialized to 0 after getting incremented after this iteration of loop
            i = -1;

            for(int k=0; k<mergePointers; k++)
                fin[k].close();
            runsLeftToMerge = runsLeftToMerge - mergePointers;
            if(runsLeftToMerge>=M)
                mergePointers = M-1;
            else
                mergePointers = runsLeftToMerge;

            memset(&record, '\0', sizeof(record));
            for(int k=0; k<22; k++)
                record[k].did = 999999999;

            //runNum = runNum - 1; //The next continue statement skips one run file
            j--; //The next continue statement skips one run file

            //cout << "RUN   J : " << runNum << "   " << j;
            runNum = j;
        }

    }

    cout << "End of Pass Num " << passNum << " with # of Runs Created = " << runNum << endl;
    //deleteRuns(numOfRuns , passNum-1, "dept");
    passNum++;
    return runNum; // Returns number of Runs created for that pass

}

void sortMergeJoin(int numOfRunsE, int numOfRunsD, int passNumE, int passNumD) {
    cout << "\n--------------In Opt Sort Merge Join--------------" << endl;

    fstream empIn[numOfRunsE];
    fstream deptIn[numOfRunsD];

    for(int i=0;i<numOfRunsE;i++) {
        string filename = "emp" + to_string(passNumE) + "run" + to_string(i+1) + ".txt";
        empIn[i].open(filename);
    }

    for(int i=0;i<numOfRunsD;i++) {
        string filename = "dept" + to_string(passNumD) + "run" + to_string(i+1) + ".txt";
        deptIn[i].open(filename);
    }


    joinTuple outBuf;
    string line, word;
    std::vector<string> tupleE, tupleD;
    streamoff savedPos;

    empBlock recordE;
    deptBlock recordD;
    int currManagerId, currEId;

    // Did not work with M/2. Probably Memory issue
    // Error Reported: Windows cannot run the program
    const int sizeRecords = ceil(M/3);
    std::array<empBlock, sizeRecords> empRecords;
    std::array<deptBlock, sizeRecords> deptRecords;

    //initialize
    for(int i=0; i<ceil(M/3); i++) {
        if(i>=numOfRunsE) {
            empRecords[i].eid = 999999999;
        }
        else {
            getline(empIn[i], line, '\n');
            stringstream sE(line);
            tupleE.clear();
            while(getline(sE, word, ',')) {
                tupleE.push_back(word);
            }
            empRecords[i].eid = stoi(tupleE[0]);
            empRecords[i].ename = tupleE[1];
            empRecords[i].age = stoi(tupleE[2]);
            empRecords[i].salary = stod(tupleE[3]);
        }
    }

    for(int i=0; i<ceil(M/3); i++) {
        if(i>=numOfRunsD) {
            deptRecords[i].managerid = 999999999;
        }
        else {
            getline(deptIn[i], line, '\n');
            stringstream sD(line);
            tupleD.clear();
            while(getline(sD, word, ',')) {
                tupleD.push_back(word);
            }
            deptRecords[i].did = stoi(tupleD[0]);
            deptRecords[i].dname = tupleD[1];
            deptRecords[i].budget = stod(tupleD[2]);
            deptRecords[i].managerid = stoi(tupleD[3]);
        }
    }

    int counterE = 0;
    int counterD = 0;
    //cout << "HERE" << endl;
    ofstream outFile;
    outFile.open("Join.csv", ios::app);
    while(true) { // Breaks after counterE reaches numOfRunsE


        empBlock *ptr = std::min_element(empRecords.begin(), empRecords.end(), empMinRecord);
        // Block outBuf contains smallest tuple
        int minIndE;
        recordE = *ptr;

        minIndE = ptr - empRecords.begin();
        if(empIn[minIndE].eof()) {
            counterE++;
            //deleteRuns(numOfRuns , passNum-1 , "emp");
        }

        if(counterE == numOfRunsE)
                break;

        //cout << "------------E-----------" << recordE.eid << endl;
        getline(empIn[minIndE], line, '\n');
        stringstream sE(line);
        tupleE.clear();
        while(getline(sE, word, ',')) {
            tupleE.push_back(word);
        }
        empRecords[minIndE].eid = stoi(tupleE[0]);
        empRecords[minIndE].ename = tupleE[1];
        empRecords[minIndE].age = stoi(tupleE[2]);
        empRecords[minIndE].salary = stod(tupleE[3]);

        while(true) { // Breaks after counterD reaches numOfRunsD

            if(counterD == numOfRunsD){
                break;
            }

            deptBlock *ptrD = std::min_element(deptRecords.begin(), deptRecords.end(), deptMinRecord);
            // Block outBuf contains smallest tuple
            int minIndD;
            recordD = *ptrD;

            minIndD = ptrD - deptRecords.begin();
            //cout << "Here2" << minIndD;
            if(deptIn[minIndD].eof()){
                counterD++;
                continue;
            }
            if(recordE.eid > recordD.managerid) {
                continue;
            }
            else if(recordE.eid < recordD.managerid) {
                break;
            }
            else {
                outBuf.eid = recordE.eid;
                outBuf.ename = recordE.ename;
                outBuf.age = recordE.age;
                outBuf.salary = recordE.salary;
                outBuf.did = recordD.did;
                outBuf.dname = recordD.dname;
                outBuf.budget = recordD.budget;
                outBuf.managerid = recordD.managerid;

                outFile << outBuf.did << "," << outBuf.dname << "," << outBuf.budget << "," << outBuf.managerid << outBuf.eid << "," << outBuf.ename << "," << outBuf.age << "," << outBuf.salary << "\n";

                cout << outBuf.ename << endl;
            }

            //cout << "------------D-----------" << endl;
            //cout << recordD.managerid << endl;
            getline(deptIn[minIndD], line, '\n');
            stringstream sD(line);
            //cout << line << endl;
            tupleD.clear();
            while(getline(sD, word, ',')) {
                tupleD.push_back(word);
            }
            deptRecords[minIndD].did = stoi(tupleD[0]);
            deptRecords[minIndD].dname = tupleD[1];
            deptRecords[minIndD].budget = stod(tupleD[2]);
            deptRecords[minIndD].managerid = stoi(tupleD[3]);

        }
    }

    cout << "Done" << endl;
}

int main() {
    int numOfRunsE = readEmp();

    // SORTING OF Emp.csv
    double x, base;
    x = (float)numOfRunsE/M;
    base = M-1;

    int maxPassesE;
    if(numOfRunsE==1)
        maxPassesE = 1;
    else
        maxPassesE = ceil(log(x)/log(base)) + 1;

    for(int i=1; i<=maxPassesE; i++) {
        numOfRunsE = passIthEmp(numOfRunsE, maxPassesE);
        if(numOfRunsE < ceil(M/3)) {
            cout << "EMP No of Passes | Runs: " << maxPassesE << " | " << numOfRunsE << endl << endl;
            break;
        }
    }

    passNum = 0; // Resetting global passNum

    int maxPassesD, numOfRunsD;
    numOfRunsD = readDept();
    //double x, base;
    x = (float)numOfRunsD/M;
    base = M-1;
    if(numOfRunsD==1)
        maxPassesD = 1;
    else
        maxPassesD = ceil(log(x)/log(base)) + 1;

    for(int i=1; i<=maxPassesD; i++) {
        numOfRunsD = passIthDept(numOfRunsD, maxPassesD);
        if(numOfRunsD < ceil(M/3)) {
            cout << "DEPT No of Passes | Runs: " << maxPassesD << " | " << numOfRunsD << endl << endl;
            break;
        }
    }

    // Below is Optimized MergeSort
    // empSorted and deptSorted are not deleted as they could be used in normal sortMergeJoin Algorithm
    sortMergeJoin(numOfRunsE, numOfRunsD, maxPassesE-1, maxPassesD-1);
    deleteRuns(numOfRunsE, maxPassesE-1, "emp");
    deleteRuns(numOfRunsD, maxPassesD-1, "dept");

}
