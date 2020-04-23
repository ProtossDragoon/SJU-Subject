#include "student.h"
using namespace std;

int main() 
{
	/* 생성자가 잘 호출되고 인스턴스가 정상적으로 생성되는가 */

	CStudent *student1 = new CStudent("name1", "010-1111-1111", "student1@naver.com"); // 학생1 : 포인터로
	CStudent::PrintCurrentDataCount();
	cout << endl;
	CStudent student2("name1", "010-1111-1112", "student1@naver.com"); // 학생2
	CStudent::PrintCurrentDataCount();
	cout << endl;
	CStudent student3("name1", "010-1111-1113", "student1@naver.com"); // 학생3
	cout << endl;
	CStudent::PrintCurrentDataCount();
	cout << endl;


	/* 멤버 함수 및 멤버 변수가 잘 동작하는가 */

	student1->set_strPhoneNumber("NAN"); // set_strPhoneNumber Test
	student1->PrintStudentInfo();
	cout << endl;
	student2.set_strEmail("student2@gmail.com"); // set_strEmail Test
	student2.PrintStudentInfo();
	cout << endl;
	student3.set_strName("name3"); // set_strName Test
	student3.PrintStudentInfo();
	cout << endl;
	CStudent::PrintCurrentDataCount();


	/* 객체 제거가 잘 동작하는가 */

	delete student1; // 동적할당을 통해 생성한 객체 제거
	cout << endl;
	CStudent::PrintCurrentDataCount();
	cout << endl;
	student2.~CStudent(); // 일반 인스턴스 소멸자 호출을 통한 객체 제거
	student2.PrintStudentInfo();
	cout << endl;
	CStudent::PrintCurrentDataCount();
}