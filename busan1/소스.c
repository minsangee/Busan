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
// ��Ʈ��
void intro() {
    printf("�� �� �� I N T R O \n");
    Sleep(3000); // 3�� ���
    system("cls"); // ȭ�� �����
}
//���� ���� ����
int train() {
    int len;
    do {
        printf("���� ���� ����(%d ~ %d)>> ", LEN_MIN, LEN_MAX);
        if (scanf_s("%d", &len) != 1) {
            while (getchar() != '\n'); 
            len = 0;
        }
    } while (len < LEN_MIN || len > LEN_MAX);
    return len;
}
//Ȯ�� ����
int probability() {
    int prob;
    do {
        printf("���� Ȯ�� 'p' ����(%d ~ %d)>> ", PROB_MIN, PROB_MAX);
        if (scanf_s("%d", &prob) != 1 || prob < PROB_MIN || prob > PROB_MAX) {
            while (getchar() != '\n');
            prob = 0;
        }
    } while (prob < PROB_MIN || prob > PROB_MAX);
    return prob;
}
// ������ ü�� ����
int MDSSTM() {
    int stm;
    do {
        printf("������ ü�� ����(%d ~ %d)>> ", STM_MIN, STM_MAX);
        if (scanf_s("%d", &stm) != 1) {
            while (getchar() != '\n');
            stm = 0;
        }
    } while (stm < STM_MIN || stm > STM_MAX);
    return stm;
}
// ��׷� ����
int aggro() {
    int agro;
    do {
        printf("��׷� ����(%d ~ %d)>> ", AGGRO_MIN, AGGRO_MAX);
        if (scanf_s("%d", &agro) != 1) {
            while (getchar() != '\n');
            agro = 0;
        }
    } while (agro < STM_MIN || agro > STM_MAX);
    return agro;
}
// ������ �ù�, ������ ��ġ�� ����ϴ� �Լ�
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
// �ùΰ� ������ ��ġ�� �̵���Ű�� �Լ�
void moveEntities(int* Clo, int* Zlo, int prob, int count) {
    if (rand() % 100 < (100 - prob)) {
        (*Clo)--; // Ȯ���� ���� �ù��� ��ġ �̵�
    }
    if (count % 2 != 0 && rand() % 100 < prob) {
        (*Zlo)--; // Ȯ���� ���� ������ ��ġ �̵�
    }
}
// �ùΰ� ������ ���¸� ����ϴ� �Լ�
void Citizenmov(int Clo, int prevClo, int prob, int count) {
    if (prevClo != Clo) {
        printf("citizen: %d -> %d\n", prevClo, Clo); // �ù��� ��ġ ���� ���
    }
    else {
        printf("citizen: stay %d\n", Clo); // �ù��� ��ġ ���� ���
    }
}

// ���� ���� ��� �Լ�
int Zombimov(int Zlo, int prevZlo)
if (count % 2 == 0) {
    printf("zombie cannot move\n\n"); // ���� �̵����� �ʴ� ��� ���
}
else {
    if (rand() % 100 < prob) {
        printf("zombie : %d -> %d\n\n", prevZlo, Zlo); // ������ ��ġ ���� ���
    }
    else {
        printf("zombie: stay %d\n\n", Zlo); // ������ ��ġ ���� ���
    }
//������ ���� ��� �Լ�
int Mdsmov(int Mlo) { 
    if ()
}

// ���� ���� ������ Ȯ���ϰ� �޽����� ����ϴ� �Լ�
void outro(int Clo, int Zlo) {
    if (Clo == 1) {
        printf("�ù��� ���� ���� �����߽��ϴ�. �ù��� ������ Ż���߽��ϴ�.\n");
        exit(0); // �ù��� ������ Ż���� ��� ���α׷� ����
    }
    if (Zlo == Clo + 1) {
        printf("�ù��� ���񿡰� ���Ƚ��ϴ�. �ù� ���.\n");
        exit(0); // ���� �ù��� ���� ��� ���α׷� ����
    }
}
int main(void) {
    srand((unsigned int)time(NULL)); // ���� ���� �ʱ�ȭ
    intro(); // �Ұ� �޽��� ���
    int len = train(); // ���� ���� �Է� �ޱ�
    int prob = probability(); // Ȯ�� �Է� �ޱ�
    int stm = MDSSTM(); // ������ ü�� �Է� �ޱ�
    int agro = aggro(); // ��׷� �Է� �ޱ�
    int Clo = len - 6; // �ʱ� �ù� ��ġ ����
    int Zlo = len - 3; // �ʱ� ���� ��ġ ����
    int count = 0; // �̵� Ƚ�� �ʱ�ȭ

    printTrain(len, Clo, Zlo); // �ʱ� ���� ���� ���
    // ���� ����
    while (1) {
        int prevClo = Clo, prevZlo = Zlo; // ���� ��ġ ����
        moveEntities(&Clo, &Zlo, prob, count); // �ùΰ� ���� �̵�
        printTrain(len, Clo, Zlo); // ���� ���� ���� ���
        printStatus(Clo, Zlo, prevClo, prevZlo, prob, count); // ���� ���� ���
        outro(Clo, Zlo); // ���� ���� ���� Ȯ��
        Sleep(4000); // 4�� ���
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