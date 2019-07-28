#include <iostream>
#include <vector>

#include "dictionary.h"
#include "Table.h"

using namespace std;

float getScore(const vector<VisualizableNoun> &nounsOne, const vector<VisualizableNoun> &nounsTwo) {
	if (nounsOne.size() == 0 && nounsTwo.size() == 0) return 0;
	int totalScore = 0;
	for (auto noun : nounsOne) {
		totalScore += noun.score;
	}
	for (auto noun : nounsTwo) {
		totalScore += noun.score;
	}
	int totalNouns = nounsOne.size() + nounsTwo.size();
	return ((float)totalScore / totalNouns);
}

unordered_map<string, vector<VisualizableNoun>> resultTable;

vector<VisualizableNoun> maximizeScore(string digits) {
	if (resultTable[digits].size() > 0) return resultTable[digits];

	VisualizableNoun asIsNoun = dictionary[digits];
	if (asIsNoun.word != "") {
		vector<VisualizableNoun> asIs = { asIsNoun };
		resultTable[digits] = asIs;
		return asIs;
	}

	vector<VisualizableNoun> bestSplit;
	float bestSplitScore = 0;
	for (int i = 1; i < digits.size(); i++) {
		vector<VisualizableNoun> splitA = maximizeScore(digits.substr(0, i));
		vector<VisualizableNoun> splitB = maximizeScore(digits.substr(i, digits.size() - i));

		bool currentSplitIsBetter = false;
		float currentSplitScore = 0;
		int totalWordsInSplit = splitA.size() + splitB.size();

		if (bestSplit.size() == 0) { 
			currentSplitIsBetter = true; 
		}
		if (totalWordsInSplit < bestSplit.size()) { 
			currentSplitIsBetter = true; 
		}
		if (totalWordsInSplit == bestSplit.size()) {
			currentSplitScore = getScore(splitA, splitB);
			if (currentSplitScore > bestSplitScore) { 
				currentSplitIsBetter = true; 
			}
		}

		if (currentSplitIsBetter) {
			bestSplitScore = currentSplitScore;
			bestSplit.clear();
			bestSplit.reserve(splitA.size() + splitB.size());
			bestSplit.insert(bestSplit.end(), splitA.begin(), splitA.end());
			bestSplit.insert(bestSplit.end(), splitB.begin(), splitB.end());
		}
	}
	resultTable[digits] = bestSplit;
	return bestSplit;
}

void printHelp() {
	cout << "Usage:\n\tmajor [digits to encode into major system]" << endl << endl;
	cout << "Major system rules:" << endl;
	Table table(2);
	table.addRow({ "Numeral", "Associated sounds" });
	table.addRow({ "0","S, soft C, Z, X (in xylophone)" });
	table.addRow({ "1","T, D" });
	table.addRow({ "2","N" });
	table.addRow({ "3","M" });
	table.addRow({ "4","R" });
	table.addRow({ "5","L" });
	table.addRow({ "6","CH, J, soft G, SH, C (in cello and special)" });
	table.addRow({ "7","K, hard C, Q, hard G" });
	table.addRow({ "8","F, PH, V, GH (in laugh)" });
	table.addRow({ "9","P, B" });
	table.addRow({ "Unassigned","H, Y, W, A, E, I, O, U, silent letters" });
	cout << table.getFormattedTable() << endl;
	cout << "*Please note that the major system is based on word sounds not their spellings!" << endl;
}

int main(int argc, char* argv[]) {
	if (argc == 1) {
		printHelp();
		return 0;
	}
	string input = "";
	for (int i = 1; i < argc; i++) {
		input += argv[i];
	}
	string filteredInput = "";
	for (char c : input) {
		if (c >= '0' && c <= '9') {
			filteredInput.push_back(c);
		}
	}
	if (filteredInput.size() == 0) {
		cerr << "Error: You must pass at least one digit character as an argument" << endl;
		return -1;
	}
	if (filteredInput.size() < input.size()) {
		cout << "Interpreting input as: " << filteredInput << endl;
	}
	auto result = maximizeScore(filteredInput);
	cout << endl;
	for (auto word : result) {
		cout << word.word << " ";
	}
	cout << endl << endl;
	return 0;
}