// DataStructureAssignment2.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
// 컴소과 2013726058 최형준
// this source code wrote in Visual Studio 2017 
#include "stdafx.h"

int calculator(istream& ins);
void once_calculate(istream& ins, stack<int>& numbers, stack<char>& operators, int& number, char& symbol);
void recursive_calculate(stack<int>& numbers, stack<char>& operators);
void print_result();
bool flag = true; //to deal with "devided by zero"
int balance = 0; //to deal with "parenthesis"

int calculator(istream& ins) {
	//pre : input istream (cin)
	//post : left one element in numbers, possible no element in operators
	const char LEFT_PARENTHESIS = '(';
	const char RIGHT_PARENTHESIS = ')';
	
	//priority mapping
	map<char, int>priority;
	priority['^'] = 3;
	priority['*'] = 2, priority['/'] = 2;
	priority['+'] = 1, priority['-'] = 1;

	stack<int> numbers;
	stack<char> operators;
	int number = 0;
	char symbol = NULL;
	flag = true; 
	balance = 0;
	bool meaning = true; //to deal with "choose once or recursive"

	while (ins && ins.peek() != '\n' ) {
		//claculate ins[0] ~ ins[end]
		//pre : cin isn't empty
		//post : one calculate cycle is done when iterator scan '\n'
		if (isdigit(ins.peek())) {
			//peek is digit, store number decimally
			int tmp;
			ins >> tmp;
			number = number * 10 + tmp;
			meaning = true;
		}
		else {
			//peek is not digit
			if (operators.empty() || ins.peek() == LEFT_PARENTHESIS || (ins.peek() != RIGHT_PARENTHESIS && operators.top() == LEFT_PARENTHESIS)) {
				//if operators is empty or peek is '(' or operator.top is '('
				ins >> symbol;
				operators.push(symbol);
				balance++;
				if (operators.top() != LEFT_PARENTHESIS) {
					//if operators is empty or operators.top is '('
					if (meaning) {
						numbers.push(number);
					}
					balance--;
				}
			}

			else if (priority[operators.top()] < priority[(char)ins.peek()]) {
				//if peek > top
				if(meaning) numbers.push(number);
				ins >> symbol;
				operators.push(symbol);
			}

			else {
				//if peek <= top or peek == ')'
				if (ins.peek() == RIGHT_PARENTHESIS) {
					//if peek == ')'
					if (operators.top() != LEFT_PARENTHESIS) {
						if (meaning) {
							once_calculate(ins, numbers, operators, number, symbol);
						}
						else {
							recursive_calculate(numbers, operators); 
							ins >> symbol;
						}
					}
					balance--;
					if(operators.top() == RIGHT_PARENTHESIS)  operators.pop();
					//remove ')' from operators
					if (!operators.empty()) {
						while (operators.top() != LEFT_PARENTHESIS) {
							recursive_calculate(numbers, operators);
						}
					}
					if (!operators.empty())  operators.pop();
					//remove '(' from operators
				}
				else if (priority[(char)ins.peek()] < priority[operators.top()]) {
					//if peek < top 
					if (meaning) {
						once_calculate(ins, numbers, operators, number, symbol);
					}
					else {
						recursive_calculate(numbers, operators);
						ins >> symbol;
						operators.push(symbol);
					}	
				}
			}
			number = 0;
			meaning = false;
		}
	}

	do {
		//calculate remain numbers, operators
		//pre : no exist balanced parenthesis in operators
		//post : remain one element in numbers
		if (meaning) {
			//if number is meaningful
			once_calculate(ins, numbers, operators, number, symbol);
			number = 0;
			meaning = false;
		}
		else {
			//if number is meaningless
			recursive_calculate(numbers, operators);
		}
	} while (numbers.size() > 1); //  !operators.empty()

	
	if (operators.empty() && balance == 0 && flag) {
		//return result
		return numbers.top();
	}
	else {
		return NULL;
	}
}

void once_calculate(istream& ins, stack<int>& numbers, stack<char>& operators, int& number, char& symbol) {
	//pre : meaning is true, exist one element to calculate in numbers
	//post : result is pushed in numbers, scaned operator is pushed in poerators
	int num1, num2;
	if (numbers.size() < 1) return;
	num1 = numbers.top(); numbers.pop();
	num2 = number;
	switch (operators.top()) {
	case '+': numbers.push(num1 + num2); break;
	case '-': numbers.push(num1 - num2); break;
	case '*': numbers.push(num1 * num2); break;
	case '/': if (num2 == 0) { flag = false; break; } numbers.push(num1 / num2); break;
	case '%': if (num2 == 0) { flag = false; break;	} numbers.push(num1 % num2); break;
	case '^': numbers.push((int)pow(num1, num2)); break;
	}
	if(!operators.empty()) operators.pop(); else return;
	if (ins.peek() != '\n') {
		ins >> symbol;
		operators.push(symbol);
	}
}

void recursive_calculate(stack<int>& numbers, stack<char>& operators) {
	//pre : exist two element to calculate in numbers
	//post : result is pushed in numbers, throw scaned operator
	int num1, num2;
	if (numbers.size() < 2) return;
	num2 = numbers.top(); numbers.pop();
	num1 = numbers.top(); numbers.pop();

	switch (operators.top()) {
	case '+': numbers.push(num1 + num2); break;
	case '-': numbers.push(num1 - num2); break;
	case '*': numbers.push(num1 * num2); break;
	case '/': if (num2 == 0) { flag = false; break;	} numbers.push(num1 / num2); break;
	case '%': if (num2 == 0) { flag = false; break; } numbers.push(num1 % num2); break;
	case '^': numbers.push((int)pow(num1, num2)); break;
	}
	if (!operators.empty()) operators.pop(); else return;
}

void print_result() {
	//pre : 
	//post : correctly print result
	do {
		int result = calculator(cin);
		if (flag == true && balance == 0) {	cout << "result : " << result << endl;	}
		else {	cout << "Error!" << endl;	}
		cin.ignore(INT_MAX, '\n');
	} while (cin && cin.peek() != '0');
	//repeat until input is "0\n"
}

int main()
{
	print_result();
    return 0;
}

