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
int Mgro;
int Cgro;
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
        printf("madongseok move(0.rest, 1.provoke)>> ");
        scanf_s("%d", &command);
        while (getchar() != '\n');

        if (Mlo == Zlo - 1 || Mlo == Zlo + 1) { // 마동석과 좀비가 인접한 경우
            if (command == ACTION_REST) {
                if (Mgro > AGGRO_MIN) Mgro -= 1; // 어그로 감소
                if (Mgro < AGGRO_MIN) Mgro = AGGRO_MIN; // 어그로 최소값 유지
                printf("madongseok: stay %d (aggro: %d, stamina: %d)\n", Mlo, Mgro, stm); // 마동석 위치 유지 출력
            }
            else {
                Mgro -= 1;
                if (Mgro < AGGRO_MIN) Mgro = AGGRO_MIN; // 어그로 최소값 유지
                printf("madongseok: cannot move, only rest (aggro: %d, stamina: %d)\n", Mgro, stm);
            }
            break;
        }

        if (command == ACTION_PROVOKE) {
            if (Mlo > 0) {
                Mlo--;
                if (Mgro < AGGRO_MAX) Mgro += 1; // 어그로 증가
                printf("madongseok: %d -> %d (aggro: %d, stamina: %d)\n", Mlo + 1, Mlo, Mgro, stm); // 마동석 위치 출력
            }
            break;
        }
        else if (command == ACTION_REST) {
            if (Mgro > AGGRO_MIN) Mgro -= 1; // 어그로 감소
            printf("madongseok: stay %d (aggro: %d)\n", Mlo, Mgro); // 마동석 위치 유지 출력
            break;
        }
        else {
            printf("\n");
        }
    } while (command != ACTION_REST && command != ACTION_PROVOKE);
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
    if (rand() % 100 < (100 - prob)) {
        Clo--;
    }
    if (prevClo != Clo) {
        if (Cgro < AGGRO_MAX) Cgro += 1; // 어그로 증가
        printf("citizen: %d -> %d (aggro: %d)\n", prevClo, Clo, Cgro);
    }
    else if (prevClo == Clo) {
        if (Cgro > AGGRO_MIN) Cgro -= 1; // 어그로 감소
        printf("citizen: stay %d (aggro: %d)\n", Clo, Cgro);
    }
    return Clo;
}
// 좀비 움직임
int Zombimov() {
    int prevZlo = Zlo;

    // 어그로 수치에 따라 이동할 대상 결정
    int targetLo;
    // 수정된 부분: 마동석과 시민의 어그로를 비교하여 높은 쪽으로 이동 결정
    if (Mgro >= Cgro) {
        targetLo = Mlo; // 마동석의 어그로가 높거나 같으면 마동석 쪽으로 이동
    }
    else {
        targetLo = Clo; // 시민의 어그로가 더 높으면 시민 쪽으로 이동
    }

    // 좀비의 이동 로직
    if (count % 2 != 0) { // 좀비는 홀수 턴에만 움직임
        if (Zlo < targetLo) {
            Zlo++; // 대상이 좀비보다 오른쪽에 위치해 있으면 한 칸 오른쪽으로 이동
        }
        else if (Zlo > targetLo) {
            Zlo--; // 대상이 좀비보다 왼쪽에 위치해 있으면 한 칸 왼쪽으로 이동
        }
    }

    if (count % 2 == 0) {
        printf("zombie cannot move\n\n");
    }
    else {
        if (prevZlo != Zlo) {
            printf("zombie : %d -> %d\n\n", prevZlo, Zlo);
        }
    }
    return Zlo;
}

// 아웃트로
void outro(int Clo, int Zlo) {
    if (Clo == 1) {
        printf("시민이 열차 끝에 도착했습니다. 시민이 열차를 탈출했습니다.\n");
        exit(0);
    }
    if (Zlo == Clo + 1) {
        printf("시민이 좀비에게 물렸습니다. 시민 사망.\n");
        exit(0);
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

        Clo = Citizenmov(); // 시민 이동
        Zlo = Zombimov(); // 좀비 이동
        Mlo = MDSmov(); // 마동석 이동 <- 여기 위치 변경
        outro(Clo, Zlo); // 게임 종료 조건 확인
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