#pragma once
#include <iostream>
#include <stdlib.h>
#include <string>
#include <string.h>
using namespace std;
class CStudent
{

private:
	string m_strName;
	string m_strPhoneNumber;
	string m_strEmail;
	
	// 고유한 값이므로 const 상수
	const int m_kId;


public:

	// 외부에서 초기화를 해주기 위해 public 으로 선언
	static int s_nCountObject;
	CStudent(string Name, string PhoneNumber, string Email, int id = s_nCountObject);
	~CStudent() { s_nCountObject--; };

	// 간단한 함수에 한해 inline 으로 구현

	// getter, inline function
	string get_strName() const { return m_strName; };
	string get_strPhoneNumber() const { return m_strPhoneNumber; };
	string get_strEmail() const { return m_strEmail; };
	static int get_nCountObject() { return s_nCountObject; }

	// setter, inlnine function
	void set_strName(string strName) { m_strName = strName; };
	void set_strPhoneNumber(string strPhoneNumber) { m_strPhoneNumber = strPhoneNumber; };
	void set_strEmail(string strEmail) { m_strEmail = strEmail; };

	// methods
	void PrintStudentInfo() const;
	static void PrintCurrentDataCount() { cout << "Current " << s_nCountObject << " data exist in the storage." << endl; };
};