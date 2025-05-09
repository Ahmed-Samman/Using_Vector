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

		while (getline(MyFile ,Line))
		{

			Clients = ConvertStringFromFileToRecord(Line);
			AllClients.push_back(Clients);

		}
		MyFile.close();
	}
	return AllClients;
}


void PrintClient(stClientData C)
{
	cout << "| " << setw(15) << left << C.AccountNumber;
	cout << "| " << setw(10) << left << C.PinCode;
	cout << "| " << setw(40) << left << C.Name;
	cout << "| " << setw(12) << left << C.Phone;
	cout << "| " << setw(12) << left << C.AccountBalance;
}
void PrintHeader(vector <stClientData> vAllClients)
{

	cout << setw(50) << "Client List (" << vAllClients.size() << ") Cliet(s).\n";
	cout << "_______________________________________________________________________________________________\n\n";
	cout << "| " << left << setw(15) << "Account Number";
	cout << "| " << left << setw(10) << "Pin Code";
	cout << "| " << left << setw(40) << "Client Name";
	cout << "| " << left << setw(12) << "Phone";
	cout << "| " << left << setw(12) << "Balance";
	cout << "\n_______________________________________________________________________________________________\n\n";


	for (stClientData &C : vAllClients)
	{
		PrintClient(C);
		cout << endl;				
	}

}




int main()
{



	vector <stClientData> vAllClients = AddDataFromFileToRecord(ClientFileName);

	PrintHeader(vAllClients);



	return 0;
}