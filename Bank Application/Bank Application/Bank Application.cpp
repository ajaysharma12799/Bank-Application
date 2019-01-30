// Bank Application.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <ostream>
#include <vector>
#include <map>
#include <cstdlib>
#include <istream>
#include <string.h>

using namespace std;

#define Min_Balance 500

class InsufficientFunds
{

};

//Accounts class for containing all info of clients about their account

class Account
{
private:
	long accountnumber;
	string first_name;
	string last_name;
	string phone_number;
	float balance;
	static long NextAccount_Number;
public:
	Account()
	{
	
	}
	Account(string f_name,string l_name,string phone_number,float balance)
	{
		first_name = f_name;
		last_name = l_name;
		this->phone_number = phone_number;
		this->balance = balance;
	}

	//Accessors for accessing private member using functions

	//for getting account number 
	long getAccNumber()
	{
		return accountnumber;
	}
	//for getting firstname
	string getFirstName()
	{
		return first_name;
	}
	//for getting lastname
	string getLastName()
	{
		return last_name;
	}
	//for getting balance
	float getBalance()
	{
		return balance;
	}
	
	//function for depositing money into account
	void Deposit(float amount);
	//function for withdrawing money into accounts
	void Withdraw(float amount);
	//function for setting last account_number.
	static void setLastAccountNumber(long accountnumber);
	//function for remember last account_number after application quits 
	static long getLastAccountNumber();

	//overloading ofstream operator which will write into file
	friend ofstream & operator<<(ofstream &outfile, Account &acc);
	//overloading ifstream operator which will get data from file
	friend ifstream & operator>>(ifstream &infile,Account &acc);
	//overloading ostream oeprator operator which will display data 
	friend ostream & operator<<(ostream &output, Account &acc);
};
//use of this variable for automatically assiging account number 
long Account::NextAccount_Number = 0;


//Bank class for managing all operation which are performed by Bank


class Bank
{
private:
	//making map here bcoz it is fast for accessing on accounts base here
	map<long, Account> accounts;
public:
	Bank();
	//function for opening bank account
	void OpenAccount(string f_name, string l_name, string phone_number, float balance);
	//function for checking balance enquiry
	Account BalanceEnquiry(long account_number);
	//function for depositing balance into accounts
	Account Deposit(long account_number,float amount);
	//function for withdrawing balance into accounts
	Account Withdraw(long account_number,float amount);
	//function for closing accounts
	void CloseAccount(long account_number);
	//function for showing all accounts
	void ShowAllAccounts();
	//destructor for destroying object 
	~Bank();
};

