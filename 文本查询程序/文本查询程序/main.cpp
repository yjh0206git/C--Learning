#include "Query.h"
#include "TextQuery.h"
#include <string>
#include <set>
#include <iostream>
#include <vector>
#include<array>


using namespace std;

bool get_word(string& s1) {
	cout << "enter a word to search for, or q to quit, or h to history:";
	cin >> s1;
	if (!cin || s1 == "q") return false;
	else return true;
}
int main(int argc, char** argv) {
	// gets file to read and builds map to support queries
	ifstream infile;
	infile.open("storyDataFile");
	TextQuery file(infile);
	vector<array<string, 3>> h;

	// iterate with the user: prompt for a word to find and print results
	while (true) {
		string sought1, sought2, sought3;
		if (!get_word(sought1)) {
			break;
		}

		if (sought1 != "h") {
			cout << "\nenter second and third words: ";
			cin >> sought2 >> sought3;
			// find all the occurrences of the requested string
			Query q = (Query(sought1) & Query(sought2)) | Query(sought3);
			h.push_back({ sought1, sought2, sought3 });
			cout << "\nExecuting Query for: " << q << endl;
			const auto results = q.eval(file);
			// report matches
			print(cout, results);
		}
		else        // 用户输入了"h"，表示要提取历史查询
		{
			cout << "\nenter Query no.: ";
			int i;
			cin >> i;
			if (i < 1 || i > h.size())    // 历史编号合法性检查
			{
				cout << "\nBad Query no." << endl;
			}
			else {
				// 提取三个查询词，重构查询
				Query q = (Query(h[i - 1][0]) & Query(h[i - 1][1])) | Query(h[i - 1][2]);;
				cout << "\nExecuting Query for: " << q << endl;
				const auto results = q.eval(file);
				// report matches
				print(cout, results);
			}
		}
	}
	system("pause");
	return 0;
}