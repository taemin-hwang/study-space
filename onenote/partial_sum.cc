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
	vector<int> sumArr; //sumArr[i] has maximum sum of arr[0..i]
	sumArr.resize(arr.size());

	sumArr[0] = arr[0];
	for(int i = 1; i < arr.size(); i++) {
		// sumArr[i-1] is less than 0, throw sumArr[i-1]
		// otherwise, add sumArr[i-1] to sumArr[i]
		sumArr[i] = max(sumArr[i-1], 0) + arr[i];
	}

	return *max_element(sumArr.begin(), sumArr.end());
}

int getMaxSumOfSubarrayWithDP2(const vector<int>& arr) {
	int maxSum = arr[0];
	int tmpSum = arr[0];

	for(int i = 1; i < arr.size(); i++) {
		tmpSum = max(tmpSum, 0) + arr[i];
		maxSum = max(tmpSum, maxSum);
	}

	return maxSum;
}

int main() {
	vector<int> arr{1, 0, 3, -40, 12, 3, 4, 5, -1, 12, 10};


	cout << getMaxSumOfSubarrayWithBruteForce(arr) << endl;
	cout << getMaxSumOfSubarrayWithDP(arr) << endl;
	cout << getMaxSumOfSubarrayWithDP2(arr) << endl;
	return 0;
}
