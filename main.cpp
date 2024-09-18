//Francisco Bumanglag 
//Date: September 13, 2024 
//Chapter 11 Assignments -- CMPR121 Chapter 11 Structured Data 

#include <iostream>     //for input-output operations
#include <string>       //for string handling
#include <iomanip>      //for output formatting
#include <cstdlib>      //for system commands
#include <cctype>       //for isdigit
#include <limits>       //for input validation
#include <regex>        //for regex validation of phone and date formats
#include <ctime>        //for random number generation
//#include "input.h"      //code from professor -- didnt use or need

using namespace std;

//enumerated type for months
enum Months { JAN, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC };

//challenge3 structure for storing division sales data
struct DivisionData {
    string divisionName;
    double quarterlySales[4];
    double totalYearlySales;
    double avgQuarterlySales;
};

//challenge5 structure for weather statistics
struct WeatherStats {
    double rainfall;
    double maxTemp;
    double minTemp;
    double avgTemp;
};

//challenge8 structure to store customer information
struct ClientInfo {
    string fullName = "";
    string streetAddress = "";
    string cityStateZip = "";
    string contactNumber = "";
    double acctBalance = 0.0;
    string lastPayment = "";
};

//challenge10 structure for presenter information
struct Presenter {
    string name;
    string phoneNumber;
    string topic;
    double fee;
};

//challenge12 structure to store student details
struct CourseStudent {
    string fullName;
    int studentId;
    double* testScores;
    double avgScore;
    char finalGrade;
};

//function prototypes 
int getIntInput(const string& promptMessage, int minValue, int maxValue);  //used for validated integer input across various challenges
void challenge3();  //challenge3
void displayWeatherStats(); //challenge5
void challenge8();  //challenge8
string getPhoneNumberInput(const string& promptMessage);  //challenge8
double getBalanceInput(const string& promptMessage);  //challenge8
string getDateInput(const string& promptMessage);  //challenge8
void enterClientData(ClientInfo& client, int index);  //challenge8
void modifyClientData(ClientInfo& client, int index, int arraySize);  //challenge8
void displayClientData(const ClientInfo& client, int index);  //challenge8
void searchClientByName(ClientInfo clients[], int arraySize);  //challenge8
bool isValidPhoneNumber(const string& phone); //challenge10 & challenge8
void challenge10();  //challege10
bool isValidFee(const string& fee); //challenge10
void challenge12();  //challenge 12
void computeGrade(CourseStudent& student, int numTests); //challenge12
char determineLetterGrade(double avgScore); //challenge12
void enterStudentData(CourseStudent& student, int numTests, bool autoGenerate); //challenge12


//used for all challenges -- validate and retrieves integer input from the user
int getIntInput(const string& promptMessage, int minValue, int maxValue) {
    int userInput;
    while (true) {
        cout << promptMessage;
        cin >> userInput;

        //check if input is a valid integer and within range
        if (cin.good() && userInput >= minValue && userInput <= maxValue) {
            break;  //exit the loop if valid input
        }
        else {
            cout << "Invalid input. Please enter a number between " << minValue << " and " << maxValue << ".\n";
            cin.clear(); //clear error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); //ignore remaining invalid input
        }
    }
    return userInput;
}

//validates phone number in format n-nnn-nnn-nnnn
bool isValidPhoneNumber(const string& phone) {
    if (phone.length() != 14) return false; //check length
    if (phone[0] != '1' || phone[1] != '-' || phone[5] != '-' || phone[9] != '-') return false; //check format
    for (int i = 2; i < 5; ++i) { if (!isdigit(phone[i])) return false; } //check nnn
    for (int i = 6; i < 9; ++i) { if (!isdigit(phone[i])) return false; } //check nnn
    for (int i = 10; i < 14; ++i) { if (!isdigit(phone[i])) return false; } //check nnnn
    return true;
}

//validates fee input as numeric
bool isValidFee(const string& fee) {
    for (char c : fee) {
        if (!isdigit(c)) return false; //check if all characters are digits
    }
    return true;
}

