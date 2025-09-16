#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "Number.h"
#include "String.h"
using namespace std;

const string filename = "Bank.txt";
string seperator = "#...#";

enum enATMSystemOptions
{
    QuickWithDraw = 1, NormalWithdraw = 2, Deposit = 3, CheckBalance = 4, ChangePInCode = 5, Logout = 6
};

enum enQuickWithDrawOptions {
    Twenty = 1, Fifty = 2, OneHundered = 3, TwoHundered = 4, FourHundered = 5, SixHundered = 6,
    EightHundered = 7, OneThousand = 8, Exit = 9
};

struct stClientsInfo {
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double Balance;
    bool   MarkForDelete = false;
};

stClientsInfo Client;

void ShowATMSystemMainScreen();

void GoBackToATMSytemMenu();

void Login();

void QuickWithdraw(int Amount);

stClientsInfo ConvertLineToRecord(string line)
{
    stClientsInfo client;

    vector <string> Data = str::SplitString(line, seperator);

    client.AccountNumber = Data[0];
    client.PinCode = Data[1];
    client.Name = Data[2];
    client.Phone = Data[3];
    client.Balance = stod(Data[4]);

    return client;
}

string ConvertRecordToLine(stClientsInfo client)
{
    string line;
    line += client.AccountNumber + seperator;
    line += client.PinCode + seperator;
    line += client.Name + seperator;
    line += client.Phone + seperator;
    line += to_string(client.Balance);

    return line;
}

vector <stClientsInfo> LoadDataFromFileToVector()
{
    fstream file;
    vector <stClientsInfo> vClients;
    string line;

    file.open(filename, ios::in); // Read Mode

    while (getline(file, line))
    {
        if (line != "")
        {
            vClients.push_back(ConvertLineToRecord(line));
        }
    }
    file.close();
    return vClients;
}

void LoadDataFromVectortoFile(vector <stClientsInfo>& vClientData)
{
    fstream file;

    file.open(filename, ios::out);

    for (stClientsInfo client : vClientData)
    {
        string line = ConvertRecordToLine(client);
        if (client.MarkForDelete == false)
        {
            file << line << endl;
        }
    }
}

void ShowClientBalance()
{
    system("cls");

    cout << "\n=================================\n";
    cout << "\tCheck Balance Screen\n";
    cout << "\n=================================\n";

    cout << "Your Balance is: " << Client.Balance << "\n\n";
    
}

void DepositOrWithdraw(int amount)
{
    vector <stClientsInfo> VClientsInfo = LoadDataFromFileToVector();

    for (stClientsInfo &C : VClientsInfo)
    {
        if (Client.AccountNumber == C.AccountNumber)
        {
            Client.Balance += amount;
            C = Client;
        }
    }
    LoadDataFromVectortoFile(VClientsInfo);
}

void PerformDepositOperation()
{
    int AmountToDespoit = Num::ReadPositiveNumber("Enter a positive deposit amount: ");


    string answer;
    cout << "\nAre you sure you want perform this transaction? (y/n): ";
    getline(cin >> ws, answer);

    if (answer == "y" || answer == "Y")
    {
        DepositOrWithdraw(AmountToDespoit);

        cout << "\nDone successfully. New Balance is: " << Client.Balance << endl;
    }
}

void ShowDepositScreen()
{

    system("cls");

    cout << "\n=================================\n";
    cout << "\tDeposit Screen\n";
    cout << "\n=================================\n";

    PerformDepositOperation();
}

bool CheckBalanceToWithdraw(int amount)
{
    if (Client.Balance >= amount)
    {
        return true;
    }
    else
    {
        cout << "\n\nThe amount exceeds your balance, make another choice!\n";
        cout << "\n\nPress AnyKey to continue...";
        system("pause>0");
        return false;
    }
}

