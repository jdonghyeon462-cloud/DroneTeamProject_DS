/*01.c
프로그램 기능:
- 드론 지휘통제실에서 사용할 좌표 데이터를 생성한다.
- 시작 지점은 항상 (0, 0)으로 고정한다.
- 이후 MAX개의 좌표를 난수로 생성한다.

- 생성 범위:
	xpos: 0 ~ 500
	ypos: 0 ~ 50
- 시작 지점 (0, 0)과 중복되는 좌표는 저장하지 않는다.
- 이미 생성된 좌표와 중복되는 좌표도 저장하지 않는다.
- 최종 좌표 데이터는 01.txt 파일에 저장한다.
	*/
#include "cdh.h"

int run01()
{
	FILE* fp = fopen("01.txt", "w");
	if (fp == NULL)
	{
		printf("파일 생성 실패\n");
		return 1;
	}

	DP* p;
	p = (DP*)malloc(sizeof(DP) * MAX);

	if (p == NULL)
	{
		printf("메모리 할당 실패\n");
		fclose(fp);
		return 1;
	}
	printf("지휘통제실에서 좌표를 전파합니다!!\n");
	// 아래 srand 를 사용한 이유는 실행할때마다 다른 난수를 생성하기 위함임
	// 현재 시간을 기준으로 난수 초기값을 설정함
	srand((unsigned int)time(NULL));
	// 시작 지점 (0,0) 으로 지정함
	int x1 = 0, y1 = 0;
	int count = 0;

	while (count < MAX)
	{
		int xpos = rand() % 501;		//xpos의 범위는 0~500 , ypos의 범위는 0~50 
		int ypos = rand() % 51;			// 왜 둘의 범위가 다른가 ? 자폭드론의 경우 높이보단, 더 높이가 아닌 더 멀리 날아가서 임무를 수행하기 때문임
		int samePosition = 0;			// 중복일 경우를 제외하기 위한 변수 samePosition 
		// 1일때 중복 0일땐 중복이 아님
		if (xpos == x1 && ypos == y1)	// 시작 지점 (0,0) 과 같은 좌표 제외하기 위한 조건문if
		{
			samePosition = 1;	// 왜 같은 경우 1이냐 같다면 true 1, 다르다면 false 0 으로 구분하기 위함
		}
		// 아래 코드부턴 저장한 좌표와 중복되는지 확인하기 위함임
		for (int i = 0; i < count; i++)
		{
			if ((p + i)->xpos == xpos && (p + i)->ypos == ypos)
			{
				samePosition = 1;
				break;
			}
		}

		if (samePosition == 0)		// 0이므로 서로 다른 좌표이다 즉 아래는 저장할 변수임
		{
			(p + count)->xpos = xpos;		
			(p + count)->ypos = ypos;
			count++;				// count변수는 횟수가 아닌 중복이 아닌것을 성공적으로 저장한 좌표 개수임!
		}
	}
	// 시작지점 (0,0) 을 화면과 파일에 출력하는 것
	printf("%d %d\n", x1, y1);
	fprintf(fp, "%d %d\n", x1, y1);
	// MAX 는 4 임 즉 4번 생성한것을 화면, 파일에 출력하는 것
	// 즉 서로 다른 좌표를 저장한것을 화면과 파일에 출력하는 코드임
	for (int i = 0; i < MAX; i++)	
	{
		printf("%d %d\n", (p + i)->xpos, (p + i)->ypos);
		fprintf(fp, "%d %d\n", (p + i)->xpos, (p + i)->ypos);
	}
	printf("계속 진행하려면 01.txt 파일을 닫으십시오 \n");
	free(p);
	fclose(fp);

	system("notepad.exe 01.txt");	// 텍스트 파일 자동 생성
	return 0;
}