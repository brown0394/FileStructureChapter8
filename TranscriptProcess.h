#pragma once

#ifndef TRANSPOST_H
#define TRANSPOST_H

#include "mastrans.h"
#include "recfile.h"
#include "length.h"
#include "student.h"
#include "CourseRegistration.h"
#include "strclass.h"
#include <vector>

class TranscriptProcess : public MasterTransactionProcess<String>
	// Transcript processing of a Transcript file and a journal file
	// the item type is int to represent an account number
{
public:
	TranscriptProcess(); // constructor
	~TranscriptProcess();
	// Basic list processing methods
	int InitializeList(int ListNumber, char* List1Name);
	int InitializeOutput(char* OutputListName);
	int NextItemInList(int ListNumber); //get next item from this list
	String Item(int ListNumber); // return current item from this list
	int ProcessItem(int ListNumber); // process the item in this list
	int FinishUp(); // complete the processing

	// master/transaction methods
	virtual int ProcessNewMaster();//  when new master read
	virtual int ProcessCurrentMaster();// each transaction for a master
	virtual int ProcessEndMaster();// after all transactions for a master
	virtual int ProcessTransactionError();// no master for transaction

protected:
	// members
	int PrevCredit; // number of month to be processed
	LengthFieldBuffer Sbuffer, Cbuffer; // buffers for files
	RecordFile<Student> StudentFile; // list 1
	RecordFile<CourseRegistration> CourseFile;// list 2
	char* StudentNumber[3]; // current item in each list
	Student student; // current Transcript object
	CourseRegistration course; // current journal object
	ofstream OutputList; // text output file for post method
	static char LowNum;// lower than the lowest account number
	static char HighNum[10];// higher than the highest account number

	int NextItemInStudent();
	int NextItemInCourse();

	vector<Student*> students;
	char* filename;
};

#endif