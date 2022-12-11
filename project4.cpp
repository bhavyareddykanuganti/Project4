// Project 4
// Bhavya Reddy Kanuganti
// Fall 2022
// Computing Structures
#include <iostream>
#include <list>     // stl list library
#include <iterator> // to iterate through the list
using namespace std;
class GL; // prototype for class GL
// node class to store char and generalized linked list called down
class node
{
protected:
	char* charVariable; // single char variable pointer (not an array)
	GL* down;           // going down to the next level
public:
	node(); // default constructor
	// setters
	void setCharVariable(char var);
	void setDown(GL* d);
	// getters
	char* getChar();
	GL* getDown();
	// display
	void displayChar();
};
node::node()//default constructor
{
	charVariable = NULL;//initialising char variable to null
	down = NULL;//initialising down to null
}
//setters
void node::setCharVariable(char var)//char variable setter
{
	if (var == '\0')//if given var is null
		charVariable = NULL;//setting value to null
	else
	{
		charVariable = new char(var);//if not null assigning the variable
		//*charVariable = var;
	}
}
void node::setDown(GL* d)//setting down pointer
{
	down = d;
}
//getters
char* node::getChar()//returns the char variable
{
	return charVariable;
}
GL* node::getDown()//returns down
{
	return down;
}
//display function
void node::displayChar()
{
	cout << *charVariable << " ";//displaying the char variable
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// class Generalized List
class GL
{
protected:
	list<node> head; // head of the list - each object is of type node class
public:
	GL();                                         // default constructor
	void buildGL(string l);                       // to build the generalized list
	bool findCharInExpression(char findThisChar); // given a char, find it in a given expression
	int heightOfGL();                             // return the height of the GL using the GL
	void searchDuplicates();                      // print all the duplicates in the GL
	void display();                               // display list
};
GL::GL()//default constructor
{
}
void GL::buildGL(string l)//to build the generalized list
{
	node* tempNode = new node;//temporary node

	int S = 0;//intialising the level to 0
	bool f = false;
	for (int i = 0; i < l.size(); i++)//looping through the size of string
	{
		if (l[i] >= 'a' && l[i] <= 'z' && S == 0)//if it is a character in level 0
		{
			//tempNode = new node;//create a temp node
			tempNode->setCharVariable(l[i]);//setting variable
			tempNode->setDown(NULL);//setting down to null
			head.push_back(*tempNode);//using push back to push to head
		}
		else if (l[i] == '(' && S == 0)//if it has open brace in level 0
		{
			GL* tempGL;//temporaray gl pointer variable
			f = true;
			string sub;//sub string
			size_t start = l.find_first_of("("),//to find the corresponding open and close paranthesis
				end = l.find_last_of(")");
			if (start != string::npos && end != string::npos)
				sub = l.substr(start + 1, end - start - 1);//getting substring
			//cout << sub<<endl;
			tempNode->setCharVariable('\0');//setting variable to null
			tempGL = new GL;//creating temp gl
			tempGL->buildGL(sub);//recursively calling using substring
			tempNode->setDown(tempGL);//setting down pointer
			head.push_back(*tempNode);//push back to head
			S++;
		}
		else if (l[i] == ')')
			S--;//decrementing level if ')' is found
		else if (l[i] == '(')
			S++;//incrementing the level'(' is found
	}
}
int h = 1;//initialising to 1
int GL::heightOfGL()
{

	//cout << "outside for"<<endl;
	for (list<node>::iterator itr = head.begin(); itr != head.end(); ++itr)//iterating through head
	{
		//cout << "inside"<<endl;
		if (itr->getChar() == NULL && itr->getDown() != NULL)//checking for next level
		{
			//cout << "if inside"<<endl;
			return h + (itr->getDown()->heightOfGL());//recursive call for heightOfGL
		}
	}
	//cout << "above return" << endl;
	return h;//returning h
}
bool GL::findCharInExpression(char findThisChar)//find
{
	for (list<node>::iterator itr = head.begin(); itr != head.end(); ++itr)//iterating through head
	{
		//cout << "inside for"<<endl;
		if (itr->getChar() != NULL)//checking if the character is present
		{
			//cout << "inside if" << endl;
			if (*(itr->getChar()) == findThisChar) //checking if the charcter matches
				return true;//returns true if the above condition is correct
		}
	}
	for (list<node>::iterator itr = head.begin(); itr != head.end(); ++itr)//iterating through head
	{
		if (itr->getDown() != NULL)//checking if down is not null
		{
			//cout << "inside else" << endl;
			return itr->getDown()->findCharInExpression(findThisChar);//recursive call for finding char in expression
		}
	}
	return false;//return false if character is not present
}
list<char> dups;//global variable to store duplicate characters

void GL::searchDuplicates()
{
	GL* temp = NULL;
	list<char> tempchar;//temporary list for characters
	for (list<node>::iterator itr = head.begin(); itr != head.end(); ++itr)//iterating through head
	{
		if (itr->getChar() != NULL)//if the charcter variable is present
		{
			for (list<char>::iterator itrTemp = tempchar.begin(); itrTemp != tempchar.end(); ++itrTemp)//iterating through temporary list for characters
			{
				if (*itrTemp == *(itr->getChar()))//checking if the variable is present
					dups.push_back(*itrTemp);//if it is present then push_back to dups
			}
			tempchar.push_back(*(itr->getChar()));//push_back to temporary charcter list
		}
		else if (itr->getDown() != NULL)//checking for the further levels
			temp = itr->getDown();//if there are other levels present the assigning it to GL* temp
	}
	//list<node>::iterator itr = head.begin();
	if (temp != NULL)//checking if other levels are present
	{
		for (list<char>::iterator itrdTemp = tempchar.begin(); itrdTemp != tempchar.end(); ++itrdTemp)//iterating through temporary char list
		{
			if (temp->findCharInExpression(*itrdTemp))//calling the findCharInExpression to check if character is present or not
				dups.push_back(*itrdTemp);//if present pushing it to dups
		}
		temp->searchDuplicates();//recursive call for search duplicates
	}
}

void GL::display()//display function
{
	for (list<node>::iterator itr = head.begin(); itr != head.end(); ++itr)//iterating through head
	{
		if (itr->getChar() != NULL)//checking if character is present
			itr->displayChar();//if present the display the character
		else if (itr->getChar() == NULL && itr->getDown() != NULL)// check for the further levels
		{
			//cout << "inside";
			itr->getDown()->display();//call display() recursively
		}
	}
}
int main()
{
	int numExpressions; // number of expressions
	char option;        // command from the input file
	// read the number of expressions given
	cin >> numExpressions;
	cout << "Number of expressions: " << numExpressions << endl;
	cout << endl;
	GL* expressions = new GL[numExpressions]; // an array of expressions / an array of GL objects
	string gll;
	int exp;
	char c, c1, c2;

	for (int i = 0; i < numExpressions; i++)
	{
		cin >> gll;
		expressions[i].buildGL(gll);
	}
	// read one line/expression at a time and call the buildGL method for each expression[i]
	// read in and process all the options using switch case
/*expressions[1].findPath('b');
if (path.size() != 0)
{
	for (list<char>::iterator itr = path.begin(); itr != path.end(); ++itr)
	{
		cout << *itr;//printing duplicate variables if duplicates are found
		cout << " ";
	}
}*/
	while (cin >> option)
	{
		switch (option)
		{
		case 'D'://Method to display all expressions
		{
			cout << "Displaying all expressions:" << endl;
			for (int i = 0; i < numExpressions; i++)
			{
				cout << "Expression " << i << " : ";
				expressions[i].display();
				cout << endl;
			}
			cout << endl;
			break;
		}
		case 'F'://find the character variable in given expression
		{
			cin >> exp >> c;
			//cin >> c;
			cout << "Find " << c << " in " << exp << ": ";
			if (expressions[exp].findCharInExpression(c) == true)
				cout << "found" << endl;
			else if (expressions[exp].findCharInExpression(c) == false)
				cout << "not found" << endl;
			//cout << endl;
			cout << endl;
			break;
		}
		case 'H'://height of the given expression
		{
			cin >> exp;
			cout << "Height of expression " << exp << " : ";
			cout << expressions[exp].heightOfGL() - 1 << endl;
			cout << endl;
			break;
		}
		case 'U'://finding the duplicates in the expression
		{
			cin >> exp;
			cout << "Duplicates in " << exp << " : ";
			expressions[exp].searchDuplicates();
			if (dups.size() != 0)
			{
				for (list<char>::iterator itr = dups.begin(); itr != dups.end(); ++itr)
				{
					cout << *itr;//printing duplicate variables if duplicates are found 
					cout << " ";
				}
			}
			else if (dups.size() == 0)
				cout << "None";//printing none if duplicates are not found
			cout << endl;
			cout << endl;
			break;
		}
		default:

		{
			cout << "Command not recognized" << endl;
			cout << endl;
			break;
		}
		}
	}

	return 0;
} // main
