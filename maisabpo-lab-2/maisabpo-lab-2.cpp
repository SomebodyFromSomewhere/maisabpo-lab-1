#include <iostream>
#include <string>
#include <bitset>

#define TYPE uint64_t

template <typename T>
T xorOp(T op1, T op2)
{
	return op1 ^ op2;
}

template <typename T>
T andOp(T op1, T op2)
{
	return op1 & op2;
}

template <typename T>
T orOp(T op1, T op2)
{
	return op1 | op2;
}

template <typename T>
T shl(T value, T shift)
{
	return value << shift;
}

template <typename T>
T shr(T value, T shift)
{
	return value >> shift;
}

template <typename T>
T shl_c(T value, T shift) {
	uint32_t typeSize = (sizeof(T) * 8);
	if ((shift &= (typeSize - 1)) == 0)
		return value;
	return (value << shift) | (value >> (typeSize - shift));
}

template <typename T>
T shr_c(T value, T shift) {
	uint32_t typeSize = (sizeof(T) * 8);
	if ((shift &= (typeSize - 1)) == 0)
		return value;
	return (value >> shift) | (value << (typeSize - shift));
}

template <typename T>
T evaluateExpr_internal(T(*op)(T, T), const T& operand1, const T& operand2)
{
	T result = 0;
	result = op(operand1, operand2);
	std::cout << "|" << std::bitset<sizeof(T) * 8>(operand1) << "|" << (int64_t)operand1 << '\n'; // sizeof(uint8_t) = 1 byte * 8 = 8 bits
	std::cout << "|" << std::bitset<sizeof(T) * 8>(operand2) << "|" << (int64_t)operand2 << '\n'; // int64_t is here because types like uint8_t and etc expanding to unsigned char that in output displays symbol
	std::string separator = "";
	for (int i = 0; i < sizeof(T) * 8; i++) separator += "-";
	std::cout << "|" + separator + "|" << '\n';
	std::cout << "|" << std::bitset<sizeof(T) * 8>(result) << "|" << (int64_t)result << std::endl;

	return result;
}

template <typename T>
T evaluateExpr(T(*op)(T, T), const T& operand1, const T& operand2)
{
	return evaluateExpr_internal(op, operand1, operand2);
}

template <typename T>
T evaluateExpr(T(*op)(T, T), const std::string& operand1, const std::string& operand2)
{
	T convertedOperand1 = 0;
	T convertedOperand2 = 0;

	try
	{
		convertedOperand1 = std::stoi(operand1);
		convertedOperand2 = std::stoi(operand2);
	}
	catch (const std::invalid_argument&)
	{
		std::cout << "Invalid argument was given skipping..." << std::endl;
		return (T)0;
	}

	return evaluateExpr_internal(op, convertedOperand1, convertedOperand2);
}


int main()
{
	std::string command;
	std::string operand1;
	std::string operand2;
	TYPE result = 0;
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
			std::cout << "set1 pos" << '\n';
			std::cout << "set0 pos" << '\n';
			std::cout << "shl shifts_count value" << '\n';
			std::cout << "shr shifts_count value" << '\n';
			std::cout << "shlc shifts_count value" << '\n';
			std::cout << "shrc shifts_count value" << '\n';
			std::cout << "exit" << '\n';
			continue;
		}

		// Handling commands with 1 operand \\

		std::cin >> operand1;

		if (command == "set1")
		{
			TYPE convertedOperand1 = std::stoi(operand1);
			if (convertedOperand1 <= 0) convertedOperand1 = 1;
			result = evaluateExpr(orOp<TYPE>, result, (TYPE)std::pow(2, convertedOperand1 - 1)); // Можно было сделать через bitset set
			continue;
		}
		else if (command == "set0")
		{
			TYPE convertedOperand1 = std::stoi(operand1);
			if (convertedOperand1 <= 0) convertedOperand1 = 1;
			TYPE mask_inv = static_cast<uint64_t>(1) << (convertedOperand1 - 1) % 8;
			result = evaluateExpr(andOp<TYPE>, result, (TYPE)~mask_inv); //  Можно было сделать через bitset reset
			continue;
		}

		// Handling commands with 2 operands \\

		std::cin >> operand2;
		if (command == "xor")
			result = evaluateExpr(xorOp<TYPE>, operand1, operand2);
		else if (command == "and")
			result = evaluateExpr(andOp<TYPE>, operand1, operand2);
		else if (command == "or")
			result = evaluateExpr(orOp<TYPE>, operand1, operand2);
		else if (command == "shl")
			result = evaluateExpr(shl<TYPE>, operand1, operand2);
		else if (command == "shr")
			result = evaluateExpr(shr<TYPE>, operand1, operand2);
		else if (command == "shlc")
			result = evaluateExpr(shl_c<TYPE>, operand1, operand2);
		else if (command == "shrc")
			result = evaluateExpr(shr_c<TYPE>, operand1, operand2);
		else
			std::cout << "Invalid command or argument!" << std::endl;

		/*
			shlc - циклически сдвинуть число2 на число1 бит влево
			shrc - циклически сдвинуть число2 на число1 бит вправо
			mix - число1 указывает порядок бит(числа от 0 до 7), каждый байт числа 2 переставить указанном порядке
		*/

	}

	return 0;
}