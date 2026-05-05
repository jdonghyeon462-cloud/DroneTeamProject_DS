#include "cdh.h"

int main() {
    int repeat = 1, run;

    do {
        printf("자폭 드론 시뮬레이터를 실행합니다.\n");

        printf("\n===================================\n");
        printf("[STEP 1] 01.c 실행\n");
        run = run01();
        if (run == 1)
        {
            printf("[ERROR] 01.c 실행 실패\n");
            break;
        }

        printf("\n===================================\n");
        printf("[STEP 2] 02.c 실행\n");
        run = run02();
        if (run == 1)
        {
            printf("[ERROR] 02.c 실행 실패\n");
            break;
        }

        printf("\n===================================\n");
        printf("[STEP 3] 03.c 실행\n");
        run = run03();
        if (run == 1)
        {
            printf("[ERROR] 03.c 실행 실패\n");
            break;
        }

        printf("\n===================================\n");
        printf("[STEP 4] 04.c 실행\n");
        run = run04();
        if (run == 1)
        {
            printf("[ERROR] 04.c 오류발생\n");
            break;
        }

        do
        {
            printf("다시 실행하시겠습니까?(Yes: 1, No: 0)\n");
            scanf("%d", &repeat);
            if (repeat != 0 && repeat != 1)
                printf("0또는 1로 입력하시오.\n");
            else if (repeat == 1)
                printf("프로그램을 재실행합니다.\n");
        } while (repeat != 0 && repeat != 1);

    } while (repeat);

    printf("프로그램을 종료합니다.\n");
    return 0;
}