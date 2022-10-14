#include <iostream>
#include "linkedStack.cpp"
using namespace std;
#define	 bufferMAXSIZE	 1024

int 	evalPostfix(char* str);
void	InfixToPostfix(char* postfix, char* infix);
int		isOperator(int op);
int		precedence(int op);

int main(void)
{
	int	res;
	char	infixStr[bufferMAXSIZE], postfixStr[bufferMAXSIZE];

	cout << "수식 입력: ";
	cin.getline(infixStr, bufferMAXSIZE);	// getline(cin, infixStr);

	InfixToPostfix(postfixStr, infixStr);
	cout << "\n후위표기법 변환: " << postfixStr << endl;

	res = evalPostfix(postfixStr);
	cout << "연산결과: " << res << endl;

	return 0;
}

int  evalPostfix(char* str) {
	int	op1, op2, res;
	char	temp[bufferMAXSIZE], *p;
	LinkedStack<int>	s;
	while (*str) {
		// 피연산자 일 경우...
		if (*str >= '0' && *str <= '9') {
			p = temp;	// 한 자리 이상을 처리 하기 위해...
			while (*str >= '0' && *str <= '9')
				*p++ = *str++;
			*p = '\0';
			s.push(atoi(temp));		// atoi(temp.c_str());
		}
		else if (isOperator(*str)) {	// 연산자 일 경우...
			op2 = s.pop();
			op1 = s.pop();
			switch (*str) {
			case '+': s.push(op1 + op2);	break;
			case '-': s.push(op1 - op2);	break;
			case '*': s.push(op1 * op2);	break;
			case '/': s.push(op1 / op2);	break;
			}
			str++;
		}
		else if (*str == ' ')	 str++;
		else {
			printf("잘못된 수식!!! \n");
			// s.~LinkedStack();
			return 0;
		}
	}

	// 스택에 남은 최종 결과 값
	if (!s.isEmpty())
		res = s.pop();

	// s.~LinkedStack();
	return res;
}

// 중위 표기법을 후위표기법으로 변환
void  InfixToPostfix(char* postfix, char* infix) {
	LinkedStack<int>	s;
	while (*infix) {
		// 1) '(' 는 스택에 push
		if (*infix == '(')
			s.push(*infix++);
		// 2) ')'를 만나면 '('가 나올 때까지 pop 한 후에 '('는 버린다.
		else if (*infix == ')') {
			while (s.peek() != '(') {
				*postfix++ = s.pop();
				*postfix++ = ' ';
			}
			s.pop();	// '(' 를 버린다.
			infix++;
		}
		// 3) 연산자인 경우...
		else if (isOperator(*infix)) {
			while (!s.isEmpty() &&
				precedence(s.peek()) >= precedence(*infix)) {
				// 자신보다 높은 우선순위의 연산자는 스택에서 pop
				*postfix++ = s.pop();
				*postfix++ = ' ';
			}
			s.push(*infix++);	// 자신을 push
		}

		// 4) 피연산자인 경우...
		else if (*infix >= '0' && *infix <= '9') {
			while (*infix >= '0' && *infix <= '9')
				*postfix++ = *infix++;
			*postfix++ = ' ';
		}
		else if (*infix == ' ')	infix++;
		else {
			printf("잘못된 수식!!! \n");
			// s.~LinkedStack();
			return;
		}
	}
	// 스택에 남은 연산자를 모두 pop 한다.
	while (!s.isEmpty()) {
		*postfix++ = s.pop();
		*postfix++ = ' ';
	}
	postfix--;
	*postfix = '\0';

	// s.~LinkedStack();
	return;
}

// 연산자 여부를 판별한다.
int  isOperator(int  op) {
	return (op == '+' || op == '-' || op == '*' || op == '/');
}

// 연산자 우선순위를 수치로 변환
int  precedence(int op) {
	if (op == '(') return 0;
	else if (op == '+' || op == '-') return 1;
	else if (op == '*' || op == '/') return 2;
	else return 3;
}
