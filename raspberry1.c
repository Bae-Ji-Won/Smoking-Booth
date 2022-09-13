#include <wiringPi.h>
#include <softTone.h>
#include <stdio.h>
#include <softPwm.h>

#define KEY1 23 		// 키패드 핀 번호1
#define KEY2 24 		// 키패드 핀 번호 2
#define SERVO 18		// 서보 모터 핀 번호 설정

#define MAX_KEY_BT_NUM 2		// 키 패드 개수 2개

#define BUZZER_PIN 2		// 부저 핀 번호 설정
#define SI 987			// 음악 주파수 설정

const int KeypadTable[2] = { KEY1,KEY2 };   // 키 패드 배열 설정

int KeypadRead(void) {	// keypad 버튼 눌림을  확인하여 nkeypadstate 상태 변수에 값을 저장
    int i, nKeypadstate;
    nKeypadstate = 0;
    for (i = 0; i < MAX_KEY_BT_NUM; i++) {
        if (!digitalRead(KeypadTable[i])) {
            nKeypadstate |= (1 << i);
        }
    }
    return nKeypadstate;
}
unsigned int SevenScale(unsigned char scale) {   	     // 소리 출력을 위한 설정
    unsigned int _ret = 0;
    switch (scale) {
    case 6:
        _ret = SI;
        break;
        return _ret;
    }
}

void Change_FREQ(unsigned int freq) {	     // 소리 바꾸는 함수(주파수 변경)
    softToneWrite(BUZZER_PIN, freq);
}
void STOP_FREQ(void) {		// 소리 멈추는 함수(주파수 0값)
    softToneWrite(BUZZER_PIN, 0);
}
void Buzzer_Init(void) {		// 소리 출력 함수
    softToneCreate(BUZZER_PIN);
    STOP_FREQ();
}

void motorturn(void) {
    softPwmWrite(SERVO, 5);		// 서보모터 좌측 방향 회전
}
void motoroff(void) {
    softPwmWrite(SERVO, 25);		// 서보모터 우측 방향 회전
}
void motorstop(void) {
    softPwmWrite(SERVO, 15);		// 서보모터 정지
}

int main(void) {
    if (wiringPiSetupGpio() == -1) return 1;        //gpio사용설정
    Buzzer_Init();			// 부저 사용을 위한 선언
    int i, nKeypadstate;		// 변수 선언
    int a = 0;
    int push = 1;
    int sound;
    softPwmCreate(SERVO, 0, 200);	// 서보모터 pwm 0~200

    for (i = 0; i < MAX_KEY_BT_NUM; i++) {	// 키패드 입력시 입력 키값이 INPUT값
        pinMode(KeypadTable[i], INPUT);
    }

    while (1) {
        nKeypadstate = KeypadRead();

        for (i = 0; i < MAX_KEY_BT_NUM; i++) {	// 키패드에서 버튼이 눌렸을때 동작 실행
            if ((nKeypadstate & (1 << i))) {
                if (push == 1) {
                    for (sound = 6; sound < 7; sound++)
                    {
                        motorturn();			// 서보모터 동작 실행(문 오픈)
                        Change_FREQ(SevenScale(sound));	// 문이 열리면서 동시에 소리 출력
                        delay(1200);			//1.2초 동안 문이 열림

                        motorstop();			// 서보모터 정지 문이 완전히 열린 상태
                        STOP_FREQ();			// 소리 정지
                        delay(2000);            // 사람이 들어와야 하니깐 문이 2초동안 열려있는 상태
                        motoroff();	// 서보모터 반대방향 동작 실행(문 닫힘)
                        delay(1000);	//1초동안 문이 닫힘
                        motorstop();			// 서보모터 정지
                    }
                    push = 1;

                }
            }
        }

    }


    return 0;
}