void PerformQuickWithdrawMenu(enQuickWithDrawOptions option)
{
    switch (option)
    {
    case(enQuickWithDrawOptions::Twenty):
    {
        QuickWithdraw(20);
        GoBackToATMSytemMenu();
        break;
    }

    case(enQuickWithDrawOptions::Fifty):
    {
        QuickWithdraw(50);
        GoBackToATMSytemMenu();
        break;
    }
    case(enQuickWithDrawOptions::OneHundered):
    {
        QuickWithdraw(100);
        GoBackToATMSytemMenu();
        break;
    }

    case(enQuickWithDrawOptions::TwoHundered):
    {
        QuickWithdraw(200);
        GoBackToATMSytemMenu();
        break;
    }
    case(enQuickWithDrawOptions::FourHundered):
    {
        QuickWithdraw(400);
        GoBackToATMSytemMenu();
        break;
    }

    case(enQuickWithDrawOptions::SixHundered):
    {
        QuickWithdraw(600);
        GoBackToATMSytemMenu();
        break;
    }
    case(enQuickWithDrawOptions::EightHundered):
    {
        QuickWithdraw(800);
        GoBackToATMSytemMenu();
        break;
    }
    case(enQuickWithDrawOptions::OneThousand):
    {
        QuickWithdraw(1000);
        GoBackToATMSytemMenu();
        break;
    }
    case(enQuickWithDrawOptions::Exit):
    {
        GoBackToATMSytemMenu();
        break;
    }
    }
}

void ShowQuickWithDrawScreen()
{
    system("cls");

    cout << "\n=========================================\n";
    cout << "\tQuick Withdraw\n";
    cout << "==========================================\n";
    cout << "\t[1] 20  \t[2] 50\n";
    cout << "\t[3] 100 \t[4] 200\n";
    cout << "\t[5] 400 \t[6] 600\n";
    cout << "\t[7] 800  \t[8] 1000\n";
    cout << "\t[9] Exit\n";
    cout << "\n=========================================\n";

    cout << "Your balance is: " << Client.Balance << endl;
    PerformQuickWithdrawMenu(enQuickWithDrawOptions(Num::ReadNumberFromTo("\nChoose what to withdraw from [1] to [8]: ", 1, 9)));
}

void PerformNoramlWithdrawOperation()
{
    int AmounttoWithdraw = 0;

    do
    {
        AmounttoWithdraw = Num::ReadPositiveNumber("\nEnter an amount mutliple of 5's: ");

        if (!CheckBalanceToWithdraw(AmounttoWithdraw))
        {
            return;
        }
    } while (AmounttoWithdraw % 5 != 0);


    string answer;
    cout << "\nAre you sure you want perform this transaction? (y/n): ";
    getline(cin >> ws, answer);

    if (answer == "y" || answer == "Y")
    {
        DepositOrWithdraw(AmounttoWithdraw * -1);

        cout << "\nDone successfully. New Balance is: " << Client.Balance << endl;

    }

}

void ShowNormalWithdrawScreen()
{
    system("cls");

    cout << "\n=================================\n";
    cout << "\tNormal Withdraw Screen\n";
    cout << "\n=================================\n";

    PerformNoramlWithdrawOperation();
}

int ReadAmountForNormalWithDraw()
{
    int amount = 0;
    amount = Num::ReadPositiveNumber("\nEnter an amount mutliple of 5's: ");

    while (amount % 5 != 0)
    {
        amount = Num::ReadPositiveNumber("\nEnter an amount mutliple of 5's: ");
    }
    return amount;
}

void QuickWithdraw(int Amount)
{

    while (!CheckBalanceToWithdraw(Amount))
    {
        ShowQuickWithDrawScreen();

    }

    string answer;
    cout << "\nAre you sure you want perform this transaction? (y/n): ";
    getline(cin >> ws, answer);

    if (answer == "y" || answer == "Y")
    {
        DepositOrWithdraw(Amount * -1);

        cout << "\nDone successfully. New Balance is: " << Client.Balance << endl;
    }

}

string ReadAndCheckCorrectPassword()
{
    string NewPass;
    bool validPassword = true;
    do {
        cout << "\nEnter the new password: ";
        getline(cin >> ws, NewPass);

        if (NewPass.size() < 8 || NewPass.size() > 12) {
            cout << "\nPIN Code should be between 8 and 12 characters\n";
        }
        else if (str::CountCapitalLetters(NewPass) == 0 ||
            str::CountSmallLetters(NewPass) == 0 ||
            str::CountSpecialCharacters(NewPass) == 0) {
            cout << "\nWeak PIN, PIN Code should include Small & Capital letters & Special Characters\n";
        }
        else {
            validPassword = true;
        }
    } while (!validPassword);

    return NewPass;

}