//validates and retrieves phone number input from the user
string getPhoneNumberInput(const string& promptMessage) {
    string input;
    regex phonePattern("^\\d-\\d{3}-\\d{3}-\\d{4}$"); //pattern for phone format n-nnn-nnn-nnnn
    while (true) {
        cout << promptMessage;
        getline(cin, input);

        if (regex_match(input, phonePattern)) {
            break;  //exit the loop if valid input
        }
        else {
            cout << "Invalid phone number format. Please use the format n-nnn-nnn-nnnn.\n";
        }
    }
    return input;
}

//validates and retrieves balance input from the user
double getBalanceInput(const string& promptMessage) {
    double balance;
    while (true) {
        cout << promptMessage;
        cin >> balance;

        if (cin.good() && balance >= 0) {
            break;  //exit the loop if valid input
        }
        else {
            cout << "Invalid balance. Please enter a positive amount.\n";
            cin.clear(); //clear error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); //ignore remaining invalid input
        }
    }
    return balance;
}

//validates and retrieves date input from the user in mm/dd/yyyy format
string getDateInput(const string& promptMessage) {
    string input;
    regex datePattern("^\\d{2}/\\d{2}/\\d{4}$"); //pattern for date format mm/dd/yyyy
    while (true) {
        cout << promptMessage;
        getline(cin, input);

        if (regex_match(input, datePattern)) {
            break;  //exit the loop if valid input
        }
        else {
            cout << "Invalid date format. Please enter in the format mm/dd/yyyy.\n";
        }
    }
    return input;
}

//calculate the average and letter grade for a student
void computeGrade(CourseStudent& student, int numTests) {
    double totalScore = 0;
    for (int i = 0; i < numTests; i++) {
        totalScore += student.testScores[i];
    }
    student.avgScore = totalScore / numTests;
    student.finalGrade = determineLetterGrade(student.avgScore);
}

//determine letter grade based on average
char determineLetterGrade(double avgScore) {
    if (avgScore >= 90) return 'A';
    else if (avgScore >= 80) return 'B';
    else if (avgScore >= 70) return 'C';
    else if (avgScore >= 60) return 'D';
    else return 'F';
}

//input student information
void enterStudentData(CourseStudent& student, int numTests, bool autoGenerate) {
    cout << "\n\tEnter the student's name: ";
    cin.ignore();
    getline(cin, student.fullName);

    student.studentId = getIntInput("\tEnter the student's id number: ", 1, 1000000);

    student.testScores = new double[numTests];

    if (autoGenerate) {
        //generate random test scores
        srand(time(0));  //seed for random number generation
        for (int i = 0; i < numTests; i++) {
            student.testScores[i] = rand() % 101; //random score between 0 and 100
        }
        cout << "\n\tTest score(s) have been randomly generated.\n";
    }
    else {
        //manual test score input
        for (int i = 0; i < numTests; i++) {
            student.testScores[i] = getIntInput("\tEnter the student's test score[" + to_string(i + 1) + "]: ", 0, 100);
        }
    }

    computeGrade(student, numTests);
}


