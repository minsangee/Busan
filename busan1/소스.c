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
#define MOVE_LEFT 1
#define MOVE_STAY 0
#define ATK_NONE 0
#define ATK_CITIZEN 1
#define ATK_DONGSEOK 2
#define ACTION_REST 0
#define ACTION_PROVOKE 1
#define ACTION_PULL 2
// 인트로
void intro() {
    printf("부 산 행 I N T R O \n");
    Sleep(3000); // 3초 대기
    system("cls"); // 화면 지우기
}
//열차 길이 설정
int train() {
    int len;
    do {
        printf("열차 길이 설정(%d ~ %d)>> ", LEN_MIN, LEN_MAX);
        if (scanf_s("%d", &len) != 1) {
            while (getchar() != '\n'); 
            len = 0;
        }
    } while (len < LEN_MIN || len > LEN_MAX);
    return len;
}
//확률 설정
int probability() {
    int prob;
    do {
        printf("열차 확률 'p' 설정(%d ~ %d)>> ", PROB_MIN, PROB_MAX);
        if (scanf_s("%d", &prob) != 1 || prob < PROB_MIN || prob > PROB_MAX) {
            while (getchar() != '\n');
            prob = 0;
        }
    } while (prob < PROB_MIN || prob > PROB_MAX);
    return prob;
}
// 마동석 체력 설정
int MDSSTM() {
    int stm;
    do {
        printf("마동석 체력 설정(%d ~ %d)>> ", STM_MIN, STM_MAX);
        if (scanf_s("%d", &stm) != 1) {
            while (getchar() != '\n');
            stm = 0;
        }
    } while (stm < STM_MIN || stm > STM_MAX);
    return stm;
}
// 어그로 설정
int aggro() {
    int agro;
    do {
        printf("어그로 설정(%d ~ %d)>> ", AGGRO_MIN, AGGRO_MAX);
        if (scanf_s("%d", &agro) != 1) {
            while (getchar() != '\n');
            agro = 0;
        }
    } while (agro < STM_MIN || agro > STM_MAX);
    return agro;
}
// 열차와 시민, 좀비의 위치를 출력하는 함수
void printTrain(int len, int Clo, int Zlo) {
    int M = 'M';
    int C = 'C';
    int Z = 'Z';

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < len; ++j) {
            if (j == 0 || j == len - 1) {
                printf("#");
            }
            else if (i == 1) {
                if (j == len - 2) {
                    printf("%c", M); 
                }
                else if (j == Zlo) {
                    printf("%c", Z); 
                }
                else if (j == Clo) {
                    printf("%c", C); 
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
// 시민과 좀비의 위치를 이동시키는 함수
void moveEntities(int* Clo, int* Zlo, int prob, int count) {
    if (rand() % 100 < (100 - prob)) {
        (*Clo)--; // 확률에 따라 시민의 위치 이동
    }
    if (count % 2 != 0 && rand() % 100 < prob) {
        (*Zlo)--; // 확률에 따라 좀비의 위치 이동
    }
}
// 시민과 좀비의 상태를 출력하는 함수
void Citizenmov(int Clo, int prevClo, int prob, int count) {
    if (prevClo != Clo) {
        printf("citizen: %d -> %d\n", prevClo, Clo); // 시민의 위치 변경 출력
    }
    else {
        printf("citizen: stay %d\n", Clo); // 시민의 위치 유지 출력
    }
}

// 좀비 상태 출력 함수
int Zombimov(int Zlo, int prevZlo)
if (count % 2 == 0) {
    printf("zombie cannot move\n\n"); // 좀비가 이동하지 않는 경우 출력
}
else {
    if (rand() % 100 < prob) {
        printf("zombie : %d -> %d\n\n", prevZlo, Zlo); // 좀비의 위치 변경 출력
    }
    else {
        printf("zombie: stay %d\n\n", Zlo); // 좀비의 위치 유지 출력
    }
//마동석 상태 출력 함수
int Mdsmov(int Mlo) { 
    if ()
}

// 게임 종료 조건을 확인하고 메시지를 출력하는 함수
void outro(int Clo, int Zlo) {
    if (Clo == 1) {
        printf("시민이 열차 끝에 도착했습니다. 시민이 열차를 탈출했습니다.\n");
        exit(0); // 시민이 열차를 탈출한 경우 프로그램 종료
    }
    if (Zlo == Clo + 1) {
        printf("시민이 좀비에게 물렸습니다. 시민 사망.\n");
        exit(0); // 좀비가 시민을 잡은 경우 프로그램 종료
    }
}
int main(void) {
    srand((unsigned int)time(NULL)); // 난수 생성 초기화
    intro(); // 소개 메시지 출력
    int len = train(); // 열차 길이 입력 받기
    int prob = probability(); // 확률 입력 받기
    int stm = MDSSTM(); // 마동석 체력 입력 받기
    int agro = aggro(); // 어그로 입력 받기
    int Clo = len - 6; // 초기 시민 위치 설정
    int Zlo = len - 3; // 초기 좀비 위치 설정
    int count = 0; // 이동 횟수 초기화

    printTrain(len, Clo, Zlo); // 초기 열차 상태 출력
    // 게임 루프
    while (1) {
        int prevClo = Clo, prevZlo = Zlo; // 이전 위치 저장
        moveEntities(&Clo, &Zlo, prob, count); // 시민과 좀비 이동
        printTrain(len, Clo, Zlo); // 현재 열차 상태 출력
        printStatus(Clo, Zlo, prevClo, prevZlo, prob, count); // 현재 상태 출력
        outro(Clo, Zlo); // 게임 종료 조건 확인
        Sleep(4000); // 4초 대기
        count++; // 이동 횟수 증가
    }
    return 0;
}
// 일단 부산행 1처럼 진행 -> 이동 함수 이후 마동석 함수
// 마동석은 0 or 1을 입력받아 이동 혹은 중지 가능
// if 마동석 =< 시민 어그로 면 좀비는 시민쪽 아니면 반대쪽
// stm도 구현해서 입력받게 하기
// 마동석 이동 행동 따로, 휴식 도발 붙들기 따로
// 붙들기 if문 행동 성공시, 실패시 문구 출력
// 