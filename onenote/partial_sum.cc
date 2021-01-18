#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int getMaxSumOfSubarrayWithBruteForce(const vector<int>& arr) {
	int maxSum = -1;
	int tmpSum = 0;
	for(int i = 0; i < arr.size(); i++) {
		tmpSum = 0;
		for(int j = i; j < arr.size(); j++) {
			tmpSum += arr[j];
			maxSum = max(maxSum, tmpSum);
		}
	}

	return maxSum;
}

int getMaxSumOfSubarrayWithDP(const vector<int>& arr) {
	int maxSum = 0;
	vector<int> sumArr;
	sumArr.resize(arr.size());

	sumArr[0] = arr[0];
	for(int i = 1; i < arr.size(); i++) {
		sumArr[i] = max(sumArr[i-1] + arr[i+1], sumArr[i]);
	}

	return *max_element(sumArr.begin(), sumArr.end());
}

int main() {
	vector<int> arr{1, 0, 3, -40, 12, 3, 4, 5, -1, 12, 10};
	cout << getMaxSumOfSubarrayWithBruteForce(arr) << endl;
	cout << getMaxSumOfSubarrayWithDP(arr) << endl;
	return 0;
}