int main()
{
	//making Bank object for performing task of Bank
	Bank b;
	//making Account object for performing task of Accounts
	Account acc;
	//choice variable for user-defined choice
	int choice;

	string fname, lname,phonenumber;
	long accountnumber;
	float balance,account;

	/*-----------------------------------------------------------------------------------------------------------------------------------------*/

	cout << "**************Banking System**************" << endl;
	do
	{
		cout << "Select one Option Below :";
		cout << "\n\t1 Open an Account";
		cout << "\n\t2 Balance Enquiry";
		cout << "\n\t3 Deposit";
		cout << "\n\t4 Withdraw";
		cout << "\n\t5 Close an Account";
		cout << "\n\t6 Show All Account";
		cout << "\n\t7 Quit";
		cin >> choice;
		switch (choice)
		{
			case 1:
			{
				cout << "Enter First Name :";
				cin >> fname;
				cout << "Enter Last Name :";
				cin >> lname;
				cout << "Enter Phone Number :";
				cin >> phonenumber;
				cout << "Enter Initial balance :";
				cin >> balance;
				acc = b.OpenAccount(fname, lname, phonenumber, balance);
				cout << endl << "Congrats Account is Created " << endl;
				cout << acc;
				break;
			}
			case 2:
			{
				cout << "Enter Account Number :";
				cin >> accountnumber;
				acc = b.BalanceEnquiry(accountnumber);
				cout << endl << "Your Account Details " << endl;
				cout << acc;
				break;
			}
			case 3:
			{
				cout << "Enter Account Number :";
				cin >> accountnumber;
				cout << "Enter Balance :";
				cin >> balance;
				acc = b.Deposit(accountnumber,balance);
				cout <<endl<< "Amount is Deposited " << endl;
				cout << acc;
				break;
			}
			case 4:
			{
				cout << "Enter Account Number :";
				cin >> accountnumber;
				cout << "Enter Balance :";
				cin >> balance;
				acc = b.Withdraw(accountnumber,balance);
				cout << endl << "Amount is Withdraw " << endl;
				cout << acc;
				break;
			}
			case 5:
			{
				cout << "Enter Account Number :";
				cin >> accountnumber;
				b.CloseAccount(accountnumber);
				cout << endl << "Account is CLosed " << endl;
				cout << acc;
				break;
			}
			case 6:
			{
				b.ShowAllAccounts();
				break;
			}
			case 7:
			{
				break;
			}
			default:
				cout << "Enter Correct Choice :";
				exit(0);//function work like return 0 statement
		}
	} while (choice != 7);
	return 0;
}
//function working for opening account
void Account::OpenAccount(string f_name, string l_name, string phon_number, float balance)
{
	NextAccount_Number++;
	accountnumber = NextAccount_Number;
	strcpy(first_name,f_name);
	strcpy(last_name, l_name);
	strcpy(phone_number,phon_number);
	this->balance = balance;
}
//function working for depositing balance in bank account
void Account::Deposit(float amount)
{
	balance += amount;
}
//function working for withdrawing balance from bank account
void Account::Withdraw(float amount)
{
	//checking condition for minimum balance 
	if (balance - amount < Min_Balance)
	{ 
		//throwing InsufficientFund class object
		throw InsufficientFunds();
	}
	//if not false the deducting balance from account
	else
	{
		balance -= amount;
	}
}
//function working for setting last account number 
void Account::setLastAccountNumber(long accountnumber)
{
	NextAccount_Number = accountnumber;
}
//function working for getting last account number so that it can continue from the left account number
long Account::getLastAccountNumber()
{
	return NextAccount_Number;
}
//overloading ofstream operator which will write into the file
ofstream & operator<<(ofstream &outfile,Account &acc)
{
	outfile << acc.accountnumber << endl;
	outfile << acc.first_name << endl;
	outfile << acc.last_name << endl;
	outfile << acc.phone_number << endl;
	outfile << acc.balance << endl;
	return outfile;
}
//overloading ifstream operator which will read data from file
ifstream & operator>>(ifstream &infile,Account &acc)
{
	infile >> acc.accountnumber;
	infile >> acc.first_name;
	infile >> acc.last_name;
	infile >> acc.phone_number;
	infile >> acc.balance;
	return infile;
}
//overloading ostream operator which is used to display to output
ostream & operator<<(ostream & output,Account &acc)
{
	output << "First Name :" << acc.getFirstName() << endl;
	output << "Last Name :" << acc.getLastName() << endl;
	output << "Account Number :" << acc.getAccNumber() << endl;
	output << "Balance :" << acc.getBalance() << endl;
}
//working with Bank default-constructor
Bank::Bank()
{
	//making account object for performing task
	Account account;
	//making ifstream object for working with output of file
	ifstream infile;
	//opening Bank file
	infile.open("bank.data");
	//checking the condition whether the file is open or not
	if (!infile)
	{
		//cout << "Error in Opening ! File Not Found !!" << endl;
		return;
	}
	//if file is not opened then open it and check upto end-of-file
	while (!infile.eof())
	{
		infile >> account;
		account.insert(pair<long, Account)(account.getAccNumber, account);
	}
	//setting last account number 
	Account::setLastAccountNumber(account.getAccNumber);
	//closing file
		infile.close();
}
Account Bank::OpenAccount(string f_name, string l_name, string phone_number, float balance)
{
	ofstream outfile;
	Account account(f_name,l_name,phone_number,balance);
	account.insert(pair<long, Account>(account.getAccNumber, account));
	outfile.open("Bank.data", ios::trunc);
	map<long, Account>::iterator itr;
	for (itr = accounts.begin() ; itr!= accounts.end() ; itr++)
	{
		outfile << itr->second;
	} 
	outfile.close();
	return account;
}
Account Bank::BalanceEnquiry(long account_number)
{
	map<long, Account>::iterator itr = accounts.find(account_number);
	return itr->second;
}
Account Bank::Deposit(long account_number,float amount)
{
	map<long, Account>::iterator itr = accounts.find(account_number);
	itr->second.Deposit(amount);
	return itr->second;
}
Account Bank::Withdraw(long account_number, float amount)
{
	map<long, Account>::iterator itr = accounts.find(account_number);
	itr->second.Withdraw(amount);
	return itr->second;
}
void Bank::CloseAccount(long account_number)
{
	map<long, Account>::iterator itr = accounts.find(account_number);
	cout << "Account Deleted " << itr->second;
	accounts.erase(account_number);
}
void Bank::ShowAllAccounts()
{
	map<long, Account>::iterator itr;
	for (itr = accounts.begin() ; itr != accounts.end() ; itr++)
	{
		cout << "Accounts " << itr->first << endl << itr->second << endl;
	}
}
Bank::~Bank()
{
	ofstream outfile;
	outfile.open("Bank.data", ios::trunc);
	map<long, Account>::iterator itr;
	for (itr = accounts.begin(); itr != accounts.end(); itr++)
	{
		outfile << itr->second;
	}
	outfile.close();
}