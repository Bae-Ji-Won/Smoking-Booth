//필요한 헤더파일
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>
//초음파센서 Trig, echo 핀 define
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
//LED define 직렬연결
#define LED      21
//gas sensor, fan 핀번호 설정, MCP3208 설정
#define CS_MCP3208   8
#define SPI_CHANNEL   0
#define SPI_SPEED   1000000
#define FAN1         26
#define FAN2         19
#define FAN3         13
#define FAN4         6


void fnd(int cnt) { // Common - Anode type fnd
    switch (cnt) {//switch - case문을 통해 FND에 abcdefg 핀 각각 출력 통제
    case 0://0 숫자 FND 출력
        digitalWrite(a, LOW);
        digitalWrite(b, LOW);
        digitalWrite(c, LOW);
        digitalWrite(d, LOW);
        digitalWrite(e, LOW);
        digitalWrite(f, LOW);
        digitalWrite(g, HIGH);
        break;

    case 1://1 숫자 FND 출력
        digitalWrite(a, HIGH);
        digitalWrite(b, LOW);
        digitalWrite(c, LOW);
        digitalWrite(d, HIGH);
        digitalWrite(e, HIGH);
        digitalWrite(f, HIGH);
        digitalWrite(g, HIGH);
        break;

    case 2://2 숫자 FND 출력
        digitalWrite(a, LOW);
        digitalWrite(b, LOW);
        digitalWrite(c, HIGH);
        digitalWrite(d, LOW);
        digitalWrite(e, LOW);
        digitalWrite(f, HIGH);
        digitalWrite(g, LOW);
        break;

    case 3://3 숫자 FND 출력
        digitalWrite(a, LOW);
        digitalWrite(b, LOW);
        digitalWrite(c, LOW);
        digitalWrite(d, LOW);
        digitalWrite(e, HIGH);
        digitalWrite(f, HIGH);
        digitalWrite(g, LOW);
        break;

    case 4://4 숫자 FND 출력
        digitalWrite(a, HIGH);
        digitalWrite(b, LOW);
        digitalWrite(c, LOW);
        digitalWrite(d, HIGH);
        digitalWrite(e, HIGH);
        digitalWrite(f, LOW);
        digitalWrite(g, LOW);
        break;

    case 5://5 숫자 FND 출력
        digitalWrite(a, LOW);
        digitalWrite(b, HIGH);
        digitalWrite(c, LOW);
        digitalWrite(d, LOW);
        digitalWrite(e, HIGH);
        digitalWrite(f, LOW);
        digitalWrite(g, LOW);
        break;

    case 6://6 숫자 FND 출력
        digitalWrite(a, LOW);
        digitalWrite(b, HIGH);
        digitalWrite(c, LOW);
        digitalWrite(d, LOW);
        digitalWrite(e, LOW);
        digitalWrite(f, LOW);
        digitalWrite(g, LOW);
        break;

    case 7://7 숫자 FND 출력
        digitalWrite(a, LOW);
        digitalWrite(b, LOW);
        digitalWrite(c, LOW);
        digitalWrite(d, HIGH);
        digitalWrite(e, HIGH);
        digitalWrite(f, LOW);
        digitalWrite(g, HIGH);
        break;

    case 8://8 숫자 FND 출력
        digitalWrite(a, LOW);
        digitalWrite(b, LOW);
        digitalWrite(c, LOW);
        digitalWrite(d, LOW);
        digitalWrite(e, LOW);
        digitalWrite(f, LOW);
        digitalWrite(g, LOW);
        break;

    case 9://9 숫자 FND 출력
        digitalWrite(a, LOW);
        digitalWrite(b, LOW);
        digitalWrite(c, LOW);
        digitalWrite(d, HIGH);
        digitalWrite(e, HIGH);
        digitalWrite(f, LOW);
        digitalWrite(g, LOW);
        break;
    }
    printf("fnd = %d\n", cnt); // fnd 출력 숫자 터미널에도 표시

}

float getDistance1(void) //첫번째 거리측정 함수 - 초음파 센서
{
    // 받아올 거리값과 시간 초기화
    float fDistance;
    int nStartTime, nEndTime;

    digitalWrite(TP1, LOW); // triger핀 pulse 제어
    delayMicroseconds(2);

    digitalWrite(TP1, HIGH); // triger핀 pulse 제어
    delayMicroseconds(10);
    digitalWrite(TP1, LOW); // triger핀 pulse 제어

    while (digitalRead(EP1) == LOW); // echo핀 시작시간 저장
    nStartTime = micros();

    while (digitalRead(EP1) == HIGH);// echo핀 도착시간 저장
    nEndTime = micros();

    fDistance = (nEndTime - nStartTime) * 0.034 / 2.; //거리 값에 수식에 따라 저장

    return fDistance;
}

float getDistance2(void) //두번째 거리측정 함수 - 초음파 센서
{
    // 받아올 거리값과 시간 초기화
    float sDistance;
    int nStartTime, nEndTime;

    digitalWrite(TP2, LOW);// triger핀 pulse 제어
    delayMicroseconds(2);

    digitalWrite(TP2, HIGH);// triger핀 pulse 제어
    delayMicroseconds(10);
    digitalWrite(TP2, LOW);// triger핀 pulse 제어

    while (digitalRead(EP2) == LOW);// echo핀 시작시간 저장
    nStartTime = micros();

    while (digitalRead(EP2) == HIGH);// echo핀 도착시간 저장
    nEndTime = micros();

    sDistance = (nEndTime - nStartTime) * 0.034 / 2.;//거리 값에 수식에 따라 저장

    return sDistance;
}

