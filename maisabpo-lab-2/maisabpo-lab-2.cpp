#include <iostream>
#include <string>
#include <bitset>


int xorOp(int op1, int op2)
{
	return op1 ^ op2;
}

int andOp(int op1, int op2)
{
	return op1 & op2;
}

int orOp(int op1, int op2)
{
	return op1 | op2;
}

int evaluateExpr(int (*op)(int, int), const std::string& operand1, const std::string& operand2)
{
	int convertedOperand1 = 0;
	int convertedOperand2 = 0;
	int result = 0;
	convertedOperand1 = std::stoi(operand1);
	convertedOperand2 = std::stoi(operand2);
	result = op(convertedOperand1, convertedOperand2);
	std::cout << "|" << std::bitset<32>(convertedOperand1) << "|" << convertedOperand1 << '\n';
	std::cout << "|" << std::bitset<32>(convertedOperand2) << "|" << convertedOperand2 << '\n';
	std::cout << "|--------------------------------|" << '\n';
	std::cout << "|" << std::bitset<32>(result) << "|" << result << std::endl;

	return result;
}

int evaluateExpr(int (*op)(int, int), const int& operand1, const int& operand2)
{
	int result = 0;
	result = op(operand1, operand2);
	std::cout << "|" << std::bitset<32>(operand1) << "|" << operand1 << '\n';
	std::cout << "|" << std::bitset<32>(operand2) << "|" << operand2 << '\n';
	std::cout << "|--------------------------------|" << '\n';
	std::cout << "|" << std::bitset<32>(result) << "|" << result << std::endl;

	return result;
}

int main()
{
	std::string command;
	std::string operand1;
	std::string operand2;
	int result = 0;
	std::cout << "Enter an operation and two operands: " << std::endl;
	while (std::cin >> command)
	{
		// Handling commands without operands \\

		if (command == "exit")
			break;
		else if (command == "help")
		{
			std::cout << "Available commands: " << '\n';
			std::cout << "xor op1 op2" << '\n';
			std::cout << "and op1 op2" << '\n';
			std::cout << "or op1 op2" << '\n';
			std::cout << "exit" << '\n';
			continue;
		}

		// Handling commands with 1 operand \\

		std::cin >> operand1;

		if (command == "set1")
		{
			int convertedOperand1 = std::stoi(operand1);
			if (convertedOperand1 <= 0) convertedOperand1 = 1;
			result = evaluateExpr(orOp, result, std::pow(2, convertedOperand1 - 1)); // Можно было сделать через bitset set
			continue;
		}
		else if (command == "set0")
		{
			int convertedOperand1 = std::stoi(operand1);
			if (convertedOperand1 <= 0) convertedOperand1 = 1;
			int mask_inv = 1 << (convertedOperand1 - 1) % 32;
			result = evaluateExpr(andOp, result, ~mask_inv); //  Можно было сделать через bitset reset
			continue;
		}

		// Handling commands with 2 operands \\

		std::cin >> operand2;
		if (command == "xor")
			result = evaluateExpr(xorOp, operand1, operand2);
		else if (command == "and")
			result = evaluateExpr(andOp, operand1, operand2);
		else if (command == "or")
			result = evaluateExpr(orOp, operand1, operand2);
		else
			std::cout << "Invalid command or argument!" << std::endl;
		/*
			shl - сдвинуть число2 на число1 бит влево
			shr - сдвинуть число2 на число1 бит вправо
			shl - циклически сдвинуть число2 на число1 бит влево
			shr - циклически сдвинуть число2 на число1 бит вправо
			mix - число1 указывает порядок бит(числа от 0 до 7), каждый байт числа 2 переставить указанном порядке
		*/

	}

	return 0;
}