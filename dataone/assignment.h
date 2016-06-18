#ifndef ASSIGNMENT_H
#define ASSIGNMENT_H

#include <stdio.h>
#include <iostream>
#include <list>
#include "date.h"

using namespace std;

enum Status{ assigned = 1, completed = 2, late = 3 };

class assignment{
private:
	Date dueDate;
	string description;
	Date assignedDate;
	Status status;

public:
	assignment();
	assignment(assignment& other);
	const assignment& operator=(const assignment& rhs);

	friend istream &operator>>(istream& in, assignment current);
	friend istream &operator<<(ostream& out, assignment current);
};

#endif