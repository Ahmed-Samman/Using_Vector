#include<iostream>
#include<string>
#include<cctype>
#include<vector>
#include<fstream>
#include<iomanip>
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

vector <string> SplitString(string Str, string delim)
{
	vector <string> vSplitWords;

	string sWord; // define a string variable
	short Pos = 0;

	// use find() function to get the position of the delimiter
	while ((Pos = Str.find(delim)) != std::string::npos) // true
	{
		sWord = Str.substr(0, Pos); // store the word
		if (sWord != " ")
		{
			vSplitWords.push_back(sWord);
		}
		Str.erase(0, Pos + delim.length()); // erase() until position and move to next word. 
	}
	if (Str != " ")
	{
		vSplitWords.push_back(Str);
	}
	return vSplitWords;
}
stClientData ConvertStringFromFileToRecord(string Line)
{
	stClientData EachClient;
	vector <string> vClient = SplitString(Line, "#//#");

	EachClient.AccountNumber = vClient[0];
	EachClient.PinCode = vClient[1];
	EachClient.Name = vClient[2];
	EachClient.Phone = vClient[3];
	EachClient.AccountBalance = stod(vClient[4]);

	return EachClient;
}
vector <stClientData> AddDataFromFileToRecord(string FileName)
{
	fstream MyFile;
	vector <stClientData> AllClients;

	MyFile.open(FileName, ios::in);
	if (MyFile.is_open())
	{
		string Line;
		stClientData Clients;

		while (getline(MyFile, Line))
		{
			Clients = ConvertStringFromFileToRecord(Line);

			AllClients.push_back(Clients);
		}
		MyFile.close();
	}
	return AllClients;
}


void PrintRecordFromStruct(stClientData ClientInfo)
{
	cout << "\n\nThe following is the extracted client record:\n\n";

	cout << "Account Number : " << ClientInfo.AccountNumber << endl;
	cout << "Pin Code       : " << ClientInfo.PinCode << endl;
	cout << "Name           : " << ClientInfo.Name << endl;
	cout << "Phone          : " << ClientInfo.Phone << endl;
	cout << "Account Balance: " << ClientInfo.AccountBalance << endl;

}
string ReadAccountNumber()
{
	string AccountNmber = "";
	cout << "Please enter Account Number? ";
	cin >> AccountNmber;
	return AccountNmber;
}
bool CheckAccountNumberFromUser(string AccountNumber, vector <stClientData> vAllClients, stClientData& Client)
{

	for (stClientData& C : vAllClients)
	{
		if (C.AccountNumber == AccountNumber)
		{
			Client = C;
			return true;
		}
	}
	return false;
}
void PrintClient(string AccountNumber, vector <stClientData> vAllClients, stClientData Client)
{
	if (CheckAccountNumberFromUser(AccountNumber, vAllClients, Client))
	{
		PrintRecordFromStruct(Client);
	}
	else
	{
		cout << "Client with account nimber (" << AccountNumber << ") is not found!\n";
	}
}


// Update  a client
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
void SaveClientsDataToFile(string ClientFileName, vector <stClientData> vAllClients)
{
	fstream MyFile;

	MyFile.open(ClientFileName, ios::out);

	string DataLine;

	if (MyFile.is_open())
	{
		for (stClientData& C : vAllClients)
		{	

			DataLine = ConvertRecordToLine(C);
			MyFile << DataLine << endl;
			
		}
		MyFile.close();
	}
}
stClientData FillClientData(string AccountNumber)
{
	stClientData ClientData;

	ClientData.AccountNumber = AccountNumber;

	cout << "\n\nEnter PinCode? ";
	getline(cin >> ws, ClientData.PinCode);

	cout << "Enter Name? ";
	getline(cin ,ClientData.Name);

	cout << "Enter Phone? ";
	getline(cin, ClientData.Phone);

	cout << "Enter Account Balance? ";
	cin >> ClientData.AccountBalance;

	return ClientData;
}
bool UpdateClientByAccountNumber(string AccountNumber, vector <stClientData>& vAllClients)
{
	stClientData Client;
	char Answer = 'n';

	if (CheckAccountNumberFromUser(AccountNumber, vAllClients, Client))
	{
		PrintRecordFromStruct(Client);

		cout << "\n\nAre you sure you want update this client? y/n ? ";
		cin >> Answer;
		if (toupper(Answer) == 'Y')
		{
			for  (stClientData &C : vAllClients)
			{
				if (C.AccountNumber == AccountNumber)
				{
					C = FillClientData(AccountNumber);
					break;
				}
			}
			
			SaveClientsDataToFile(ClientFileName, vAllClients);

			cout << "\n\nClient Updated Successfully.\n\n";
			return true;
		}
	}
	else
	{
		cout << "\nClient with AccountNumber(" << AccountNumber << ") Not Found!\n";
		return false;
	}
}



int main()
{

	vector <stClientData> vAllClients = AddDataFromFileToRecord(ClientFileName);
	string AccountNumber = ReadAccountNumber();

	UpdateClientByAccountNumber(AccountNumber, vAllClients);
	




	return 0;
}