// CHALLENGE 3: CORPORATE SALES DATA
void challenge3() {
    DivisionData divisions[4] = { {"East"}, {"West"}, {"North"}, {"South"} };

    system("cls");
    cout << "CMPR121: Chapter 11 - Challenge3. Corporate Sales Data\n";
    cout << string(80, char(205)) << "\n"; //separator line
    cout << "R-random (R) or I-console (I for manual) input? ";
    char inputMode;
    cin >> inputMode;
    cin.ignore(); //clear any remaining input

    if (inputMode == 'R' || inputMode == 'r') {
        for (auto& div : divisions) {
            for (double& sale : div.quarterlySales) {
                sale = rand() % 300 + 1;  //generate random sales between $1 and $300
            }
        }
    }
    else if (inputMode == 'I' || inputMode == 'i') {
        for (auto& div : divisions) {
            cout << "\n" << div.divisionName << " division\n";
            cout << string(80, char(196)) << "\n";
            for (int i = 0; i < 4; i++) {
                do {
                    cout << "Enter the " << (i + 1) << "-quarter sales amount: $";
                    cin >> div.quarterlySales[i];
                    if (div.quarterlySales[i] < 0) {
                        cout << "Invalid input. Please enter a non-negative number.\n";
                    }
                } while (div.quarterlySales[i] < 0);
            }
        }
    }
    else {
        cout << "Invalid option entered. Please choose 'R' or 'I'.\n";
        return;
    }

    cout << "\nDivision Name            1st-Qtr       2nd-Qtr         3rd-Qtr       4th-Qtr          Total Sales          Avg Quarterly\n";
    cout << string(120, char(196)) << "\n";

    double totalAllDivisions = 0;
    double quarterlySums[4] = { 0, 0, 0, 0 };
    for (auto& div : divisions) {
        div.totalYearlySales = 0;
        for (int i = 0; i < 4; ++i) {
            div.totalYearlySales += div.quarterlySales[i];
            quarterlySums[i] += div.quarterlySales[i];
        }
        div.avgQuarterlySales = div.totalYearlySales / 4;
        totalAllDivisions += div.totalYearlySales;

        cout << setw(15) << left << div.divisionName;
        for (int i = 0; i < 4; ++i) {
            cout << setw(10) << right << "$" << fixed << setprecision(2) << div.quarterlySales[i];
        }
        cout << setw(14) << right << "$" << div.totalYearlySales
            << setw(16) << right << "$" << div.avgQuarterlySales << "\n";
    }
    cout << string(120, char(196)) << "\n";

    cout << setw(15) << left << "Average";
    for (double sum : quarterlySums) {
        cout << setw(10) << right << "$" << fixed << setprecision(2) << sum / 4;
    }
    cout << setw(14) << right << "$" << totalAllDivisions / 4
        << setw(16) << right << "$" << totalAllDivisions / (4 * 4) << "\n";

    cout << string(120, char(196)) << "\n";

    system("pause");
}

// CHALLENGE 5: WEATHER STATISTICS MODIFICATION
void displayWeatherStats() {
    WeatherStats monthlyWeather[12];
    const string monthNames[] = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
    char inputChoice;

    system("cls");
    cout << "CMPR121: Chapter 11 - Challenge5. Weather Statistics Modification\n";
    cout << string(80, char(205)) << "\n";
    cout << "R-random (R) or M-manual (M) input? ";
    cin >> inputChoice;
    cin.ignore();

    double totalRainfall = 0;
    double hottestTemp = -numeric_limits<double>::max();
    double coldestTemp = numeric_limits<double>::max();
    int hottestMonth = 0;
    int coldestMonth = 0;

    if (inputChoice == 'R' || inputChoice == 'r') {
        for (int i = JAN; i <= DEC; ++i) {
            monthlyWeather[i].rainfall = (rand() % 300 + 1) / 100.0;
            monthlyWeather[i].maxTemp = (rand() % 100 + 1);
            monthlyWeather[i].minTemp = -(rand() % 100 + 1);
            monthlyWeather[i].avgTemp = (monthlyWeather[i].maxTemp + monthlyWeather[i].minTemp) / 2.0;

            totalRainfall += monthlyWeather[i].rainfall;

            if (monthlyWeather[i].maxTemp > hottestTemp) {
                hottestTemp = monthlyWeather[i].maxTemp;
                hottestMonth = i;
            }

            if (monthlyWeather[i].minTemp < coldestTemp) {
                coldestTemp = monthlyWeather[i].minTemp;
                coldestMonth = i;
            }
        }
    }
    else if (inputChoice == 'M' || inputChoice == 'm') {
        for (int i = JAN; i <= DEC; ++i) {
            monthlyWeather[i].rainfall = getIntInput("Enter the total rainfall for " + monthNames[i] + ": ", 0, 1000);
            monthlyWeather[i].maxTemp = getIntInput("Enter the max temperature for " + monthNames[i] + ": ", -100, 150);
            monthlyWeather[i].minTemp = getIntInput("Enter the min temperature for " + monthNames[i] + ": ", -100, 150);
            monthlyWeather[i].avgTemp = (monthlyWeather[i].maxTemp + monthlyWeather[i].minTemp) / 2.0;

            totalRainfall += monthlyWeather[i].rainfall;

            if (monthlyWeather[i].maxTemp > hottestTemp) {
                hottestTemp = monthlyWeather[i].maxTemp;
                hottestMonth = i;
            }

            if (monthlyWeather[i].minTemp < coldestTemp) {
                coldestTemp = monthlyWeather[i].minTemp;
                coldestMonth = i;
            }
        }
    }
    else {
        cout << "Invalid option.\n";
        return;
    }

    cout << "\nMonth            Rainfall(in)   High Temp   Low Temp   Avg Temp\n";
    cout << string(80, char(196)) << "\n";

    for (int i = JAN; i <= DEC; ++i) {
        cout << setw(15) << left << monthNames[i]
            << setw(16) << right << monthlyWeather[i].rainfall
            << setw(11) << right << monthlyWeather[i].maxTemp
            << setw(11) << right << monthlyWeather[i].minTemp
            << setw(13) << right << monthlyWeather[i].avgTemp << "\n";
    }

    cout << string(80, char(196)) << "\n";
    cout << "Total Annual Rainfall    : " << totalRainfall << " inches\n";
    cout << "Highest Temperature (+)  : " << hottestTemp << " degrees in " << monthNames[hottestMonth] << "\n";
    cout << "Lowest Temperature   (-) : " << coldestTemp << " degrees in " << monthNames[coldestMonth] << "\n";
}

