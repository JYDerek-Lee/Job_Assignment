#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define MAX_STACK_SIZE 100
typedef struct {
	int stack[MAX_STACK_SIZE];
	int top;
} StackType;

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
	/*if (is_empty(s)) {
	fprintf(stderr, "���� ���� ����\n");
	exit(1);
	}
	else*/ return s->stack[s->top];
}

int prec(char op) {
	switch (op) {
	case '(': case ')': return 0;
	case '+': case '-': return 1;
	case '*': case '/': return 2;
	}
	return -1;
}
// ���� ǥ�� ���� -> ���� ǥ�� ����
void infix_to_postfix(char exp[]) {
	int i = 0, j = 0, k = 0;
	char ch, top_op, num[64][64] = { 0 };
	int len = strlen(exp);
	StackType s;

	init(&s);
	printf("����ǥ��������� ��ȯ : ");
	for (i = 0; i<len; i++) {
		ch = exp[i];
		switch (ch) {
		case '+': case '-': case '*': case '/': // ������
			// ���ÿ� �ִ� �������� �켱������ �� ũ�ų� ������ ���
			while (!is_empty(&s) && (prec(ch) <= prec(peek(&s)))) {
				printf("%c", pop(&s));
				j++;
				k = 0;
				num[j][k] = pop(&s);
			}
			push(&s, ch);
			j++;
			k = 0;
			break;
		case '(':	// ���� ��ȣ
			push(&s, ch);
			break;
		case ')':	// ������ ��ȣ
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
		default:		// �ǿ�����
			printf("%c", ch);
			num[j][k] = ch;
			k++;
			break;
		}
	}

	while (!is_empty(&s)) {
		printf("%c", pop(&s));
	}

	/*
	while (!top_op == -1) {	// ���ÿ� ����� �����ڵ� ���
		printf("%c", pop(&s));
		j++;
		k = 0;
		num[j][k] = pop(&s);
		top_op = pop(&s);
	}
	printf("\n");
	for (i = 0; i <= j; i++) {
		printf("%s\n", num[i]);
	}
	*/
}

main() {
	char str[50];

	printf("������ �Է��ϼ��� : ");
	gets(str);
	infix_to_postfix(str);
}
