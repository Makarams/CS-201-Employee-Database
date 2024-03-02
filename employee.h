#pragma once
#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include "database.h"

string format(string text) {        // Return a string with a lenght of 15
	string temp = "";
	if (text.length() > 15) {       // if the string is larger than 15 it will convert the 12th to 15th char to ... and delete the rest
		for (int i = 0; i < 12; i++) {
			temp += text[i];    // add the character one by one
		}
		temp += "...";      // replace the remaining character with ...
	}
	else {      // if the string length is less than 15 it will add some additional space
		temp += text;
		for (int i = 0; i < 15 - (int)text.length(); i++) {
			temp += " ";    // add extra space 
		}
	}
	return temp;    // return a string of size 15
}

class program {
public:
	program();
	program(int);
	void main();    // The main program that will be used by the user
	// This is all features that the users can use  
	void display();     // Displaying all the employee information 
	void adding();      // Adding additional entry to the database if it is not full
	void deleting();        // Deleting the first entry inside the database if it is not empty
	void searching();   // Searching for employee by using ID
	void editing();     // Making modification to an employee information
	void readfile();        // Retrieving all the database information stored in the csv file
	void writefile();       // Writing all the current database information to a csv file
	void sortingAscen();    // Sorting the ID based on ascending order
	void sortingDescen();       // Sorting the ID based on descending order

private:
	Employee app;       // This is the database that will be used when the program start
	const int size;     // The max size of the list 
};
program::program() : app(10), size(10) {}       // Initializing the size to 10 and the max size of the database to 10 also
program::program(int size) : app(size), size(size) {}   // Initializing the size and max list size to the given parameter
void program::main() {      // This is the main program that will be used by the users
	while (true) {      // Loop until the user exit the program
		system("cls");
		// This is all the available choice for the users
		cout << "Employee Database" << endl
			<< "1. Display Database" << endl
			<< "2. Add Employee" << endl
			<< "3. Delete Employee" << endl
			<< "4. Search Employee" << endl
			<< "5. Edit Employee" << endl
			<< "6. Save to File" << endl
			<< "7. Read from File" << endl
			<< "8. Sort (Ascending)" << endl
			<< "9. Sort (Descending)" << endl
			<< "10. Exit" << endl
			<< "Enter a choice: ";	// display all the possible choice for user
		int choice;		// used for storing the input
		choice = getInt();    // Get integer from user input
		switch (choice) {   // if the input is not in the switch case it will break and continue with the program
		case 1:
			display();      // Displaying all the employee information 
			break;
		case 2:
			adding();      // Adding additional entry to the database if it is not full
			break;
		case 3:
			deleting();     // Deleting the first entry inside the database if it is not empty
			break;
		case 4:
			searching();   // Searching for employee by using ID
			break;
		case 5:
			editing();     // Making modification to an employee information
			break;
		case 6:
			writefile();       // Writing all the current database information to a csv file
			break;
		case 7:
			readfile();        // Retrieving all the database information stored in the csv file
			break;
		case 8:
			sortingAscen();    // Sorting the ID based on ascending order
			break;
		case 9:
			sortingDescen();       // Sorting the ID based on descending order
			break;
		case 10:    // for when the user exit the program
			system("cls");
			cout << "      Thank you!" << endl;
			system("pause");
			exit(0);
		default:    // Default case
			cout << "Invalid choice." << endl;
		}
		system("pause");
	}
}
void program::display() {	// displaying all the record
	system("cls");      // clear the screen and display using the method from employee
	app.display();		// used the display function of the object
}

void program::deleting() {		// delete the first record in the list
	if (app.size() == 0) {     // If the database is empty then the function exits and display a message
		cout << "Database is empty!" << endl;	// exit the function if the list is empty
		return;
	}
	app.searchID(app.head());   // Display the first node that will be delete 
	app.deleteEntry();      // Deleting the first node
	cout << "Entry has been deleted" << endl;
}

void program::adding() {	// adding a new employee to the list
	system("cls");	// clear the screen
	if (app.size() == size) {       // if the current size of the list is equal to size then the message will display and exits the program
		cout << "The database is full!" << endl;	// exit the function if the list is full
		return;
	}
	// Creating a temporary variable to store the data to be added
	int id, age, salary;
	char gender;
	string firstName, lastName;
	cout << "    Employee ID: ";
	id = getInt();		// get an integer from the user
	while (id <= 0 || id > 99999) {       // Verifying the ID
		system("cls");		// clear the screen
		cout << "Invalid Input!\nID must have at least 1 digits and no higher than 5 digits\n       Employee ID: ";
		id = getInt();      // Get input integer from user
	}
	// If the id is already inside the database then the message will display and exit the program
	if (app.isIn(id)) {		// check if the id has already been used
		cout << "The ID has already been used!" << endl;	// exit the function if the id is found
		return;
	}
	cout << "    Employee First Name: ";
	firstName = getString();	// get firstName
	cout << "    Employee Last Name: ";
	lastName = getString();		// get lastName
	cout << "    Employee Age: ";
	age = getInt();	//	get the age
	while (age < 18 || age > 60) {    // Verifying the age of the employee
		system("cls");	// ask for another input if the age is not correct
		cout << "Invalid Input!\n    Employee Age(18-60): ";
		age = getInt();
	}
	cout << "    Employee Salary: ";
	salary = getInt();	// get the salary
	while (salary < 100 || salary > 9999) {    // Verifying the age of the employee
		system("cls");	// ask for another input if the age is not correct
		cout << "Invalid Input!\n    Employee Salary(100-9999): ";
		salary = getInt();
	}
	cout << "    Employee Gender: ";
	gender = getChar();		// get the character from user
	// if gender is empty or the size of larger than 1 it will convert it to -
	gender = (tolower(gender) == 'f' || tolower(gender) == 'm') ? toupper(gender) : '-';
	app.addEntry(id, format(firstName), format(lastName), age, salary, gender);		// add a new entry to the list
	system("cls");      // Clear the screen	
	cout << "New Employee!" << endl;
	app.searchID(id);       // Display the newly added employee
}

