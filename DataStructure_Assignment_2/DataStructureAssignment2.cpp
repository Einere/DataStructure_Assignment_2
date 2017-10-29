// DataStructureAssignment2.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
// 컴소과 2013726058 최형준
#include "stdafx.h"

int calculator(istream& ins);
void once_calculate(istream& ins, stack<int>& numbers, stack<char>& operators, int& number, char& symbol);
void recursive_calculate(stack<int>& numbers, stack<char>& operators);
void print_result();
bool flag = true; //to deal with "devided by zero"

int calculator(istream& ins) {
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
	int balance = 0; //to deal with "parenthesis"
	char symbol = NULL;
	flag = true; 
	bool meaning = true; //to deal with "choose once or recursive"

	while (ins && ins.peek() != '\n' ) {
		//claculate ins[0] ~ ins[end]
		if (isdigit(ins.peek())) {
			//peek is digit, store number decimally
			int tmp;
			ins >> tmp;
			number = number * 10 + tmp;
			meaning = true;
		}
		else {
			//peek is not digit
			if (operators.empty() || ins.peek() == LEFT_PARENTHESIS || operators.top() == LEFT_PARENTHESIS) {
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
				numbers.push(number);
				ins >> symbol;
				operators.push(symbol);
			}
			else {
				//if peek <= top or peek == ')'
				if (ins.peek() == RIGHT_PARENTHESIS) {
					//if peek == ')'
					once_calculate(ins, numbers, operators, number, symbol);

					balance--;
					operators.pop();
					//remove ')' from operators

					while (operators.top() != LEFT_PARENTHESIS) {
						recursive_calculate(numbers, operators);
					}
					operators.pop();
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
	//cout << "number : " << number << endl;
	//cout << "top : " << numbers.top() << endl;
	//cout << "flag : " << flag << endl;

	while (!operators.empty()) {
		//calculate remain numbers, operators
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
	}
	//return result
	if (operators.empty() && balance == 0 && flag == true) {
		return numbers.top();
	}
	else {
		return NULL;
	}
}

void once_calculate(istream& ins, stack<int>& numbers, stack<char>& operators, int& number, char& symbol) {
	int num1, num2;
	num1 = numbers.top(); if (!numbers.empty()) numbers.pop();
	num2 = number;
	switch (operators.top()) {
	case '+': numbers.push(num1 + num2); break;
	case '-': numbers.push(num1 - num2); break;
	case '*': numbers.push(num1 * num2); break;
	case '/': if (num2 == 0) { flag = false; break; } numbers.push(num1 / num2); break;
	case '%': if (num2 == 0) { flag = false; break;	} numbers.push(num1 % num2); break;
	case '^': numbers.push((int)pow(num1, num2)); break;
	}
	operators.pop();
	if (ins.peek() != '\n') {
		ins >> symbol;
		operators.push(symbol);
	}
}

void recursive_calculate(stack<int>& numbers, stack<char>& operators) {
	int num1, num2;
	num2 = numbers.top(); if (!numbers.empty()) numbers.pop();
	num1 = numbers.top(); if (!numbers.empty()) numbers.pop();

	switch (operators.top()) {
	case '+': numbers.push(num1 + num2); break;
	case '-': numbers.push(num1 - num2); break;
	case '*': numbers.push(num1 * num2); break;
	case '/': if (num2 == 0) { flag = false; break;	} numbers.push(num1 / num2); break;
	case '%': if (num2 == 0) { flag = false; break; } numbers.push(num1 % num2); break;
	case '^': numbers.push((int)pow(num1, num2)); break;
	}
	operators.pop();
}

void print_result() {
	do {
		int result = calculator(cin);
		if (flag == true) {	cout << "result : " << result << endl;	}
		else {	cout << "Error!" << endl;	}
		cin.ignore(INT_MAX, '\n');
	} while (cin && cin.peek() != '0');
}

int main()
{
	print_result();
    return 0;
}

