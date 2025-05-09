#include<iostream>
#include<string>
#include<cctype>
#include<vector>
#include<fstream>
using namespace std;

const string ClientFileName = "ClientData.txt";

struct stClientData
{
	string AccountNumber;
	string PinCode;
	string Name;
	string Phone;
	double AccountBalance;
};

stClientData ReadNewClient()
{
	stClientData ClientData;

	cout << "Enter Account Number? ";
	getline(cin >> ws, ClientData.AccountNumber); // Usage of std::ws will extract all the whitespace character

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
	Str += to_string(Client.AccountBalance);

	return Str;
}

void AddDataLineToFile(string FileName, string stDataLine)
{
	fstream ClientDatafile;

	ClientDatafile.open(FileName, ios::out | ios::app);

	if (ClientDatafile.is_open())
	{

		ClientDatafile << stDataLine << endl;

		ClientDatafile.close();
	}

}
void AddNewClient()
{

	stClientData Client = ReadNewClient();
	AddDataLineToFile(ClientFileName, ConvertRecordToLine(Client));

}
void AddClients()
{

	char AddClient = 'y';
	
	do
	{
		system("cls");
		cout << "Adding New Client:\n\n";
		
		AddNewClient();

		cout << "Client Added Successfully, do you want to add more clients? ";
		cin >> AddClient;

	} while (toupper(AddClient) == 'Y');
}



int main()
{

	
	AddClients();

	

	return 0;

}