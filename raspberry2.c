//�ʿ��� �������
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>
//�����ļ��� Trig, echo �� define
#define TP1      2
#define EP1      3
#define TP2      4
#define EP2      17
//fnd define
#define a      14
#define b      15
#define c      18
#define d      23
#define e      24
#define f      25
#define g      7
//LED define ���Ŀ���
#define LED      21
//gas sensor, fan �ɹ�ȣ ����, MCP3208 ����
#define CS_MCP3208   8
#define SPI_CHANNEL   0
#define SPI_SPEED   1000000
#define FAN1         26
#define FAN2         19
#define FAN3         13
#define FAN4         6


void fnd(int cnt) { // Common - Anode type fnd
    switch (cnt) {//switch - case���� ���� FND�� abcdefg �� ���� ��� ����
    case 0://0 ���� FND ���
        digitalWrite(a, LOW);
        digitalWrite(b, LOW);
        digitalWrite(c, LOW);
        digitalWrite(d, LOW);
        digitalWrite(e, LOW);
        digitalWrite(f, LOW);
        digitalWrite(g, HIGH);
        break;

    case 1://1 ���� FND ���
        digitalWrite(a, HIGH);
        digitalWrite(b, LOW);
        digitalWrite(c, LOW);
        digitalWrite(d, HIGH);
        digitalWrite(e, HIGH);
        digitalWrite(f, HIGH);
        digitalWrite(g, HIGH);
        break;

    case 2://2 ���� FND ���
        digitalWrite(a, LOW);
        digitalWrite(b, LOW);
        digitalWrite(c, HIGH);
        digitalWrite(d, LOW);
        digitalWrite(e, LOW);
        digitalWrite(f, HIGH);
        digitalWrite(g, LOW);
        break;

    case 3://3 ���� FND ���
        digitalWrite(a, LOW);
        digitalWrite(b, LOW);
        digitalWrite(c, LOW);
        digitalWrite(d, LOW);
        digitalWrite(e, HIGH);
        digitalWrite(f, HIGH);
        digitalWrite(g, LOW);
        break;

    case 4://4 ���� FND ���
        digitalWrite(a, HIGH);
        digitalWrite(b, LOW);
        digitalWrite(c, LOW);
        digitalWrite(d, HIGH);
        digitalWrite(e, HIGH);
        digitalWrite(f, LOW);
        digitalWrite(g, LOW);
        break;

    case 5://5 ���� FND ���
        digitalWrite(a, LOW);
        digitalWrite(b, HIGH);
        digitalWrite(c, LOW);
        digitalWrite(d, LOW);
        digitalWrite(e, HIGH);
        digitalWrite(f, LOW);
        digitalWrite(g, LOW);
        break;

    case 6://6 ���� FND ���
        digitalWrite(a, LOW);
        digitalWrite(b, HIGH);
        digitalWrite(c, LOW);
        digitalWrite(d, LOW);
        digitalWrite(e, LOW);
        digitalWrite(f, LOW);
        digitalWrite(g, LOW);
        break;

    case 7://7 ���� FND ���
        digitalWrite(a, LOW);
        digitalWrite(b, LOW);
        digitalWrite(c, LOW);
        digitalWrite(d, HIGH);
        digitalWrite(e, HIGH);
        digitalWrite(f, LOW);
        digitalWrite(g, HIGH);
        break;

    case 8://8 ���� FND ���
        digitalWrite(a, LOW);
        digitalWrite(b, LOW);
        digitalWrite(c, LOW);
        digitalWrite(d, LOW);
        digitalWrite(e, LOW);
        digitalWrite(f, LOW);
        digitalWrite(g, LOW);
        break;

    case 9://9 ���� FND ���
        digitalWrite(a, LOW);
        digitalWrite(b, LOW);
        digitalWrite(c, LOW);
        digitalWrite(d, HIGH);
        digitalWrite(e, HIGH);
        digitalWrite(f, LOW);
        digitalWrite(g, LOW);
        break;
    }
    printf("fnd = %d\n", cnt); // fnd ��� ���� �͹̳ο��� ǥ��

}

