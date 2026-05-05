// 01.txt 파일을 읽어서 정렬하면서 연결리스트에 삽입하고 파일에 출력
/*02.c
프로그램 기능:
- 01.txt 파일에 저장된 좌표 데이터를 읽어온다.
- 읽어온 좌표를 원점(0, 0)으로부터의 거리 기준으로 정렬한다.
- 정렬 방식은 연결 리스트에 좌표를 삽입하면서 거리 오름차순이 유지되도록 한다.

- 거리 계산 기준:
	sqrt(x * x + y * y)

- 정렬된 좌표에는 A, B, C 순서로 Point 이름을 부여한다.
- 정렬 결과는 화면에 출력하고 02.txt 파일에 저장한다.
- 사용이 끝난 연결 리스트의 동적 할당 메모리를 해제한다.

입력 파일: 01.txt

출력 파일: 02.txt
	*/
#include "cdh.h"

// 공백 연결 리스트를 생성하는 연산
linkedList_h02* createlinkedList_h02(void)
{
	linkedList_h02* L;
	L = (linkedList_h02*)malloc(sizeof(linkedList_h02));
	L->head = NULL;		// 공백 리스트이므로 NULL로 설정
	return L;
}

// 연결 리스트의 전체 메모리를 해제하는 연산
void freelinkedList_h02(linkedList_h02* L)
{
	listNode02* p;
	while (L->head != NULL)
	{
		p = L->head;
		L->head = L->head->link;
		free(p);
		p = NULL;
	}
}

// 원점기준 거리를 구하는 연산
double getDist02(int x, int y)
{
	double dist = sqrt((double)x * x + (double)y * y); // 오버플로우 방지를 위한 형변환
	return dist;
}

// 연결 리스트를 순서대로 화면과 파일에 출력하는 연산
void printList02(linkedList_h02* L, FILE* fp)
{
	listNode02* p;
	p = L->head;
	fprintf(fp, "%-6s %-6s %-6s\n", "Point", "X", "Y");
	fprintf(stdout, "%-6s %-6s %-6s\n", "Point", "X", "Y");
	while (p != NULL)
	{
		fprintf(fp, "%-6c %-6d %-6d\n", p->name, p->x, p->y);
		fprintf(stdout, "%-6c %-6d %-6d %-10.2lf\n", p->name, p->x, p->y, getDist02(p->x, p->y));
		p = p->link;
	}
}

// 첫 번째 노드로 삽입하는 연산
void insertFirstNode02(linkedList_h02* L, int a, int b)
{
	listNode02* newNode;
	newNode = (listNode02*)malloc(sizeof(listNode02));	// 삽입할 새 노드 할당
	newNode->x = a;
	newNode->y = b;
	newNode->link = L->head;
	L->head = newNode;
}

// 노드를 pre 뒤에 삽입하는 연산
void insertMiddleNode02(linkedList_h02* L, listNode02* pre, int a, int b)
{
	listNode02* newNode;
	newNode = (listNode02*)malloc(sizeof(listNode02));
	newNode->x = a;
	newNode->y = b;
	if (L->head == NULL)			// 공백 리스트인 경우
	{
		newNode->link = NULL;		// 새 노드를 첫 번째이자 마지막 노드로 연결
		L->head = newNode;
	}
	else if (pre == NULL)			// 삽입 위치를 지정하는 포인터 pre가 NULL인 경우
	{
		newNode->link = L->head;
		L->head = newNode;			// 새 노드를 첫 번째 노드로 삽입
	}
	else
	{
		newNode->link = pre->link;	// 포인터 pre의 노드 뒤에 새 노드 연결
		pre->link = newNode;
	}
}

// 마지막 노드로 삽입하는 연산 
void insertLastNode02(linkedList_h02* L, int a, int b)
{
	listNode02* newNode;
	listNode02* temp;
	newNode = (listNode02*)malloc(sizeof(listNode02));
	newNode->x = a;
	newNode->y = b;
	newNode->link = NULL;
	if (L->head == NULL)		// 현재 리스트가 공백인 경우
	{
		L->head = newNode;		// 새 노드를 리스트의 시작 노드로 연결
		return;
	}
	// 현재 리스트가 공백이 아닌 경우 	
	temp = L->head;
	while (temp->link != NULL)
		temp = temp->link;		// 현재 리스트의 마지막 노드를 찾음
	temp->link = newNode;		// 새 노드를 마지막 노드(temp)의 다음 노드로 연결 
}

