#include "Table.h"

Table::Table(int numberOfColumns)
{
	this->numberOfColumns = numberOfColumns;
}

void Table::addRow(vector<string> values)
{
	if (values.size() == numberOfColumns) {
		for (string s : values)
			this->values.push_back(s);
	}
}

void Table::clearTable()
{
	values.clear();
}

string Table::getFormattedTable()
{
	string result = "";

	const char topRightCorner = 191;
	const char topLeftCorner = 218;
	const char bottomLeftCorner = 192;
	const char bottomRightCorner = 217;
	const char horizontalLine = 196;
	const char verticalLine = 179;
	const char topIntersection = 194;
	const char rightIntersection = 180;
	const char bottomIntersection = 193;
	const char leftIntersection = 195;
	const char middleIntersection = 197;

	int* columnWidths = new int[numberOfColumns];
	for (int i = 0; i < numberOfColumns; i++) {
		columnWidths[i] = 0;
	}

	//Find width of each column
	for (int i = 0; i < values.size(); i++) {
		int currentColumn = i % numberOfColumns;
		int currentStringLength = values[i].length();
		if (columnWidths[currentColumn] < currentStringLength) {
			columnWidths[currentColumn] = currentStringLength;
		}
	}

	//Print top of table
	result.push_back(topLeftCorner);
	for (int col = 0; col < numberOfColumns; col++) {
		for (int chr = 0; chr < columnWidths[col]; chr++) {
			result.push_back(horizontalLine);
		}
		if (col + 1 < numberOfColumns)
			result.push_back(topIntersection);
	}
	result.push_back(topRightCorner);
	result.push_back('\n');

	int numberOfRows = values.size() / numberOfColumns;
	int numberOfLines = numberOfRows * 2 - 1;

	//Print the middle of the table
	for (int line = 0; line < numberOfLines; line++) {
		if (line % 2 == 0) { //Content line
			result.push_back(verticalLine);
			for (int col = 0; col < numberOfColumns; col++) {
				string content = values[numberOfColumns * (line / 2) + col];
				for (int i = 0; i < columnWidths[col]; i++) {
					if (i < content.length()) {
						result.push_back(content[i]);
					}
					else {
						result.push_back(' ');
					}
				}
				result.push_back(verticalLine);
			}
			result.push_back('\n');
		}
		else { //Table structure line
			result.push_back(leftIntersection);
			for (int col = 0; col < numberOfColumns; col++) {
				for (int chr = 0; chr < columnWidths[col]; chr++) {
					result.push_back(horizontalLine);
				}
				if (col + 1 < numberOfColumns)
					result.push_back(middleIntersection);
			}
			result.push_back(rightIntersection);
			result.push_back('\n');
		}
	}

	//Print bottom of table
	result.push_back(bottomLeftCorner);
	for (int col = 0; col < numberOfColumns; col++) {
		for (int chr = 0; chr < columnWidths[col]; chr++) {
			result.push_back(horizontalLine);
		}
		if (col + 1 < numberOfColumns)
			result.push_back(bottomIntersection);
	}
	result.push_back(bottomRightCorner);
	result.push_back('\n');

	delete[] columnWidths;

	return result;
}
