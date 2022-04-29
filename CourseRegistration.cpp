#include "CourseRegistration.h"
#include <strstream>
#include <iomanip>

CourseRegistration::CourseRegistration() :numberOfCreditHours{ 0 }, grade{0.0f}
{
	this->courseId = new char[10];
	this->courseId[0] = '\0';
	this->studentId = new char[10];
	this->studentId[0] = '\0';
	this->courseName = new char[20];
	this->courseName[0] = '\0';
}

void CourseRegistration::courseStrCpy(char*& self, const char* str) {
	if (strlen(self) < strlen(str)) {
		delete[] self;
		self = new char[strlen(str) + 1];
		strcpy(self, str);
	}
	else {
		strcpy(self, str);
	}
}

CourseRegistration::CourseRegistration(const CourseRegistration& course) {
	this->grade = course.grade;
	this->numberOfCreditHours = course.numberOfCreditHours;

	this->studentId = new char[strlen(course.studentId) + 1];
	strcpy(this->studentId, course.studentId);
	this->courseId = new char[strlen(course.courseId) + 1];
	strcpy(this->courseId, course.courseId);
	this->courseName = new char[strlen(course.courseName) + 1];
	strcpy(this->courseName, course.courseName);
}

CourseRegistration::CourseRegistration(char* courseId, char* studentId, char* courseName, int credit, float grade) {
	this->numberOfCreditHours = credit;
	this->grade = grade;

	this->studentId = new char[strlen(studentId) + 1];
	strcpy(this->studentId, studentId);
	this->courseId = new char[strlen(courseId) + 1];
	strcpy(this->courseId, courseId);
	this->courseName = new char[strlen(courseName) + 1];
	strcpy(this->courseName, courseName);

}
CourseRegistration::~CourseRegistration() {
	delete[] studentId;
	delete[] courseId;
	delete[] courseName;
}

CourseRegistration& CourseRegistration::operator =(const CourseRegistration& course) {
	this->numberOfCreditHours = course.numberOfCreditHours;
	this->grade = course.grade;

	courseStrCpy(studentId, course.studentId);
	courseStrCpy(courseId, course.studentId);
	courseStrCpy(courseName, course.courseName);
	return *this;
}

void CourseRegistration::setStudentId(const char* id) {
	courseStrCpy(studentId, id);
}
char* CourseRegistration::getStudentId() {
	return this->studentId;
}
void CourseRegistration::setCredit(int credit) {
	this->numberOfCreditHours = credit;
}
int CourseRegistration::getCredit() {
	return this->numberOfCreditHours;
}
void CourseRegistration::setCourseId(const char* id) {
	courseStrCpy(courseId, id);
}
char* CourseRegistration::getCourseId() {
	return this->courseId;
}
void CourseRegistration::setGrade(float grade) {
	this->grade = grade;
}
float CourseRegistration::getGrade() {
	return this->grade;
}
void CourseRegistration::setCourseName(const char* courseName) {
	courseStrCpy(this->courseName, courseName);
}
char* CourseRegistration::getCourseName() {
	return this->courseName;
}


std::ostream& operator << (std::ostream& stream, const CourseRegistration& course) {
	stream << "Course Id : " << course.courseId << "\nStudent Id : " << course.studentId <<
		"\nCourse Name : " << course.courseName << "\nNumber of Credit Hours : " << course.numberOfCreditHours <<
		"\nGrade : " << course.grade << "\n\n";
	return stream;
}

void setCourseStream(std::istream& stream, CourseRegistration& course)
{
	char delim = '|';
	char buffer[31];
	stream.getline(buffer, 30, delim);
	course.setCourseId(buffer);
	stream.getline(buffer, 30, delim);
	course.setStudentId(buffer);
	stream.getline(buffer, 30, delim);
	course.setCourseName(buffer);
	stream.getline(buffer, 30, delim);
	course.setCredit(atoi(buffer));
	stream.getline(buffer, 30, delim);
	course.setGrade(atof(buffer));
}

void checkValid(char *str) {
	for (char* c = str; *c != '\0'; ++c) {
		if (!(isdigit(*c))) {
			if ((*c) == '.') {
				continue;
			}
			str[0] = '0'; str[1] = '\0'; break;
		}
	}
}

