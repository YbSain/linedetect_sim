# 유튜브 링크 
## 화면

[https://youtu.be/uKRLkhhVYKI](https://youtu.be/5Y556hC90vM?si=HEa8OffGyhtZt3Km)    
// lt 7 cw     
https://youtu.be/Q3MHuUEuacA    
// lt 5 ccw 영상이다.    

## 로봇 포함

https://youtu.be/u5oisMOyLfY?si=Iy2T5Farp4BU9hrC     
//lt 7 ccw로 영상에 따라 바퀴의 속도가 조절되는 모습    
https://youtube.com/shorts/CuHqS9DtVdc?si=HBAjNF9FTvHQ2NUm    
//lt 5cw    
# 정리

## 상단부

https://github.com/YbSain/linedetect_sim/blob/2eb5db4c19b9c1369dc76f515ed46ecc4777fe9b/main2.cpp#L3-L6


동작 및 함수에 관련된 파트들이다.

### 영상관련

https://github.com/YbSain/linedetect_sim/blob/eeb3ecc53bb2024f5b73598c171bc358f028a2c9/main.cpp#L29-L38

카메라와 GSTREAMER를 이용하여 영상 처리함

#### Roi

writer2는 사이즈를 640, 90으로 따로 조절 해 주었음.

### 런타임 지정

https://github.com/YbSain/linedetect_sim/blob/2eb5db4c19b9c1369dc76f515ed46ecc4777fe9b/main2.cpp#L57


메인 코드 내부에서 while(true) 반복문 시작과 동시에 시간을 측정시키기 위해 사용되었다.

https://github.com/YbSain/linedetect_sim/blob/f438ca49c20454c5b0a74a5ffef41b31045e4049/main.cpp#L98-L101


코드의 후반부분에  end1이 들어가며 시간 계산을 마무리한 뒤, diff에 초기화하여 cout으로 출력하는 작업을 거침

## 전처리

https://github.com/YbSain/linedetect_sim/blob/f438ca49c20454c5b0a74a5ffef41b31045e4049/main.cpp#L79-L85


해당 과정은 원본 > Roi범위 > GrayScale > 밝기 조절 > 이진화 > 잡음관리까지 포함시킨 Mat makethresh()를 사용하였고, 추후 레이블링을 하기 위해서 clone()을 만들어, GrayScale영상을 하나 구비 해 두었다.

https://github.com/YbSain/linedetect_sim/blob/f438ca49c20454c5b0a74a5ffef41b31045e4049/main.cpp#L111-L134

위에서 사용된 makethresh() 내부 모습인데, 640x360 중 높이가 90cm인 하단 부분을 Roi범위로 지정하고 싶어, y점을 270으로 지정하였다.

Mat frame은 원본영상을 그대로 받아두었고, mean()함수를 사용하여 기존 영상의 밝기를 변수에 초기화한 뒤, 원하는 밝기를 선정하여서

밝기 계산을 위한 값 = 원하는 밝기 - 현재 밝기를 사용하여 현재 밝기가 원하는 밝기보다 밝을 경우 음수 값이 나오고, 어두울 경우 양수 값이 나오는데

converTo() 함수를 이용하여 같은 영상조건으로 해당 수치만큼 셈하도록 만들었음.

이후에는 이진화 및, 잡음 추가 작업이 이루어져있다.

## 조건

https://github.com/YbSain/linedetect_sim/blob/f438ca49c20454c5b0a74a5ffef41b31045e4049/main.cpp#L135-L166

초기에 영상의 중앙을 기준으로 거리(x좌표)가 50, -50 사이 일 경우 작동하게함 < 좌표이기때문에 반대 방향으로 갈 경우 음수처리되어 양수와 음수를 둘 다 처리함    

해당파트는 Labeling으로 칭한 함수를 통해 targetCenter 즉 매번 움직이는 도로의 중심좌표를 짚고, 영상의 중앙 좌표를 비교하여 error값에 사용할 객체의 무게중심을 구해내는 파트임.    

labels, stats, centroids를 사용해서 도로를 네모 + 붉은 색으로 표현하고, 그 외의 감지되는 것은 다른 색으로 표현하였다.

xdistance는 타겟의 센터 위치 - 무게중심 x좌표의 차이인데, 이 값의 차이가 너무 크거나 너무 작을 경우, 해당 객체가 아닌 다른 객체를 인지 했을 거라 판단하여, 다시 감지 할 때까지 다른 행동을 하지 않음.  

가장 처음으로는 bool으로 가장 처음 좌표를 선정 한 뒤, true로 전환하여 아래의 조건문을 활용하도록 함.    

true로 전환 된 이후에는 조건에 부합할경우 현재 중앙좌표와 바운딩 박스를 지속적으로 저장하게 하고, 해당 객체의 중앙에는 circle 테두리에는 rectangle을 그려냄.  

이후 해당함수는 Grayframe 즉, 해당 객체의 움직임을 보여주기위한 rect, circle이 그려진 영상을 반환한다.

https://github.com/YbSain/linedetect_sim/blob/f438ca49c20454c5b0a74a5ffef41b31045e4049/main.cpp#L167-L169

해당 함수는 getError 즉 영상의 중앙 x좌표 값과, 타겟이 된 도로위치 객체의 x좌표를 비교하여 int getError의 반환 값으로 반환시킴.



### DXL 모터

https://github.com/YbSain/linedetect_sim/blob/f438ca49c20454c5b0a74a5ffef41b31045e4049/main.cpp#L58-L60

https://github.com/YbSain/linedetect_sim/blob/f438ca49c20454c5b0a74a5ffef41b31045e4049/main.cpp#L87-L95

     if (mx.kbhit()){
         char ch = mx.getch();
         if (ch == 'q') break;
         else if (ch == 's') mode = true;
     }

해당 조건문에서 s 를 받을 경우 mode가 true로 변경되며 95번째 줄에 있는 조건문의 조건이 만족돼서 mx.setVelocity(좌, 우); 함수가 작동됨에 따라 모터가 작동하는 방식이다.

좌, 우 즉 lval, rval 값은 위에서 구한 Error 값을 토대로 0.1만큼 곱해서 해당 속도를 조절하도록 하였음.

-> 추후에 시뮬레이션 한 이후 K의 값은 조절할 예정


