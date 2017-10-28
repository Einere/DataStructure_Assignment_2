// DataStructureAssignment2.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
#include "stdafx.h"

int calculator(istream& ins);
void once_calculate(istream& ins, stack<int>& numbers, stack<char>& operators, int& number, char& symbol);
void recursive_calculate(stack<int>& numbers, stack<char>& operators);

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

	while (ins && ins.peek() != '\n') {
		//translate ins[0] ~ ins[end]
		if (isdigit(ins.peek())) {
			//peek is digit, store number decimally
			int tmp;
			ins >> tmp;
			number = number * 10 + tmp;
		}
		else {
			//peek is not digit
			if (operators.empty() || ins.peek() == LEFT_PARENTHESIS || operators.top() == LEFT_PARENTHESIS) {
				//if operators is empty or peek is '(' or operator.top is '('
				ins >> symbol;
				operators.push(symbol);
				left_parenthesis++;
				if (operators.top() != LEFT_PARENTHESIS) {
					numbers.push(number);
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
				//if peek <= top, operate(numbers.top, number) 
				if (number == 0) {
					recursive_calculate(numbers, operators);
					ins >> symbol;
					operators.push(symbol);
				}
				else {
					once_calculate(ins, numbers, operators, number, symbol);
				}
				
				//if peek == ')'
				if (operators.top() == RIGHT_PARENTHESIS) {
					right_parenthesis++;
					operators.pop();

					while (operators.top() != LEFT_PARENTHESIS) {
						recursive_calculate(numbers, operators);
					}
					operators.pop();
					//remove '(' from operators
				}
			}
			number = 0;
		}
	}
	numbers.push(number);

	//calculate remain numbers, operators
	while (!operators.empty()) {
		recursive_calculate(numbers, operators);
	}

	return numbers.top();
}

void once_calculate(istream& ins, stack<int>& numbers, stack<char>& operators, int& number, char& symbol) {
	int num1, num2;
	num1 = numbers.top(); numbers.pop();
	num2 = number;

	switch (operators.top()) {
	case '+': numbers.push(num1 + num2); break;
	case '-': numbers.push(num1 - num2); break;
	case '*': numbers.push(num1 * num2); break;
	case '/': numbers.push(num1 / num2); break;
	case '%': numbers.push(num1 % num2); break;
	case '^': numbers.push((int)pow(num1, num2)); break;
	}
	operators.pop();
	ins >> symbol;
	operators.push(symbol);
}

void recursive_calculate(stack<int>& numbers, stack<char>& operators) {
	int num1, num2;
	num2 = numbers.top(); numbers.pop();
	num1 = numbers.top(); numbers.pop();

	switch (operators.top()) {
	case '+': numbers.push(num1 + num2); break;
	case '-': numbers.push(num1 - num2); break;
	case '*': numbers.push(num1 * num2); break;
	case '/': numbers.push(num1 / num2); break;
	case '%': numbers.push(num1 % num2); break;
	case '^': numbers.push((int)pow(num1, num2)); break;
	}
	operators.pop();
}

int main()
{
	do{
		int result = calculator(cin);
		cout << "result : " << result << endl;
		cin.ignore(INT_MAX, '\n');
	} while (cin && cin.peek() != '0');

    return 0;
}

