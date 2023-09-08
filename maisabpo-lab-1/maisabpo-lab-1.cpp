#include <iostream>
#include <sstream>
#include <bitset>
#include <fstream>
#include <string>
#include <vector>

bool is_file_exists(const std::string& filename)
{
	std::ifstream file(filename.c_str());
	return file.good();
}

template <typename T>
std::vector<T> string_to_int_array(const std::string& convertString)
{
	std::vector<T> convertedString = {};

	for (auto c : convertString)
		convertedString.push_back((T)c);

	return convertedString;
}
template <typename inT, typename outT>
std::vector<outT> convert_to_bits(inT num)
{
	const uint32_t size = sizeof(inT) * 8;
	std::vector<outT> convertedNum = {};
	std::bitset<size> binary(num);
	for (int i = 0; i < size / 8; i++)
		convertedNum.push_back((outT)std::bitset<size>{binary.to_string().substr(i * 8, 8)}.to_ulong());

	return convertedNum;
}

template <typename inT, typename outT>
std::vector<outT> convert_int_arr_to_bits_array(std::vector<inT> arr)
{
	std::vector<outT> convertedArr = {};
	for (int num : arr)
	{
		if (num < 0)
			num += 256;
		std::vector<outT> temp = convert_to_bits<inT, outT>(num);
		for (outT byte : temp)
			convertedArr.push_back(byte);
	}

	return convertedArr;
}

template <typename T>
void print_in_hex(std::vector<T> arr, const char* format = "%02x ")
{
	for (int i = 0; i < arr.size(); i++)
	{
		printf(format, arr[i]);
		if ((i + 1) % 10 == 0)
			std::cout << '\n';
	}
	std::cout << std::endl;
}

template <typename T>
void print_in_dec(std::vector<T> arr, const char* format = "%08u ")
{
	for (int i = 0; i < arr.size(); i++)
	{
		printf(format, arr[i]);
		if ((i + 1) % 10 == 0)
			std::cout << '\n';
	}
	std::cout << std::endl;
}

int main(int argc, char** argv)
{
	std::string fileName = "";
	bool debugEnabled = true;

	// Program parameters handling
	for (int i = 0; i < argc; i++)
	{
		if (strcmp(argv[i], "-F") == 0 || strcmp(argv[i], "--file-name") == 0)
		{
			if (i < argc + 1 && argv[i + 1] != "")
			{
				fileName = argv[i + 1];
				i++;
			}
		}

		if (strcmp(argv[i], "-S") == 0 || strcmp(argv[i], "--silence") == 0)
		{
			debugEnabled = false;
		}

		if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0)
		{
			std::cout << "Usage: " << argv[0] << " -F <file name>" << '\n';
			std::cout << "\t-F, --file-name <file name> reads and outputs file\'s content in hex8, dec8, hex16, dec16, hex32." << '\n';
			std::cout << "\t-S, --silence disables any debug information." << '\n';
			std::cout << "-h, --help prints this message." << std::endl;

			return 0; // Exiting
		}
	}

	if (debugEnabled)
	{
		if (fileName == "")
			std::cout << "Filename was not provided using sometext.txt." << std::endl;
	}
	if (fileName == "")
		fileName = "somefile.txt";

	if (!is_file_exists(fileName))
	{
		std::ofstream file(fileName.c_str());
		file << "Some long string from file!" << std::endl;
	}

	std::ifstream file(fileName);
	std::vector<unsigned char> fileContents(std::istreambuf_iterator<char>(file), {});
	std::string fileContentsStr(fileContents.begin(), fileContents.end());

	std::cout << "File contents: " << fileContentsStr << std::endl;

	std::vector<uint8_t> convertedFile32 = convert_int_arr_to_bits_array<uint32_t, uint8_t>(string_to_int_array<uint32_t>(fileContentsStr));

	std::cout << "============Hex32============" << std::endl;
	print_in_hex(convertedFile32);

	std::vector<uint8_t> convertedFile16 = convert_int_arr_to_bits_array<uint16_t, uint8_t>(string_to_int_array<uint16_t>(fileContentsStr));

	std::cout << "============Hex16============" << std::endl;
	print_in_hex(convertedFile16);

	for (int i = 0; i < 42; i++) std::cout << "=";
	std::cout << "Dec16";
	for (int i = 0; i < 42; i++) std::cout << "=";
	std::cout << std::endl;
	print_in_dec(convertedFile16, "%08u ");

	std::vector<uint8_t> convertedFile8 = convert_int_arr_to_bits_array<uint8_t, uint8_t>(string_to_int_array<uint8_t>(fileContentsStr));

	std::cout << "============Hex8=============" << std::endl;
	print_in_hex(convertedFile8);


	for (int i = 0; i < 17; i++) std::cout << "=";
	std::cout << "Dec8";
	for (int i = 0; i < 18; i++) std::cout << "=";
	std::cout << std::endl;
	print_in_dec(convertedFile8, "%03u ");



	return 0;
}