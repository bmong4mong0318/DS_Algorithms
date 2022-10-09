/*	
	정렬: 알고리즘 구현

	1) 기초적인 정렬 알고리즘: 선택.버블.삽입.쉘 정렬
	2) 고급 정렬 알고리즘: 퀵.병합 정렬
	3) 특수 정렬 알고리즘: 계수.기수.버킷 정렬
*/

#include <iostream>
#include <random>       // C++ 11에서 추가
using namespace std;    // C++11 이전 방법: C 스타일 난수 생성(srand와 rand 함수)

#define arrMAXSIZE 15

// 기초적인 정렬 알고리즘
void	selectionSort(int* pArr, int num);	// 선택 정렬
void	bubbleSort(int* pArr, int num);		// 버블 정렬
void	insertionSort(int* pArr, int num);	// 삽입 정렬
void	shellSort(int* pArr, int num);		// 쉘 정렬
void	intervalSort(int* pArr, int start, int num, int interval);

// // 고급 정렬 알고리즘
void	quickSort(int* pArr, int* pFirst, int* pLast);	// 퀵 정렬
void	mergeSort(int* pArr, int* pFirst, int* pLast);	// 병합 정렬

// 3) 특수 정렬 알고리즘: 계수.기수.버킷 정렬
// void  contingSort(int* pArr, int num);

void	SWAP(int* pa, int* pb);
void	PRINT(int* pArr, int num);

int main(void)
{
  int	arr[arrMAXSIZE] = { 0 };

	/* C 스타일 난수 생성(srand와 rand 함수)
		srand(static_cast<unsigned int>(time(nullptr)));
		static_cast<int>(rand() % (99 + 1UL - 0)) + 0;
	*/

	// C++ 스타일 난수 생성
	random_device rd;       // 1) 시드 설정: random_device(비결정적 난수 생성기) 생성
	mt19937	gen(rd());      // 2) 난수 생성 엔진(mt19937) 초기화
	uniform_int_distribution<int>	dis(0, 99);   // 균등 분포 정의: 범위 지정
	for (int i = 0; i < arrMAXSIZE; i++)
		*(arr + i) = dis(gen);

	cout << "정렬 전: ";
	PRINT(arr, arrMAXSIZE);

	// selectionSort(arr, arrMAXSIZE);
	// bubbleSort(arr, arrMAXSIZE);
	// insertionSort(arr, arrMAXSIZE);
	// shellSort(arr, arrMAXSIZE);
	quickSort(arr, arr, arr + arrMAXSIZE - 1);
	// mergeSort(arr, arr, arr + arrMAXSIZE - 1);
	
	cout << "정렬 후: ";
	PRINT(arr, arrMAXSIZE);

	return 0;
}

void	selectionSort(int* pArr, int num) {
	int smallest;
	for (int i = 0; i < num - 1; i++) {
		smallest = i;
		for (int j = i + 1; j < num; j++){
			if (pArr[j] < pArr[smallest])
				smallest = j;
			SWAP(&pArr[i], &pArr[smallest]);
		}
	}
}

void	bubbleSort(int* pArr, int num) {
	for (int i = 0; i < num - 1; i++)
		for (int j = i + 1; j < num; j++)
			if (pArr[i] > pArr[j])
				SWAP(&pArr[i], &pArr[j]);
}	

void	insertionSort(int* pArr, int num) {
	int j, tmp;
	for (int i = 1; i < num; i++){
		j = i - 1;
		tmp = pArr[i];
		while (j >= 0 && tmp < pArr[j]){
			pArr[j + 1] = pArr[j];
			j--;
		}
		pArr[j + 1] = tmp;
	}
}

void	shellSort(int* pArr, int num) {
	int interval = num;
	while (interval >= 1){
		interval = interval / 2;
		for (int i = 0; i < interval; i++)
			intervalSort(pArr, i, num, interval);
	}
}

void	intervalSort(int* pArr, int start, int num, int interval) {
	int cnt = num / interval;
	int tmp = start;	
	int arr[cnt];
	int j = 0;
	while (cnt--){
		arr[j++] = pArr[start];
		start += interval;
	}
	cnt = num / interval;
	insertionSort(arr, cnt);
	int k = 0;
	while (cnt--){
		pArr[tmp] = arr[k++];
		tmp += interval;
	}
}

int*	Partition(int* pArr, int* pFirst, int* pLast) {
	int pivot = *pLast;
	int i = -1;
	int last_idx = (pLast - pFirst);
	for (int j = 0; j < last_idx; j++)
		if (pArr[j] < pivot)
			SWAP(&pArr[++i], &pArr[j]);
	SWAP(&pArr[++i], pLast);
	return (&pArr[i]);
}

void	quickSort(int* pArr, int* pFirst, int* pLast) {
	// if there is over 2 value
	 if (pFirst < pLast){
		// get the mid
		int* mid = Partition(pArr, pFirst, pLast);
		int move = mid - pFirst + 1;
		// Split into 2 groups based on the center
		quickSort(pArr, pFirst, mid - 1);
		quickSort(pArr + move, mid + 1, pLast);
	 }
}

int tmp[arrMAXSIZE * 2];
void Merge(int* pArr, int* pFirst, int* mid, int* pLast){
	int mid_idx = (mid - pFirst);
	int last_idx = mid_idx + (pLast - mid);
	int t = 0, i = 0, j = mid_idx + 1;
	while (i <= mid_idx && j <= last_idx) {
		if (pArr[i] <= pArr[j])
			tmp[t++] = pArr[i++];
		else
			tmp[t++] = pArr[j++];
	}
	while (i <= mid_idx)
		tmp[t++] = pArr[i++];
	while (j <= last_idx)
		tmp[t++] = pArr[j++];
	i = 0;
	t = 0;
	while (i < pLast - pFirst + 1)
		pArr[i++] = tmp[t++];
}

void	mergeSort(int* pArr, int* pFirst, int* pLast){
	// if there is over 2 value
	if (pFirst < pLast){
		// get the mid
		int half = (pLast - pFirst) / 2;
		int* mid = pFirst + half;
		// Split into 2 groups based on the center
		mergeSort(pArr, pFirst, mid);
		mergeSort(pArr + half + 1, mid + 1, pLast);
		// merge after sort
		Merge(pArr, pFirst, mid, pLast);
	}
}

void  SWAP(int* pa, int* pb) {
	int	temp;
	temp = *pa;
	*pa = *pb;
	*pb = temp;
	return;
}

void  PRINT(int* pArr, int num) {
	for (int i = 0; i < num; i++) {
		cout.width(3);
		cout << *(pArr + i);
	}
	cout << endl;
	return;
}
