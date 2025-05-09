#include<iostream>
#include<string>
#include<cctype>
#include<vector>
using namespace std;

struct stClientData
{
	string AccountNumber;
	string PinCode;
	string Name;
	string Phone;
	double AccountBalance;
};

stClientData FillClientData()
{
	stClientData ClientData;

	cout << "Enter Account Number? ";
	getline(cin, ClientData.AccountNumber);

	cout << "Enter PinCode? ";
	getline(cin, ClientData.PinCode);

	cout << "Enter Name? ";
	getline(cin, ClientData.Name);

	cout << "Enter Phone? ";
	getline(cin, ClientData.Phone);

	cout << "Enter Account Balance? "; 
	cin >> ClientData.AccountBalance;

	return ClientData;
}

string ConvertRecordToLine(stClientData Client, string delim = "#//#")
{
	string Str = "";

	Str += Client.AccountNumber + delim;
	Str += Client.PinCode + delim;
	Str += Client.Name + delim;
	Str += Client.Phone + delim;
	Str	+= to_string(Client.AccountBalance);
	
	return Str;
}



int main()
{
	
	cout << "Please enter client data:\n\n";

	stClientData Client;
	Client = FillClientData();


	string StrRecord = ConvertRecordToLine(Client);
	cout << "\n\nClient Record for saving is: \n" << StrRecord << endl;



	return 0;

}