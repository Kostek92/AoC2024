#include "day4.h"
#include "config.h"
#include <fstream>
#include <iostream>
#include <algorithm>

int countXMAS(const std::string& line)
{
	constexpr std::string_view toFind = "XMAS";
	int count = 0;
	std::string::size_type pos = 0;
	while ((pos = line.find(toFind, pos)) != std::string::npos) {
		  ++count;
		  pos += toFind.length();
	}
	return count;
}

int countXMASBothWays(std::string line)
{
	int count = countXMAS(line);
	std::reverse(line.begin(), line.end());
	count+= countXMAS(line);
	return count;
}

int Day4::solve1() const
{
	int result = 0;
	const auto matrix = readInput();
	const int rowCount = matrix.size();
	const int colCount = matrix[0].size();
	//Horizontal
	for(const auto& row : matrix)
	{
		result+=countXMASBothWays(std::string(row.begin(), row.end()));
	}

	//Vertical
	for (int i = 0; i < colCount; ++i) {
		std::string verticalLine;

		for (int j = 0; j < rowCount; ++j) {
			verticalLine+=matrix[j][i];
		}
		result+=countXMASBothWays(verticalLine);
	}
	//Diagonal 45 degree
	for (int i = 0; i < matrix.size(); ++i) {
		std::string diagonalLine;
		int rowIndex = 0;
		int colIndex = i;

		while(colIndex >=0 && rowIndex < rowCount)
		{
			diagonalLine+=matrix[rowIndex][colIndex];
			++rowIndex;
			--colIndex;
		}
		result+=countXMASBothWays(diagonalLine);
	}

	for (int i = 1; i < matrix.size(); ++i) {
		std::string diagonalLine;
		int rowIndex = i;
		int colIndex = colCount - 1;

		while(rowIndex < rowCount && colIndex >= 0)
		{
			diagonalLine+=matrix[rowIndex][colIndex];
			++rowIndex;
			--colIndex;
		}
		result+=countXMASBothWays(diagonalLine);
	}

	//Diagonal -45 degree
	for (int i = colCount - 1; i >= 0; --i) {
		std::string diagonalLine;
		int rowIndex = 0;
		int colIndex = i;

		while(colIndex < colCount && rowIndex < rowCount)
		{
			diagonalLine+=matrix[rowIndex][colIndex];
			++rowIndex;
			++colIndex;
		}
		result+=countXMASBothWays(diagonalLine);
	}

	for (int i = 1; i < rowCount; ++i) {
		std::string diagonalLine;
		int rowIndex = i;
		int colIndex = 0;

		while(rowIndex < rowCount && colIndex < colCount)
		{
			diagonalLine+=matrix[rowIndex][colIndex];
			++rowIndex;
			++colIndex;
		}
		result+=countXMASBothWays(diagonalLine);
	}
	return result;
}

int Day4::solve2() const
{
	int result = 0;
	const auto matrix = readInput();
	const int n = matrix.size();
	for(int rowIndex = 1; rowIndex < n - 1; ++rowIndex)
	{
		for(int colIndex = 1; colIndex < n -1; ++colIndex)
		{
			if(matrix[rowIndex][colIndex] == 'A')
			{
				if(((matrix[rowIndex-1][colIndex-1] == 'M' && matrix[rowIndex+1][colIndex+1] == 'S')	//Backslash forward
				|| (matrix[rowIndex-1][colIndex-1] == 'S' && matrix[rowIndex+1][colIndex+1] == 'M'))	//Backslash backward
				&& ((matrix[rowIndex-1][colIndex+1] == 'M' && matrix[rowIndex+1][colIndex-1] == 'S')	//Slash forward
				|| (matrix[rowIndex-1][colIndex+1] == 'S' && matrix[rowIndex+1][colIndex-1] == 'M'))	//Slash backward
				)
				{
					result++;
				}
			}
		}
	}
	return result;
}

std::vector<std::vector<char>> Day4::readInput() const
{
	const std::string fileName = std::string(config::INPUT_DIR_PATH) + "\\Day4.txt";
	std::ifstream file(fileName);

	if (!file) {
		std::cerr << "Error: Unable to open file " << fileName << std::endl;
		return {};
	}

	std::vector<std::vector<char>> matrix;
	std::string line;

	while (std::getline(file, line)) {
		std::vector<char> row(line.begin(), line.end());
		matrix.push_back(row);
	}
	return matrix;

}


