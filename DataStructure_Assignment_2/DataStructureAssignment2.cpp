// DataStructureAssignment2.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
#include "stdafx.h"

int read(istream& ins);
void calculate(stack<int>& numbers, stack<char>& operators);

int read(istream& ins) {
	const char RIGHT_PARENTHESIS = ')';

	stack<int> numbers;
	stack<char> operators;
	int number;
	char symbol;

	while (ins && ins.peek() != '\n') {
		if (isdigit(ins.peek())) {
			cout << "digit" << endl;
			ins >> number;
			numbers.push(number);
			cout << numbers.top() << endl;
		}
		else if (strchr("+-*/%^", ins.peek()) != NULL) {
			cout << "operator" << endl;
			ins >> symbol;
			operators.push(symbol);
			cout << operators.top() << endl;
		}
		else if (ins.peek() == RIGHT_PARENTHESIS) {
			ins.ignore();
			calculate(numbers, operators);
		}
		else {
			ins.ignore();
		}

	}

	return numbers.top();
}

void calculate(stack<int>& numbers, stack<char>& operators) {
	int operand1 = 0, operand2 = 0;
	operand2 = numbers.top();
	numbers.pop();
	operand1 = numbers.top();
	numbers.pop();

	switch (operators.top()){
	case '+': numbers.push(operand1 + operand2); break;
	case '-': numbers.push(operand1 - operand2); break;
	case '*': numbers.push(operand1 * operand2); break;
	case '/': numbers.push(operand1 / operand2); break;
	case '%': numbers.push(operand1 % operand2); break;
	case '^': numbers.push(operand1 ^ operand2); break;
	}
	operators.pop();

	cout << "calculate" << endl;
}


int main()
{
	
	int result = read(cin);
	cout << result << endl;
	
    return 0;
}

