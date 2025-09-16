🏦 ATM Simulation System

A console-based ATM simulation written in C++.
This project demonstrates file handling, input validation, password security, and basic banking operations.

✨ Features

🔑 Login System

Validates account number & PIN code.

Data loaded from Bank.txt.

💰 Deposit

Deposit positive amounts to your account.

Confirmation before committing.

💸 Withdraw

Quick Withdraw with predefined amounts (20, 50, 100, …).

Normal Withdraw with user-defined amount (multiples of 5).

Balance validation prevents overdrawing.

📊 Check Balance

Displays current account balance.

🔄 Transfer Money

Transfer funds to another account.

Confirms recipient details before proceeding.

Requires sender PIN re-entry for extra security.

🔐 Change PIN Code

Enforces strong password rules:

8–12 characters

At least 1 uppercase, 1 lowercase, and 1 special character

Saves changes securely to Bank.txt.

🚪 Logout

Securely logs out and returns to the login screen.

ATM-Project/
│
├── Bank.txt          # Database of clients (AccountNumber, PIN, Name, Phone, Balance)
├── Number.h          # Utility functions for numeric input and validation
├── String.h          # Utility functions for string operations (split, count letters, etc.)
├── main.cpp          # Main source file containing ATM system logic
└── README.md         # Project documentation


🛠️ Technologies Used

C++ (Standard Library: <iostream>, <fstream>, <string>, <vector>)

File handling for client persistence

Procedural programming with structured data (struct, enum)
