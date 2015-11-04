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

// ���� �ʱ�ȭ �Լ�
void init(StackType *s) {
	s->top = -1;
}
// ���� ���� ���� �Լ�
int is_empty(StackType *s) {
	return (s->top == -1);
}
// ��ȭ ���� ���� �Լ�
int is_full(StackType *s) {
	return (s->top == (MAX_STACK_SIZE - 1));
}
// �����Լ�
void push(StackType *s, int item) {
	if (is_full(s)) {
		fprintf(stderr, "���� ��ȭ ����\n");
		return;
	}
	else s->stack[++(s->top)] = item;
}
// �����Լ�
int pop(StackType *s) {
	if (is_empty(s)) {
		fprintf(stderr, "���� ���� ����\n");
		exit(1);
	}
	else return s->stack[(s->top)--];
}
// ��ũ�Լ�
int peek(StackType *s) {
	if (is_empty(s)) {
		fprintf(stderr, "���� ���� ����\n");
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

int eval(int p_len, char p_num[][20]) { // ���
	int op1 = 0, op2 = 0, value = 0, i = 0, j = 0;
	StackType s;

	init(&s);
	for (i = 0; i<p_len; i++) {
		char temp[20] = { 0 };
		char m_temp = NULL;
		strcpy(temp, p_num[i]);

		m_temp = temp[0];
		if (m_temp != '+' && m_temp != '-' && m_temp != '*' && m_temp != '/') {
			value = atoi(temp); // �Է��� �ǿ������̸�
			push(&s, value);
		}
		else {   //�������̸� �ǿ����ڸ� ���ÿ��� ����
			op2 = pop(&s);
			op1 = pop(&s);
			switch (m_temp) { //������ �����ϰ� ���ÿ� ���� 
			case '+': push(&s, op1 + op2); break;
			case '-': push(&s, op1 - op2); break;
			case '*': push(&s, op1*op2); break;
			case '/': push(&s, op1 / op2); break;
			}
		}
	}
	return pop(&s);
}

// ���� ǥ�� ���� -> ���� ǥ�� ����
void infix_to_postfix(char p_exp[]) {
	int i = 0, j = 0, k = 0;
	char ch, top_op, num[10][20] = { 0 };
	int len = strlen(p_exp);
	StackType s;

	init(&s);
	printf("����ǥ��������� ��ȯ : ");
	for (i = 0; i<len; i++) {
		ch = p_exp[i];
		switch (ch) {
		case '+': case '-': case '*': case '/': // ������
			// ���ÿ� �ִ� �������� �켱������ �� ũ�ų� ������ ���
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
		case '(':   // ���� ��ȣ
			push(&s, ch);
			break;
		case ')':   // ������ ��ȣ
			top_op = pop(&s);
			// ���� ��ȣ�� ���������� ���
			while (top_op != '(') {
				printf("%c", top_op);
				j++;
				k = 0;
				num[j][k] = top_op;
				top_op = pop(&s);
			}
			break;
		default:      // �ǿ�����
			printf("%c", ch);
			num[j][k] = ch;
			k++;
			break;
		}
	}
	while (!is_empty(&s)) {   // ���ÿ� ����� �����ڵ� ���
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

	printf("������ �Է��ϼ��� : ");
	//gets(str);
	infix_to_postfix(str);
}