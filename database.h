#pragma once
#ifndef DATABASE_H
#define DATABASE_H

#include "doubleList.h"
#include <fstream>
#include<iomanip>
#include <string>
#include<chrono>
#include<ctime>

void trim(string& text) {     // remove all the space at the end and the begining of the string
	for (int i = 0; i < text.size(); i++) {     // left trim
		if (text[i] != ' ') break;      // if the next character is not a space break the loop
		text.erase(0, 1);   // remove the front character
	}

	for (int i = text.size() - 1; i >= 0; i--) {    // right trim
		if (text[i] != ' ') break;    // if the next character is not a space break the loop
		text.pop_back();      // remove a character at the back
	}
}

string getString() {    // return a line of string
	string line;        // string used for storing inpu
	getline(cin, line);     // get the entire input line
	trim(line);     // remove all the spacing at the front and the back and not the middle
	return line;    // return the entire line
}

int getInt() {      // return an integer
	string line;    // string used for storing input
	line = getString();	// assign getString to line
	if (line.size() == 0) return 0;	// if the line is empty return 0
	for (int i = 0; i < line.size(); i++)	// checking if the string list not convertable
		if ((line[i] < '0' || line[i]> '9') && line[i] != '-')
			return 0;   // return 0 if the input is not an integer

	return stoi(line);  // return an integer
}

char getChar() {        // return a char 
	string line;    // string used for storing input
	line = getString();	// assign getString to line
	if (line.size() != 1) return ' ';    // return a space if the line is length is longer than 1
	return line[0]; // return the first character of the line
}

/**
 * 	This class is created for accessing and modifying
 * 	the data of a database with the help of some
 * 	additional function inside the class. This class
 * 	used the concept of doubleList class
 *
 */
class Employee {
public:
	Employee();    // Initializing an object with no parameter
	Employee(int); // Initializing an object with a parameter
	void display(); // Method used to display all the infomation inside the linked list
	void addEntry(int, string, string, int, int, char); // Adding additional node to the list at the back
	void deleteEntry();  // Removing the first node inside the list
	void searchID(int);  // Searching through the list to find the specified ID
	void modified(int, string, string, int, int, char);   // Make modification to the node with a specified ID
	void readCSV(string);  // Adding node with the data from a csv file
	void writeCSV(string); // Delete the data inside the csv file and add infomation from the list to the csv file
	void sortAscen();      // Sorting the array in ascending order (by ID)
	void sortDescen();     // Sorting the array in descending order (by ID)
	int size() { return __id.size(); }		// return the size of the list
	int head() { return __id.head()->getData(); }	// return the first node in the list
	bool isIn(int id) {		// Retrun true is the parameter ID is inside the list and false otherwise
		return __id.count(id) != 0;	// Return false after the data is not found
	}
private:
	const int maxSize; // Creating a const variable that will store the maximum
	// size of the array
// The information in each category
	doubleList<int> __id;
	doubleList<string> __firstName;
	doubleList<string> __lastName;
	doubleList<int> __age;
	doubleList<int> __salary;
	doubleList<char> __gender;
	// The iterator for moving through the list
	doubleNode<int>* idHead = new doubleNode<int>;
	doubleNode<string>* firstNameHead = new doubleNode<string>;
	doubleNode<string>* lastNameHead = new doubleNode<string>;
	doubleNode<int>* ageHead = new doubleNode<int>;
	doubleNode<int>* salaryHead = new doubleNode<int>;
	doubleNode<char>* genderHead = new doubleNode<char>;
	// Additional function for the class that are not for user to use
	void start();		// start all the node at the head of each list
	void next();		// move all the node to the next node in each list
	void prev();		// move all the node to the prevous node in each list
	void swap(int, int);		// swapping two node value with their index
	void bubble(bool, bool);		// perform a bubble sort
	void insertion(bool, bool);		// perform an insertion sort
	void selection(bool, bool);		// perform an selection sort
};

Employee::Employee() : maxSize(10) {} // Initializing the size of the list to 10
Employee::Employee(int size) : maxSize(size) {} // Initializing the size of the list to the argument passed

