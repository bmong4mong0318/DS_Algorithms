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

// 특수 정렬 알고리즘: 계수.기수.버킷 정렬
void  countingSort(int* pArr, int num);

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

	countingSort(arr, arrMAXSIZE);
	
	cout << "정렬 후: ";
	PRINT(arr, arrMAXSIZE);

	return 0;
}

// 계수 정렬 (오름차순)
void  countingSort(int* pArr, int num) {
	int max = 0;
	// copy pArr into tmp array 
	int* tmp = pArr;
	while (*tmp){
		if (*tmp > max)
			max = *tmp;
		tmp++;
	}
	// init frequency array
	int freq[max + 1];
	for (int i = 0; i <= max; i++)
		freq[i] = 0;
	// check frequency of each value
	int ans[arrMAXSIZE];
	for (int i = 0; i < num; i++)
		freq[pArr[i]]++;
	// fill by frequency of value
	int j = 0;
	for (int i = 0; i <= max; i++)
		while (freq[i]--)
			ans[j++] = i;
	// copy values into original array
	for (int i = 0; i < num; i++)
		pArr[i] = ans[i];
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