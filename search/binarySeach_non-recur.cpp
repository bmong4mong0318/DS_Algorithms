/*	
	이진 탐색: 알고리즘 구현
	비재귀적 용법
*/
#include <iostream>

using namespace std;

#define arrMAXSIZE 10

int*	binarySearch(int* pArr, int *first, int *last, int key);
void	PRINT(int* pArr, int num);

int main(void)
{
	int	arr[arrMAXSIZE] = { 5, 9, 13, 17, 21, 28, 37, 46, 55, 88 };
	cout << "원시 데이터: ";
	PRINT(arr, arrMAXSIZE);

	int	key;
	while (true) {
		cout << "검색 데이터 입력(검색 종료: 0): ";
		cin >> key;
		if (key == 0)
			break;
			
		int*	index = binarySearch(arr, arr, arr + arrMAXSIZE - 1, key);
		if (index == NULL)	cout << "없다고!!!" << endl;
		else	cout << "검색 데이터: " << *index << ", 위치(index): " << index - arr + 1 << endl;
	}
	return 0;
}

// 이진 탐색: 비재귀적 용법
int*	binarySearch(int* pArr, int *first, int *last, int key) {
	
	int *mid;

	while (first <= last)
	{
		mid = first + (last - first) / 2;
		if (*mid == key)
			return (mid);
		else if (*mid < key)
			first = mid + 1;
		else if (*mid > key)
			last = mid - 1;
	}
	return (0);
}

void  PRINT(int* pArr, int num) {
	for (int i = 0; i < num; i++) {
		cout.width(3);
		cout << *(pArr + i);
	}
	cout << endl;
	return;
}