void Employee::start() {		// Initializing all the iterator nodes to the head of their respective list
	idHead = __id.head();
	firstNameHead = __firstName.head();
	lastNameHead = __lastName.head();
	ageHead = __age.head();
	salaryHead = __salary.head();
	genderHead = __gender.head();
}
void Employee::next() {			// Moving the iterator nodes to their next node
	idHead = idHead->getNext();
	firstNameHead = firstNameHead->getNext();
	lastNameHead = lastNameHead->getNext();
	ageHead = ageHead->getNext();
	salaryHead = salaryHead->getNext();
	genderHead = genderHead->getNext();
}

void Employee::prev() {			// Moving the iterator nodes to their prevous node
	idHead = idHead->getPrev();
	firstNameHead = firstNameHead->getPrev();
	lastNameHead = lastNameHead->getPrev();
	ageHead = ageHead->getPrev();
	salaryHead = salaryHead->getPrev();
	genderHead = genderHead->getPrev();
}

void Employee::swap(int x, int y) {		// swapping two node value with their index of each list
	__id.swap(x, y);
	__firstName.swap(x, y);
	__lastName.swap(x, y);
	__age.swap(x, y);
	__salary.swap(x, y);
	__gender.swap(x, y);
}
// This method takes 5 parameter that will be used to add the information inside
// the list
void Employee::addEntry(int id, string firstName, string lastName, int age, int salary, char gender) {
	if (__id.size() == maxSize) // Exit the function if the array is full
		return;
	// Adding a new entry to the list
	__id.push_back(id);
	__firstName.push_back(firstName);
	__lastName.push_back(lastName);
	__age.push_back(age);
	__salary.push_back(salary);
	__gender.push_back(gender);
}
void Employee::deleteEntry() { // Used the method in the linked list to pop the
	// first node in the list
	if (__id.size() == 0)
		return; // Exit the function if the list is empty
	// Here we remove the first node in the list
	__id.pop_front();
	__firstName.pop_front();
	__lastName.pop_front();
	__age.pop_front();
	__salary.pop_front();
	__gender.pop_front();
}
void Employee::display() {
	system("cls"); // clear the screen
	string line = "+-------+----------------+----------------+------+--------+--------+";
	// display the header for the table
	cout << line << endl
		<< "|   ID  |   First Name   |   Last Name    | Age  | Salary | Gender |" << endl
		<< line << endl;
	start();

	// iterate through the nodes and display their data
	while (idHead) {
		cout << "| " << left << setw(6) << idHead->getData() << "| " << firstNameHead->getData()
			<< "| " << lastNameHead->getData() << "|  " << ageHead->getData() << "  | " << left << setw(7) << salaryHead->getData()
			<< "|  " << genderHead->getData() << "     |\n";		// cout the entire line of each entry
		next();// move the current node pointers to the next node
	}
	cout << line << endl;
}
void Employee::searchID(int id) {
	string line = "+-------+----------------+----------------+------+--------+--------+";
	start();
	while (idHead) {		// Iterating through the list to find the specific id we're looking for
		if (idHead->getData() == id) {		// To check if the parameter id has the same value as the one in the list
			cout << line << endl	// display the header for the table
				<< "|   ID  |   First Name   |   Last Name    | Age  | Salary | Gender |" << endl
				<< line << endl;

			cout << "| " << left << setw(6) << idHead->getData() << "| " << firstNameHead->getData() << "| " <<
				lastNameHead->getData() << "|  " << ageHead->getData() << "  | " << left << setw(7) << salaryHead->getData()
				<< "|  " << genderHead->getData() << "     |\n";	// cout the entire line of each node
			cout << line << endl;
			return;		// exit the function after the node has been found
		}
		next();		// move the current node pointers to the next node
	}
	cout << "Not found" << endl;
}
void Employee::readCSV(string path) {
	// Removing all the existing information of the employee in the database
	__id.clear();
	__firstName.clear();
	__lastName.clear();
	__age.clear();
	__salary.clear();
	__gender.clear();
	ifstream read;
	read.open(path, ios::in); // Opening the file with the specified path
	string line, delim = ",", word;
	size_t ctr = 0;
	while (getline(read, line) && __id.size() != maxSize) { // Reading each line in the file
		for (int i = 0; i <= 4; i++) {
			ctr = line.find(delim);
			word = line.substr(0, ctr); // Making a substring for each iteration
			line.erase(0, ctr + delim.length());	// Deleting the substring 
			switch (i) { // This switch will make discision on which list to add to
			case 0:
				__id.push_back(stoi(word));		// Converting from string to integer
				break;
			case 1:
				__firstName.push_back(word);	// add the first name to the list
				break;
			case 2:
				__lastName.push_back(word);		// add the last name to the list
				break;
			case 3:
				__age.push_back(stoi(word));		// Converting from string to integer
				break;
			case 4:
				__salary.push_back(stoi(word));		// add the salary to the list
				break;
			}
		}
		__gender.push_back(line[0]);		// add the gender to the list
	}
	read.close(); // Close the opened file
}
void Employee::writeCSV(string path) {
	ofstream write;
	write.open(path, ios::out | ios::trunc); // Opening a file as write and delete
	// all the data inside the file
	start();
	while (idHead) { // Inserting data for each iteration
		write << idHead->getData() << ',' << firstNameHead->getData() << ','	// Writing all the data to a csv file with comma added after each piece of infomation
			<< lastNameHead->getData() << ',' << ageHead->getData() << ','
			<< salaryHead->getData() << ',' << genderHead->getData() << endl;

		next();		// Moving to the next node
	}
	write.close(); // Closing the file
}
void Employee::modified(int id, string firstName, string lastName, int age, int salary, char gender) {
	start(); // Placing the iteration at the head
	while (idHead) {
		if (idHead->getData() == id) { // Setting a new data for every category except the ID
			// If any of the data is NULL or empty then that data will remain unchange
			if (firstName.length() != 0)
				firstNameHead->setData(firstName);
			if (lastName.length() != 0)
				lastNameHead->setData(lastName);
			if (age)
				ageHead->setData(age);
			if (salary)
				salaryHead->setData(salary);
			if (gender)
				genderHead->setData(gender);
			return;
		}
		next();		// Moving to the next node
	}
}

