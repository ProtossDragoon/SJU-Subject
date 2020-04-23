#include "student.h"

int CStudent::s_nCountObject = 0;

CStudent::CStudent(string Name, string PhoneNumber, string Email, int id): m_kId(id+1)
// parameter : Name, Phone Number, Email
// default parameter : id 를 현재 저장되어 있는 데이터 + 1 로 초기화하도록 유도
// const member initialization : 콜론 초기화
{
	m_strName = Name;
	m_strPhoneNumber = PhoneNumber;
	m_strEmail = Email;
	s_nCountObject++;
}


void CStudent::PrintStudentInfo() const
// 현재 상태를 바꿀 권한을 주어서는 안 되는 함수이므로 const 선언
{
	cout << "student info ------: " << endl;
	cout << "m_strName----------: " << m_strName << endl;
	cout << "m_strPhoneNumber---: " << m_strPhoneNumber << endl;
	cout << "m_strEmail---------: " << m_strEmail << endl;
	cout << "m_kid--------------: " << m_kId << endl;
}