// CHALLENGE 8: CUSTOMER ACCOUNTS MANAGEMENT PROGRAM
void challenge8() {
    int clientCount;
    cout << "\n\tSpecify the size of the dynamic array for clients (1-10): ";
    cin >> clientCount;

    ClientInfo* clients = new ClientInfo[clientCount];

    char choice;
    do {
        system("cls");
        cout << "\n\tCustomer Accounts Management Program";
        cout << "\n\t" << string(80, char(205));
        cout << "\n\tDynamic Array Size: " << clientCount;
        cout << "\n\tMenu";
        cout << "\n\t" << string(80, char(196));
        cout << "\n\tA. Enter client information";
        cout << "\n\tB. Update client information";
        cout << "\n\tC. Display all client information";
        cout << "\n\tD. Search client by name";
        cout << "\n\tR. Return to Main Menu";
        cout << "\n\t" << string(80, char(205));
        cout << "\n\tOption: ";
        cin >> choice;
        choice = toupper(choice);
        cin.ignore(); //clear the buffer

        switch (choice) {
        case 'A':
            for (int i = 0; i < clientCount; ++i) {
                enterClientData(clients[i], i);
            }
            break;
        case 'B': {
            int index = getIntInput("Specify the client's index (0..." + to_string(clientCount - 1) + "): ", 0, clientCount - 1);
            modifyClientData(clients[index], index, clientCount);
            break;
        }
        case 'C':
            for (int i = 0; i < clientCount; ++i) {
                displayClientData(clients[i], i);
            }
            break;
        case 'D':
            searchClientByName(clients, clientCount);
            break;
        case 'R':
            break;
        default:
            cout << "\n\tERROR: Invalid option.\n";
        }

        system("pause");
    } while (choice != 'R');

    delete[] clients;
}

//function to enter client data
void enterClientData(ClientInfo& client, int index) {
    cout << "\n\tClient Index: " << index << endl;
    cout << "\tEnter the client's full name: ";
    getline(cin, client.fullName);

    cout << "\tEnter the client's address: ";
    getline(cin, client.streetAddress);

    cout << "\tEnter the client's city, state, and zip: ";
    getline(cin, client.cityStateZip);

    client.contactNumber = getPhoneNumberInput("\tEnter the client's phone number (n-nnn-nnn-nnnn): ");

    client.acctBalance = getBalanceInput("\tEnter the account balance: $");

    cin.ignore(numeric_limits<streamsize>::max(), '\n'); //clear input buffer before getline

    client.lastPayment = getDateInput("\tEnter the last payment date (mm/dd/yyyy): ");
}