void Employee::sortAscen() { // Sorting the list in ascending order using bubble
	if (__id.size() == 1 || __id.empty()) return;
	int option;		// option is for checking and len is for storing the number of node in the list
	string getID = "1. Sort by id\n2. Sort by salary\nOption: ",	// mcq for either id or salary
		getSort = "1. Bubble Sort\n2. Insertion Sort\n3. Selection Sort\nOption: ";	// mcq for either bubble sort or insertion sort
	bool sort;		// check the sorting method
	cout << getID;		// display the mcq
	option = getInt();	// get the option
	while (option != 1 && option != 2) {		// incorrect input
		cout << "Invalid input\n" << getID;		// repeat the process
		option = getInt();
	}
	sort = (option == 1) ? true : false;		// id(true) or salary(false)
	system("cls");		// clear the screen
	cout << getSort;	// display the mcq
	option = getInt();	// get the option
	while (option != 1 && option != 2 && option != 3) {		// incorrect input
		cout << "Invalid input\n" << getSort;
		option = getInt();
	}
	system("cls");		// clear screen

	auto now = chrono::system_clock::now();		// start the timer

	switch (option) {	// check the sorting method
	case 1:
		bubble(sort, true);
		break;
	case 2:
		insertion(sort, true);
		break;
	case 3:
		selection(sort, true);
		break;
	}
	auto end = chrono::system_clock::now();		// stop the timer

	chrono::duration<double> elapsed_seconds = end - now;		// get the result
	cout << "finished sorting in: " << elapsed_seconds.count() * 1000 << "ms\n";		// display the result
}
void Employee::sortDescen() { // Sorting the list in descending order using
	if (__id.size() == 1 || __id.empty()) return;
	int option;		// option is for checking and len is for storing the number of node in the list
	string getID = "1. Sort by id\n2. Sort by salary\nOption: ",	// mcq for either id or salary
		getSort = "1. Bubble Sort\n2. Insertion Sort\n3. Selection Sort\nOption: ";	// mcq for either bubble sort or insertion sort
	bool sort;		// check the sorting method
	cout << getID;		// display the mcq
	option = getInt();	// get the option
	while (option != 1 && option != 2 && option != 3) {		// incorrect input
		cout << "Invalid input\n" << getID;		// repeat the process
		option = getInt();
	}
	sort = (option == 1) ? true : false;		// id(true) or salary(false)
	system("cls");		// clear the screen
	cout << getSort;	// display the mcq
	option = getInt();	// get the option
	while (option != 1 && option != 2 && option != 3) {		// incorrect input
		cout << "Invalid input\n" << getSort;
		option = getInt();
	}
	system("cls");		// clear screen

	auto now = chrono::system_clock::now();		// start the timer

	switch (option) {	// check the sorting method
	case 1:
		bubble(sort, false);
		break;
	case 2:
		insertion(sort, false);
		break;
	case 3:
		selection(sort, false);
		break;
	}
	auto end = chrono::system_clock::now();

	chrono::duration<double> elapsed_seconds = end - now;
	cout << "finished sorting in: " << elapsed_seconds.count() * 1000 << "ms\n";
}

