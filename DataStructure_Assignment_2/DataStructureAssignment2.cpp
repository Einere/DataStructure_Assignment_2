// DataStructureAssignment2.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
#include "stdafx.h"

int calculator(istream& ins);

int calculator(istream& ins) {
	const char RIGHT_PARENTHESIS = ')';
	
	//priority mapping
	map<char, int>priority;
	priority['^'] = 3;
	priority['*'] = 2, priority['/'] = 2;
	priority['+'] = 1, priority['-'] = 1;

	stack<int> numbers;
	stack<char> operators;
	int number = 0;
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
			if (operators.empty()) {
				//if operators is empty
				ins >> symbol;
				numbers.push(number);
				operators.push(symbol);
			}
			else if (priority[operators.top()] < priority[(char)ins.peek()]) {
				//if peek > top
				ins >> symbol;
				numbers.push(number);
				operators.push(symbol);
			}
			else {
				//if peek <= top, operate(numbers.top, number) 
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
			number = 0;
		}
	}
	numbers.push(number);

	//calculate remain numbers, operators
	while (!operators.empty()) {
		int num1, num2;
		num2 = numbers.top(); numbers.pop();
		num1 = numbers.top(); numbers.pop();

		switch (operators.top()) {
		case '+': numbers.push(num1 + num2); break;
		case '-': numbers.push(num1 - num2); break;
		case '*': numbers.push(num1 * num2); break;
		case '/': numbers.push(num1 / num2); break;
		case '%': numbers.push(num1 % num2); break;
		case '^': numbers.push(num1 ^ num2); break;
		}
		operators.pop();
	}

	return numbers.top();
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

