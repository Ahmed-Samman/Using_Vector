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
bool CheckAccountNumberFromUser(string AccountNumber, stClientData &Client)
{
	vector <stClientData> vAllClients = AddDataFromFileToRecord(ClientFileName);

	for (stClientData &C : vAllClients)
	{
		if (C.AccountNumber == AccountNumber)
		{
			Client = C;
			return true;
		}
	}
	return false;
}
void PrintAccountNumber(string AccountNumber, stClientData Client)
{
	if (CheckAccountNumberFromUser(AccountNumber, Client))
	{
		PrintRecordFromStruct(Client);
	}
	else
	{
		cout << "\nClient with AccountNumber(" << AccountNumber << ") Not Found!\n";
	}
}



int main()
{

	stClientData Client;
	string AccountNumber = ReadAccountNumber();

	PrintAccountNumber(AccountNumber, Client);
	



	return 0;
}