void SaveNewPasswordToFile(string NewPass)
{
    vector <stClientsInfo> VClientsInfo = LoadDataFromFileToVector();

    for (stClientsInfo& C : VClientsInfo)
    {
        if (Client.AccountNumber == C.AccountNumber)
        {
            Client.PinCode = NewPass;
            C = Client;
        }
    }
    LoadDataFromVectortoFile(VClientsInfo);
}

void PerformChangePasswordOperation()
{
    string currentpass, NewPass;
    bool WrongPass = false;
    do
    {
        if (WrongPass)
        {
            cout << "Wrong Password! Please Try again!";
        }

        cout << "\nEnter Current PIN Code: ";
        getline(cin >> ws, currentpass);

        WrongPass = (Client.PinCode != currentpass) ? true : false;

    } while (WrongPass);

    NewPass = ReadAndCheckCorrectPassword();
    
    cout << "\nDone successfully, Your New Pin Code is: " << NewPass << endl;

    //save in file
    SaveNewPasswordToFile(NewPass);

}

void ShowChangePasswordScreen()
{
    system("cls");

    cout << "\n=================================\n";
    cout << "\tChange PIN Code";
    cout << "\n=================================\n";

    PerformChangePasswordOperation();
}

void GoBackToATMSytemMenu()
{
    cout << "\n\nPress any key to go back to Main Menue...";
    system("pause>0");

    system("cls");

    ShowATMSystemMainScreen();

}

bool FindClientByAccountNumberAndPinCode(string AccountNumber, string PinCode, stClientsInfo& Client)
{

    vector <stClientsInfo> vClients = LoadDataFromFileToVector();

    for (stClientsInfo C : vClients)
    {

        if (C.AccountNumber == AccountNumber && C.PinCode == PinCode)
        {
            Client = C;
            return true;
        }

    }
    return false;

}

void PerformATMSytemMenu(enATMSystemOptions option)
{
    switch (option)
    {
    case(enATMSystemOptions::QuickWithDraw):
    {
        ShowQuickWithDrawScreen();
        GoBackToATMSytemMenu();
        break;
    }
    case(enATMSystemOptions::NormalWithdraw):
    {
        ShowNormalWithdrawScreen();
        GoBackToATMSytemMenu();
        break;
    }
    case(enATMSystemOptions::Deposit):
    {
        ShowDepositScreen();
        GoBackToATMSytemMenu();
        break;
    }
    case(enATMSystemOptions::CheckBalance):
    {
        ShowClientBalance();
        GoBackToATMSytemMenu();
        break;
    }
    case(enATMSystemOptions::ChangePInCode):
    {
        ShowChangePasswordScreen();
        GoBackToATMSytemMenu();
        break;
    }
    case(enATMSystemOptions::Logout ):

        Login();
        break;
    }

}

void ShowATMSystemMainScreen()
{
    system("cls");
    cout << "\n=====================================\n";
    cout << "\t ATM Main Menu Screen";
    cout << "\n=====================================\n";
    cout << "\t [1] Quick Withdraw \n";
    cout << "\t [2] Noraml Withdraw \n";
    cout << "\t [3] Deposit \n";
    cout << "\t [4] Check Balance \n";
    cout << "\t [5] Change PIN Code \n";
    cout << "\t [6] Logout \n";
    cout << "\n=====================================\n";

    PerformATMSytemMenu(enATMSystemOptions(Num::ReadPositiveNumber("Choose What do you want to do? [1 to 6]: ")));

}

void Login()
{

    bool IsValidLogin = true;
    do
    {
        system("cls");

        cout << "\n-----------------------------------\n";
        cout << "\tLogin Screen\n";
        cout << "-----------------------------------\n";

        if (!IsValidLogin)
        {
            cout << "Invalid Account Number/Pin Code!\n";
            IsValidLogin = false;
        }

        string AccountNumber, PinCode;
        cout << "Enter Account Number: ";
        getline(cin >> ws, AccountNumber);

        PinCode = str::Readtext("Enter Pin Code: ");

        IsValidLogin = FindClientByAccountNumberAndPinCode(AccountNumber, PinCode, Client);


    } while (!IsValidLogin);

    ShowATMSystemMainScreen();
}



int main()
{

    Login();

   



    return 0;
}
