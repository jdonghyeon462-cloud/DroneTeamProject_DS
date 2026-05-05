/*03.c
프로그램 기능:
- 02.txt 파일에 저장된 정렬 좌표 데이터를 읽어온다.
- 각 지점 사이의 이동 구간을 계산한다.
- 연속된 두 지점 사이의 유클리디안 거리를 계산한다.
- 계산된 거리에 따라 배터리 소모 상수 k를 결정한다.

- 배터리 상수 기준:
	거리 100 이하: k = 1.5
	거리 100 초과: k = 1.7

- 배터리 소모량은 거리와 배터리 상수 k를 곱하여 계산한다.
- 계산된 구간명, 거리, k값, 배터리 소모량을 연결 리스트에 저장한다.
- 최종 계산 결과는 화면에 출력하고 03.txt 파일에 저장한다.
- 사용이 끝난 연결 리스트와 동적 할당 메모리를 해제한다.

입력 파일: 02.txt
출력 파일: 03.txt
	*/
#include "cdh.h"

linkedList_h03* createlinkedList_h03(void)
{
	linkedList_h03* L;
	L = (linkedList_h03*)malloc(sizeof(linkedList_h03));	// 연결리스트의 헤드 구조체 동적할당하기
	/*
	malloc 실패 검사 코드 추가
	2026.05.05 10:27 *조동현*
	*/
	if (L == NULL)
	{
		return NULL;
	}
	L->head = NULL;		// 공백 리스트이므로 NULL로 설정
	return L;
}

// 연결 리스트의 전체 메모리를 해제하는 연산
void freeLinkedList_h03(linkedList_h03* L)
{
	listNode03* p;
	/*
	L이 NULL인 경우 해제할 리스트 없으니 검사 코드 추가
	2026.05.05 10:30 *조동현*
	*/
	while (L->head != NULL) {	// head가 NULL이될때 까지 첫번째 노드 하나씩 제거
		p = L->head;
		L->head = L->head->link;	// 중요! 다음 노드로 이동시키기
		free(p);
		p = NULL;
	}
}

// 연결 리스트를 순서대로 출력하는 연산
void printList03(linkedList_h03* L, FILE* fp)
{
	listNode03* p;
	double total_distance = 0;	// 지점들의 거리의 합
	double total_battery = 0;	// 전체 배터리 소모량의 합
	/*
	리스트 또는 파일 포인터가 잘못된 경우 출력하지 않게 하기위한 코드 추가
	2026.05.05 11:39 *조동현*
	*/
	if (L == NULL || fp == NULL)
	{
		return;
	}
	p = L->head;
	//연결리스트 모든 노드 순서대로 출력
	while (p != NULL)
	{
		printf("%-8s %-10.1f %-6.1f %-10.1f\n", p->pointname, p->distance, p->k, p->battery_used);
		fprintf(fp, "%-8s %-10.1f %-6.1f %-10.1f\n\n", p->pointname, p->distance, p->k, p->battery_used);
		total_distance += p->distance;	// 총 거리 누적
		total_battery += p->battery_used;	// 총 배터리 소모량 누적
		p = p->link;	// 중요 ! 다음 노드 이동
	}
	// TOTAL은 확인용으로 화면에 출력한다 만약에 03.txt에 TOTAL을 저장하면 04.c의 fscanf 형식과 맞지 않을 수 있으므로 파일에는 저장하지 않는다.
	printf("%-8s %-10.1f %-6s %-10.1f\n", "TOTAL", total_distance, "-", total_battery);
}