void program::searching() {// Searching through the list to find the employee
	system("cls");
	int id;	 // used for storing input id
	cout << "    Employee ID: ";
	id = getInt();	// get the employee id
	while (id <= 0 || id > 99999) {       // Verifying the ID
		system("cls");	// clear the screen
		cout << "Invalid Input!\n    Employee ID: ";
		id = getInt();      // Get input integer from user
	}
	if (!app.isIn(id)) {    // if the ID is not in the database then the message will display and exit the function
		cout << "The ID is not inside the database!" << endl;
		return;
	}
	app.searchID(id);       // Display the result
}
void program::editing() {   // This method is used to modified existing employee information (except ID)
	// Creating a temporary variable to store the information
	int id, age, salary;
	string firstName;
	string lastName;
	char gender;
	int option;

	system("cls");
	// ask the user to input their option
	cout << "Edit Employee" << endl
		<< "1. Firstname" << endl
		<< "2. Lastname" << endl
		<< "3. Age" << endl
		<< "4. Salary" << endl
		<< "5. Gender" << endl
		<< "6. ALL" << endl
		<< "Option: ";	// display all the posible choice
	option = getInt();	// get user option
	while (option < 1 || option > 6) {
		system("cls");	// ask for another input if the age is not correct
		cout << "Invalid Input!\n    Option(1-6): ";
		option = getInt();
	}
	cout << "Enter employee ID: ";
	id = getInt();  // ask the user to input the ID of the employee to be modified
	if (!app.isIn(id)) {    // if the ID is not in the list then the function exits
		cout << "The ID is not inside the database!" << endl;
		return;
	}
	switch (option) {     // goto the the option that the user select'
	case 1:
		cout << "Enter Firstname: ";
		firstName = getString();	// storing firstName
		firstName = format(firstName);	// format firstName
		break;
	case 2:
		cout << "Enter Lastname: ";
		lastName = getString();		// storing lastName
		lastName = format(lastName);	// format lastName
		break;
	case 3:
		cout << "Enter Age: ";
		age = getInt();		// storing age
		while (age < 18 || age>	60) {	// verify user age
			system("cls");		// if the age is not correct
			cout << "Please enter age: ";	// it will ask for another input
			age = getInt();
		}
		break;
	case 4:
		cout << "Enter Salary: ";
		salary = getInt();
		while (salary < 100 || salary > 9999) {
			system("cls");	// ask for another input if the age is not correct
			cout << "Invalid Input!\n    Employee Age(18-60): ";
			salary = getInt();
		}
		break;
	case 5:
		cout << "Enter Gender: ";
		gender = getChar();		// storing char
		// if the char is not f or m it will convert it to -
		gender = (tolower(gender) == 'f' || tolower(gender) == 'm') ? toupper(gender) : '-';
		break;
	case 6:
		cout << "Enter Firstname: ";
		firstName = getString();	// storing firstName
		firstName = format(firstName);	// format firstName

		cout << "Enter Lastname: ";
		lastName = getString();		// storing lastName
		lastName = format(lastName);	// format lastName

		cout << "Enter Age: ";
		age = getInt();		// storing age
		while (age < 18 || age>60) {	// verify user age
			system("cls");		// if the age is not correct
			cout << "Please enter age again: ";	// it will ask for another input
			age = getInt();
		}

		cout << "Enter Salary: ";
		salary = getInt();
		while (salary < 100 || salary > 9999) {
			system("cls");	// ask for another input if the age is not correct
			cout << "Invalid Input!\n    Employee Age(18-60): ";
			salary = getInt();
		}

		cout << "Enter Gender: ";
		gender = getChar();		// storing char
		// if the char is not f or m it will convert it to -
		gender = (tolower(gender) == 'f' || tolower(gender) == 'm') ? toupper(gender) : '-';	// format gender
		break;
	default:
		return;	// exit the function
	}
	app.searchID(id);   // display the employee current information
	cout << endl << "Has been changed to" << endl;
	app.modified(id, firstName, lastName, age, salary, gender); // make modification to the information if the data is null the changes is not made
	app.searchID(id);   // display the changed information
}
void program::writefile() {
	app.writeCSV("data.csv");   // saving all the data to the database
	system("cls");
	cout << "Data has been save to file" << endl;
}
void program::readfile() {
	app.readCSV("./data.csv");    // get the data from the database
	system("cls");
	cout << "Data has been retrieved" << endl;
}

void program::sortingAscen() {  // sorting the employee by ID (Ascending order)
	app.sortAscen();
	cout << "Database has been sorted in ascending order" << endl;
}

void program::sortingDescen() { // sorting the employee by ID (Descending order)
	app.sortDescen();
	cout << "Database has been sorted in descending order" << endl;
}

#endif