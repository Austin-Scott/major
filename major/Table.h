#pragma once
#include <vector>
#include <string>

using namespace std;

class Table {
private:
	//Cell values of the table in row major ordering
	vector<string> values;
	int numberOfColumns;
public:
	Table(int numberOfColumns);
	//Adds a row to the bottom of the table.
	//values.size() must equal numberOfColumns or this function won't do anything.
	void addRow(vector<string> values);
	void clearTable();
	//Returns a string of the table with formatting ready to be printed to the console.
	string getFormattedTable();
};