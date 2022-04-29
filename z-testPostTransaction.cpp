/*
교재: 367, 20번 programming project
Ledger 대신에 Student, Journal 대신에 course registration class를 정의한다.
*/

//#include "recfile.h"
//#include "stdlib.h"
//#include <fstream>
//#include <string.h>
//#include "length.h"
#include "TranscriptProcess.h"

int makeFile() {
	Student stRecord[12]{
		{"201525231", "이솔선", "서울", "2015.03.01", 999},
		{"201624532", "서명호", "인천", "2018.03.01", 821},
		{"201624641", "장성수", "화천", "2016.03.01", 845},
		{"201714552", "김수범", "순천", "2017.03.01", 542},
		{"201725132", "김철수", "영주", "2017.03.01", 251},
		{"201822514", "이수린", "울산", "2018.03.01", 254},
		{"201824641", "최성찬", "수원", "2020.03.01", 777},
		{"201824645", "임동화", "용인", "2018.03.01", 542},
		{"201914020", "오명수", "부산", "2019.03.01", 562},
		{"201925841", "박선수", "대전", "2019.03.01", 354},
		{"202025142", "강형석", "광주", "2020.03.01", 352},
		{"202221241", "조강동", "충주", "2022.03.01", 152}
	};
	CourseRegistration crRecord[10]{
		{"059", "201824641", "파일구조", 356, 4.5},
		{"060", "201824641", "자료구조", 250, 4.35},
		{"061", "201824641", "알고리즘", 333, 4.2},
		{"059", "201824645","파일구조", 210, 3.5},
		{"062", "201824645","운영체제", 220, 4.1},
		{"061", "201914020", "컴퓨터구조", 182, 3.3},
		{"059", "201925841", "c++프로그래밍", 100, 3.7},
		{"056", "201925841", "소프트웨어시스템", 135, 4.2},
		{"061", "202025142", "이산수학", 212, 3.5},
		{"063", "202221241", "논리회로", 320, 3.8}
	};
	LengthFieldBuffer Sbuffer;
	RecordFile<Student> StudentFile(Sbuffer);
	int result = StudentFile.Create("Student.dat", ios::out);
	cout << "Create file Student.dat" << endl;
	if (!result)
	{
		cout << "Unable to Create file " << "Student.dat" << endl;
		return 0;
	}
	for (int i = 0; i < 12; ++i) {
		StudentFile.Write(stRecord[i]);
	}
	StudentFile.Close();

	LengthFieldBuffer Cbuffer;
	RecordFile<CourseRegistration> courseFile(Cbuffer);
	int flag = courseFile.Create("Course.dat", ios::out);
	cout << "Create file Course.dat"<< endl;
	if (!flag)
	{
		cout << "Unable to Create file " << "Course.dat" << endl;
		return 0;
	}
	for (int i = 0; i < 10; ++i) {
		courseFile.Write(crRecord[i]);
	}
	courseFile.Close();
	return 1;
}

int readFile() {
	Student stRecord[12];
	CourseRegistration crRecord[10];

	LengthFieldBuffer Sbuffer;
	RecordFile<Student> StudentFile(Sbuffer);
	int result = StudentFile.Open("Student.dat", ios::in);
	cout << "Open file Student.dat" << endl;
	if (!result)
	{
		cout << "Unable to Open file " << "Student.dat" << endl;
		return 0;
	}
	for (int i = 0; i < 12; ++i) {
		StudentFile.Read(stRecord[i]);
		cout << stRecord[i] << endl;
	}
	StudentFile.Close();

	LengthFieldBuffer Cbuffer;
	RecordFile<CourseRegistration> courseFile(Cbuffer);
	int flag = courseFile.Open("Course.dat", ios::in);
	cout << "Open file Course.dat" << endl;
	if (!flag)
	{
		cout << "Unable to Open file " << "Course.dat" << endl;
		return 0;
	}
	for (int i = 0; i < 10; ++i) {
		courseFile.Read(crRecord[i]);
		cout << crRecord[i] << endl;
	}
	courseFile.Close();
	return 1;
}

int showTranscript() {
	char ch[100];
	fstream TranscriptJournal;
	TranscriptJournal.open("Transcript.txt", ios::in);
	if (!TranscriptJournal.is_open()) {
		cout << "Unable to Open file " << "Transcript.txt" << endl;
		return 0;
	}
	while (1) {
		TranscriptJournal.getline(ch, 99);
		if (TranscriptJournal.fail()) break;
		cout << ch << endl;
	}
	return 1;
}

int readTranscriptFile() {
	
	cout << "Showing the new credits" << endl;
	LengthFieldBuffer Lbuffer;
	RecordFile<Student> lFile(Lbuffer);
	Student student;
	int result = lFile.Open("Student.dat", ios::in);
	if (!result)
	{
		cout << "Unable to Open file " << "Student.dat" << endl;
		return 0;
	}
	while (1)
	{
		int res = lFile.Read(student);
		if (res <= 0) break;
		cout << "Transcript" << endl;
		cout << '\n' << student << endl;
	}

	lFile.Close();
	return true;
}

int main(void)
{
	makeFile();
	readFile();

	cout << "Posting " << endl;
	TranscriptProcess Posting;	
	Posting.PostTransactions("Student.dat", "Course.dat", "Transcript.txt");

	//Modify to show the file Transcript.txt
	cout << '\n' << endl;
	showTranscript();

	//Modify to show Transcript.Print();
	cout << '\n' << endl;
	readTranscriptFile();
	
	system("pause");
	return 1;
}