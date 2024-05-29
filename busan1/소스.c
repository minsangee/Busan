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
// ������ �̵� ����
#define MOVE_LEFT 1
#define MOVE_STAY 0
// ������ ���� ���
#define ATK_NONE 0
#define ATK_CITIZEN 1
#define ATK_DONGSEOK 2
// ������ �ൿ
#define ACTION_REST 0
#define ACTION_PROVOKE 1
#define ACTION_PULL 2
// ���� ���� ����
int len;
int prob;
int stm;
int Mgro;
int Cgro;
int Clo;
int Zlo;
int Mlo;
int count;
// ��Ʈ�� �Լ�
void intro() {
    printf("�� �� �� I N T R O \n");
}
// ���� ���� ����
int train() {
    int len;
    do {
        printf("���� ���� ����(%d ~ %d)>> ", LEN_MIN, LEN_MAX);
        scanf_s("%d", &len);
        while (getchar() != '\n');
    } while (len < LEN_MIN || len > LEN_MAX);
    return len;
}
// Ȯ�� ����
int probability() {
    int prob;
    do {
        printf("���� Ȯ�� 'p' ����(%d ~ %d)>> ", PROB_MIN, PROB_MAX);
        scanf_s("%d", &prob);
        while (getchar() != '\n');
    } while (prob < PROB_MIN || prob > PROB_MAX);
    return prob;
}
// ������ ü�� ����
int MDSSTM() {
    int stm;
    do {
        printf("������ ü�� ����(%d ~ %d)>> ", STM_MIN, STM_MAX);
        scanf_s("%d", &stm);
        while (getchar() != '\n');
    } while (stm < STM_MIN || stm > STM_MAX);
    return stm;
}
// ������ �̵� �Լ�
int MDSmov() {
    int command;
    do {
        printf("madongseok move(0.rest, 1.provoke)>> ");
        scanf_s("%d", &command);
        while (getchar() != '\n');

        if (Mlo == Zlo - 1 || Mlo == Zlo + 1) { // �������� ���� ������ ���
            if (command == ACTION_REST) {
                if (Mgro > AGGRO_MIN) Mgro -= 1; // ��׷� ����
                if (Mgro < AGGRO_MIN) Mgro = AGGRO_MIN; // ��׷� �ּҰ� ����
                printf("madongseok: stay %d (aggro: %d, stamina: %d)\n", Mlo, Mgro, stm); // ������ ��ġ ���� ���
            }
            else {
                Mgro -= 1;
                if (Mgro < AGGRO_MIN) Mgro = AGGRO_MIN; // ��׷� �ּҰ� ����
                printf("madongseok: cannot move, only rest (aggro: %d, stamina: %d)\n", Mgro, stm);
            }
            break;
        }

        if (command == ACTION_PROVOKE) {
            if (Mlo > 0) {
                Mlo--;
                if (Mgro < AGGRO_MAX) Mgro += 1; // ��׷� ����
                printf("madongseok: %d -> %d (aggro: %d, stamina: %d)\n", Mlo + 1, Mlo, Mgro, stm); // ������ ��ġ ���
            }
            break;
        }
        else if (command == ACTION_REST) {
            if (Mgro > AGGRO_MIN) Mgro -= 1; // ��׷� ����
            printf("madongseok: stay %d (aggro: %d)\n", Mlo, Mgro); // ������ ��ġ ���� ���
            break;
        }
        else {
            printf("\n");
        }
    } while (command != ACTION_REST && command != ACTION_PROVOKE);
    return Mlo;
}
// ���� ���� �Լ�
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
// �ù� ������
int Citizenmov() {
    int prevClo = Clo;
    if (rand() % 100 < (100 - prob)) {
        Clo--;
    }
    if (prevClo != Clo) {
        if (Cgro < AGGRO_MAX) Cgro += 1; // ��׷� ����
        printf("citizen: %d -> %d (aggro: %d)\n", prevClo, Clo, Cgro);
    }
    else if (prevClo == Clo) {
        if (Cgro > AGGRO_MIN) Cgro -= 1; // ��׷� ����
        printf("citizen: stay %d (aggro: %d)\n", Clo, Cgro);
    }
    return Clo;
}
// ���� ������
int Zombimov() {
    int prevZlo = Zlo;

    // ��׷� ��ġ�� ���� �̵��� ��� ����
    int targetLo;
    // ������ �κ�: �������� �ù��� ��׷θ� ���Ͽ� ���� ������ �̵� ����
    if (Mgro >= Cgro) {
        targetLo = Mlo; // �������� ��׷ΰ� ���ų� ������ ������ ������ �̵�
    }
    else {
        targetLo = Clo; // �ù��� ��׷ΰ� �� ������ �ù� ������ �̵�
    }

    // ������ �̵� ����
    if (count % 2 != 0) { // ����� Ȧ�� �Ͽ��� ������
        if (Zlo < targetLo) {
            Zlo++; // ����� ���񺸴� �����ʿ� ��ġ�� ������ �� ĭ ���������� �̵�
        }
        else if (Zlo > targetLo) {
            Zlo--; // ����� ���񺸴� ���ʿ� ��ġ�� ������ �� ĭ �������� �̵�
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

// �ƿ�Ʈ��
void outro(int Clo, int Zlo) {
    if (Clo == 1) {
        printf("�ù��� ���� ���� �����߽��ϴ�. �ù��� ������ Ż���߽��ϴ�.\n");
        exit(0);
    }
    if (Zlo == Clo + 1) {
        printf("�ù��� ���񿡰� ���Ƚ��ϴ�. �ù� ���.\n");
        exit(0);
    }
}
// �����Լ�
int main(void) {
    srand((unsigned int)time(NULL)); // ���� ���� �ʱ�ȭ
    intro(); // ��Ʈ�� ��� �� ����(���� ����)
    len = train(); // ���� ���� �Է� �ޱ�
    prob = probability(); // Ȯ�� �Է� �ޱ�
    stm = MDSSTM(); // ������ ü�� �Է� �ޱ�
    Clo = len - 6; // �ʱ� �ù� ��ġ ����
    Zlo = len - 3; // �ʱ� ���� ��ġ ����
    Mlo = len - 2; // ������ �ʱ� ��ġ ����
    count = 0; // �̵� Ƚ�� �ʱ�ȭ
    printTrain(len, Clo, Zlo, Mlo); // �ʱ� ���� ���� ���
    // ���� ����
    while (1) {
        // ���� ���� ���� ���
        printTrain(len, Clo, Zlo, Mlo);

        Clo = Citizenmov(); // �ù� �̵�
        Zlo = Zombimov(); // ���� �̵�
        Mlo = MDSmov(); // ������ �̵� <- ���� ��ġ ����
        outro(Clo, Zlo); // ���� ���� ���� Ȯ��
        count++; // �̵� Ƚ�� ����
    }
    return 0;
}

// �ϴ� �λ��� 1ó�� ���� -> �̵� �Լ� ���� ������ �Լ�
// �������� 0 or 1�� �Է¹޾� �̵� Ȥ�� ���� ����
// if ������ =< �ù� ��׷� �� ����� �ù��� �ƴϸ� �ݴ���
// stm�� �����ؼ� �Է¹ް� �ϱ�
// ������ �̵� �ൿ ����, �޽� ���� �ٵ�� ����
// �ٵ�� if�� �ൿ ������, ���н� ���� ���
// 