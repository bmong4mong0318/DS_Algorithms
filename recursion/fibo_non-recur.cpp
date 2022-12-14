/*	
	피보나치 수열: 성능 평가
	비재귀적 용법
*/

#include <iostream>
#include <ctime>	// clock, clock_t, CLOCKS_PER_SEC
using namespace std;
// clock 함수: 프로그램에 의해 프로세서가 소비된 시간을 반환하는 함수
// CLOCKS_PER_SEC: 초당 clock ticks의 수를 나타낸 매크로 상수(시스템에 따라 기본값이 다름)

// 피보나치 수열: 비재귀적 용법
int  Fibo(int num);

int main(void)
{
	int	num;

	cout << "### 피보나치 수열 구하기 ### \n" << endl;
	cout << "몇 번째 수열까지 출력할까요: ";
	cin >> num;

	clock_t		start, finish;
	double		seconds;

	start = clock();	// start time
	for (int i = 1; i <= num; i++) {
		cout.width(8);
		if (i % 5)	cout << Fibo(i);
		else	cout << Fibo(i) << endl;
	}
	finish = clock();	// end time

	seconds = (double)(finish - start) / CLOCKS_PER_SEC;  	// CPU time
	cout << num << "번째 피보나치 수열 계산 시간: " << seconds << endl;

	return 0;
}

// 피보나치 수열: 비재귀적 용법
// dynamic programming
int Fibo(int num)
{
	int a = 1;
	int b = 1;
	int c = 0;

	if (num == 1 || num == 2)
		return (1);
	for (int i = 3; i <= num; i++){
		c = a + b;
		a = b;
		b = c;
	}
	return (c);
}