void LEDOn(void) { //LED ON 함수
    digitalWrite(LED, HIGH);
}

void LEDOff(void) { //LED OFF 함수
    digitalWrite(LED, LOW);
}

void FANOn(void) { //FAN ON 함수
    digitalWrite(FAN1, HIGH); // 1번FAN
    digitalWrite(FAN2, HIGH);// 2번FAN
    digitalWrite(FAN3, HIGH);// 3번FAN
    digitalWrite(FAN4, HIGH);// 4번FAN
}

void FANOff(void) { //FAN OFF 함수
    digitalWrite(FAN1, LOW);// 1번FAN
    digitalWrite(FAN2, LOW);// 2번FAN
    digitalWrite(FAN3, LOW);// 3번FAN
    digitalWrite(FAN4, LOW);// 4번FAN

}

int ReadMcp3208ADC(unsigned char adcChannel) { //3208 사용시 쓰는 함수 (Analog to Digital Converter)
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
    //값 초기화
    int smokelChannel = 2;
    int smokeValue = 0;
    int enter = 0;
    int out = 0;
    int cnt = 0;
    int reset = 0;
    //오류 발생시 문장
    if (wiringPiSetupGpio() == -1) {
        fprintf(stdout, "Not start wiringPi:%s\n", strerror(errno));
        return 1;
    }
    //SPI관련 오류 발생시 문장
    if (wiringPiSPISetup(SPI_CHANNEL, SPI_SPEED) == -1) {
        fprintf(stdout, "spi failed : %s\n", strerror(errno));
        return 1;
    }
    //기본적인 GPIO핀 설정
    pinMode(CS_MCP3208, OUTPUT); //3208소자 핀
    pinMode(FAN1, OUTPUT); // FAN1번 출력핀
    pinMode(FAN2, OUTPUT); // FAN2번 출력핀
    pinMode(FAN3, OUTPUT); // FAN3번 출력핀
    pinMode(FAN4, OUTPUT); // FAN4번 출력핀
    pinMode(TP1, OUTPUT); // 초음파센서1번 Triger핀
    pinMode(EP1, INPUT); // 초음파센서1번 echo핀
    pinMode(TP2, OUTPUT); // 초음파센서2번 Triger핀
    pinMode(EP2, INPUT); // 초음파센서2번 echo핀
    //fnd a~g 출력핀 설정
    pinMode(a, OUTPUT);
    pinMode(b, OUTPUT);
    pinMode(c, OUTPUT);
    pinMode(d, OUTPUT);
    pinMode(e, OUTPUT);
    pinMode(f, OUTPUT);
    pinMode(g, OUTPUT);
    pinMode(LED, OUTPUT); // LED 4가지 전체 출력핀

    //fnd, LED 초기화
    fnd(0);
    digitalWrite(LED, LOW);

    while (1) {
        //거리측정 한 값 가져오기
        float fDistance = getDistance1();
        float sDistance = getDistance2();
        //연기 측정 값 가져오기
        smokeValue = ReadMcp3208ADC(smokelChannel);
        //거리값 출력
        printf("fDistance: %.2fcm, ", fDistance);
        printf("sDistance: %.2fcm\n", sDistance);

        if (fDistance < 8) { //첫번째 센서에 걸리면 enter를 1로
            enter = 1;
            if (out == 1) {
                cnt--; // 두번째 센서가 걸린상태로 첫번째센서에 걸리면 fnd 감소 (퇴장)
                if (cnt < 0) cnt = 0; //0일때 잘못 측정 되었을때를 대비한 오버플로우 방지
                enter = 0; // fnd감소하였으니 나머지 값 초기화
                out = 0;
                reset = 0;
                fnd(cnt); //fnd에 cnt값 출력
                delay(700); //사람 인식을 안정적으로 하기위해 잠시 딜레이
            }
        }
        if (sDistance < 8) { //두번째 센서에 걸리면 out을 1로
            out = 1;
            if (enter == 1) {
                cnt++; // 첫번째 센서가 걸린상태로 두번째 센서에 걸리면 fnd 증가 (입장)
                if (cnt > 9) cnt = 9; //9일때 잘못 측정 되었을때를 대비한 오버플로우 방지
                enter = 0; // fnd증가하였으니 나머지 값 초기화
                out = 0;
                reset = 0;
                fnd(cnt); //fnd에 cnt값 출력
                delay(700); //사람 인식을 안정적으로 하기위해 잠시 딜레이

            }
        }
        //안에 사람이 있으면 LED켜기 없으면 끔
        if (cnt > 0) LEDOn();
        else if (cnt == 0) { // 사람 없을때는 FAN도 종료
            LEDOff();
            FANOff();
        }

        //연기측정해서 일정값 이상이면 FAN 동작
        if (smokeValue >= 1000) FANOn(); //평상시 value가 700정도를 유지하여 1000으로 설정
        else if (smokeValue < 1000) FANOff();
        printf("smoke sensor value = %u\n", smokegValue);

        reset++; //while문이 돌아가는 동안 값 증가
        if (reset > 15) { //while문이 10번 돌아갈동안 초음파센서 두개를 모두 못지나갈 경우 초기화
            enter = 0;
            out = 0;
            reset = 0;
        }

        delay(100); // while문의 센서 받아들이는 딜레이
    }
    return 0;
}