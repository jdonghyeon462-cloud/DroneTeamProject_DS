#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

// ==========
// 01.c
// ==========
#define MAX 4
#define SMAX 10

typedef struct dronePosition
{
	int xpos;
	int ypos;
} DP;


// ==========
// 02.c
// ==========
typedef struct ListNode02 // 노드 구조체
{
	char name;
	int x;
	int y;
	struct ListNode02* link;
} listNode02;

typedef struct           // // head 노드를 구조체로 정의
{
	listNode02* head;
} linkedList_h02;

linkedList_h02* createlinkedList_h02(void);
void freelinkedList_h02(linkedList_h02* L);
double getDist02(int x, int y);
void printList02(linkedList_h02* L);
void printListFile02(linkedList_h02* L, FILE* fp);
void insertFirstNode02(linkedList_h02* L, int a, int b);
void insertMiddleNode02(linkedList_h02* L, listNode02* pre, int a, int b);
void insertLastNode02(linkedList_h02* L, int a, int b);
listNode02* searchNode02(linkedList_h02* L, int a, int b);
listNode02* searchPreNode02(linkedList_h02* L, listNode02* temp);

// ==========
// 03.c
// ==========
#define PointMAX 5	// 지점 개수
#define TrashMAX 50	//필요 없는 줄을 저장 시킬 휴지통 역할 배열 크기

typedef struct ListNode03
{
	char pointname[3];
	double distance;
	double k;
	double battery_used;
	struct ListNode03* link;
} listNode03;

// 리스트의 시작을 나타내는 head 노드를 구조체로 정의
typedef struct
{
	listNode03* head;
} linkedList_h03;

typedef struct Distance	//지점간 거리를 구할 때 사용할 구조체 배열
{
	char pointname;	//지점 이름
	int x;
	int y;
} d;

linkedList_h03* createlinkedList_h03(void);
void freeLinkedList_h03(linkedList_h03* L);
void printList03(linkedList_h03* L, FILE* fp);
void insertLastNode03(linkedList_h03* L, double distance, double k, double battery_used, char* pointname);


// ==========
// 04.c
// ==========
#define TSIZE 20
#define BACKSIZE 30

typedef struct route {
	char section[TSIZE];
	double distance04;
	double k04;
	double battery04;
	double total04;
	int state04;
	int event04;
} route;

typedef struct stacknode {
	route data04;
	struct stacknode* link04;
} stacknode;

void clearstack();
void push(route data);
int pop(route* out);
void printLine(FILE* fp2);
void printHeader(FILE* fp2);
void printRow(FILE* fp2, route data, char backroute[]);


// ==========
// DroneProject.c
// ==========
int run01();
int run02();
int run03();
int run04();
