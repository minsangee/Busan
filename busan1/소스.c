#include <stdio.h>
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
int Zpull = 0;
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
// ������ �̵� �Լ�
int Zombimov() {
    if (Zpull) {
        printf("zombie cannot move this turn.\n");
        Zpull = 0; // ���� �Ͽ� ���� �ٽ� ������ �� �ֵ��� ����
        return Zlo;
    }
    int prevZlo = Zlo; // ���� ���� ��ġ ����
    int targetLo = Mgro > Cgro ? Mlo : Clo; // ��׷� ��ġ�� ���� ��ǥ ��ġ ����
    if (count % 2 != 0) {
        if (Zlo < targetLo && (Mlo - Zlo) != 1) {
            Zlo++;
        }
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
    return Zlo;
}
// ������ ���� �Լ�
void zombieAction() {
    if (Mlo == Zlo + 1) { // ������ ���
        // ���� ����
        printf("zombie attacked madongseok (aggro: %d vs %d, madongseok stamina %d -> ", Cgro, Mgro, stm);
        if (stm == 0) {
            printf("0)\n");
        }
        else {
            printf("%d -> %d)\n", stm, stm - 1);
        }
        stm -= 1;
        if (stm <= STM_MIN) {
            printf("���� ����. ������ ���.\n");
            exit(0);
        }
    }
}
// ������ �̵� �Լ�
int MDSmov() {
    int command;
    int prevMgro = Mgro;
    int prevstm = stm;
    do {
        printf("\nmadongseok move(0: stay, 1: left)>> ");
        scanf_s("%d", &command);
        while (getchar() != '\n');
        int prevMlo = Mlo; 
        // �������� ���� �����ϰų� ���� ��ġ�� ��� ���� �޽�
        if (Mlo == Zlo + 1) {
            printf("�������� ����� ������ �־� ������ �޽��� ���մϴ�.\n");
            command = MOVE_STAY;
        }
        if (command == MOVE_LEFT) {
            if (Mlo > 0) {
                Mlo--;
                if (Mgro < AGGRO_MAX) Mgro += 1; // ��׷� ����
                printf("madongseok: %d -> %d (aggro: %d -> %d, stamina: %d)\n\n", prevMlo, Mlo, prevMgro, Mgro, stm);
            }
            break;
        }
        else if (command == MOVE_STAY) {
            if (Mgro > AGGRO_MIN) Mgro -= 1; // ��׷� ����
            printf("madongseok: stay %d (aggro: %d -> %d, stamina: %d)\n\n", Mlo, prevMgro, Mgro, stm);
            break;
        }
        else {
            printf("\n");
        }
    } while (command != MOVE_STAY && command != MOVE_LEFT);
    // �̵� �� ���� ���� ���
    printTrain(len, Clo, Zlo, Mlo);
    return Mlo;
}
// ������ �ൿ �Լ�
void MDSaction() {
    int command;
    int prevMgro = Mgro;
    int prevstm = stm;
    if (Mlo == Zlo + 1) { // ������ ���
        do {
            printf("\nmadongseok action(0: rest, 1: provoke, 2: pull)>> ");
            scanf_s("%d", &command);
            while (getchar() != '\n');
            if (command == ACTION_REST) {
                if (Mgro > AGGRO_MIN) Mgro -= 1; // ��׷� ����
                if (stm < STM_MAX) stm += 1; // ü�� ����
                printf("������ �޽� (aggro: %d -> %d, stamina: %d -> %d)\n\n", prevMgro, Mgro, prevstm, stm);
            }
            else if (command == ACTION_PROVOKE) {
                prevMgro = Mgro;
                Mgro = AGGRO_MAX; // ��׷� �ִ�� ����
                printf("madongseok provokes (aggro: %d -> %d, stamina: %d)\n\n", prevMgro, Mgro, stm);
            }
            else if (command == ACTION_PULL) {
                prevMgro = Mgro; // ���� ��׷� ����
                prevstm = stm; // ���� ü�� ����
                Mgro = (Mgro + 2 > AGGRO_MAX) ? AGGRO_MAX : Mgro + 2; // ��׷� ����, �ִ밪 ����
                stm -= 1; // ü�� ����
                int success = rand() % 100 < (100 - prob); // 100-p%�� Ȯ���� ����
                if (success) {
                    Zpull = 1;
                    printf("madongseok pulled zombie... Next turn, it can't move\nmadongseok: %d (aggro: %d->%d, stamina: %d -> %d)\n\n", Zlo, prevMgro, Mgro, prevstm, stm);
                }
                else {
                    printf("madongseok failed to pull zombie.\n(aggro: %d -> %d, stamina: %d -> %d)\n\n", prevMgro, Mgro, prevstm, stm);
                }
            }
        } while (command != ACTION_REST && command != ACTION_PROVOKE && command != ACTION_PULL);
    }
    else { // �������� ���� ��� pull ������ ������ ���
        do {
            printf("\nmadongseok action(0: rest, 1: provoke)>> ");
            scanf_s("%d", &command);
            while (getchar() != '\n');
            if (command == ACTION_REST) {
                if (Mgro > AGGRO_MIN) Mgro -= 1; // ��׷� ����
                if (stm < STM_MAX) stm += 1; // ü�� ����
                printf("������ �޽� (aggro: %d -> %d, stamina: %d)\n\n", prevMgro, Mgro, stm);
            }
            else if (command == ACTION_PROVOKE) {
                prevMgro = Mgro;
                Mgro = AGGRO_MAX; // ��׷� �ִ�� ����
                printf("madongseok provokes (aggro: %d -> %d, stamina: %d)\n\n", prevMgro, Mgro, stm);
            }
        } while (command != ACTION_REST && command != ACTION_PROVOKE);
    }
}
// �ù� �̵� �Լ�(�ù� �ൿ �Լ��� ������ ����)
int Citizenmov() {
    int prevClo = Clo;
    int prevCgro = Cgro;
    if (Clo != 1 && rand() % 100 < (100 - prob)) { 
        Clo--;
    }
    if (prevClo != Clo) {
        prevCgro = Cgro;
        if (Cgro < AGGRO_MAX) Cgro += 1; // ��׷� ����
        printf("citizen: %d -> %d (aggro: %d -> %d)\n", prevClo, Clo, prevCgro, Cgro);
    }
    else {
        prevCgro = Cgro;
        if (Cgro > AGGRO_MIN) Cgro -= 1; // ��׷� ����
        printf("citizen: stay %d (aggro: %d -> %d)\n", Clo, prevCgro, Cgro); // �ù��� �������� ����
    }
    if ((Zlo - Clo) != 1) { // ����� �ù�, ������ ��� �������� ���� ���
        printf("citizen does nothing.\n");
    }
    return Clo;
}
// �ù� ��� Ȥ�� ������ ��µǴ� �ƿ�Ʈ��
void outro(int Clo, int Zlo) {
    if (Clo == 1) {
        printf("!!!YOU WIN!!!\n");
        exit(0);
    }
    if (Zlo == Clo + 1) { // �ù��� ����� ������ ���
        printf("�ù��� ���񿡰� ���Ƚ��ϴ�. �ù� ���.\n");
        exit(0);
    }
    if ((Zlo - Clo) == 1 && (Mlo - Zlo) == 1) { // �� �� ������ ���
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

        if (prevClo != Clo || prevZlo != Zlo) {
            printTrain(len, Clo, Zlo, Mlo);
        }

        Mlo = MDSmov(); // ������ �̵�
        zombieAction(); // ������ �̵� �Ŀ� ������ ���� �߻�
        MDSaction(); // ������ �ൿ
        outro(Clo, Zlo); // ���� ���� ���� Ȯ��
        count++; // �̵� Ƚ�� ����
    }
}