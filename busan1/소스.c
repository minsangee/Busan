#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>
#include <time.h>

#define LEN_MIN 15
#define LEN_MAX 50
#define STM_MIN 0
#define STM_MAX 5
#define PROB_MIN 10
#define PROB_MAX 90
#define AGGRO_MIN 0
#define AGGRO_MAX 5
// 마동석 이동 방향
#define MOVE_LEFT 1
#define MOVE_STAY 0
// 좀비의 공격 대상
#define ATK_NONE 0
#define ATK_CITIZEN 1
#define ATK_DONGSEOK 2
// 마동석 행동
#define ACTION_REST 0
#define ACTION_PROVOKE 1
#define ACTION_PULL 2
// 전역 변수 설정
int len;
int prob;
int stm;
int Mgro = 1;
int Cgro = 1;
int Clo;
int Zlo;
int Mlo;
int count;
// 인트로 함수
void intro() {
    printf("부 산 행 I N T R O \n");
}
// 열차 길이 설정
int train() {
    int len;
    do {
        printf("열차 길이 설정(%d ~ %d)>> ", LEN_MIN, LEN_MAX);
        scanf_s("%d", &len);
        while (getchar() != '\n');
    } while (len < LEN_MIN || len > LEN_MAX);
    return len;
}
// 확률 설정
int probability() {
    int prob;
    do {
        printf("열차 확률 'p' 설정(%d ~ %d)>> ", PROB_MIN, PROB_MAX);
        scanf_s("%d", &prob);
        while (getchar() != '\n');
    } while (prob < PROB_MIN || prob > PROB_MAX);
    return prob;
}
// 마동석 체력 설정
int MDSSTM() {
    int stm;
    do {
        printf("마동석 체력 설정(%d ~ %d)>> ", STM_MIN, STM_MAX);
        scanf_s("%d", &stm);
        while (getchar() != '\n');
    } while (stm < STM_MIN || stm > STM_MAX);
    return stm;
}
// 마동석 이동 함수
int MDSmov() {
    int command;
    do {
        printf("\nmadongseok move(0: stay, 1: left)>> ");
        scanf_s("%d", &command);
        while (getchar() != '\n');

        int prevMlo = Mlo; // 이전 위치 저장

        // 마동석과 좀비가 인접하거나 같은 위치인 경우
        if (Mlo == Zlo + 1) {
            printf("마동석은 좀비와 인접해 있어 강제로 휴식을 취합니다.\n");
            command = MOVE_STAY;
        }

        if (command == MOVE_LEFT) {
            if (Mlo > 0) {
                Mlo--;
                if (Mgro < AGGRO_MAX) Mgro += 1; // 어그로 증가
                printf("madongseok: %d -> %d (aggro: %d, stamina: %d)\n\n", prevMlo, Mlo, Mgro, stm); // 마동석 위치 출력
            }
            break;
        }
        else if (command == MOVE_STAY) {
            if (Mgro > AGGRO_MIN) Mgro -= 1; // 어그로 감소
            printf("madongseok: stay %d (aggro: %d, stamina: %d)\n\n", Mlo, Mgro, stm); // 마동석 위치 유지 출력
            break;
        }
        else {
            printf("\n");
        }
    } while (command != MOVE_STAY && command != MOVE_LEFT);
    return Mlo;
}


