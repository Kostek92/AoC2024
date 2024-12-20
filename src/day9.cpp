#include "day9.h"
#include "config.h"
#include <fstream>
#include <iostream>
#include <vector>

int charToInt(char c)
{
	return c - '0';
}

long long Day9::solve1()
{
	const auto diskMap = getInput();
	std::vector<int> filesMap;
	std::vector<int> spacesMap;
	std::vector<int> formated;
	long long checksum = 0;

	bool file = true;
	for (const auto descriptor : diskMap) {
		if(file)
		{
			filesMap.push_back(charToInt(descriptor));
		}
		else
		{
			spacesMap.push_back(charToInt(descriptor));
		}
		file = !file;
	}
	int lastIndexWithFiles = filesMap.size() - 1;
	for(int i = 0; i < filesMap.size(); ++i)
	{
		while(filesMap[i])
		{
			formated.push_back(i);
			filesMap[i]--;
		}
		int spacesLeft = spacesMap[i];
		while(spacesLeft)
		{
			if(lastIndexWithFiles == 0)
			{
				break;
			}
			if(filesMap[lastIndexWithFiles] == 0)
			{
				lastIndexWithFiles--;
			}
			else
			{
				formated.push_back(lastIndexWithFiles);
				filesMap[lastIndexWithFiles]--;
				spacesLeft--;
			}
		}
	}
	for(int i = 0; i < formated.size(); ++i)
	{
		checksum += i *formated[i];
	}
	return checksum;
}

long long Day9::solve2()
{
	const auto diskMap = getInput();
	std::vector<int> filesMap;
	std::vector<int> spacesMap;
	std::vector<int> formated;
	long long checksum = 0;

	bool file = true;
	for (const auto descriptor : diskMap) {
		if(file)
		{
			filesMap.push_back(charToInt(descriptor));
		}
		else
		{
			spacesMap.push_back(charToInt(descriptor));
		}
		file = !file;
	}
	int lastIndexWithFiles = filesMap.size() - 1;
	for(int i = 0; i < filesMap.size(); ++i)
	{
		while(filesMap[i])
		{
			formated.push_back(i);
			filesMap[i]--;
		}
		int spacesLeft = spacesMap[i];
		while(spacesLeft)
		{
			if(lastIndexWithFiles == 0)
			{
				break;
			}
			if(spacesLeft >= filesMap[lastIndexWithFiles])
			{
				while(filesMap[lastIndexWithFiles])
				{
					formated.push_back(lastIndexWithFiles);
					filesMap[lastIndexWithFiles]--;
					spacesLeft--;
				}
			}
			lastIndexWithFiles--;
			break;
			// if(filesMap[lastIndexWithFiles] == 0)
			// {
			// 	lastIndexWithFiles--;
			// }
		}
	}
	std::cout <<"\nformatted\n";
	for(int i = 0; i < formated.size(); ++i)
	{
		std::cout << formated[i];
		checksum += i *formated[i];
	}
	std::cout <<"\nformatted\n";
	return checksum;
}


std::string Day9::getInput() const
{
	const std::string fileName = std::string(config::INPUT_DIR_PATH) + "\\Day9.txt";
	std::ifstream file(fileName);

	if (!file) {
		std::cerr << "Error: Unable to open file " << fileName << std::endl;
		return {};
	}

	std::string line;
	std::getline(file, line);

	return line;
}
