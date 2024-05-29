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
int Mgro = 1;
int Cgro = 1;
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
        printf("\nmadongseok move(0: stay, 1: left)>> ");
        scanf_s("%d", &command);
        while (getchar() != '\n');

        int prevMlo = Mlo; // ���� ��ġ ����

        // �������� ���� �����ϰų� ���� ��ġ�� ���
        if (Mlo == Zlo + 1) {
            printf("�������� ����� ������ �־� ������ �޽��� ���մϴ�.\n");
            command = MOVE_STAY;
        }

        if (command == MOVE_LEFT) {
            if (Mlo > 0) {
                Mlo--;
                if (Mgro < AGGRO_MAX) Mgro += 1; // ��׷� ����
                printf("madongseok: %d -> %d (aggro: %d, stamina: %d)\n\n", prevMlo, Mlo, Mgro, stm); // ������ ��ġ ���
            }
            break;
        }
        else if (command == MOVE_STAY) {
            if (Mgro > AGGRO_MIN) Mgro -= 1; // ��׷� ����
            printf("madongseok: stay %d (aggro: %d, stamina: %d)\n\n", Mlo, Mgro, stm); // ������ ��ġ ���� ���
            break;
        }
        else {
            printf("\n");
        }
    } while (command != MOVE_STAY && command != MOVE_LEFT);
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
    if (Clo != 1 && rand() % 100 < (100 - prob)) { // �ù��� ������ �������� �������� �ʾҰ�, �̵� Ȯ���� ����
        Clo--;
    }
    if (prevClo != Clo) {
        if (Cgro < AGGRO_MAX) Cgro += 1; // ��׷� ����
        printf("citizen: %d -> %d (aggro: %d)\n", prevClo, Clo, Cgro);
    }
    else {
        if (Cgro > AGGRO_MIN) Cgro -= 1; // ��׷� ����
        printf("citizen: stay %d (aggro: %d)\n",Clo, Cgro); // �ù��� �������� ����
    }
    if ((Zlo - Clo) != 1) { // ����� �ù�, ������ ��� �������� ���� ���
        printf("citizen does nothing.\n");
    }
    return Clo;
}
// ���� ������
int Zombimov() {
    int prevZlo = Zlo; // ���� ���� ��ġ ����
    int targetLo = Mgro > Cgro ? Mlo : Clo; // ��׷� ��ġ�� ���� ��ǥ ��ġ ����

    // ���� �������� �����ϴ� ���
    if (Mgro > Cgro && (Mlo - Zlo) == 1) {
        printf("Zombie attacked madongseok (aggro: %d vs %d, madongseok stamina %d -> %d)\n", Cgro, Mgro, stm, stm-1);
        stm -= 1;
        if (stm == STM_MIN) {
            printf("���� ����. ������ ���.\n");
            exit(0);
        }
        return Zlo; // ����� �̵����� ����
    }

    // ���� ������ ó�� (Ȧ�� �Ͽ��� ������)
    if (count % 2 != 0) {
        // ����� ���񺸴� �����ʿ� ������ �������� ��ġ�� �ʴ� ���
        if (Zlo < targetLo && (Mlo - Zlo) != 1) {
            Zlo++;
        }
        // ����� ���񺸴� ���ʿ� ���� ��
        else if (Zlo > targetLo) {
            Zlo--;
        }
        // ������ ��ġ�� ����Ǿ��ٸ�, �̸� ���
        if (prevZlo != Zlo) {
            printf("zombie : %d -> %d\n", prevZlo, Zlo);
        }
    }
    else {
        printf("zombie cannot move %d \n", Zlo);
    }

    // ����� �ù�, ������ ��� �������� ���� ���
    if ((Zlo - Clo) != 1 && (Mlo - Zlo) != 1) {
        printf("zombie attacked nobody.\n");
    }

    return Zlo;
}



// �ƿ�Ʈ��
void outro(int Clo, int Zlo) {
    if (Clo == 1) {
        printf("�ù��� ���� ���� �����߽��ϴ�. �ù��� ������ Ż���߽��ϴ�.\n");
        exit(0);
    }
    if (Zlo == Clo + 1) { // �ù��� ����� ������ ���
        printf("�ù��� ���񿡰� ���Ƚ��ϴ�. �ù� ���.\n");
        exit(0);
    }
    if (abs(Zlo - Clo) == 1 && abs(Zlo - Mlo) == 1) { // �� �� ������ ���
        if (Cgro >= Mgro) { // �ù��� ��׷ΰ� �� ���ų� ���� ���
            printf("�ù��� ���񿡰� ���Ƚ��ϴ�. �ù� ���.\n");
            exit(0);
        }
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

        int prevClo = Clo;
        int prevZlo = Zlo;
        int prevMlo = Mlo;

        Clo = Citizenmov(); // �ù� �̵�
        Zlo = Zombimov(); // ���� �̵�

        // ����� �κи� ���
        if (prevClo != Clo || prevZlo != Zlo) {
            printTrain(len, Clo, Zlo, Mlo);
        }

        Mlo = MDSmov(); // ������ �̵� <- ���� ��ġ ����
        outro(Clo, Zlo); // ���� ���� ���� Ȯ��
        count++; // �̵� Ƚ�� ����
    }
    return 0;
}
