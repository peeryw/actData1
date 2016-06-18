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

void addAssn(list<assignment> List, assignment Assn){
	Date tempAssn, tempDue;
	tempAssn = Assn.getAssignedDate();
	tempDue = Assn.getDueDate();
	if (tempDue <= tempAssn){
		cout << "Due date is less than or equal to assigned date";
		return;
	}
	list <assignment>::iterator it;
	for (it = List.begin(); it != List.end(); it++){
		if (*it == Assn){
			cout << "Assignment already exists";
			return;
		}
	}
	List.push_back(Assn);
}

void sort(list<assignment> L1, list<assignment> L2, list<assignment> L3){
	L1.sort();
	L2.sort();
	L3.sort();
}

void findAssnByDate(list<assignment> Assn, list<assignment> Comp, Date assnDate){
	list <assignment>::iterator it;
	for (it = Assn.begin(); it != Assn.end(); it++){
		if(it->getDueDate() == assnDate){
			assignment Temp = *it;
			it = Assn.erase(it);
			Comp.push_back(Temp);
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

int main(){
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
	
	bool menuBool = false;
	int menuInput;
	while (!menuBool){
		
		cout << "welcome to the menu based assignment system!\n";
		cout << "What would you like to do?\n";
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
		case 1 : printAssignments(Assigned, Completed);
		case 2 : addAssn(Assigned, <#assignment Assn#>);
	}
	

	
	system("pause");
	return 0;
}
