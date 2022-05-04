#include "TranscriptProcess.h"
#include <iomanip>
//#include <string>
TranscriptProcess::TranscriptProcess()
	: MasterTransactionProcess<String>(), StudentFile(Sbuffer), CourseFile(Cbuffer), filename(nullptr)
{
	PrevCredit = 0;
	StudentNumber[1] = new char[10];
	StudentNumber[2] = new char[10];
	StudentNumber[0] = nullptr;
}

int TranscriptProcess::InitializeList(int ListNumber, char* ListName)
{
	StudentNumber[ListNumber][0] = LowNum;
	switch (ListNumber)
	{
	case 1: // initialize ledger file
		filename = new char[strlen(ListName) + 1];
		strcpy(filename, ListName);
		return StudentFile.Open(ListName, ios::in);
	case 2: // initialize ledger file
		return CourseFile.Open(ListName, ios::in);
	}
	return FALSE;
}

int TranscriptProcess::InitializeOutput(char* OutputListName)
{
	OutputList.open(OutputListName);
	return 1;
}

int TranscriptProcess::NextItemInList(int ListNumber)
//get next item from this list
{
	switch (ListNumber)
	{
	case 1: return NextItemInStudent();
	case 2: return NextItemInCourse();
	}
	return FALSE;
}

String TranscriptProcess::Item(int ListNumber)
// return current item from this list
{
	return String(StudentNumber[ListNumber]);
}

int TranscriptProcess::ProcessItem(int ListNumber)
// process the item in this list when it first appears
{
	switch (ListNumber)
	{
	case 1: // process new ledger object
		student.PrintHeader(OutputList);
	case 2: // process journal file
		course.PrintLine(OutputList);
	}
	return TRUE;
}

int TranscriptProcess::ProcessNewMaster()//  when new master read
{// first step in proceesing master record
 // print the header and setup last month's balance
	student.PrintHeader(OutputList);
	PrevCredit = student.getCredit();
	//ledger.Balances[MonthNumber] = ledger.Balances[MonthNumber - 1];
	return TRUE;
}

int TranscriptProcess::ProcessCurrentMaster()// each transaction for a master
{// add the transaction amount to the balance for this month	
	//ledger.Balances[MonthNumber] += journal.Amount;
	student.setCredit(student.getCredit() + course.getCredit());
	return TRUE;
}

ostream& PrintCreditHours(ostream& stream,
	int PreviousCredit, int CurrentCredit)
{// print balances line of report
	stream << "\t\t\t\tPrev. credit: "
		<< setw(8) << PreviousCredit
		<< "\tNew credit:\t"
		<< setw(8) << CurrentCredit << endl;
	return stream;
}

int TranscriptProcess::ProcessEndMaster()// after all transactions for a master
{// print the balances line to output	
	PrintCreditHours(OutputList, PrevCredit, student.getCredit());
	students.push_back(new Student(student));
	return TRUE;
}

int TranscriptProcess::ProcessTransactionError()// no master for transaction
{// print error message to standard error
	cerr << "Error no student id" << endl;
	cerr << course.getStudentId();
	course.PrintLine(cerr);
	return TRUE;
}

int TranscriptProcess::FinishUp()
// complete the processing
{
	StudentFile.Close();
	CourseFile.Close();
	OutputList.close();

	if (!students.empty()) {
		if (!StudentFile.Create(filename, ios::out)) {
			return FALSE;
		}
		for (int i = 0; i < students.size(); ++i) {
			StudentFile.Write(*students[i]);
		}
		StudentFile.Close();
	}
	return TRUE;
}

int TranscriptProcess::NextItemInStudent()
{
	int res = StudentFile.Read(student);
	if (res <= 0)
	{
		strcpy(StudentNumber[1], HighNum);
		return FALSE;
	}
	if (strcmp(student.getId(), StudentNumber[1]) < 0)
	{
		cerr << "Student id out of order" << endl; exit(0);
	}
	strcpy(StudentNumber[1], student.getId());
	return TRUE;
}

int TranscriptProcess::NextItemInCourse()
{
	int res = CourseFile.Read(course);
	if (res <= 0)
	{
		strcpy(StudentNumber[2], HighNum);
		return FALSE;
	}
	if (strcmp(course.getStudentId(), StudentNumber[2]) < 0)
	{
		cerr << "Course student id out of order" << endl; exit(0);
	}
	strcpy(StudentNumber[2], course.getStudentId());
	return TRUE;
}

char TranscriptProcess::LowNum = '0';
char TranscriptProcess::HighNum[10]{ "300000000" };

TranscriptProcess::~TranscriptProcess() {
	while (!students.empty()) {
		Student* elem = students.back();
		delete elem;
		students.pop_back();
	}
}