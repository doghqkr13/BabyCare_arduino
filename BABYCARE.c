// 프로젝트명 : BABY CARE
// 의도 : 아기를 하루종일 볼 수 없는 엄마들에게 아이의 상태와 정보들을 수시로 받아봄으로써 활동을 자유롭게 할 수 있다.
#define LIGHT_POINT 500

#define LED_EN_PIN 6
#define SW_EN_PIN 7
#define SW_NUM 23
#define BUZZER 40
#define EL_SW 41
#define MOTION_SEN 0
#define LIGHT_SEN A0
#define TEMP_SEN A2
 
int DC_MOTOR[3] = {45, 46, 47};
int LED_NUM[9]={0,22,24,26,28,30,32,34,36};
int data; //온도
float data2; //온도2
char a ;
 
void setup() {
  

   while(!Serial);
   Serial.begin(9600);

   pinMode(LED_EN_PIN, OUTPUT);
   pinMode(SW_EN_PIN, OUTPUT);
   digitalWrite(LED_EN_PIN, LOW);
   digitalWrite(SW_EN_PIN, LOW);

   //움직임을 감지하여 부저로 알람
   
   pinMode(MOTION_SEN, INPUT);  //아기의 반복된 움직임을 감지하기 위함(아기가 자다 깼을 경우)
   pinMode(BUZZER, OUTPUT);     //방에 있지 않은 보호자에게 부저로 알림을 울리기 위함



   //빛의 조절을 통해 최적의 조도를 유지
   
   pinMode(LIGHT_SEN, INPUT);   //빛센서를 이용하여 아기가 잠들기 위한 최적의 조도를 유지하기 위함
   
   led_pin_set();               //밝음, 적당, 어두움 3단계로 나누어 1.밝을 시 모든 LED를 끔, 2.적당할 시 중간단계의 LED유지, 3.어두울 시 모든LED를 켜는 식으로 구현
   

   //온도 조절을 통해 따뜻한 온도를 유지
  
   pinMode(TEMP_SEN, INPUT);    //온도센서를 이용하여 방 안의 온도를 측정하기 위함
   dc_motor_set();              //방안의 온도가 적정수준보다 높으면 DC_MOTOR를 사용하여 환풍기를 정회전 시키기 위함, 낮으면 보일러를 키는 등으로 연계가 가능하다.
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void loop() {
   digitalWrite(MOTION_SEN, LOW);
   digitalWrite(BUZZER, LOW);
   

  if(digitalRead(MOTION_SEN) == HIGH)
  {
    buzzer_control();
   }

  if(800<analogRead(LIGHT_SEN))
   {
    led_reset();
    }
   else if(600<analogRead(LIGHT_SEN)<800)
    {
   a = 'a';
     led_control(a);
    }
    
 data=analogRead(TEMP_SEN);
 data2=data/2.046;
 data2-=50;
 
  if(43<data2){
  dc_motor_active();}

  Serial.println(digitalRead(MOTION_SEN)); //움직임감지
  Serial.println(analogRead(LIGHT_SEN)); //빛감지
  Serial.println(analogRead(TEMP_SEN)); //온도감지
  Serial.print("temp:"); //온도감지
  Serial.println(data2);
  Serial.println("");
  delay(2000);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------
 
//buzzer 켜기
void buzzer_control(){
  digitalWrite(BUZZER, HIGH);
  delay(1000); 
  digitalWrite(BUZZER, LOW); 
}
 
//LED 제어
void led_control(char a){
  if(a == 'a'){
    for(int b=1;b<5;b++){
    digitalWrite(LED_NUM[b],HIGH);
    }
    delay(2000);
    for(int b=1;b<5;b++){
    digitalWrite(LED_NUM[b],LOW);
    }
  }
}


void led_controlbb(){
  for(int b=1;b<9;b++){
    digitalWrite(LED_NUM[b],HIGH);
    }
    delay(2000);
  for(int b=1;b<9;b++){
    digitalWrite(LED_NUM[b],LOW);
    }
}
//LED 초기화
void led_reset(){
  for(int a=1;a<9;a++){
    digitalWrite(LED_NUM[a],LOW);
  }
}
//LED pinMode set
void led_pin_set(){
  for(int a=1;a<9;a++){
    pinMode(LED_NUM[a],OUTPUT);
  }
}
//DC_MOTOR pinMode set
void dc_motor_set(){
  for(int a=0;a<3;a++){
    pinMode(DC_MOTOR[a],OUTPUT);
  }
}

void dc_motor_active(){
   digitalWrite(DC_MOTOR[0],HIGH);
   digitalWrite(DC_MOTOR[1],LOW);
   digitalWrite(DC_MOTOR[2],HIGH);
}