//function to modify client data by index
void modifyClientData(ClientInfo& client, int index, int arraySize) {
    cout << "\n\tClient Index                : " << index << endl;
    cout << "\tName                        : " << client.fullName << endl;
    cout << "\tAddress                     : " << client.streetAddress << endl;
    cout << "\tCity, State, Zipcode         : " << client.cityStateZip << endl;
    cout << "\tPhone number                : " << client.contactNumber << endl;
    cout << "\tAccount Balance             : $" << fixed << setprecision(2) << client.acctBalance << endl;
    cout << "\tLast Payment Date           : " << client.lastPayment << endl;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "\n\tClient Index: " << index << endl;

    cout << "\tEnter the client's full name: ";
    getline(cin, client.fullName);

    cout << "\tEnter the client's address: ";
    getline(cin, client.streetAddress);

    cout << "\tEnter the client's city, state, and zip: ";
    getline(cin, client.cityStateZip);

    client.contactNumber = getPhoneNumberInput("\tEnter the client's phone number (n-nnn-nnn-nnnn): ");

    client.acctBalance = getBalanceInput("\tEnter the account balance: $");

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    client.lastPayment = getDateInput("\tEnter the last payment date (mm/dd/yyyy): ");
}

//function to display client information
void displayClientData(const ClientInfo& client, int index) {
    cout << "\n\tClient Index                : " << index << endl;
    cout << "\tName                        : " << client.fullName << endl;
    cout << "\tAddress                     : " << client.streetAddress << endl;
    cout << "\tCity, State, Zipcode         : " << client.cityStateZip << endl;
    cout << "\tPhone number                : " << client.contactNumber << endl;
    cout << "\tAccount Balance             : $" << fixed << setprecision(2) << client.acctBalance << endl;
    cout << "\tLast Payment Date           : " << client.lastPayment << endl;
}

//function to search for a client by name
void searchClientByName(ClientInfo clients[], int arraySize) {
    string searchName;
    cout << "\n\tEnter the search name: ";
    getline(cin, searchName);

    bool found = false;
    for (int i = 0; i < arraySize; ++i) {
        if (clients[i].fullName == searchName) {
            displayClientData(clients[i], i);
            found = true;
        }
    }

    if (!found) {
        cout << "\n\tNo client found with the name: " << searchName << endl;
    }
}

