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


string ReadAccountNumber()
{
	string AccountNmber = "";
	cout << "Please enter Account Number? ";
	cin >> AccountNmber;
	return AccountNmber;
}
bool CheckAccountNumberFromUser(string AccountNumber, stClientData& Client, vector <stClientData> &vAllClients)
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
void PrintRecordFromStruct(stClientData ClientInfo)
{
	cout << "\n\nThe following is the extracted client record:\n\n";

	cout << "Account Number : " << ClientInfo.AccountNumber << endl;
	cout << "Pin Code       : " << ClientInfo.PinCode << endl;
	cout << "Name           : " << ClientInfo.Name << endl;
	cout << "Phone          : " << ClientInfo.Phone << endl;
	cout << "Account Balance: " << ClientInfo.AccountBalance << endl;

}
bool PrintAccountNumber(string AccountNumber, stClientData Client, vector <stClientData> vAllClients)
{
	if (CheckAccountNumberFromUser(AccountNumber, Client, vAllClients))
	{
		PrintRecordFromStruct(Client);
		return true;
	}
	else
	{
		cout << "\nClient with AccountNumber(" << AccountNumber << ") Not Found!\n";
		return false;
	}
}


// delete a client
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
vector <stClientData> DeleteRecordFromeVector(string FileName, string AccountNumber, vector <stClientData>& vAllClients)
{
	fstream MyFile;
	string DataLine;

	MyFile.open(FileName, ios::out);

	if (MyFile.is_open())
	{
		for (stClientData& C : vAllClients)
		{
			if (C.AccountNumber != AccountNumber)
			{
				DataLine = ConvertRecordToLine(C);
				MyFile << DataLine << endl;
			}
		}
		MyFile.close();
	}

	//Refresh Clients In Vector
	return vAllClients = AddDataFromFileToRecord(FileName);
}
bool Check()
{
	char DeleteClient = 'Y';
	cout << "\n\nDo you want to delete This client? ";
	cin >> DeleteClient;

	if (toupper(DeleteClient) == 'Y')
	{
		return true;
	}
	else
	{
		return false;
	}
}

int main()
{

	stClientData Client;
	
	vector <stClientData> vAllClients = AddDataFromFileToRecord(ClientFileName);
	string AccountNumber = ReadAccountNumber();
	bool IsFound = PrintAccountNumber(AccountNumber, Client, vAllClients);

	// delete a Client
	if (IsFound && Check())
	{

		DeleteRecordFromeVector(ClientFileName, AccountNumber, vAllClients);
		cout << "\nClient deleted Successfully.\n";
	}
	


	return 0;
}