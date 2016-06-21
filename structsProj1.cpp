/*
Name:	Jack Goza, Joshua Ford, Scott Peery
Course:	CS303
Program:	Project 1A
Due Date:	

Description: This is an assignment tracker. It reads in a file as well as takes 
input from a menu based GUI. It will track the number of assignments in three ways. 
1. assigned, 2. completed, 3. completed/uncompleted assignments that are late.
The GUI will allow the user to read in a txt file of assignments and status: this 
includes dates assigned, due, description, and status. The menus will also allow
the user to do the following:
1. add new assignment
2. complete an assignment
3. edit the assignment due date
4. edit the assignment description
5. output number of assignments due
6. output number of assignments late
7. output assignments due in descending order
8. output assignments late in descending order
The output on screen will be as follows:
<date due>, <description>, <date assigned>, <assignment status>
ex: 2-11-2015, linked lists, 2-2-2-15, late

Inputs: Will read in a txt file into a doubly linked list

Outputs: Will output to original txt file, updating and over writing to reflect
changes made. i.e.- new assignments added, assignments completed, assignments late.

Algorithm:

Check that input file exists
Read in file
Check data before adding to lists
Throw exception and handle if bad info
Assign data read to doubly linked list
while reading in data, put in descending order
	this will make searching by date easier as well as adding
	new assignments in the correct order maximizing efficiency
Close file
Do this at opening of program every time to ensure any additions or
	changes are included for the user
Create menu based GUI
	Use switch case to handle choices

Write to file(Update function)
Open file for writing ONLY when output function called
Close file when completed
This will update and overwrite previous file with the lists in descending order,
allowing an O(n) efficiency when imported the next time.

*****SPECIAL NOTE*****
GitHub is not user friendly to noobs, but gives extra credit
Must submit a project report (3-4 pages) with the following information
1. Assumptions, 2. UML class diagram, 3. Efficiency Algorithm, 4. References
Must submit Individual Report


*/
//
//  stuctsProj1.cpp
//  dataone
//
//  Created by John Goza on 6/16/16.
//  Copyright � 2016 JohnGoza. All rights reserved.
//

#include <stdio.h>
#include "assignment.h"
#include <fstream>
#include <list>
#include <iterator>
#include <limits>

using namespace std;

Date inputDate(){
	Date date;

	string temp;
	while (true){
		
		try {
			getline(cin, temp);
			Date date(temp);
			if (date.valid_date(date.getDay(), date.getMonth(), date.getYear())){
				return date;
			}
			else{
				throw exception();
			}
		}
		catch (exception){
			cout << "Please enter a valid date(dd-mm-yyyy): ";
		}
	}
}

assignment getAssn(){
	assignment newAssn;
	string temp;
	char tempC;

	cout << "Due Date: (dd-mm-yyyy); ";
	newAssn.setDueDate(inputDate());

	cout << endl << "Description: ";
	getline(cin, temp);
	newAssn.setDescription(temp);

	do{
		cout << endl << "Assigned Date: ";
		newAssn.setAssignedDate(inputDate());
		if (newAssn.getDueDate() <= newAssn.getAssignedDate())
			cout << "Invalid Assigned Date";

	} while (newAssn.getDueDate() <= newAssn.getAssignedDate());
		
	do{
		cout << endl << "Status: " << endl << "1. assigned\n2, completed\n3. late\n";
		cin >> tempC;
		getline(cin, temp);
	}while (temp != "" || (int)tempC < 49 || int(tempC > 51));
	newAssn.setStatus((int)tempC - 48);

	return newAssn;
}

void addAssn(list<assignment> List){
	string Assnstr, Duestr, Decstr;

	cout << "Enter assignment date in form 00/00/0000 : \n";
	cin >> Assnstr;
	cout << "\nEnter assignment due date in form 00/00/0000 : \n";
	cin >> Duestr;
	cout << "\nEnter assignment description:\n";
	cin >> Decstr;
	
	Date tempAssn(Assnstr);
	Date tempDue(Duestr);
	
	if (tempDue <= tempAssn){
		cout << "Due date is less than or equal to assigned date";
		return;
	}
	
	assignment Assn;
	Assn.setAssignedDate(tempAssn);
	Assn.setDueDate(tempDue);
	Assn.setDescription(Decstr);
	
	list <assignment>::iterator it;
	for (it = List.begin(); it != List.end(); it++){
		if (*it == Assn){
			cout << "Assignment already exists";
			return;
		}
	}
	List.push_back(Assn);
} // This is redundant

void sort(list<assignment> L1, list<assignment> L2, list<assignment> L3){
	L1.sort();
	L2.sort();
	L3.sort();
}

void markComplete(list<assignment> Assn, list<assignment> Comp, Date assnDate){
	list <assignment>::iterator it;
	for (it = Assn.begin(); it != Assn.end(); it++){
		if(it->getDueDate() == assnDate){
			assignment Temp = *it;
			it = Assn.erase(it);
			Comp.push_back(Temp);
			if 
			return;
		}
	}
	cout << "Assignment not found.\n";
	return;
}

void printAssignments(list<assignment> Assn, list<assignment> Comp){
	cout << "Completed assignments:\n";
	list <assignment>::iterator it;
	string dateString;
	for (it = Assn.begin(); it != Assn.end(); it++){
		//dateString = it->getAssignedDate();
		cout << dateString << ' ' << it->getDescription() << ' ';
	}
	
}

void markComplete(list<assignment> Assn, list<assignment> Comp, Date givenDate){
	
}

int main(){
	SetConsoleTitle(TEXT("Assignment System, Proj1A, BY: J. Goza, J. Ford, S. Peery)); // set console title
	
	list<assignment> Assignments;
	list<assignment> Assigned;
	list<assignment> Completed;

	assignment temp;

	ifstream in("assignment.txt");

	while (in.good()){
		in >> temp;
		Assignments.push_back(temp);
		if (temp.getStatus() == assigned){
			Assigned.push_back(temp);
		}
		else{
			Completed.push_back(temp);
		}
	}
	
	bool menuBool = false; bool runAgain = true;
	int menuInput = 0;
	
	cout << "Welcome to the menu based assignment system!\n";
	
	while(runAgain){
		menuBool = false;
	
		while (!menuBool){
	
		cout << "\n"<< "What would you like to do?\n";
		cout << "1. Display assignments\n"
		<< "2. Add assignment to workload\n"
		<< "3. Edit due date for assignment\n"
		<< "4. Edit assignment description\n"
		<< "5. Log assignment completion\n"
		<< "6. Display number of late assignments\n"
		<< "7. Save    8. Exit\n\n";
		
		cin >> menuInput;
		if (cin.good()){
			menuBool=true;
			break;
		}
		else{
			cout << "Please limit input to integer coressponding to your choice\n\n";
			cin.clear(); cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	}
	
	switch(menuInput){
		case 1 : printAssignments(Assigned, Completed); break;
		case 2 : addAssn(Assigned); break;
		case 3 :
			
		case 5 :
		case 7 : printAssignments(Assigned, Completed);
		case 8 : cout << "Goodbye!"; runAgain = false; break;
	}
	}

	
	system("pause");
	return 0;
}
