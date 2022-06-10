#include <cstdio>
#include <stack>
#include <queue>
#include <iostream>
#include<string.h>
#include<math.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <iterator>      
#include <algorithm>

using namespace std;

fstream myFile;

// remove all spaces
void trim(string &s)
{
	int index = 0;
	if(!s.empty())
	{
		while((index = s.find(' ')) != string::npos)
		{
			s.erase(index, 1);
		}
	}
}


// show string 
void show(string &s)
{
	for (string::iterator it = s.begin(); it != s.end(); ++it)
	{
		printf("%c", *it);
		myFile << *it;
	}
	printf("\n");
	myFile << "\n";
}

// show queue
void showQueue(queue<string> q)
{
	while(!q.empty())
	{
		printf("%s ", q.front().c_str());
		myFile << q.front().c_str();
		q.pop();
	}
	printf("\n");
	myFile << "\n";
}


// infix to suffix
void change(string &str, queue<string> &q)
{
	//stacks
	stack<char> cs;
	//tempStr save data temps
	string tempStr;
	//remove infix space
	trim(str);

	for (string::iterator it = str.begin(); it != str.end(); ++it)
	{
		if (*it >= '0' && *it <='9')// out put number to suffix
		{
			tempStr.push_back(*it);
			while(*(it+1)>='0' && *(it+1)<='9')
			{
				it++;
				tempStr.push_back(*it);
			}
			q.push(tempStr);
			tempStr.clear();
		}
		else if (*it == '(')// left go stack cause first calss
		{
			cs.push(*it);

		}
		else if(*it == ')')// meet "(" pop stack untile meet ")"
		{
			while(!cs.empty() && cs.top() != '(')
			{
				tempStr.push_back(cs.top());
				q.push(tempStr);
				tempStr.clear();

				cs.pop();
			}
			cs.pop();//pop "("
		}
		else
		{
			switch(*it)
			{
				case '*':
				case '/':
				{
					//*/ is first class except "()"
					//lift go first if same class
					//same level, pop then output
					if (!cs.empty())
					{
						if(cs.top() == '*' || cs.top() == '/')
						{
							//strDst.push_back(cs.top());
							tempStr.push_back(cs.top());
							q.push(tempStr);
							tempStr.clear();

							cs.pop();
						}
					}
					cs.push(*it);
					break;
				}
				case '+':
				case '-':
				{
					//in stack if it's first class you will have to output then pop 
					//On the stack, the left parenthesis has the lowest priority, and the priority 
					//of */+- is greater than or equal to +-. All operators except the left parenthesis 
					//must be popped first and output.
					while (!cs.empty() && cs.top() != '(')
					{
						//strDst.push_back(cs.top());
						tempStr.push_back(cs.top());
						q.push(tempStr);
						tempStr.clear();

						cs.pop();
					}
					cs.push(*it);
					break;
				}
				default:
				{
					printf("Illegal input: %c\n", *it);
					myFile << "Illegal input: %c\n" , *it;
					myFile << endl;
				}
			}//end of switch
		}
	}//end of for
	// scan the thing and if still operator remaining all go suffix
	while(!cs.empty())
	{
		//strDst.push_back(cs.top());
		tempStr.push_back(cs.top());
		q.push(tempStr);
		tempStr.clear();

		cs.pop();
	}
}//end of function change


////////////////////////////////////////////////////////////////////////////////////////////////

int isOp(string &str)// check if it's operator
{
	if (str == "+" || str == "-" || str == "*" || str=="/")
	{
		return 1;
	}
	else return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////

double calculate(queue<string> &q)
{
	stack<string> s;//save
	double temp, temp1, temp2;
	string tempStr;
	while(!q.empty())
	{
		tempStr = q.front();
		q.pop();
		if (!isOp(tempStr))//is number go stack
		{
			s.push(tempStr);
		}
		else//else operator
		{
			temp2 = stod(s.top()); // second
			s.pop();
			temp1 = stod(s.top()); // first
			s.pop();

			if (tempStr == "+")
			{
				temp = temp1 + temp2;
			}
			else if (tempStr == "-")
			{
				temp = temp1 - temp2;
			}
			else if (tempStr == "*")
			{
				temp = temp1 * temp2;
			}
			else if (tempStr == "/")
			{
				temp = temp1 / temp2;
			}

			//stack the result
			s.push(to_string(temp));    //int to string then go stack
		}//end of else

	}// end of while
	myFile << stod(s.top()) << endl;
	return stod(s.top());   //reutrn
}// end of function calculate

////////////////////////////////////////////////////////////////////////////////////////////////////
void test()
{
    
    myFile.open("result.txt",ios::out);//open the global file
    
    
    
    int cumt = 1;
    string all = "";
	cout << "enter da name of file :D"<< endl;
    string inputfile;// input your file name here plz and remeber to add .txt
    cin >> inputfile;
    ifstream fin(inputfile);
    string s;
    while(getline(fin, s)){
        
        cout <<"run: " << cumt<< endl;
        myFile << "run: ";
        myFile << cumt;
        myFile <<endl;
        
        
    queue<string> q;
	string str = s;
	show(str);
	change(str, q);
	showQueue(q);
	
	cout << calculate(q)<<endl;
	cumt = cumt + 1;
	
    }
}

int main(int argc, char const *argv[])
{
	test();
	return 0;
}
