#include <iostream>
using namespace std;

// node : data, link
class DNode {
private:
	int data;
	DNode* prev;
	DNode* next;
	friend class DLinkedList;
};

class DLinkedList {
private:
	DNode*	head;	// first node;
	DNode*	tail;	// last  node;
	int		count;	// number of node
public:
	DLinkedList();							// 생성자
	~DLinkedList();							// 소멸자 : 전체 노드 삭제
	bool	isEmpty() const;				// 빈 리스트 여부 판단
	int		countDNode()	const;			// 탐색 : 노드의 총 개수(count)
	DNode*	frontDNode() const;				// 탐색 : 첫번째 노드
	DNode*	rearDNode() const;				// 탐색 : 맨 마지막 노드
	DNode*	makeDNode(const int& e) const;	// 새로운 노드 생성
	void	addRear(const int& e);			// 삽입 : 맨 마지막 노드
	void	removeFront();					// 삭제 : 첫번째 노드
	void	printDLinkedList();				// 리스트의 전체 노드 출력 (순방향)
	void	revPrintDLinkedList();			// 리스트의 전체 노드 출력 (역방향)
};


// 생성자
DLinkedList::DLinkedList()
	: head(NULL) {}

// 빈 리스트 여부 판단
bool DLinkedList::isEmpty() const {
	return (head == NULL);
}

// 탐색 : 노드의 총 개수(count)
int DLinkedList::countDNode() const {
	if (isEmpty()) return (0);
	int		count = 0;
	DNode* rNode = head;
	while (rNode->next) {
		rNode = rNode->next;
		count++;
	}
	return count;
}

// 탐색 : 첫번째 노드
DNode* DLinkedList::frontDNode() const {
	return (head);
}

// 탐색 : 맨 마지막 노드
DNode* DLinkedList::rearDNode() const {
	if (isEmpty()) return (NULL);
	DNode* rNode = head;
	while (rNode->next)
		rNode = rNode->next;
	return (rNode);
}

// 새로운 노드 생성
DNode* DLinkedList::makeDNode(const int &e) const {
	DNode* rNode = new DNode;
	rNode->data = e;
	rNode->prev = NULL;
	rNode->next = NULL;
	return (rNode);
}

// 삽입 : 맨 마지막 노드
void DLinkedList::addRear(const int& e) {
	DNode* nNode = makeDNode(e);
	if (isEmpty()) head = nNode;
	else {
		DNode* rNode = rearDNode();
		rNode->next = nNode;
		nNode->prev = rNode;
	}
}

// 삭제 : 첫번째 노드
void DLinkedList::removeFront() {
	DNode* old;
	while (head) {
		old = head;
		head = old->next;
		if (old->next != NULL)
			old->next->prev = NULL;
		delete old;
	}
}

// 소멸자 : 전체 노드 삭제
DLinkedList::~DLinkedList() {
	while (!isEmpty()) removeFront();
}

// 리스트의 전체 노드 출력 (순방향)
void DLinkedList::printDLinkedList() {
	if (isEmpty()) return;
	DNode* temp = head;
	while (temp) {
		cout.width(3);
		cout << temp->data << "->>";
		temp = temp->next;
	}
	cout << "NULL" << endl;
}

// 리스트의 전체 노드 출력 (역방향)
void DLinkedList::revPrintDLinkedList() {
	if (isEmpty()) return;
	DNode* temp = rearDNode();
	while (temp) {
		cout.width(3);
		cout << temp->data << "<<-";
		temp = temp->prev;
	}
	cout << "NULL" << endl;
}


int main(void)
{
	int num;
	DLinkedList sList = DLinkedList();
	while (true) {
		cout << "임의의 정수 입력(종료: 0): ";
		cin >> num;
		if (num == 0) break ;
		// 맨 마지막 노드로 삽입
		sList.addRear(num);
	}

	//전체 원소 출력
	if (sList.isEmpty()) {
		cout << "입력된 데이터가 없습니다..." << endl;
		return (0);		// sList.~DLinkedList();
	}
	printf("\n ### 입력된 데이터 ### \n\n");
	sList.printDLinkedList();
	sList.revPrintDLinkedList();
	// 소멸자: 전체 원소 삭제
	sList.~DLinkedList();
	return (0);
}