float getDistance1(void) //ù��° �Ÿ����� �Լ� - ������ ����
{
    // �޾ƿ� �Ÿ����� �ð� �ʱ�ȭ
    float fDistance;
    int nStartTime, nEndTime;

    digitalWrite(TP1, LOW); // triger�� pulse ����
    delayMicroseconds(2);

    digitalWrite(TP1, HIGH); // triger�� pulse ����
    delayMicroseconds(10);
    digitalWrite(TP1, LOW); // triger�� pulse ����

    while (digitalRead(EP1) == LOW); // echo�� ���۽ð� ����
    nStartTime = micros();

    while (digitalRead(EP1) == HIGH);// echo�� �����ð� ����
    nEndTime = micros();

    fDistance = (nEndTime - nStartTime) * 0.034 / 2.; //�Ÿ� ���� ���Ŀ� ���� ����

    return fDistance;
}

float getDistance2(void) //�ι�° �Ÿ����� �Լ� - ������ ����
{
    // �޾ƿ� �Ÿ����� �ð� �ʱ�ȭ
    float sDistance;
    int nStartTime, nEndTime;

    digitalWrite(TP2, LOW);// triger�� pulse ����
    delayMicroseconds(2);

    digitalWrite(TP2, HIGH);// triger�� pulse ����
    delayMicroseconds(10);
    digitalWrite(TP2, LOW);// triger�� pulse ����

    while (digitalRead(EP2) == LOW);// echo�� ���۽ð� ����
    nStartTime = micros();

    while (digitalRead(EP2) == HIGH);// echo�� �����ð� ����
    nEndTime = micros();

    sDistance = (nEndTime - nStartTime) * 0.034 / 2.;//�Ÿ� ���� ���Ŀ� ���� ����

    return sDistance;
}

void LEDOn(void) { //LED ON �Լ�
    digitalWrite(LED, HIGH);
}

void LEDOff(void) { //LED OFF �Լ�
    digitalWrite(LED, LOW);
}

void FANOn(void) { //FAN ON �Լ�
    digitalWrite(FAN1, HIGH); // 1��FAN
    digitalWrite(FAN2, HIGH);// 2��FAN
    digitalWrite(FAN3, HIGH);// 3��FAN
    digitalWrite(FAN4, HIGH);// 4��FAN
}

void FANOff(void) { //FAN OFF �Լ�
    digitalWrite(FAN1, LOW);// 1��FAN
    digitalWrite(FAN2, LOW);// 2��FAN
    digitalWrite(FAN3, LOW);// 3��FAN
    digitalWrite(FAN4, LOW);// 4��FAN

}

