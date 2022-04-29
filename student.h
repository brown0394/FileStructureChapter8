#pragma once

#ifndef STUDENT
#define STUDENT

#include <iostream>

#include "iobuffer.h"
//#include "fixfld.h"
#include "length.h"
//#include "delim.h"
class Student
{
	// data members
	char* StudentId; char *Name; char *Address;
	char *DateOfFirstEnrollment; int NumberOfCreditHours;
	void studentStrCpy(char* &self, const char* str);

	friend std::ostream& operator << (std::ostream& stream, const Student& student);
	friend std::istream& operator >> (std::istream& stream, Student& student);

public:
	// method
	Student(); // default constructor
	Student(const Student&);
	Student(char* , char* , char* , char* , int);
	~Student();

	Student& operator =(const Student&);
	void setId(const char*);
	char *getId();
	void setCredit(int);
	int getCredit();
	void setName(const char*);
	char *getName();
	void setAddress(const char*);
	char *getAddress();
	void setDate(const char*);
	char* getDate();
	void creditIncr();

	void Clear();
	char* Key() const;
	int Unpack(IOBuffer&);
	int Pack(IOBuffer&) const;
	//static int InitBuffer(FixedFieldBuffer& Buffer);
	static int InitBuffer(LengthFieldBuffer&);
	//static int InitBuffer(DelimFieldBuffer&);

	ostream& PrintHeader(ostream& stream);
};

#endif