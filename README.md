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
#### &nbsp;&nbsp; 2. 사람이 들어오면 LCD로 인원수 출력(1명 이상일시 자동으로 부스안 조명 켜짐)
#### &nbsp;&nbsp; 3. 문이 제대로 닫히지 않았을 경우 LED 점등
#### &nbsp;&nbsp; 4. 연기가 감지되면 환풍기 작동
![6](https://user-images.githubusercontent.com/82360230/189921267-8eb793ca-fcd2-42a2-b223-1dd5c28b06e0.jpg)

## 🔧 주요 부품
![1](https://user-images.githubusercontent.com/82360230/189916413-2fb921e4-3158-46c7-b1d6-053dc425471e.png)

<br />

## 📐 설계 단계
![3](https://user-images.githubusercontent.com/82360230/189916431-c1c9476f-36b4-4273-9b32-851bdad2b104.png)

## 📗 기능 설계
### (1) 전체적인 기능도
![2](https://user-images.githubusercontent.com/82360230/189916425-f3b6029d-6363-4427-a227-3be1a28cc2b6.png)

### (2) 세부 기능도
![4](https://user-images.githubusercontent.com/82360230/189916439-387d7de9-53bf-4aed-876a-a4db3be48c26.png)

## 📘 기능 구현
### 1. 문 자동 오픈
![문_AdobeExpress](https://user-images.githubusercontent.com/82360230/189928460-ce607146-5050-4f5b-96bd-78282a5a7f78.gif)
<br>
- 버튼센서를 통해 버튼을 누르면 자동으로 문이 열림
- 문이 열리고 3초뒤 자동으로 닫힘

<br>

### 2. 인원수 체크
![인원수_AdobeExpress](https://user-images.githubusercontent.com/82360230/189928452-b50f8ce2-1fe8-44dc-84d2-04253c9bfdd1.gif)
<br>
- 벽면에 초음파 센서 2개를 부착하여 물체가 이동했을때 인식함
  - 2개의 센서를 연달아 부착하여 앞쪽에 있는 센서에 먼저 물체가 인식이 되면 들어온것으로 판단하여 외부의 FND센서에 +1을 해줌
  - 뒤쪽에 있는 센서에 먼저 물체가 인식이 되면 안에서 밖으로 나간것으로 판단하여 외부의 FND센서에 -1을 해줌
  - 이때, 최소 1명이라도 흡연부스 안으로 들어오면 자동으로 전등 LED가 켜지고 내부에 아무도 없으면 자동으로 LED가 꺼짐 

<br>

### 3. 가스센서, 팬동작
![가스센서_AdobeExpress](https://user-images.githubusercontent.com/82360230/189928465-8d4c43c6-e3ed-454c-a999-d5553f348777.gif)
![팬동작_AdobeExpress](https://user-images.githubusercontent.com/82360230/189928403-ba34d05e-3cf3-4ccc-a83c-36798dd4dd5d.gif)
<br> 
- 흡연부스 안에서 흡연을 시작하면 천장에 부착된 가스센서를 통해 연기를 흡수해 해당 연기의 양을 측정하여 숫자로 변환
- 측정한 숫자가 설정한 범위를 넘어갈 경우 자동으로 팬 센서가 동작하여 연기를 밖으로 
