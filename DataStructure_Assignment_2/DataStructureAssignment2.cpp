// DataStructureAssignment2.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
#include "stdafx.h"

int calculator(istream& ins);
void once_calculate(istream& ins, stack<int>& numbers, stack<char>& operators, int& number, char& symbol);
void recursive_calculate(stack<int>& numbers, stack<char>& operators);
void print_result();
bool flag = true;

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
	int left_parenthesis = 0;
	int right_parenthesis = 0;
	char symbol;
	flag = true;
	bool is_init = false;

	while (ins && ins.peek() != '\n' ) {
		//translate ins[0] ~ ins[end]
		if (isdigit(ins.peek())) {
			//peek is digit, store number decimally
			int tmp;
			ins >> tmp;
			number = number * 10 + tmp;
			is_init = false;
		}
		else {
			//peek is not digit
			if (operators.empty() || ins.peek() == LEFT_PARENTHESIS || operators.top() == LEFT_PARENTHESIS) {
				//if operators is empty or peek is '(' or operator.top is '('
				ins >> symbol;
				operators.push(symbol);
				left_parenthesis++;
				if (operators.top() != LEFT_PARENTHESIS) {
					if (number != 0) {
						numbers.push(number);
					}
					left_parenthesis--;
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

					right_parenthesis++;
					operators.pop();
					//remove ')' from operators

					while (operators.top() != LEFT_PARENTHESIS) {
						recursive_calculate(numbers, operators);
					}
					operators.pop();
					//remove '(' from operators
				}
				else if (number == 0) {
					//if peek < top and number == 0
					if (numbers.size() == 1) {
						once_calculate(ins, numbers, operators, number, symbol);
					}
					else {
						recursive_calculate(numbers, operators);
						ins >> symbol;
						operators.push(symbol);
					}
					
				}
				else {
					once_calculate(ins, numbers, operators, number, symbol);
				}
				
				
			}
			number = 0;
			is_init = true;
		}
		
	}
	cout << "number : " << number << endl;
	//cout << "top : " << numbers.top() << endl;
	cout << "flag : " << flag << endl;
	cout << "aaaa" << endl;

	while (!operators.empty()) {
		cout << "bbbb" << endl;
		//calculate remain numbers, operators
		if ((number != 0) ) {
			//if end digit, numbers.size == 1
			cout << "cccc" << endl;
			once_calculate(ins, numbers, operators, number, symbol);
			cout << "dddd" << endl;
		}
		else {
			//if end operator, numbers.size > 1
			if (numbers.size() == 1) { 
				//if number == 0, numbers.size > 1 -> devide by zero
				cout << "eeee" << endl;
				once_calculate(ins, numbers, operators, number, symbol);
				cout << "ffff" << endl;
			}
			else {
				cout << "gggg" << endl;
				recursive_calculate(numbers, operators);
				cout << "hhhh" << endl;
			}
		}
	}
	cout << "iiii" << endl;
	//return result
	if (operators.empty() && left_parenthesis == right_parenthesis && flag == true) {
		cout << "jjjj" << endl;
		return numbers.top();
	}
	else {
		cout << "kkkk" << endl;
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
	case '/': 
		if (num2 == 0) {
			flag = false; break;
		}
		numbers.push(num1 / num2); break;
	case '%': 
		if (num2 == 0) {
			flag = false; break;
		}
		numbers.push(num1 % num2); break;
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
	case '/': 
		if (num2 == 0) {
			flag = false; break;
		}
		numbers.push(num1 / num2); break;
	case '%': 
		if (num2 == 0) {
			flag = false; break;
		}
		numbers.push(num1 % num2); break;
	case '^': numbers.push((int)pow(num1, num2)); break;
	}
	operators.pop();
}

void print_result() {
	do {
		int result = calculator(cin);
		if (flag == true) {
			cout << "result : " << result << endl;
		}
		else {
			cout << "Error!" << endl;
		}
		cin.ignore(INT_MAX, '\n');
	} while (cin && cin.peek() != '0');
}

int main()
{
	print_result();
    return 0;
}