void Employee::bubble(bool id, bool ascen) {

	int len = __id.size();

	for (int i = 0; i < len; i++) {		// iterate through the list
		start();		// Assigning all the iterator at the head of the list
		for (int j = 1; j < len - i; j++) {
			if (id) {		// sort by id
				// Swap the current node and the next node if the condition is met
				if ((ascen) ? idHead->getData() > idHead->getNext()->getData() : idHead->getData() < idHead->getNext()->getData()) {
					swap(j, j + 1);		// swap the 2 node
				}
			}
			else {		// sort by salary
				if ((ascen) ? salaryHead->getData() > salaryHead->getNext()->getData() : salaryHead->getData() < salaryHead->getNext()->getData()) {
					swap(j, j + 1);		// swap the 2 node
				}
			}
			next();		// Moving the iterator to the next node
		}
	}
}

void Employee::insertion(bool id, bool ascen) {
	int  key;		// key is used to store the data for insertion sort
	if (id) {		// id
		for (int i = 2; i <= __id.size(); i++) {		// loop through the list
			key = __id.valueAt(i);	// store the data

			for (int k = i-1; k > 0; k--) {		// iterating in reverse 
				// check if it in ascending or descending order
				if ((ascen) ? key < __id.valueAt(k) : key > __id.valueAt(k)) {
					swap(k + 1, k);		// swap the 2 node
				}
				else break;		// break out of the loop if the element is already in place
			}
		}
	}
	else {	// salary
		for (int i = 2; i <= __id.size(); i++) {		// loop through the list
			key = __salary.valueAt(i);	// store the data

			for (int k = i-1; k > 0; k--) {		// iterating in reverse 
				// check if it in ascending or descending order
				if ((ascen) ? key < __salary.valueAt(k) : key > __salary.valueAt(k)) {
					swap(k + 1, k);		// swap the 2 node
				}
				else break;		// break out of the loop if the element is already in place
			}
		}
	}
}

void Employee::selection(bool id, bool ascen) {
	int len = __id.size(), min, ctr;	// len is used to store the lenght of the list, min is used to store the minimum value of each iteration
	// ctr is used for storing the location of the min value
	if (id) {		// sort by id
		for (int i = 1; i <= len; i++) {	// start the iteration
			ctr = 0;
			min = __id.valueAt(i);		// get the data
			for (int j = i + 1; j <= len; j++) {		// loop through the list to find the minimum value and it location
				// find the condition for swapping
				if ((ascen) ? min > __id.valueAt(j) : min < __id.valueAt(j)) {	// if the condition is true 
					min = __id.valueAt(j);	// store the min value
					ctr = j;	// store the location
				}
			}
			if (ctr != 0)
				swap(i, ctr);	// start the swapping process
		}
	}
	else {		// sort by salary
		for (int i = 1; i < len; i++) {	// start the iteration
			ctr = 0;
			min = __salary.valueAt(i);		// get the data
			for (int j = i + 1; j <= len; j++) {		// loop through the list to find the minimum value and it location
				// find the condition for swapping
				if ((ascen) ? min > __salary.valueAt(j) : min < __salary.valueAt(j)) {	// if the condition is true 
					min = __salary.valueAt(j);	// store the min value
					ctr = j;	// store the location
				}
			}
			if (ctr != 0)
				swap(i, ctr);	// start the swapping process
		}
	}
}
#endif // !DATABASE_H



