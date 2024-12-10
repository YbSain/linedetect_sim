# 유튜브 링크 
## 화면

[https://youtu.be/uKRLkhhVYKI](https://youtu.be/5Y556hC90vM?si=HEa8OffGyhtZt3Km)
## 로봇 포함

https://youtube.com/shorts/T-Y4QZZH1-U?si=685WmZXFb4cQ0NZB

# 정리

## 상단부

https://github.com/YbSain/CVworkspace/blob/a0ea67aa84102feed9ac5c457ffd2c65a42abfba/linetrace/main.cpp#L11-L21

동작 및 함수에 관련된 파트들이다.

### 영상관련

https://github.com/YbSain/CVworkspace/blob/a0ea67aa84102feed9ac5c457ffd2c65a42abfba/linetrace/main.cpp#L32-L47

해당 파트에서 cap으로 "7_it_ccw_100rpm_in.mp4" 영상을 입력받고, 그것을 gstream으로 윈도우즈의 powershell 환경에서 확인할 수 있게 만들었다.

#### Roi

writer2는 사이즈를 640, 90으로 따로 조절 해 주었음.

### 런타임 지정

https://github.com/YbSain/CVworkspace/blob/0889c5afc8b5aceb50e80173acf98271cf089b5f/linetrace/main.cpp#L61

메인 코드 내부에서 while(true) 반복문 시작과 동시에 시간을 측정시키기 위해 사용되었다.

https://github.com/YbSain/CVworkspace/blob/0889c5afc8b5aceb50e80173acf98271cf089b5f/linetrace/main.cpp#L86-L91

코드의 후반부분에  end1이 들어가며 시간 계산을 마무리한 뒤, diff에 초기화하여 cout으로 출력하는 작업을 거침

https://github.com/YbSain/CVworkspace/blob/0889c5afc8b5aceb50e80173acf98271cf089b5f/linetrace/main.cpp#L67-L69

해당 과정은 원본 > Roi범위 > GrayScale > 밝기 조절 > 이진화 > 잡음관리까지 포함시킨 Mat makethresh()를 사용하였고, 추후 레이블링을 하기 위해서 clone()을 만들어, GrayScale영상을 하나 구비 해 두었다.

https://github.com/YbSain/CVworkspace/blob/0889c5afc8b5aceb50e80173acf98271cf089b5f/linetrace/main.cpp#L100-L123

위에서 사용된 makethresh() 내부 모습인데, 640x360 중 높이가 90cm인 하단 부분을 Roi범위로 지정하고 싶어, y점을 270으로 지정하였다.

Mat frame은 원본영상을 그대로 받아두었고, mean()함수를 사용하여 기존 영상의 밝기를 변수에 초기화한 뒤, 원하는 밝기를 선정하여서

밝기 계산을 위한 값 = 원하는 밝기 - 현재 밝기를 사용하여 현재 밝기가 원하는 밝기보다 밝을 경우 음수 값이 나오고, 어두울 경우 양수 값이 나오는데

converTo() 함수를 이용하여 같은 영상조건으로 해당 수치만큼 셈하도록 만들었음.

이후에는 이진화 및, 잡음 추가 작업이 이루어져있다.

https://github.com/YbSain/CVworkspace/blob/0889c5afc8b5aceb50e80173acf98271cf089b5f/linetrace/main.cpp#L71-L73

해당파트는 Labeling으로 칭한 함수를 통해 targetCenter 즉 매번 움직이는 도로의 중심좌표를 짚고, 영상의 중앙 좌표를 비교하여 error값을 구해내는 파트임.

https://github.com/YbSain/CVworkspace/blob/0889c5afc8b5aceb50e80173acf98271cf089b5f/linetrace/main.cpp#L124-L155

이는 레이블링 함수인데, labels, stats, centroids를 사용해서 도로를 네모 + 붉은 색으로 표현하고, 그 외의 감지되는 것은 다른 색으로 표현하였다.

xdistance는 타겟의 센터 위치 - 무게중심 x좌표의 차이인데, 이 값의 차이가 너무 크거나 너무 작을 경우, 해당 객체가 아닌 다른 객체를 인지 했을 거라 판단하여, 다시 감지 할 때까지 다른 행동을 하지 않음.  

가장 처음으로는 bool으로 가장 처음 좌표를 선정 한 뒤, true로 전환하여 아래의 조건문을 활용하도록 함.    

true로 전환 된 이후에는 조건에 부합할경우 현재 중앙좌표와 바운딩 박스를 지속적으로 저장하게 하고, 해당 객체의 중앙에는 circle 테두리에는 rectangle을 그려냄.

이후 해당함수는 Grayframe 즉, 해당 객체의 움직임을 보여주기위한 rect, circle이 그려진 영상을 반환한다.

https://github.com/YbSain/CVworkspace/blob/0889c5afc8b5aceb50e80173acf98271cf089b5f/linetrace/main.cpp#L153-L155

해당 함수는 getError 즉 영상의 x좌표 중앙 값과, 타겟이 된 도로위치 객체의 x좌표를 비교하여 int getError의 반환 값으로 반환시킴.

