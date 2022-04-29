/*
����: 367, 20�� programming project
Ledger ��ſ� Student, Journal ��ſ� course registration class�� �����Ѵ�.
*/

//#include "recfile.h"
//#include "stdlib.h"
//#include <fstream>
//#include <string.h>
//#include "length.h"
#include "TranscriptProcess.h"

int makeFile() {
	Student stRecord[12]{
		{"201525231", "�ּ̼�", "����", "2015.03.01", 999},
		{"201624532", "����ȣ", "��õ", "2018.03.01", 821},
		{"201624641", "�强��", "ȭõ", "2016.03.01", 845},
		{"201714552", "�����", "��õ", "2017.03.01", 542},
		{"201725132", "��ö��", "����", "2017.03.01", 251},
		{"201822514", "�̼���", "���", "2018.03.01", 254},
		{"201824641", "�ּ���", "����", "2020.03.01", 777},
		{"201824645", "�ӵ�ȭ", "����", "2018.03.01", 542},
		{"201914020", "�����", "�λ�", "2019.03.01", 562},
		{"201925841", "�ڼ���", "����", "2019.03.01", 354},
		{"202025142", "������", "����", "2020.03.01", 352},
		{"202221241", "������", "����", "2022.03.01", 152}
	};
	CourseRegistration crRecord[10]{
		{"059", "201824641", "���ϱ���", 356, 4.5},
		{"060", "201824641", "�ڷᱸ��", 250, 4.35},
		{"061", "201824641", "�˰���", 333, 4.2},
		{"059", "201824645","���ϱ���", 210, 3.5},
		{"062", "201824645","�ü��", 220, 4.1},
		{"061", "201914020", "��ǻ�ͱ���", 182, 3.3},
		{"059", "201925841", "c++���α׷���", 100, 3.7},
		{"056", "201925841", "����Ʈ����ý���", 135, 4.2},
		{"061", "202025142", "�̻����", 212, 3.5},
		{"063", "202221241", "��ȸ��", 320, 3.8}
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