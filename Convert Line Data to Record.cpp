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

stClientData ConvertLineToRecord(string Str, string delim = "#//#")
{
	stClientData ClientInfo;
	vector<string> vClient = SplitString(Str, delim);

	ClientInfo.AccountNumber = vClient[0];
	ClientInfo.PinCode = vClient[1];
	ClientInfo.Name = vClient[2];
	ClientInfo.Phone = vClient[3];
	ClientInfo.AccountBalance = stod(vClient[4]);

	return ClientInfo;
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



int main()
{

	string StrRecord = "A150#//#1234#//#Ahmed Samman#//#01025019008#//#5270.000000";
	cout << "Line Record is:\n" << StrRecord << endl;


	stClientData Client = ConvertLineToRecord(StrRecord);
	PrintRecordFromStruct(Client);



	return 0;
}