std::istream& operator >> (std::istream& stream, CourseRegistration& course) {
	char buffer[20];
	std::cout << "Enter course id: " << std::flush;
	stream.getline(buffer, 10);//, or <cr> to end: " << std::flush;
	
	course.setCourseId(buffer);
	//if (strlen(course.courseId) == 0) return stream;
	std::cout << "Enter student id: " << std::flush; stream.getline(buffer, 10);
	course.setStudentId(buffer);
	std::cout << "Enter course name: " << std::flush; stream.getline(buffer, 19);
	course.setCourseName(buffer);
	std::cout << "Enter number of credit hours: " << std::flush; stream.getline(buffer, 5);
	checkValid(buffer);
	course.setCredit(atoi(buffer));
	std::cout << "Enter course grade: " << std::flush; stream.getline(buffer, 5);
	checkValid(buffer);
	course.setGrade(atof(buffer));
	return stream;
}
/*
int CourseRegistration::InitBuffer(FixedFieldBuffer& Buffer)
// initialize a FixedTextBuffer to be used for Persons
{
	int result;
	result = Buffer.AddField(9); // CourseId [10];
	result = result && Buffer.AddField(9); // StudentId [10];
	result = result && Buffer.AddField(19); // courseName [20];
	result = result && Buffer.AddField(4); // NumberOfCreditHours [5];
	result = result && Buffer.AddField(4); // Grade [5];
	return result;
}*/

void toString(char* str, int number) {
	sprintf(str, "%-4d", number);
}

void toString(char* str, float fnum) {
	sprintf(str, "%-4.2f", fnum);
}

void CourseRegistration::Clear()
{
	// set each field to an empty string
	courseId[0] = 0;
	studentId[0] = 0;
	courseName[0] = 0;
	numberOfCreditHours = 0;
	grade = 0;
}

int CourseRegistration::InitBuffer(LengthFieldBuffer& Buffer)
// initialize a LengthTextBuffer to be used for Persons
{
	return TRUE;
}
/*
int CourseRegistration::InitBuffer(DelimFieldBuffer& Buffer)
// initialize a DelimTextBuffer to be used for Persons
{
	return TRUE;
}*/

int CourseRegistration::Pack(IOBuffer& Buffer) const
{// pack the fields into a FixedFieldBuffer, 
 // return TRUE if all succeed, FALSE o/w
	int numBytes;
	Buffer.Clear();
	numBytes = Buffer.Pack(courseId);//동적 바인딩
	if (numBytes == -1) return FALSE;
	numBytes = Buffer.Pack(studentId);
	if (numBytes == -1) return FALSE;
	numBytes = Buffer.Pack(courseName);
	if (numBytes == -1) return FALSE;
	char credit[5];
	toString(credit, numberOfCreditHours);
	numBytes = Buffer.Pack(credit);
	if (numBytes == -1) return FALSE;
	toString(credit, grade);
	numBytes = Buffer.Pack(credit);
	if (numBytes == -1) return FALSE;
	return TRUE;
}

int CourseRegistration::Unpack(IOBuffer& Buffer)
{
	Clear();
	int numBytes;
	//power of virtual functions
	numBytes = Buffer.Unpack(courseId);//Unpack()에 대항 F12를 누르면 일치하는 3개 함수 존재 - 동적 바인딩
	if (numBytes == -1) return FALSE;
	courseId[numBytes] = 0;
	numBytes = Buffer.Unpack(studentId);
	if (numBytes == -1) return FALSE;
	studentId[numBytes] = 0;
	numBytes = Buffer.Unpack(courseName);
	if (numBytes == -1) return FALSE;
	courseName[numBytes] = 0;
	char num[5];
	numBytes = Buffer.Unpack(num);
	if (numBytes == -1) return FALSE;
	num[numBytes] = 0;
	numberOfCreditHours = atoi(num);
	numBytes = Buffer.Unpack(num);
	if (numBytes == -1) return FALSE;
	num[numBytes] = 0;
	grade = atof(num);

	return TRUE;
}

char* CourseRegistration::Key() const
{// produce key as concatenation of Label and IdNum
	std::ostrstream key;
	key << courseId << studentId << ends;
	return key.str();
}

ostream& CourseRegistration::PrintLine(ostream& stream)
{
	stream.setf(ios::right, ios::adjustfield);
	stream << studentId << '\t';
	stream.setf(ios::right, ios::adjustfield);
	stream << '\t' << setw(6) << courseId << '\t';
	stream.setf(ios::left, ios::adjustfield);
	stream << setw(30) << courseName;
	stream.setf(ios::right, ios::adjustfield);
	stream << '\t' << numberOfCreditHours;
	stream.setf(ios::right | ios::fixed, ios::floatfield);
	stream.precision(2);
	stream << '\t' << setw(8) << setprecision(2) << grade << endl;
	return stream;
}