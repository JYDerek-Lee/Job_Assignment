#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 100

typedef struct {
	int stack[MAX_STACK_SIZE];
	int top;
} StackType;

typedef struct {
	char data[64];
} Buffer;

// 스택 초기화 함수
void init(StackType *s) {
	s->top = -1;
}
// 공백 상태 검출 함수
int is_empty(StackType *s) {
	return (s->top == -1);
}
// 포화 상태 검출 함수
int is_full(StackType *s) {
	return (s->top == (MAX_STACK_SIZE - 1));
}
// 삽입함수
void push(StackType *s, int item) {
	if (is_full(s)) {
		fprintf(stderr, "스택 포화 에러\n");
		return;
	}
	else s->stack[++(s->top)] = item;
}
// 삭제함수
int pop(StackType *s) {
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else return s->stack[(s->top)--];
}
// 피크함수
int peek(StackType *s) {
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else return s->stack[s->top];
}

int prec(char op) {
	switch (op) {
	case '(': case ')': return 0;
	case '+': case '-': return 1;
	case '*': case '/': return 2;
	}
	return -1;
}

int eval(int p_len, char p_num[][20]) { // 계산
	int op1 = 0, op2 = 0, value = 0, i = 0, j = 0;
	StackType s;

	init(&s);
	for (i = 0; i<p_len; i++) {
		char temp[20] = { 0 };
		char m_temp = NULL;
		strcpy(temp, p_num[i]);

		m_temp = temp[0];
		if (m_temp != '+' && m_temp != '-' && m_temp != '*' && m_temp != '/') {
			value = atoi(temp); // 입력이 피연산자이면
			push(&s, value);
		}
		else {   //연산자이면 피연산자를 스택에서 제거
			op2 = pop(&s);
			op1 = pop(&s);
			switch (m_temp) { //연산을 수행하고 스택에 저장 
			case '+': push(&s, op1 + op2); break;
			case '-': push(&s, op1 - op2); break;
			case '*': push(&s, op1*op2); break;
			case '/': push(&s, op1 / op2); break;
			}
		}
	}
	return pop(&s);
}

// 중위 표기 수식 -> 후위 표기 수식
void infix_to_postfix(char p_exp[]) {
	int i = 0, j = 0, k = 0;
	char ch, top_op, num[10][20] = { 0 };
	int len = strlen(p_exp);
	StackType s;

	init(&s);
	printf("후위표기수식으로 변환 : ");
	for (i = 0; i<len; i++) {
		ch = p_exp[i];
		switch (ch) {
		case '+': case '-': case '*': case '/': // 연산자
			// 스택에 있는 연산자의 우선순위가 더 크거나 같으면 출력
			while (!is_empty(&s) && (prec(ch) <= prec(peek(&s)))) {
				j++;
				k = 0;
				num[j][k] = pop(&s);
				printf("%c", num[i]);
			}
			push(&s, ch);
			j++;
			k = 0;
			break;
		case '(':   // 왼쪽 괄호
			push(&s, ch);
			break;
		case ')':   // 오른쪽 괄호
			top_op = pop(&s);
			// 왼쪽 괄호를 만날때까지 출력
			while (top_op != '(') {
				printf("%c", top_op);
				j++;
				k = 0;
				num[j][k] = top_op;
				top_op = pop(&s);
			}
			break;
		default:      // 피연산자
			printf("%c", ch);
			num[j][k] = ch;
			k++;
			break;
		}
	}
	while (!is_empty(&s)) {   // 스택에 저장된 연산자들 출력
		j++;
		k = 0;
		num[j][k] = pop(&s);
		printf("%c", num[i]);
	}
	printf("\n");

	int re = eval(j+1, num);
	printf("%d", re);
}

void main() {
	char str[50] = {"(2+10)*2"};

	printf("수식을 입력하세요 : ");
	//gets(str);
	infix_to_postfix(str);
}