int ReadMcp3208ADC(unsigned char adcChannel) { //3208 ���� ���� �Լ� (Analog to Digital Converter)
    unsigned char buff[3];
    int nAdcValue = 0;
    buff[0] = 0x06 | ((adcChannel & 0x07) >> 2);
    buff[1] = ((adcChannel & 0x07) << 6);
    buff[2] = 0x00;
    digitalWrite(CS_MCP3208, 0);
    wiringPiSPIDataRW(SPI_CHANNEL, buff, 3);
    buff[1] = 0x0F & buff[1];
    nAdcValue = (buff[1] << 8) | buff[2];
    digitalWrite(CS_MCP3208, 1);
    return nAdcValue;
}
int main(void) {
    //�� �ʱ�ȭ
    int smokelChannel = 2;
    int smokeValue = 0;
    int enter = 0;
    int out = 0;
    int cnt = 0;
    int reset = 0;
    //���� �߻��� ����
    if (wiringPiSetupGpio() == -1) {
        fprintf(stdout, "Not start wiringPi:%s\n", strerror(errno));
        return 1;
    }
    //SPI���� ���� �߻��� ����
    if (wiringPiSPISetup(SPI_CHANNEL, SPI_SPEED) == -1) {
        fprintf(stdout, "spi failed : %s\n", strerror(errno));
        return 1;
    }
    //�⺻���� GPIO�� ����
    pinMode(CS_MCP3208, OUTPUT); //3208���� ��
    pinMode(FAN1, OUTPUT); // FAN1�� �����
    pinMode(FAN2, OUTPUT); // FAN2�� �����
    pinMode(FAN3, OUTPUT); // FAN3�� �����
    pinMode(FAN4, OUTPUT); // FAN4�� �����
    pinMode(TP1, OUTPUT); // �����ļ���1�� Triger��
    pinMode(EP1, INPUT); // �����ļ���1�� echo��
    pinMode(TP2, OUTPUT); // �����ļ���2�� Triger��
    pinMode(EP2, INPUT); // �����ļ���2�� echo��
    //fnd a~g ����� ����
    pinMode(a, OUTPUT);
    pinMode(b, OUTPUT);
    pinMode(c, OUTPUT);
    pinMode(d, OUTPUT);
    pinMode(e, OUTPUT);
    pinMode(f, OUTPUT);
    pinMode(g, OUTPUT);
    pinMode(LED, OUTPUT); // LED 4���� ��ü �����

    //fnd, LED �ʱ�ȭ
    fnd(0);
    digitalWrite(LED, LOW);

    while (1) {
        //�Ÿ����� �� �� ��������
        float fDistance = getDistance1();
        float sDistance = getDistance2();
        //���� ���� �� ��������
        smokeValue = ReadMcp3208ADC(smokelChannel);
        //�Ÿ��� ���
        printf("fDistance: %.2fcm, ", fDistance);
        printf("sDistance: %.2fcm\n", sDistance);

        if (fDistance < 8) { //ù��° ������ �ɸ��� enter�� 1��
            enter = 1;
            if (out == 1) {
                cnt--; // �ι�° ������ �ɸ����·� ù��°������ �ɸ��� fnd ���� (����)
                if (cnt < 0) cnt = 0; //0�϶� �߸� ���� �Ǿ������� ����� �����÷ο� ����
                enter = 0; // fnd�����Ͽ����� ������ �� �ʱ�ȭ
                out = 0;
                reset = 0;
                fnd(cnt); //fnd�� cnt�� ���
                delay(700); //��� �ν��� ���������� �ϱ����� ��� ������
            }
        }
        if (sDistance < 8) { //�ι�° ������ �ɸ��� out�� 1��
            out = 1;
            if (enter == 1) {
                cnt++; // ù��° ������ �ɸ����·� �ι�° ������ �ɸ��� fnd ���� (����)
                if (cnt > 9) cnt = 9; //9�϶� �߸� ���� �Ǿ������� ����� �����÷ο� ����
                enter = 0; // fnd�����Ͽ����� ������ �� �ʱ�ȭ
                out = 0;
                reset = 0;
                fnd(cnt); //fnd�� cnt�� ���
                delay(700); //��� �ν��� ���������� �ϱ����� ��� ������

            }
        }
        //�ȿ� ����� ������ LED�ѱ� ������ ��
        if (cnt > 0) LEDOn();
        else if (cnt == 0) { // ��� �������� FAN�� ����
            LEDOff();
            FANOff();
        }

        //���������ؼ� ������ �̻��̸� FAN ����
        if (smokeValue >= 1000) FANOn(); //���� value�� 700������ �����Ͽ� 1000���� ����
        else if (smokeValue < 1000) FANOff();
        printf("smoke sensor value = %u\n", smokegValue);

        reset++; //while���� ���ư��� ���� �� ����
        if (reset > 15) { //while���� 10�� ���ư����� �����ļ��� �ΰ��� ��� �������� ��� �ʱ�ȭ
            enter = 0;
            out = 0;
            reset = 0;
        }

        delay(100); // while���� ���� �޾Ƶ��̴� ������
    }
    return 0;
}