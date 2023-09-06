#include <iostream>
#include <sstream>
#include <bitset>
#include <fstream>
#include <string>

bool is_file_exists(const std::string& filename)
{
	std::ifstream file(filename.c_str());
	return file.good();
}

int main(int argc, char* argv[])
{
	std::string filename = "";
	bool debug_enabled = true;
	
	// Program params handling
	for (int i = 0; i < argc; i++)
	{
		if (argv[i] == "-F" || argv[i] == "--file-name")
		{
			if (i < argc + 1 && argv[i + 1] != "")
			{
				filename = argv[i + 1];
				i++;
			}
		}

		if (argv[i] == "-S" || argv[i] == "--silence")
		{
			debug_enabled = false;
		}

		if (argv[i] == "-h" || argv[i] == "--help")
		{
			std::cout << "Usage: " << argv[0] << " -F <file name>" << '\n';
			std::cout << "\t-F, --file-name <file name> reads and outputs file\'s content in hex8, dec8, hex16, dec16, hex32." << '\n';
			std::cout << "\t-S, --silence deisables any debug information." << '\n';
			std::cout << "-h, --help prints this message." << std::endl;

			return 0; // Exiting
		}
	}

	if (debug_enabled)
	{
		if (filename == "")
			std::cout << "Filename was not provided using sometext.txt." << std::endl;
	}
	if (filename == "")
		filename = "somefile.txt";
	if (!is_file_exists(filename))
	{
		std::ofstream file(filename.c_str());
		file << "Some long string to file!" << std::endl;
	}

	std::ifstream file(filename);
	std::string filecontents = "";

	return 0;
}