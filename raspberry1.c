#include <wiringPi.h>
#include <softTone.h>
#include <stdio.h>
#include <softPwm.h>

#define KEY1 23 		// Ű�е� �� ��ȣ1
#define KEY2 24 		// Ű�е� �� ��ȣ 2
#define SERVO 18		// ���� ���� �� ��ȣ ����

#define MAX_KEY_BT_NUM 2		// Ű �е� ���� 2��

#define BUZZER_PIN 2		// ���� �� ��ȣ ����
#define SI 987			// ���� ���ļ� ����

const int KeypadTable[2] = { KEY1,KEY2 };   // Ű �е� �迭 ����

int KeypadRead(void) {	// keypad ��ư ������  Ȯ���Ͽ� nkeypadstate ���� ������ ���� ����
    int i, nKeypadstate;
    nKeypadstate = 0;
    for (i = 0; i < MAX_KEY_BT_NUM; i++) {
        if (!digitalRead(KeypadTable[i])) {
            nKeypadstate |= (1 << i);
        }
    }
    return nKeypadstate;
}
unsigned int SevenScale(unsigned char scale) {   	     // �Ҹ� ����� ���� ����
    unsigned int _ret = 0;
    switch (scale) {
    case 6:
        _ret = SI;
        break;
        return _ret;
    }
}

void Change_FREQ(unsigned int freq) {	     // �Ҹ� �ٲٴ� �Լ�(���ļ� ����)
    softToneWrite(BUZZER_PIN, freq);
}
void STOP_FREQ(void) {		// �Ҹ� ���ߴ� �Լ�(���ļ� 0��)
    softToneWrite(BUZZER_PIN, 0);
}
void Buzzer_Init(void) {		// �Ҹ� ��� �Լ�
    softToneCreate(BUZZER_PIN);
    STOP_FREQ();
}

void motorturn(void) {
    softPwmWrite(SERVO, 5);		// �������� ���� ���� ȸ��
}
void motoroff(void) {
    softPwmWrite(SERVO, 25);		// �������� ���� ���� ȸ��
}
void motorstop(void) {
    softPwmWrite(SERVO, 15);		// �������� ����
}

int main(void) {
    if (wiringPiSetupGpio() == -1) return 1;        //gpio��뼳��
    Buzzer_Init();			// ���� ����� ���� ����
    int i, nKeypadstate;		// ���� ����
    int a = 0;
    int push = 1;
    int sound;
    softPwmCreate(SERVO, 0, 200);	// �������� pwm 0~200

    for (i = 0; i < MAX_KEY_BT_NUM; i++) {	// Ű�е� �Է½� �Է� Ű���� INPUT��
        pinMode(KeypadTable[i], INPUT);
    }

    while (1) {
        nKeypadstate = KeypadRead();

        for (i = 0; i < MAX_KEY_BT_NUM; i++) {	// Ű�е忡�� ��ư�� �������� ���� ����
            if ((nKeypadstate & (1 << i))) {
                if (push == 1) {
                    for (sound = 6; sound < 7; sound++)
                    {
                        motorturn();			// �������� ���� ����(�� ����)
                        Change_FREQ(SevenScale(sound));	// ���� �����鼭 ���ÿ� �Ҹ� ���
                        delay(1200);			//1.2�� ���� ���� ����

                        motorstop();			// �������� ���� ���� ������ ���� ����
                        STOP_FREQ();			// �Ҹ� ����
                        delay(2000);            // ����� ���;� �ϴϱ� ���� 2�ʵ��� �����ִ� ����
                        motoroff();	// �������� �ݴ���� ���� ����(�� ����)
                        delay(1000);	//1�ʵ��� ���� ����
                        motorstop();			// �������� ����
                    }
                    push = 1;

                }
            }
        }

    }


    return 0;
}


