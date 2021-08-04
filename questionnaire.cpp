#include <iostream>
#include <fstream>
#include <cstdlib>
#include <conio.h>
#include <string>
#include <io.h>
#include <windows.h>
#include <direct.h>  
#include <stdio.h>
#include <ctime>

using namespace std;

const unsigned char CTRL_KEY = 0XE0;
const unsigned char LEFT = 0X4B;
const unsigned char RIGHT = 0X4D;
const unsigned char DOWN = 0X50;
const unsigned char UP = 0X48;
const unsigned char ENTER = 13;
const unsigned char ESC = 0X1B;
const unsigned char DEL = 0X7F;
const unsigned char F1 = 0X3B;
const unsigned char BACKSPACE = 8;

void readFile();
void writeFile();
void printInduction();
void selection();
void printQuestion(int);
void printAnswer(int);
void setProblem(int);
void editProblem(int);
void printProblem(int);
void cls();
void deleteProblem(int);
void practiceProblem(int);
void addProblem();
void printEditInduction();
void printPracticeProblemInduction();
void printSegmentLine();
void addProblemInduction();

int pNum = 0;
bool returnFlag = false;

class problem
{
public:
	void setProblemNumber(int num);
	void setQuestion(string que);
	void setAnswer(string ans);
	string getAnswer();
	string getQuestion();
	int getProblemNumber();

private:
	int problemNumber;
	string question;
	string answer;
};
void problem::setProblemNumber(int num)
{
	problemNumber = num;
}
void problem::setQuestion(string que)
{
	question = que;
}
void problem::setAnswer(string ans)
{
	answer = ans;
}
int problem::getProblemNumber()
{
	return problemNumber;
}
string problem::getAnswer()
{
	return answer;
}
string problem::getQuestion()
{
	return question;
}
problem pro[1000];

int main()
{
	readFile();
	printInduction();
	selection();
	//printQuestion(0);
	system("pause");
	return 0;
}

void readFile()
{
	ifstream infile;
	infile.open("mydata.dat");
	if (!infile)
	{
		return;
	}
	infile >> pNum;
	int n;
	string a, b;
	for (int i = 0; i < pNum; i++)
	{
		infile >> n >> a >> b;
		pro[i].setProblemNumber(n);
		pro[i].setAnswer(a);
		pro[i].setQuestion(a);
	}
	return;
}
void writeFile()
{
	ofstream outfile;
	outfile.open("mydata.dat");
	outfile << pNum << endl;
	for (int i = 0; i < 1000; i++)
	{
		outfile << pro[i].getProblemNumber() << " " << pro[i].getQuestion() << " " << pro[i].getAnswer() << endl;
	}
	return;
}
void printInduction()
{
	cout << "a = Add Problem" << endl;
	cout << "e = Edit Problem" << endl;
	cout << "p = Practice" << endl;
	printSegmentLine();
	return;
}
void selection()
{
	while (1)
	{
		cls();
		printInduction();
		string input;
		cin >> input;
		if (input == "a" || input == "A") //addProblem
		{
			addProblem();
		}
		else if (input == "e" || input == "E")
		{
			returnFlag = false;
			editProblem(0);
		}
		else if (input == "s" || input == "S") // save
		{
			writeFile();
		}
		else if (input == "p" || input == "P")
		{
			practiceProblem(0);
		}
	}
}
void addProblem()
{
	cls();
	addProblemInduction();
	int input = _getch();
	if (input == ESC)
		selection();
	if (input == ENTER)
	{
		cls();
		cout << "Add New Problem " << endl;
		printSegmentLine();
		setProblem(pNum);
		pNum++;
		cout << "Complete!!! " << endl;
	}
	addProblem();
}
void printQuestion(int i)
{
	string question = pro[i].getQuestion();
	int n = pro[i].getProblemNumber();
	cout << n << "." << question << endl;
}
void printAnswer(int i)
{
	string answer = pro[i].getAnswer();
	cout << "ans: " << answer << endl;
}
void printProblem(int i)
{
	printQuestion(i);
	printAnswer(i);
	return;
}
void setProblem(int i)
{
	string ques, ans;
	cout << "question: ";
	getline(cin, ques);
	cout << "answer: ";
	getline(cin, ans);

	pro[i].setProblemNumber(i);
	pro[i].setQuestion(ques);
	pro[i].setAnswer(ans);
	writeFile();
	return;
}
void editProblem(int i)
{
	while (1)
	{
		cls();
		printEditInduction();
		printProblem(i);
		string a, b;
		int input = _getch();
		if (input == ENTER)
		{
			cout << endl << "New Question: ";
			getline(cin, a);
			cout << "New Answer: ";
			getline(cin, b);
			pro[i].setQuestion(a);
			pro[i].setAnswer(b);
			writeFile();
		}
		if (input == LEFT && i > 0)
		{
			editProblem(i - 1);
		}
		if (input == RIGHT && i < pNum - 1)
		{
			editProblem(i + 1);
		}
		if (input == ESC)
		{
			selection();
		}
		if (input == F1)
		{
			deleteProblem(i);
		}
	}
	editProblem(i);
}
void cls()
{
	system("cls");
	return;
}
void deleteProblem(int i)
{
	cls();
	cout << "Are You Sure to DELETE This Problem? (ENTER/ESC)" << endl;
	printSegmentLine();
	while (1)
	{
		int input = _getch();
		if (input == ENTER)
		{
			for (; i < pNum; i++)
			{
				pro[i].setQuestion(pro[i + 1].getQuestion());
				pro[i].setAnswer(pro[i + 1].getAnswer());
			}
			pNum--;
			writeFile();
			return;
		}
		if (input == ESC)
		{
			break;
		}
	}
	
	return;
}
void practiceProblem(int i)
{
	cls();
	printPracticeProblemInduction();
	int num = pro[i].getProblemNumber();
	printQuestion(i);
	while (1)
	{
		int input = _getch();
		if (input == LEFT && i > 0)
		{
			practiceProblem(i - 1);
		}
		if (input == RIGHT && i < pNum - 1)
		{
			practiceProblem(i + 1);
		}
		if (input == ENTER)
		{
			cout << endl;
			printAnswer(i);
		}
		if (input == ESC)
		{
			selection();
		}
	}
	return;
}
void printEditInduction()
{
	cout << "ENTER = Edit\n"
		<< "ESC = Finish" << endl
		<< "F1 = Delete Problem" << endl;
	printSegmentLine();
}
void printPracticeProblemInduction()
{
	cout << "ENTER = Show Answer" << endl << "ESC = Return" << endl << "Direction Key To Swap Problem" << endl;
	printSegmentLine();
}
void printSegmentLine()
{
	cout << "---------------------------------------------" << endl;
}
void addProblemInduction()
{
	cout << "ENTER = Continue" << endl;
	cout << "ESC = Return" << endl;
	printSegmentLine();
}