// 기차 생성 함수
void printTrain(int len, int Clo, int Zlo, int Mlo) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < len; ++j) {
            if (j == 0 || j == len - 1) {
                printf("#");
            }
            else if (i == 1) {
                if (j == Mlo) {
                    printf("M");
                }
                else if (j == Zlo) {
                    printf("Z");
                }
                else if (j == Clo) {
                    printf("C");
                }
                else {
                    printf(" ");
                }
            }
            else {
                printf("#");
            }
        }
        printf("\n");
    }
}
// 시민 움직임
int Citizenmov() {
    int prevClo = Clo;
    if (Clo != 1 && rand() % 100 < (100 - prob)) { // 시민이 열차의 시작점에 도착하지 않았고, 이동 확률에 따라
        Clo--;
    }
    if (prevClo != Clo) {
        if (Cgro < AGGRO_MAX) Cgro += 1; // 어그로 증가
        printf("citizen: %d -> %d (aggro: %d)\n", prevClo, Clo, Cgro);
    }
    else {
        if (Cgro > AGGRO_MIN) Cgro -= 1; // 어그로 감소
        printf("citizen: stay %d (aggro: %d)\n",Clo, Cgro); // 시민이 움직이지 않음
    }
    if ((Zlo - Clo) != 1) { // 좀비와 시민, 마동석 모두 인접하지 않은 경우
        printf("citizen does nothing.\n");
    }
    return Clo;
}
// 좀비 움직임
int Zombimov() {
    int prevZlo = Zlo; // 이전 좀비 위치 저장
    int targetLo = Mgro > Cgro ? Mlo : Clo; // 어그로 수치에 따른 목표 위치 결정

    // 좀비가 마동석을 공격하는 경우
    if (Mgro > Cgro && (Mlo - Zlo) == 1) {
        printf("Zombie attacked madongseok (aggro: %d vs %d, madongseok stamina %d -> %d)\n", Cgro, Mgro, stm, stm-1);
        stm -= 1;
        if (stm == STM_MIN) {
            printf("게임 오버. 마동석 사망.\n");
            exit(0);
        }
        return Zlo; // 좀비는 이동하지 않음
    }

    // 좀비 움직임 처리 (홀수 턴에만 움직임)
    if (count % 2 != 0) {
        // 대상이 좀비보다 오른쪽에 있으며 마동석과 겹치지 않는 경우
        if (Zlo < targetLo && (Mlo - Zlo) != 1) {
            Zlo++;
        }
        // 대상이 좀비보다 왼쪽에 있을 때
        else if (Zlo > targetLo) {
            Zlo--;
        }
        // 좀비의 위치가 변경되었다면, 이를 출력
        if (prevZlo != Zlo) {
            printf("zombie : %d -> %d\n", prevZlo, Zlo);
        }
    }
    else {
        printf("zombie cannot move %d \n", Zlo);
    }

    // 좀비와 시민, 마동석 모두 인접하지 않은 경우
    if ((Zlo - Clo) != 1 && (Mlo - Zlo) != 1) {
        printf("zombie attacked nobody.\n");
    }

    return Zlo;
}



// 아웃트로
void outro(int Clo, int Zlo) {
    if (Clo == 1) {
        printf("시민이 열차 끝에 도착했습니다. 시민이 열차를 탈출했습니다.\n");
        exit(0);
    }
    if (Zlo == Clo + 1) { // 시민이 좀비와 인접한 경우
        printf("시민이 좀비에게 물렸습니다. 시민 사망.\n");
        exit(0);
    }
    if (abs(Zlo - Clo) == 1 && abs(Zlo - Mlo) == 1) { // 둘 다 인접한 경우
        if (Cgro >= Mgro) { // 시민의 어그로가 더 높거나 같은 경우
            printf("시민이 좀비에게 물렸습니다. 시민 사망.\n");
            exit(0);
        }
    }
}

// 메인함수
int main(void) {
    srand((unsigned int)time(NULL)); // 난수 생성 초기화
    intro(); // 인트로 출력 후 유지(임의 설정)
    len = train(); // 열차 길이 입력 받기
    prob = probability(); // 확률 입력 받기
    stm = MDSSTM(); // 마동석 체력 입력 받기
    Clo = len - 6; // 초기 시민 위치 설정
    Zlo = len - 3; // 초기 좀비 위치 설정
    Mlo = len - 2; // 마동석 초기 위치 설정
    count = 0; // 이동 횟수 초기화
    printTrain(len, Clo, Zlo, Mlo); // 초기 열차 상태 출력
    // 게임 루프
    while (1) {
        // 현재 열차 상태 출력
        printTrain(len, Clo, Zlo, Mlo);

        int prevClo = Clo;
        int prevZlo = Zlo;
        int prevMlo = Mlo;

        Clo = Citizenmov(); // 시민 이동
        Zlo = Zombimov(); // 좀비 이동

        // 변경된 부분만 출력
        if (prevClo != Clo || prevZlo != Zlo) {
            printTrain(len, Clo, Zlo, Mlo);
        }

        Mlo = MDSmov(); // 마동석 이동 <- 여기 위치 변경
        outro(Clo, Zlo); // 게임 종료 조건 확인
        count++; // 이동 횟수 증가
    }
    return 0;
}
