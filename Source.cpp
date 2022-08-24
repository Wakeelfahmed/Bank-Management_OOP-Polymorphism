#include<iostream>
#include<conio.h>
#include<ctime>
using namespace std;
class Account_Info
{
protected:
	string Account_Number;
	string Account_Holder_Name;
	int Balance;
public:
	static int Number_of_Accounts;
	Account_Info() :Account_Holder_Name(""), Account_Number(""), Balance(0) {}
	Account_Info(string Account_Number, string Account_Holder_Name, int Balance) : Account_Holder_Name(Account_Holder_Name), Account_Number(Account_Number), Balance(Balance) {}
	void set_Account_Number(string Account_Number) { this->Account_Number = Account_Number; }
	void set_Account_Holder_Name(string Account_Holder_Name) { this->Account_Holder_Name = Account_Holder_Name; }
	void set_Balance(int Balance) { this->Balance = Balance; }
	int get_Balance() const { return Balance; }
	string get_Account_Holder_Name() const { return Account_Holder_Name; }
	string get_Account_Number() const { return Account_Number; }
	virtual bool deposit(int Amount_To_Depsoit) = 0;
	virtual bool withdraw(int Amount_To_Withdraw) {
		if (Balance >= Amount_To_Withdraw)
		{
			Balance -= Amount_To_Withdraw;
			return 1;
		}
		return 0;
	}
	virtual void User_Input() {
		for (int i = 0; i < 10; i++)
		{
			int randomNum; char random;
			randomNum = rand() % 101;
			if (randomNum >= 50)
			{
				random = ((char)65 + rand() % 26);
				Account_Number = Account_Number + random;
			}
			else {
				random = 48 + rand() % 10;
				Account_Number = Account_Number + random;
			}
		}
		cout << "\nAccount Number:" << Account_Number;
		cout << "\nEnter Account Holder Name:";		cin >> Account_Holder_Name;
		cout << "Enter Account Balance:";		cin >> Balance;
	}
	void virtual display_Details() {
		cout << "Account Number:" << Account_Number;
		cout << "\nAccount Holder Name:";		cout << Account_Holder_Name;
		cout << "\nAccount Balance:";		cout << Balance << endl;
	}
};
int Account_Info::Number_of_Accounts = -1;
class  Savings_Account : public Account_Info {
protected:
	int Minimum_Balance;
public:
	Savings_Account() : Minimum_Balance(0) {}
	bool deposit(int Amount_To_Depsoit) {
		Balance = (Balance + Amount_To_Depsoit) - 50;
		cout << "Rs.50 has been deducted\n";
		return 1;	//Successfull Transaction.
		return 0;	//Transaction Failed.
	}
	bool withdraw(int Amount_To_Withdraw) {
		if (Balance - Amount_To_Withdraw + 50 < Minimum_Balance)
		{
			return 0;
		}

		Balance -= 50;
		Balance -= Amount_To_Withdraw; //Charges
		cout << "Rs.50 has been deducted\n";
		return 1;	//Successfull Transaction.

		return 0;	//Transaction Failed.
	}
};
class Checking_Account : public Account_Info {
protected:
	float Processing_charges;
public:
	Checking_Account() : Processing_charges(50) {}
	void set_Processing_Charges(int New_Processing_Charges) {
		Processing_charges = New_Processing_Charges;
	}
	bool deposit(int Amount_To_Depsoit) {
		if (Amount_To_Depsoit >= 500000)
		{
			cout << "1% of Processing charges has been deducted"
				<< "Note:Processing_charges are " << Processing_charges << endl;
			Balance = Balance + Amount_To_Depsoit - (float(Processing_charges / 100) * 1);
			return 1;
		}
		Balance += Amount_To_Depsoit;
		return 1;
	}
	bool withdraw(int Amount_To_Withdraw) {
		if (Balance >= Amount_To_Withdraw)
		{
			Balance -= Amount_To_Withdraw;
			return 1;
		}
		return 0;
	}
};
class Person_info {
private:
	string Name;
	long long int CNIC;
	int Contact_Number;
	string E_Mail;
public:
	Person_info() : Name(""), Contact_Number(0), CNIC(0), E_Mail("") {}
	void set_name(string name) { this->Name = name; }
	void set_CNIC(long long int CNIC) { this->CNIC = CNIC; }
	void set_Contact_Number(int Contact_Number) { this->Contact_Number = Contact_Number; }
	void set_E_Mail(string E_Mail) { this->E_Mail = E_Mail; }
	string get_name() const { return  Name; }
	long long int get_CNIC() const { return CNIC; }
	int get_Contact_Number() const { return Contact_Number; }
	string get_E_Mail() const { return E_Mail; }
	void User_Input() {
		cout << "Enter Name:";		cin >> Name;
		cout << "Enter CNIC:";		cin >> CNIC;
		cout << "Enter Contact Number:";		cin >> Contact_Number;
		cout << "Enter E_Mail:";		cin >> E_Mail;
	}
	void display_Details() {
		cout << "\nName:" << Name;
		cout << "\nCNIC:" << CNIC;
		cout << "\nContact Number:" << Contact_Number;
		cout << "\nE_Mail:" << E_Mail << endl;
	}
};
class Junior_Account : public Account_Info {
protected:
	Person_info Father;
	Person_info Mother;
public:
	Junior_Account() {}
	Junior_Account(Person_info Father, Person_info Mother) {
		this->Father = Father; this->Mother = Mother;
	}
	bool deposit(int Amount_To_Depsoit) {
		if (Amount_To_Depsoit >= 5000)
		{
			cout << "Transaction reported sent to Parents via E-mail and Contact number:\n"
				<< "Father's Number:" << Father.get_Contact_Number() << "\tFather's E-mail:" << Father.get_E_Mail()
				<< "\nMother's Number:" << Father.get_Contact_Number() << "\tMother's E-mail:" << Father.get_E_Mail() << endl;
			Balance += Amount_To_Depsoit;
			return 1;
		}
		else
		{
			Balance += Amount_To_Depsoit;
			return 1;
		}
	}
	bool withdraw(int Amount_To_Withdraw) {
		if (Balance >= Amount_To_Withdraw)
		{
			Balance -= Amount_To_Withdraw;
			return 1;
		}
		return 0;
	}
	void User_Input() {
		cout << "Enter Father's detail:\n"; Father.User_Input();
		cout << "Enter Mother's detail:\n"; Mother.User_Input();
		Account_Info::User_Input();
	}
	void display_Details() {
		cout << "Father's detail:\n";
		Father.display_Details();
		cout << "Mother's detail:\n";
		Mother.display_Details();
		Account_Info::display_Details();
	}
};
void Validate_Input(int start, int& Input, int end) {
	while (Input < start || Input > end)
		Input = _getch() - '0';
}
int main() {
	srand(time(0));
	Account_Info* Accounts[100];
	Savings_Account my;
	int Input[5], Amount = 0;
	cout << "1. Create Account  \t" << "2. Manage Account  " << "\t3. Deposit Money  " << "\t4. Withdraw Money";
	Input[0] = _getch() - '0';
	Validate_Input(1, Input[0], 4);
	while (1)
	{
		switch (Input[0])
		{
		case 1:

			cout << "\nSelect type of Account\n"
				<< "1. Saving Account \t" << "\t2. Checking Account " << "\t3. Junior Account\n";
			Input[1] = _getch() - '0';
			Validate_Input(1, Input[1], 3);
			switch (Input[1])
			{
			case 1:
				Account_Info::Number_of_Accounts++;
				Accounts[Account_Info::Number_of_Accounts] = new Savings_Account;
				Accounts[Account_Info::Number_of_Accounts]->User_Input();
				break;

			case 2:
				Account_Info::Number_of_Accounts++;
				Accounts[Account_Info::Number_of_Accounts] = new Checking_Account;
				Accounts[Account_Info::Number_of_Accounts]->User_Input();
				break;

			case 3:
				Account_Info::Number_of_Accounts++;
				Accounts[Account_Info::Number_of_Accounts] = new Junior_Account;
				Accounts[Account_Info::Number_of_Accounts]->User_Input();
				break;
			}
			break;
		case 2:
			system("CLS");
			cout << "Select your Account\n";
			for (int i = 0; i <= Account_Info::Number_of_Accounts; i++)
			{
				cout << i << " . ";
				cout << Accounts[i]->get_Account_Holder_Name();
				cout << endl;
			}
			Input[1] = _getch() - '0';
			Validate_Input(0, Input[1], Account_Info::Number_of_Accounts);

			Accounts[Input[1]]->display_Details();
			break;

		case 3:
			system("CLS");
			cout << "Select the Account to Deposit Money into\n";
			for (int i = 0; i <= Account_Info::Number_of_Accounts; i++)
			{
				cout << i << " . ";
				cout << Accounts[i]->get_Account_Holder_Name();
				cout << endl;
			}
			Input[1] = _getch() - '0';
			Validate_Input(0, Input[1], Account_Info::Number_of_Accounts);
			cout << "Enter the Amount to Deposit:";
			cin >> Amount;
			if (Accounts[Input[1]]->deposit(Amount))
				cout << "Transaction Sucessful\n";
			else
				cout << "Transaction Failed\n";
			cout << "New Balance" << Accounts[Input[1]]->get_Balance() << endl;
			break;
		case 4:
			system("CLS");
			cout << "Select the Account to Withdraw Money from\n";
			for (int i = 0; i <= Account_Info::Number_of_Accounts; i++)
			{
				cout << i << " . ";
				cout << Accounts[i]->get_Account_Holder_Name();
				cout << endl;
			}
			Input[1] = _getch() - '0';
			Validate_Input(0, Input[1], Account_Info::Number_of_Accounts);
			cout << "Enter the Amount to Withdraw:";
			cin >> Amount;
			if (Accounts[Input[1]]->withdraw(Amount)) {
				cout << "Transaction Sucessful\n";
			}
			else
				cout << "Transaction Failed\n";
			cout << "New Balance" << Accounts[Input[1]]->get_Balance() << endl;
			break;
		}
		cout << "1. Create Account  \t" << "2. Manage Account  " << "\t3. Deposit Money  " << "\t4. Withdraw Money";
		Input[0] = _getch() - '0';
		Validate_Input(1, Input[0], 4);

	}
}