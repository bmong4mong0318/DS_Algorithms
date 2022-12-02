/*
	그래프 표현(인접 리스트): 알고리즘 구현
		파일명: GraphAdjSList.cpp
			- main	: 그래프 생성 및 간선 추가
			- 클래스 : GNode
			- 클래스 : GraphType
				그래프 생성.소멸 : GraphType, ~GraphType
				그래프 간선 추가 : insertEdge
				그래프 전체 출력 : printAdjMatrix
				그래프 순회: DFSAdjSList, BFSAdjSList
*/

#include <iostream>
#include <cstring>
#include <stack>
#include <queue>
using namespace std;

// GNode class
class GNode {
private:
	int	__vertex;	// 정점
	int	__weight;	// 가중치
	GNode*	__link;
	friend class GraphType;
public:
	GNode(int vertex, int weight);
};

// 그래프 노드 생성
GNode::GNode(int vertex = 0, int weight = 0)
	: __vertex(vertex), __weight(weight), __link(nullptr) {}

// GraphType class
class GraphType {
private:
	int	__vertex;		// 정점의 개수
	GNode** __adjSList;		// 인접 리스트
public:
	GraphType(int vertex);
	~GraphType(void);
	void	insertEdge(int vertex1, int vertex2, int weight);
	void	printAdjSList(void) const;
	void	DFSAdjSList(int  vertex);	// 그래프 순회: 깊이 우선 순회(DFS)
	void	BFSAdjSList(int  vertex);	// 그래프 순회: 너비 우선 순회(BFS)
};

// 생성자: 그래프 생성
GraphType::GraphType(int vertex) : __vertex(vertex) {
	__adjSList = new GNode * [vertex + 1];
	memset(__adjSList, 0, sizeof(GNode*) * (vertex + 1));
}

// 소멸자: 그래프 삭제
GraphType::~GraphType(void) {
	GNode* old;
	for (int i = 0; i < __vertex; i++) {
		old = __adjSList[i];
		while (old) {
			__adjSList[i] = old->__link;
			delete old;
			old = __adjSList[i];
		}
	}
	delete[] __adjSList;
}

// 그래프 간선 추가
void  GraphType::insertEdge(int  row, int  col, int weight) {
	if (row >= __vertex || col >= __vertex) {
		// cout << "그래프에 없는 정점입니다!!!" << endl;
		return;
	}

	GNode* newGNode = new GNode(col, weight);
	if (__adjSList[row] == nullptr)
		__adjSList[row] = newGNode;
	else {
		GNode* rNode = __adjSList[row];
		while (rNode->__link)
			rNode = rNode->__link;
		rNode->__link = newGNode;
	}
}

// 그래프 전체 출력
void  GraphType::printAdjSList(void) const {
	char	ch;
	for (int i = 0; i < __vertex; i++) {
		ch = i + 65;
		cout << "\t정점 " << ch << "의 인접 리스트";
		GNode* tNode = __adjSList[i];
		while (tNode) {
			cout.width(3);
			ch = tNode->__vertex + 65;
			cout << ch << " ->>";
			tNode = tNode->__link;
		}
		cout << " NULL" << endl;
	}
}

// 그래프 순회: 깊이 우선 순회(DFS)
void	GraphType::DFSAdjSList(int  vertex){
	// 각 정점의 방문 (Visitied) 여부: true, false
	int *pVisited = new int[__vertex];
	memset(pVisited, 0, sizeof(int) * __vertex);

	stack<int>	S;
	S.push(vertex);				// Start Vertex
	pVisited[vertex] = true;	// 정점 방문
	char	ch = vertex + 65;
	cout.width(3); cout << ch;

	int v = vertex;
	GNode* w;
	while(!S.empty()) {
		w = __adjSList[v];
		while (w) {		// 인접한 정점이 있는 동안...
			// 방문 안한 인접 정점에 대해서 수행
			if(!pVisited[w->__vertex]){
				S.push(w->__vertex);
				pVisited[w->__vertex] = true; // 정점 방문
				cout.width(3); cout << ch;
				v = w->__vertex;
				w = __adjSList[v];
			}
			else w = w->__link;
		}
		// 방문 안한 인접 정점이 없으면 스택 pop
		v = S.top(); S.pop();
	}
	cout << endl;
	delete []pVisited;
}

// 그래프 순회: 너비 우선 순회(BFS)
void	GraphType::BFSAdjSList(int  vertex){
	// 각 정점의 방문 (Visitied) 여부: true, false
	int *pVisited = new int[__vertex];
	memset(pVisited, 0, sizeof(int) * __vertex);

	queue<int>	Q;
	Q.push(vertex);				// Start Vertex
	pVisited[vertex] = true;	// 정점 방문
	char	ch = vertex + 65;
	cout.width(3); cout << ch;

	int v = vertex;
	GNode* w;
	while(!Q.empty()) {
		v = Q.front(); Q.pop();
		w = __adjSList[v];
		while (w) {		// 인접한 정점이 있는 동안...
			// 방문 안한 인접 정점에 대해서 수행
			if(!pVisited[w->__vertex]){
				Q.push(w->__vertex);
				pVisited[w->__vertex] = true; // 정점 방문
				char ch = w->__vertex + 65;
				cout.width(3); cout << ch;
			}
			w = w->__link;
		}
	}
	cout << endl;
	delete []pVisited;
}




int main(void)
{
	// G2 : 무향 그래프
	GraphType	G2 = GraphType(3);

	// 정점: A(0)
	G2.insertEdge(0, 1, 0);		// A(0) - B(1)
	G2.insertEdge(0, 2, 0);		// A(0) - C(2)

	// 정점: B(1)
	G2.insertEdge(1, 0, 0);		// B(1) - A(0)
	G2.insertEdge(1, 2, 0);		// B(1) - C(2)

	// 정점: C(2)
	G2.insertEdge(2, 1, 0);		// C(2) - B(1)
	G2.insertEdge(2, 0, 0);		// C(2) - A(0)

	cout << "\n##### 그래프(G2): 인접 리스트 #####" << endl;
	G2.printAdjSList();

	// G4 : 유향 그래프
	GraphType	G4 = GraphType(3);

	// 정점: A(0)
	G4.insertEdge(0, 1, 0);		// A(0) - B(1)
	G4.insertEdge(0, 2, 0);		// A(0) - C(2)

	// 정점: B(1)
	G4.insertEdge(1, 0, 0);		// B(1) - A(0)
	G4.insertEdge(1, 2, 0);		// B(1) - C(2)

	cout << "\n##### 그래프(G4): 인접 리스트 #####" << endl;
	G4.printAdjSList();

	return 0;
}