// CHALLENGE 10: SPEAKERS BUREAU SEARCH PROGRAM
void challenge10() {
    int presenterCount = getIntInput("\nSpecify the size of the dynamic array to be allocated (1-10): ", 1, 10);
    Presenter* presenters = new Presenter[presenterCount]; //dynamically allocate array of presenters

    char choice;
    do {
        system("cls"); //clear the screen
        cout << "\n\tSearch Functions for the Presenters' Bureau Program";
        cout << "\n\t" << string(80, char(205));
        cout << "\n\tDynamic Array Size: " << presenterCount;
        cout << "\n\tMenu";
        cout << "\n\t" << string(80, char(196));
        cout << "\n\tA. Input Presenter Information";
        cout << "\n\tB. Update Presenter Information";
        cout << "\n\tC. Display ALL Presenters";
        cout << "\n\tD. Search Presenter(s) by topic";
        cout << "\n\tR. Return to Main Menu";
        cout << "\n\t" << string(80, char(205));
        cout << "\n\tOption: ";
        cin >> choice;
        choice = toupper(choice); //convert to uppercase for uniformity
        cin.ignore();  //clear the input buffer

        switch (choice) {
        case 'A': {
            //input presenter information
            for (int i = 0; i < presenterCount; ++i) {
                cout << "\n\tEnter the presenter's full name: ";
                getline(cin, presenters[i].name);

                //validate phone number
                do {
                    cout << "\tEnter the presenter's phone number (n-nnn-nnn-nnnn): ";
                    getline(cin, presenters[i].phoneNumber);
                    if (!isValidPhoneNumber(presenters[i].phoneNumber)) {
                        cout << "\tERROR: Phone number must be in the format n-nnn-nnn-nnnn.\n";
                    }
                } while (!isValidPhoneNumber(presenters[i].phoneNumber));

                cout << "\tEnter the presenter's speaking topic: ";
                getline(cin, presenters[i].topic);

                //validate fee input
                string feeInput;
                do {
                    cout << "\tEnter the presentation fee amount: $";
                    getline(cin, feeInput);
                    if (!isValidFee(feeInput)) {
                        cout << "\tERROR: Fee must be numeric.\n";
                    }
                } while (!isValidFee(feeInput));

                presenters[i].fee = stod(feeInput); //convert to double
            }
            break;
        }
        case 'B': {
            //update presenter information
            int index = getIntInput("\n\tSpecify the presenter's index (0..." + to_string(presenterCount - 1) + "): ", 0, presenterCount - 1);

            //display current information
            cout << "\n\tIndex          : " << index;
            cout << "\n\tName           : " << presenters[index].name;
            cout << "\n\tPhone Number   : " << presenters[index].phoneNumber;
            cout << "\n\tSpeaking Topic : " << presenters[index].topic;
            cout << "\n\tPresentation Fee: $" << fixed << setprecision(2) << presenters[index].fee;

            //clear the input buffer after using cin
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            //enter updated information
            cout << "\n\n\tIndex: " << index;
            cout << "\n\tEnter the presenter's full name: ";
            getline(cin, presenters[index].name);  //get updated presenter name

            //validate phone number for update
            do {
                cout << "\n\tEnter the presenter's phone number (n-nnn-nnn-nnnn): ";
                getline(cin, presenters[index].phoneNumber);
                if (!isValidPhoneNumber(presenters[index].phoneNumber)) {
                    cout << "\tERROR: Phone number must be in the format n-nnn-nnn-nnnn.\n";
                }
            } while (!isValidPhoneNumber(presenters[index].phoneNumber));

            cout << "\n\tEnter the presenter's speaking topic: ";
            getline(cin, presenters[index].topic);  //get updated presenter topic

            //validate fee input for update
            string feeInput;
            do {
                cout << "\tEnter the presentation fee amount: $";
                getline(cin, feeInput);
                if (!isValidFee(feeInput)) {
                    cout << "\tERROR: Fee must be numeric.\n";
                }
            } while (!isValidFee(feeInput));

            presenters[index].fee = stod(feeInput); //convert to double
            break;
        }

        case 'C': {
            //display all presenters
            for (int i = 0; i < presenterCount; ++i) {
                cout << "\n\tIndex          : " << i;
                cout << "\n\tName           : " << presenters[i].name; //separate line for name
                cout << "\n\tPhone Number   : " << presenters[i].phoneNumber;
                cout << "\n\tSpeaking Topic : " << presenters[i].topic;
                cout << "\n\tPresentation Fee: $" << fixed << setprecision(2) << presenters[i].fee;
                cout << "\n";
            }
            break;
        }
        case 'D': {
            //search presenters by topic
            string searchTopic;
            cout << "\n\tEnter a search topic string: ";
            getline(cin, searchTopic);

            bool found = false;
            for (int i = 0; i < presenterCount; ++i) {
                if (presenters[i].topic.find(searchTopic) != string::npos) {
                    found = true;
                    cout << "\n\tIndex          : " << i;
                    cout << "\n\tName           : " << presenters[i].name;
                    cout << "\n\tPhone Number   : " << presenters[i].phoneNumber;
                    cout << "\n\tSpeaking Topic : " << presenters[i].topic;
                    cout << "\n\tPresentation Fee: $" << fixed << setprecision(2) << presenters[i].fee;
                    cout << "\n";
                }
            }

            if (!found) {
                cout << "\n\tNo presenter found for the topic: " << searchTopic;
            }
            break;
        }
        case 'R': //return to main menu
            break;
        default:
            //handle invalid option
            cout << "\n\tERROR: Invalid option.\n";
        }

        system("pause"); //pause the system to allow the user to view results
    } while (choice != 'R'); //repeat the loop until user chooses 'R'

    delete[] presenters;  //free the dynamically allocated array
}