// 마지막 노드로 삽입하는 연산 
void insertLastNode03(linkedList_h03* L, double distance, double k, double battery_used, char* pointname)
{
	listNode03* newNode;
	listNode03* temp;
	// 리스트가 없으면 삽입할 수 없으므로 종료한다.
	if (L == NULL)
	{
		return;
	}
	newNode = (listNode03*)malloc(sizeof(listNode03));
	/*
	노드 동적 할당 실패 검사 하기위한 코드 추가
	2026.05.05 17:29 *조동현*
	*/
	if (newNode == NULL)
	{
		printf("노드 메모리 할당 실패\n");
		return;
	}
	// 새노드에 구간 정보 저장
	newNode->distance = distance;
	newNode->k = k;
	newNode->battery_used = battery_used;
	strcpy(newNode->pointname, pointname);
	newNode->link = NULL;
	if (L->head == NULL)
	{		// 현재 리스트가 공백인 경우					
		L->head = newNode;		// 새 노드를 리스트의 시작 노드로 연결
		return;
	}
	// 현재 리스트가 공백이 아닌 경우 	
	temp = L->head;
	while (temp->link != NULL) temp = temp->link;	// 현재 리스트의 마지막 노드를 찾음
	temp->link = newNode;							// 새 노드를 마지막 노드(temp)의 다음 노드로 연결 
}

int run03()
{
	//printf("한글 출력 확인\n");
	linkedList_h03* L = createlinkedList_h03();
	/* 유효성 검사 코드 추가 *조동현* 2026.05.05 15:29 */
	if (L == NULL)
	{
		printf("리스트 생성 실패\n");
		return 1;
	}
	FILE* p1;
	FILE* p2;
	p1 = fopen("02.txt", "r");
	p2 = fopen("03.txt", "w");
	if (p1 == NULL || p2 == NULL)
	{
		printf("파일 열기 실패\n");
		return 1;
	}

	d* points = (d*)malloc(sizeof(d) * PointMAX);
	if (p1 == NULL || p2 == NULL)
	{
		printf("File open failed\n");

		if (p1 != NULL)
			fclose(p1);

		if (p2 != NULL)
			fclose(p2);

		freeLinkedList_h03(L);
		free(L);

		return 1;
	}

	char pointname;	//지점 이름을 읽을 변수
	int x, y;	//02.txt에서 읽어올 좌표값
	double battery_used;	//배터리 소모량
	double k;	//배터리 상수 100m 이하 1.5, 100m초과 1.7 
	double distance;	//거리
	char trash[TrashMAX];	//02.txt 첫번쨰 헤더 줄 건너뛰기 위한 임시 배열

	fgets(trash, 50, p1);	//한줄 건너뛰기
	for (int i = 0; i < PointMAX; i++)
	{
		/* 유효성 검사 코드 추가 *조동현* 2026.05.05 16:17 */
		if (fscanf(p1, " %c %d %d", &pointname, &x, &y) != 3) {
			printf("%d번째 좌표 읽기 실패\n", i + 1);
			freeLinkedList_h03(L);
			free(L);
			fclose(p1);
			fclose(p2);
			free(points);

			return 1;
		}
		points[i].x = x;
		points[i].y = y;
		points[i].pointname = pointname;
	}

	for (int i = 0; i < PointMAX - 1; i++)	//distance, k, battery_used 계산해서 연결리스트에 저장
	{
		int x1 = points[i].x;
		int x2 = points[i + 1].x;
		int y1 = points[i].y;
		int y2 = points[i + 1].y;
		char sum_pointname[SMAX];
		for (int j = 0; j < 2; j++)	//지점의 이름을 합치는 코드
		{
			sum_pointname[j] = points[i + j].pointname;	//A,B 지점이면 합쳐서 AB를 저장
		}
		sum_pointname[2] = '\0';
		distance = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));	//두 지점 사이의 거리구하는 공식(유클리디안 거리)
		if (distance <= 100)
		{
			k = 1.5;
		}
		else
		{
			k = 1.7;
		}
		battery_used = k * distance;
		/*
		확인용 프롬포트 출력
		2026.05.05 16:20 수정 *조동현*
		printf("INSERT Before %s %.1f %.1f %.1f\n", sum_pointname, distance, k, battery_used);
		*/
		printf("INSERT 전: %s %.1f %.1f %.1f\n", sum_pointname, distance, k, battery_used);
		insertLastNode03(L, distance, k, battery_used, sum_pointname);
	}
	printf("%-8s %-10s %-6s %-10s\n", "구간", "거리", "k", "배터리");
	printList03(L, p2);
	printf("계속 진행하려면 03.txt 파일을 닫으십시오 \n");

	freeLinkedList_h03(L);
	free(L);
	fclose(p1);
	fclose(p2);
	free(points);
	system("notepad.exe 03.txt");
	return 0;
}