// 새로운 노드가 들어갈 곳은 찾는 연산
listNode02* searchNode02(linkedList_h02* L, int a, int b)
{
	listNode02* temp;
	double new_dist, cur_dist;
	new_dist = getDist02(a, b);
	temp = L->head;
	while (temp != NULL) // temp가 순회하면서 삽입할 노드의 거리보다 현재 거리가 더 크면 위치 반환
	{
		cur_dist = getDist02(temp->x, temp->y);
		if (new_dist <= cur_dist)
			return temp;
		else
			temp = temp->link;
	}
	// 삽입할 노드의 거리가 가장 클 때 NULL 반환
	return temp;
}

// 노드를 중간에 삽입하려면 이전 노드를 알아야 하기 때문에 이전 노드를 찾는 연산
listNode02* searchPreNode02(linkedList_h02* L, listNode02* temp)
{
	listNode02* pre;
	pre = L->head; // 헤드부터 탐색 시작
	// pre가 연결리스트를 순회하면서 temp 전 노드의 주소 반환
	while (pre != NULL)
	{
		if (pre->link == temp)
			return pre;
		else
			pre = pre->link;
	}
	// temp를 찾지 못하는 경우 이전 노드가 헤드이기 때문에 NULL 반환
	return pre;
}

// Point 이름을 붙이는 함수
void naming02(linkedList_h02* L)
{
	char n = 'A';
	listNode02* p;
	p = L->head;
	// p가 연결리스트를 순회하면서 노드에 이름을 저장함
	while (p != NULL)
	{
		p->name = n++;
		p = p->link;
	}
}

int run02() {
	FILE* fp1, * fp2, * fp3; // 각각 01.txt, 02.txt를 위한 파일포인터
	int x, y, nodeCount = 0;
	listNode02* p, * pre;
	linkedList_h02* L; // head 주소를 가지고 있는 구조체를 가리키는 포인터

	printf("지휘통제실에서 좌표를 라우팅합니다!!\n");
	printf("입력파일: 01.txt\n");
	printf("출력파일: 02.txt\n");
	printf("정렬 기준: 원점(0,0)으로부터의 거리\n");

	fp1 = fopen("01.txt", "r");
	fp2 = fopen("02.txt", "w");
	fp3 = fopen("04.txt", "a+");
	L = createlinkedList_h02();

	// 파일을 다 읽을 때까지 반복해서 거리기준으로 위치를 찾아서 연결리스트 노드 삽입
	while (fscanf(fp1, "%d %d", &x, &y) != EOF)
	{
		p = searchNode02(L, x, y);
		if (p == NULL) { // 노드 중 거리가 가장 클 때
			insertLastNode02(L, x, y);
		}
		else {
			pre = searchPreNode02(L, p);
			if (pre == NULL) { // 이전 노드가 헤드일 경우
				insertFirstNode02(L, x, y);
			}
			else {
				insertMiddleNode02(L, pre, x, y);
			}
		}
		nodeCount++;
	}

	fclose(fp1); // 파일을 다 읽었으므로 파일 닫기
	naming02(L);

	printList02(L, fp2); // 파일과 화면에 리스트 출력
	fprintf(fp3, "\n[데이터 추가 날짜] %s %s\n", __DATE__, __TIME__);
	printList02(L, fp3); // 파일과 화면에 리스트 출력

	fclose(fp2); // 파일에 쓰고 나서 파일 닫기
	fclose(fp3); // 파일에 쓰고 나서 파일 닫기

	printf("\n총 노드 개수: %d\n", nodeCount);

	printf("\n정렬 완료! 결과는 02.txt에 저장되었습니다.\n");
	printf("계속 진행하려면 02.txt 파일을 닫으십시오 \n");

	freelinkedList_h02(L); // 연결리스트 동적 할당 메모리 해제
	free(L); // 헤드 구조체 동적 할당 메모리 해제
	system("notepad.exe 02.txt");
	return 0;
}