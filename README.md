# Smoking-Booth

### 라즈베리파이를 이용한 자동화 흡연부스

# 🗓 프로젝트 기간
- 2021년 11월 07일 ~ 2021년 12월 15일
<br />

# ⚙️ 기술 스택
<div>
  <img src="https://img.shields.io/badge/c-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white">
  <img src="https://img.shields.io/badge/Raspberry Pi-A22846?style=for-the-badge&logo=Raspberry Pi&logoColor=black">
</div>

<br />

## ☁️ 프로젝트 주요 기능 
#### &nbsp;&nbsp; 1. 버튼을 누르면 출입구 Open 
#### &nbsp;&nbsp; 2. 사람이 들어오면 LCD로 인원수 출력
#### &nbsp;&nbsp; 3. 문이 제대로 닫히지 않았을 경우 LED 점등
#### &nbsp;&nbsp; 4. 연기가 감지되면 환풍기 작동
![6](https://user-images.githubusercontent.com/82360230/189921267-8eb793ca-fcd2-42a2-b223-1dd5c28b06e0.jpg)

## 🔧 주요 부품
![1](https://user-images.githubusercontent.com/82360230/189916413-2fb921e4-3158-46c7-b1d6-053dc425471e.png)

<br />

## 📐 설계 단계
![3](https://user-images.githubusercontent.com/82360230/189916431-c1c9476f-36b4-4273-9b32-851bdad2b104.png)

## 📗 기능 설계
![2](https://user-images.githubusercontent.com/82360230/189916425-f3b6029d-6363-4427-a227-3be1a28cc2b6.png)

![4](https://user-images.githubusercontent.com/82360230/189916439-387d7de9-53bf-4aed-876a-a4db3be48c26.png)

## 📘 기능 구현
# 1. 문 자동 오픈
![문_AdobeExpress](https://user-images.githubusercontent.com/82360230/189928460-ce607146-5050-4f5b-96bd-78282a5a7f78.gif)
(1) 버튼 클릭
(2) 서보모터 동작
(3) 일정 시간 후 자동으로 닫힘

# 2. 인원수 체크
![인원수_AdobeExpress](https://user-images.githubusercontent.com/82360230/189928452-b50f8ce2-1fe8-44dc-84d2-04253c9bfdd1.gif)
(1) 초음파 센서를 통한 지나간 사람 체크
(2) 코드 내부에서 입장 퇴장 판단
    - 2개의 초음파 센서를 5cm정도 간격을 두고 설치함(앞쪽의 센서를 a, 뒤쪽의 센서를 b라 가정)
    - a센서에 먼저 감지가 된 후 b센서에 감지가 되면 입장한 것으로 판단하여 숫자 증가
    - b센서에 먼저 감지가 된 후 a센서에 감지가 되면 퇴장한 것으로 판단하여 숫자 감소
(3) FND센서를 통한 현재 흡연부스 안 인원 체크
    - 인원이 1명이상일때 자동으로 LED센서를 통해 조명이 켜짐
    - 인원이 0명일때 자동으로 LED센서가 꺼짐
    
# 3. 가스센서, 팬동작
![가스센서_AdobeExpress](https://user-images.githubusercontent.com/82360230/189928465-8d4c43c6-e3ed-454c-a999-d5553f348777.gif)

![팬동작_AdobeExpress](https://user-images.githubusercontent.com/82360230/189928403-ba34d05e-3cf3-4ccc-a83c-36798dd4dd5d.gif)

(1) 천장에 가스센서를 통해 흡연가스(연기) 감지
(2) 설정해놓은 가스 치수를 초과할 시 자동으로 FAN이 동작하게 됨
(3) FAN을 통해 내부의 연기를 외부로 배출시킴
