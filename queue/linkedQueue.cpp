/*
	큐: 알고리즘 구현 --단순연결리스트
		파일명: LinkedQueue.h
		클래스: SNode
		클래스: LinkedQueue
			- 생성자.소멸자 	 	 : LinkedQueue, ~LinkedQueue
			- 데이터 삽입.삭제  	 : push, pop			// enQueue, deQueue
			- 데이터 확인	   		: front, back		  // peek
			- 빈 큐 여부 판단		: empty
			- 큐 크기				: size
			- 큐의 전체 원소 출력	: printQueue
*/

#include <iostream>
using namespace std;

inline void error(const char* message) {
	cout << message;
	exit(100);
}

// SNode class
template <typename E>
class SNode {
private:
	E		__data;
	SNode<E>*	__link;
	template <typename T> friend class LinkedQueue;
public:
	SNode();
};

// 새로운 노드(data, link) 생성
template <typename E>
SNode<E>::SNode() : __data(__data), __link(NULL) {}

// LinkedQueue class
template <typename E>
class LinkedQueue {
private:
	SNode<E>*	__front, *__rear;
	int		__count;
public:
	LinkedQueue();
	~LinkedQueue();
	void	push(const E& e);	// enQueue
	void	pop(void);		// deQueue
	E&	front(void) const;
	E&	back(void) const;
	bool	empty(void) const;
	int	size(void) const;
	void	printQueue(void) const;
};

// 생성자: 빈 큐 생성
template <typename E>
LinkedQueue<E>::LinkedQueue() : __front(NULL), __rear(NULL) {}

// 소멸자 : 큐 삭제 -- 모든 노드 삭제
template <typename E>
LinkedQueue<E>::~LinkedQueue()	{
	SNode<E>* temp = __front;
	while (temp) {
		__front = temp->__link;
		free(temp);
		temp = __front;
	}
}

// push(enQueue) : 큐에 데이터 삽입
template <typename E>
void	LinkedQueue<E>::push(const E& e) {
	SNode<E>* newSNode = new SNode<int>;
	newSNode->__data = e;
	if (__front)	__rear->__link = newSNode;
	else        __front = newSNode;
	__rear = newSNode;
}

// pop(deQueue) : 큐에서 데이터 삭제
template <typename E>
void	LinkedQueue<E>::pop(void) {
	if (empty()) error("STACK IS EMPTY");		// throw "ERROR::STACK IS EMPTY";
	SNode<int>* temp = __front;
	E data = temp->__data;
	__front = temp->__link;
	if (!__front)
		__rear = NULL;
	free(temp);
}

// front(peek) : 큐에서 첫 번째 원소 확인
template <typename E>
E& LinkedQueue<E>::front(void) const {
	if (empty()) error("STACK IS EMPTY");	// throw "ERROR::STACK IS EMPTY";
	return  __front->__data;
}

// back(peek) : 큐에서 맨 마지막 원소 확인
template <typename E>
E& LinkedQueue<E>::back(void) const {
	if (empty()) error("STACK IS EMPTY");	// throw "ERROR::STACK IS EMPTY";
	return  __rear->__data;
}

// empty : 큐의 공백 상태 여부 판단
template <typename E>
bool	LinkedQueue<E>::empty(void) const {
	return __front == NULL;
}

// size: 큐의 크기
template <typename E>
int		LinkedQueue<E>::size(void) const {
	return __count;
}

// printQueue : 큐의 전체 원소 출력
template <typename E>
void	LinkedQueue<E>::printQueue(void) const {
	SNode<E>* temp = __front;
	cout << "\n QUEUE [";
	while (temp) {
		cout.width(3);
		cout << temp->__data;
		temp = temp->__link;
	}
	cout << " ]" << endl;
}

int main(void)
{
	int			num, choice;
	LinkedQueue<int>	LQ;

	while (true) {
		system("cls");
		cout << "\n ### 큐 구현: 단순 연결 리스트 ### \n" << endl;
		cout << "1) 데이터 삽입(push, enQueue)" << endl;
		cout << "2) 데이터 삭제(pop, deQueue)" << endl;
		cout << "3) 전체 출력" << endl;
		cout << "4) 프로그램 종료 \n" << endl;
		cout << "메뉴 선택: ";
		cin >> choice;

		switch (choice) {
			case 1: cout << "\n삽입 할 데이터 입력: ";
				cin >> num;		LQ.push(num);	break;
			case 2: cout << "삭제 된 데이터: " << LQ.front() << endl;
				LQ.pop();		break;
			case 3: LQ.printQueue();
				break;
			case 4: cout << "프로그램 종료..." << endl;
				return 0;
			default: cout << "잘못 선택 하셨습니다." << endl;
		}
		system("pause");
	}
	return 0;	// s.~LinkedQueue();
}