// CHALLENGE 12: COURSE GRADE TRACKER    
void challenge12() {
    int totalStudents = getIntInput("\n\tSpecify the number of students: ", 1, 100);
    int totalTests = getIntInput("\n\tSpecify the number of tests: ", 1, 10);

    CourseStudent* students = new CourseStudent[totalStudents];  //dynamically allocate array of students

    char option;
    do {
        system("cls");
        cout << "\n\tChapter 11 - Challenge 12. Course Grade";
        cout << "\n\t" << string(80, char(205));
        cout << "\n\tDynamic students array size: " << totalStudents;
        cout << "\n\tDynamic test scores array size: " << totalTests;
        cout << "\n\tMenu";
        cout << "\n\t" << string(80, char(196));
        cout << "\n\tA. Input students information";
        cout << "\n\tB. Display all students";
        cout << "\n\tR. Return to main menu";
        cout << "\n\t" << string(80, char(205));
        cout << "\n\tOption: ";
        cin >> option;
        option = toupper(option);

        switch (option) {
        case 'A': {
            //input student information
            for (int i = 0; i < totalStudents; ++i) {
                char inputMethod;
                cout << "\n\tR-random (R) or C-console (M) input test scores? ";
                cin >> inputMethod;
                inputMethod = toupper(inputMethod);
                bool autoGenerate = (inputMethod == 'R');
                enterStudentData(students[i], totalTests, autoGenerate);
            }
            break;
        }
        case 'B': {
            //display all students' information
            for (int i = 0; i < totalStudents; ++i) {
                cout << "\n\tIndex: " << i;
                cout << "\n\tName: " << students[i].fullName;
                cout << "\n\tID Number: " << students[i].studentId;
                cout << "\n\tTest Scores: ";
                for (int j = 0; j < totalTests; j++) {
                    cout << (j + 1) << ") " << fixed << setprecision(2) << students[i].testScores[j] << "  ";
                }
                cout << "\n\tTest Average: " << fixed << setprecision(2) << students[i].avgScore;
                cout << "\n\tLetter Grade: " << students[i].finalGrade;
                cout << "\n";
            }
            break;
        }
        case 'R':
            break;
        default:
            cout << "\n\tError: Invalid option.\n";
        }

        system("pause");
    } while (option != 'R');

    //free dynamic memory
    for (int i = 0; i < totalStudents; i++) {
        delete[] students[i].testScores;  //delete the test score arrays
    }
    delete[] students;  //delete the student array
}


//main function
int main() {
    while (true) {
        system("cls"); //clear the screen
        cout << "\n\tCMPR121: Chapter 11 - Structured Data by Francisco Bumanglag";
        cout << "\n\t" << string(80, char(205));
        cout << "\n\t 3. Corporate Sales Data";
        cout << "\n\t 5. Weather Statistics Modification";
        cout << "\n\t 8. Customer Accounts Management Program (includes extra credit)";
        cout << "\n\t10. Speaker's Bureau Search Program (includes extra credit)";
        cout << "\n\t12. Course Grade Tracker";
        cout << "\n\t" << string(80, char(196));
        cout << "\n\t 0. Exit Program";
        cout << "\n\t" << string(80, char(205));
        cout << "\n";

        switch (getIntInput("\tSelect an option: ", 0, 20)) {
        case 0: exit(0);
        case 3: challenge3(); break;
        case 5: displayWeatherStats(); break;
        case 8: challenge8(); break;
        case 10: challenge10(); break;
        case 12: challenge12(); break;
        default:
            cout << "\n\tERROR: Invalid option selected.\n";
        }

        system("pause");
    }

    return 0; //ends the program
}
