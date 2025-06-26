#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
	void setZeros(vector<vector<int>>& matrix) {
		int rows = matrix.size();
		int cols = matrix[0].size();

		bool firstRowZero = false;
		bool firstColZero = false;

		//Check if first column has a zero
		for (int i = 0;i < rows;i++) {
			if (matrix[i][0] == 0) {
				firstColZero = true;
				break;
			}
		}

		//Check if first row has a zero
		for (int j = 0;j < cols;j++) {
			if (matrix[0][j] == 0) {
				firstRowZero = true;
				break;
			}
		}

		//Use first row and columns as markers
		for (int i = 1;i < rows;i++) {
			for (int j = 1;j < cols;j++) {
				if (matrix[i][j] == 0) {
					matrix[i][0] = 0;
					matrix[0][j] = 0;
				}
			}
		}

		//Set cells to zero based on markers
		for (int i = 1;i < rows;i++) {
			for (int j = 1;j < cols;j++) {
				if (matrix[i][0] == 0 || matrix[0][j] == 0) {
					matrix[i][j] = 0;
				}
			}
		}

		//Set first column to zero if needed
		if (firstColZero) {
			for (int i = 0;i < rows;i++) {
				matrix[i][0] = 0;
			}
		}

		//Set first row to zero if needed
		if (firstRowZero) {
			for (int j = 0;j < cols;j++) {
				matrix[0][j] = 0;
			}
		}

	}
};

int main() {
	Solution sol;
	vector<vector<int>> mat = {
		{1,1,1},
		{1,0,1},
		{1,1,1}
	};
	sol.setZeros(mat);
	//Print result
	for (const auto& row : mat) {
		for (int val : row) {
			cout << val << " ";
		}
		cout << endl;
	}
	return 0;
}



/**🧠 What the code is doing :
It uses the first row and first column to store flags(markers) indicating which rows and columns should be zeroed out.

Since the top - left cell matrix[0][0] is shared by both the first row and column, there's ambiguity.

To avoid losing original data(whether the first row / col actually had zero), you store those in firstRowZero and firstColZero.


❌ If you skip firstRowZero and firstColZero:
matrix[0][0] will be set to 0 during marker phase — but you don’t know if it was originally 0 or not.

Result : you unintentionally zero out the first row or column, even if they didn't originally have a 0 — or worse, you miss zeroing them out when they did.

✅ Why separate checks fix it
By checking the first row / col separately before marking, you :

	Preserve the original 0s in them.

	Avoid false positives / negatives due to marker overwrites.

	Handle matrix[0][0]'s ambiguity safely.

	🟢 Final Summary
	If you don’t check the first row and column separately :

You lose track of whether they originally contained zeros.

This leads to incorrect zeroing in the final matrix.

✅ Always preserve original first row and first column info before using them as markers.*/