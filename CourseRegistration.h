#pragma once

#ifndef COURSE
#define COURSE

#include <iostream>
#include "iobuffer.h"
//#include "fixfld.h"
#include "length.h"
//#include "delim.h"

class CourseRegistration
{
	char* courseId; char* studentId; char* courseName;
	int numberOfCreditHours; float grade;
	void courseStrCpy(char*& self, const char* str);

	friend std::ostream& operator << (std::ostream& stream, const CourseRegistration& course);
	friend std::istream& operator >> (std::istream& stream, CourseRegistration& course);
public:
	// method
	CourseRegistration(); // default constructor
	CourseRegistration(const CourseRegistration&);
	CourseRegistration(char *courseId, char *studentId, char *courseName, int credit, float grade);
	~CourseRegistration();

	CourseRegistration& operator =(const CourseRegistration&);
	void setStudentId(const char*);
	char* getStudentId();
	void setCredit(int);
	int getCredit();
	void setCourseId(const char*);
	char* getCourseId();
	void setGrade(float);
	float getGrade();
	void setCourseName(const char* courseName);
	char* getCourseName();


	void Clear();
	char* Key() const;
	int Unpack(IOBuffer&);
	int Pack(IOBuffer&) const;
	//static int InitBuffer(FixedFieldBuffer& Buffer);
	static int InitBuffer(LengthFieldBuffer&);
	//static int InitBuffer(DelimFieldBuffer&);

	ostream& PrintLine(ostream& stream);
};

#endif