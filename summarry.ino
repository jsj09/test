#define DS 51 // Data
#define STCP A7 // Latch
#define SHCP 52 // Shift
#define SS595 53 // Output Enable , digitalwrite low로 gnd 처리
#define Units 32 // 1의자리 (FND 5번 핀), FND VCC 0
#define Tens 23 // 10의자리 (FND 10번 핀), FND VCC 1

//음계, 주기 반쪽(micros 단위)
#define C4 1911.128 //도
#define D4 1702.611 //레
#define E4 1516.865 // 미
#define F4 1351.372 // 파
#define G4 1275.526 // 솔
#define A4 1136.364 //라
#define B4 1012.385 //시
#define C5 955.564
#define D5 851.3107
#define E5 1516.865113
#define F5 1431.729415

const byte ROWS = 5;
const byte COLS = 4;

int buzzerPin = 17, echoPin = 18, triggerPin = 64, swPin = 2, rmcPin = 19, cdsPin = 60, servoPin0 = 4, servoPin1 = 3;
int fndPins[8] = { 30, 24, 25, 27, 26, 31, 28, 29 }; // A~G, DP
int MatrixCol[8] = { 36, 39, 40, 47, 42, 46, 34, 33 };  
int MatrixRow[8] = { 48, 35, 44, 45, 37, 43, 38, 41 };

unsigned char numData[10][8] = {{0x00, 0x38, 0x44, 0x4c, 0x54, 0x64, 0x44, 0x38}, //0
  {0x00, 0x10, 0x30, 0x50, 0x10, 0x10, 0x10, 0x7c}, //1
  {0x00, 0x38, 0x44, 0x04, 0x08, 0x10, 0x20, 0x7c}, //2
  {0x00, 0x38, 0x44, 0x04, 0x18, 0x04, 0x44, 0x38}, //3
  {0x00, 0x08, 0x18, 0x28, 0x48, 0x7c, 0x08, 0x08}, //4
  {0x00, 0x7c, 0x40, 0x78, 0x04, 0x04, 0x44, 0x38}, //5
  {0x00, 0x38, 0x40, 0x40, 0x78, 0x44, 0x44, 0x38}, //6
  {0x00, 0x7c, 0x04, 0x08, 0x10, 0x20, 0x20, 0x20}, //7
  {0x00, 0x38, 0x44, 0x44, 0x38, 0x44, 0x44, 0x38}, //8
  {0x00, 0x38, 0x44, 0x44, 0x3c, 0x04, 0x44, 0x38}
}; //9
unsigned char dotMatrix[8][8] = {0,};

int Num[10] =  { 0x3f, 0x06, 0x5b, 0x4f, 0x66,
                 0x6d, 0x7d, 0x27, 0x7f, 0x6f
               }; // fnd 0~9
int dotNum[10] = { 0xbf, 0x86, 0xdb, 0xcf, 0xe6,
                   0xed, 0xfd, 0xa7, 0xff, 0xef
                 }; // fnd 0~9+DP

char key[ROWS][COLS] = {{ 'C', '(', '%', '/' },
  { '7', '8', '9', 'X' },
  { '4', '5', '6', '-' },
  { '1', '2', '3', '+' },
  { '.', '0', 'P', '=' }
};

byte rowPins[ROWS] = { 12, 10, 8, 6, 5 };
byte colPins[COLS] = { 13, 11, 9, 7 };

char bs, pbs;  //button status, previous button status
int pck; //previous colum key
int row, col = 0;
int psw = 0, csw = 0;
int pcnt, cnt = 0;
byte toggle = 0, flag = 1, flag2 = 1, IR_tf = 0; 
int Distance; // 초음파 거리
unsigned long R_Time = 0, F_Time = 0; //rising time, falling time

unsigned long lead = 13500, scope = 100, ontime = 2200, offtime = 1100, delaymicro = 0; // 리모콘 리드코드, 오차, 1, 0
unsigned long IR_Data[34] = { 0, };
unsigned long IR_Data2[34] = { 0, };
unsigned long IR_num = 0;
int IR_num2;
unsigned char IR_hex[10] =  { 0x68, 0x30, 0x8C, 0xBD, 0x88, 0x9C, 0x5A, 0x42, 0x4A, 0x52 }; // 0 ~ 9

typedef struct {
  unsigned long previousMillis = 0, previousMillis2 = 0, previousMicros = 0;
  unsigned long currentMillis, currentMicros, currentMicros2;
  int Delay, Delay2;
  int count = 1, count2 = 0;
} DEVICE;

DEVICE FND, FNDcounter, DotMatrix, Dot, LED, SW, BUZZER, Sonic, RMC;

typedef struct {
  int melody;
  unsigned long tempo;
} MUSIC;

MUSIC music[] = { {G4, 500}, {G4, 500}, {A4, 500}, {A4, 500},
  {G4, 500}, {G4, 500}, {E4, 1000},
  {G4, 500}, {G4, 500}, {E4, 500}, {E4, 500},
  {D4, 1200},
  {G4, 500}, {G4, 500}, {A4, 500}, {A4, 500},
  {G4, 500}, {G4, 500}, {E4, 1000},
  {G4, 500}, {E4, 500}, {D4, 500}, {E4, 500},
  {C4, 1200}
};


void setup() {
  Serial.begin(115200);

  //buzzer
  pinMode( buzzerPin, OUTPUT );
  pinMode( swPin, INPUT );  // 스위치 눌렀을 때 부저로 노래 출력

  //7459
  pinMode( DS , OUTPUT );
  pinMode( STCP, OUTPUT );
  pinMode( SHCP, OUTPUT );
  pinMode( SS595, OUTPUT );
  digitalWrite( SS595, LOW );

  //FND
  pinMode( Units, OUTPUT );
  pinMode( Tens, OUTPUT );
  for ( int i = 0; i < 8; i++ ) {
    pinMode( fndPins[i], OUTPUT );
  }

  //KEY MATRIX
  for (int col = 0; col < COLS; col++ ) {
    pinMode ( colPins[col], OUTPUT );
    digitalWrite( colPins[col], HIGH );
  }
  for ( int row = 0; row < ROWS; row++ ) {
    pinMode ( rowPins[row], INPUT );
  }
  
  //DOT MATRIX
  for ( int i = 0; i < 8; i++ ) {
    pinMode( MatrixCol[i], OUTPUT );
    pinMode( MatrixRow[i], OUTPUT );
    digitalWrite( MatrixCol[i], HIGH );
  }
  
  //ULTRASONIC SENSOR
  pinMode( triggerPin, OUTPUT );
  pinMode( echoPin, INPUT );
  digitalWrite( echoPin, HIGH );
  attachInterrupt( 5, myISR, CHANGE );

  // 리모컨
  attachInterrupt( 4, RMC_ISR, FALLING );

  //조도센서+서보
  pinMode( servoPin0, OUTPUT );
  pinMode( servoPin1, OUTPUT );

}

//초음파 센서 거리 출력
void myISR() {
  if ( digitalRead(echoPin) == HIGH ) {
    Sonic.currentMicros = micros();
    R_Time = Sonic.currentMicros;
    digitalWrite( triggerPin, HIGH );

  } else {
    Sonic.currentMicros2 = micros();
    F_Time = Sonic.currentMicros2;
    Distance = ( F_Time - R_Time ) / 29 / 2 ;

    Serial.println("Distance = " + String( Distance ) );

    digitalWrite( triggerPin, LOW );
  }
}//ISR end

//적외선 센서에 리모콘 신호 감지되었을 때 인터럽트
void RMC_ISR() {
  if ( IR_tf == 0 ) {
    IR_tf = 1;
    RMC.previousMicros = micros();
  }
  else {
    RMC.currentMicros = micros();
    if ( ( delaymicro = RMC.currentMicros - RMC.previousMicros ) >= lead - scope && delaymicro <= lead + scope ) {
      RMC.previousMicros = RMC.currentMicros;
      if ( RMC.count2 != 0 ) RMC.count2 = 0;
      if ( IR_num != 0 ) IR_num = 0;
      IR_Data[RMC.count2++] = delaymicro;
      IR_num = 1;
      IR_num = IR_num << 1;
      return;
    } else (( delaymicro >= ontime - scope && delaymicro <= ontime + scope ) || ( delaymicro >= offtime - scope && delaymicro <= offtime + scope )); {
      RMC.previousMicros = RMC.currentMicros;
      IR_Data[RMC.count2++] = delaymicro;
      if ( IR_Data[RMC.count2 - 1] >= ontime - scope && IR_Data[RMC.count2 - 1] <= ontime + scope ) {
        IR_Data[RMC.count2 - 1] = 1;
        IR_num = IR_num << 1;
        IR_num |= 1;
      }
      if ( IR_Data[RMC.count2 - 1] >= offtime - scope && IR_Data[RMC.count2 - 1] <= offtime + scope ) {
        //  IR_Data[RMC.count2-1] = 0;
        IR_num = IR_num << 1 ;
      }
      return;

    }
    IR_tf = 0;
    RMC.count2 = 0;
    IR_Data[0] = 0;
  }
}//RMC ISR end

void data1() {  
  digitalWrite( DS, LOW );
  digitalWrite( SHCP, HIGH );
  digitalWrite( SHCP, LOW );
  digitalWrite( DS, LOW );
}
void data0() {  
  digitalWrite( DS, HIGH );
  digitalWrite( SHCP, HIGH );
  digitalWrite( SHCP, LOW );
  digitalWrite( DS, LOW );
}

//7459로 LED shift
void LED_ON(int num) { 
  LED.currentMillis = millis();
  if ( (LED.currentMillis - LED.previousMillis) > 500 ) {
     if ( digitalRead(swPin) == LOW ) LED.previousMillis = LED.currentMillis;
     if ( LED.count > 127 ) flag2 = 0;
     if ( LED.count < 2 ) flag2 = 1;
     if ( flag2 == 1 ) LED.count = LED.count * 2;
     if ( flag2 == 0 ) LED.count = LED.count / 2;
  }

  for ( int n = 7; n >= 0; n-- ) {
    if ( digitalRead(swPin) == LOW )  
    if ( num & ( 1 << n ) ) {
      if ( digitalRead(swPin) == LOW )   
      data0();
    }
    else {
      if ( digitalRead(swPin) == LOW )   
      data1();
    }
  }
  if ( digitalRead(swPin) == LOW )   
  digitalWrite( STCP, HIGH );
  if ( digitalRead(swPin) == LOW )  
  digitalWrite( STCP, LOW );
}

//키 매트릭스 스위치 전원
void SW_vcc() {
  SW.currentMillis = millis();
  SW.Delay = 10;
  if ( SW.currentMillis - SW.previousMillis > SW.Delay ) { // 10미리마다 전원
    if ( digitalRead(swPin) == LOW )  
    SW.previousMillis = SW.currentMillis;
    digitalWrite( colPins[psw], HIGH );
    if ( digitalRead(swPin) == LOW )   
    digitalWrite( colPins[csw], LOW );
    if ( digitalRead(swPin) == LOW )  
    psw = csw;
    csw++;
    if ( csw > 3 ) csw = 0;
  }
}

//키 매트릭스 스위치 판별
void SW_ON() {
  SW_vcc();
  SW.Delay = 1;
  SW.currentMillis = millis();
  if ( SW.currentMillis - SW.previousMillis2 > SW.Delay ) { // 1미리마다 체크
    SW.previousMillis2 = SW.currentMillis;
    if ( digitalRead(swPin) == LOW )   
    for ( row = 0; row < ROWS; row ++ ) { 
      if ( digitalRead(swPin) == LOW )   
      if ( !digitalRead(rowPins[row]) ) { //스위치 눌렸을 때
        if ( pbs == key[row][psw] ) break; //이전 키랑 지금 키 같으면 반복문 나가기
        if ( pbs == 20 ) { //이전에 아무 키도 눌리지 않았을 때
          Serial.print( key[row][psw] );
          if ( digitalRead(swPin) == LOW )   
        } else { // 20이 아닐때, 뭔가 눌렸을 때
          Serial.print( key[row][psw] );
          if ( digitalRead(swPin) == LOW )  
        }
        pbs = key[row][psw]; //이전키 저장
        pck = psw; break; // 이전 칼럼이 어디였는지 저장
      }
    }
    if ( row == 5 ) {
      if ( pck == psw ) { //다시 같은 칼럼 돌아왔을때, 스위치가 떨어졌다 아니다 판단
        pbs = 20;
        pck = 20;

      }
    }
  }
}//sw end

void printNum(int num) {
  for ( int m = 7; m >= 0; m-- ) {
    if ( Num[num] & (1 << m) ) { // 1
      if ( digitalRead(swPin) == LOW )  digitalWrite( fndPins[m] , LOW );
    }
    else { // 0
      if ( digitalRead(swPin) == LOW )  digitalWrite( fndPins[m] , HIGH );
    }
  }
}

//도트 매트릭스 
void printdotNum(int num) {
  if ( flag == 0 ) {
    if ( digitalRead(swPin) == LOW )  
    digitalWrite ( fndPins[7] , LOW );
  }
  else {
    if ( digitalRead(swPin) == LOW )  
    digitalWrite ( fndPins[7], HIGH );
  }
  for ( int m = 6; m >= 0; m-- ) {
    if ( Num[num] & (1 << m) ) { // 1
      if ( digitalRead(swPin) == LOW )   
      digitalWrite( fndPins[m] , LOW );
    }
    else { // 0
      if ( digitalRead(swPin) == LOW )   
      digitalWrite( fndPins[m] , HIGH );
    }
  }
}

void FND_count() { //FND 7세그먼트로 초음파 거리 출력
  FNDcounter.currentMillis = millis();
  Dot.Delay = 500;
  if ( FNDcounter.currentMillis - FNDcounter.previousMillis > Dot.Delay ) { //0.5초마다 카운트
    FNDcounter.previousMillis = FNDcounter.currentMillis;
    FND.count++;
    if ( digitalRead(swPin) == LOW )  
    if ( FND.count > 20 ) FND.count = 0;
    if ( flag == 1 ) {
      flag = 0; //0.5초마다 0 또는 1, 1들어올 때만 fnd 카운트 올려주면 1초에 한번씩 카운트
      FND.count2++;
      if ( FND.count2 >= 100 ) FND.count2 = 0;
    }
    else flag = 1; //dot flag
  }
}//count end

void FND_ON() {
  FND_count();
  FND.currentMillis = millis();
  if ( FND.currentMillis - FND.previousMillis > FND.Delay ) {
    if ( digitalRead(swPin) == LOW )  
    FND.previousMillis = FND.currentMillis;
    if ( toggle == 0 ) { //10의 자리
      if ( digitalRead(swPin) == LOW )   
      digitalWrite( Units, LOW );
      printNum( Distance / 10 );
      digitalWrite( Tens, HIGH );
      toggle = 1;
    }
    else { //1의 자리
      if ( digitalRead(swPin) == LOW )  
      digitalWrite( Tens, LOW );
      printdotNum( Distance % 10 );
      digitalWrite( Units, HIGH );
      toggle = 0;
    }
  }
}//FND end

void tune() { // 노래 음계
  if ( digitalRead(buzzerPin) == LOW ) {
    digitalWrite( buzzerPin, HIGH ); //반주기만큼 하이
  } else {
    digitalWrite( buzzerPin, LOW ); //남은 반주기만큼 로우
  }
}//tune end

void tempo() {
  BUZZER.count2++;
  if ( BUZZER.count2 >= (sizeof(music) / sizeof(MUSIC)) ) BUZZER.count2 = 0;
}

void Music_ON() {
  BUZZER.currentMicros = micros();
  if ( (BUZZER.currentMicros - BUZZER.previousMicros) > music[BUZZER.count2].melody ) { //멜로디
    BUZZER.previousMicros = BUZZER.currentMicros;
    if (  ( millis() - BUZZER.previousMillis < music[BUZZER.count2].tempo - 80 ) ) tune(); //현재 millis 에서 지나간 값(측정된 시간) 뺀 게
  }
  BUZZER.currentMillis = millis();
  if ( (BUZZER.currentMillis - BUZZER.previousMillis) > music[BUZZER.count2].tempo ) {
    BUZZER.previousMillis = BUZZER.currentMillis;
    tempo();
  }
}

//도트 매트릭스
void displayMatrix() { // 각 줄 on, off
  digitalWrite( MatrixCol[pcnt], HIGH );
  digitalWrite( MatrixCol[cnt], LOW );
  
  for ( int i = 0; i < 8; i++ ) {
    if ( dotMatrix[cnt][i] == 1 )
    { 
      digitalWrite( MatrixRow[i], HIGH );  
    }
    else {
      digitalWrite( MatrixRow[i], LOW );
    }
  }
}

void inputNum(int inp) {
  for ( int i = 0; i < 8; i++ ) {
    for ( int j = 0; j < 8; j++ ) {
      if ( ( numData[inp][i] << j ) & 0x80 )
        dotMatrix[j][i] = 1;
      else
        dotMatrix[j][i] = 0;
    }
  }
}

void Matrix_ON() {
  DotMatrix.currentMillis = millis();
  if ( ( DotMatrix.currentMillis - DotMatrix.previousMillis2 ) > 1 ) {  
    DotMatrix.previousMillis2 = DotMatrix.currentMillis;

    if ( cnt == 8 ) cnt = 0;
    inputNum(IR_num2); //입력받은 리모컨 값을 도트 매트릭스로 출력
    displayMatrix();
    pcnt = cnt;
    cnt++;
  }
}

void RMC_ON() {
  if ( RMC.count2 >= 33) {
    RMC.count2 = 0;
    IR_tf = 0;
    switch (IR_num) { //리모콘 값을 도트 매트릭스와 시리얼 모니터로 출력 
      case 0xFF6897 :
        IR_num = 0;
        IR_num2 = 0; 
        Serial.print("0");
        break;

      case 0xFF30CF :
        IR_num = 1;
        IR_num2 = 1;
        Serial.print("1");
        break;

      case 0xFF18E7 :
        IR_num = 2;
        IR_num2 = 2;
        Serial.print("2");
        break;

      case 0xFF7A85 :
        IR_num = 3;
        IR_num2 = 3;
        Serial.print("3");
        break;

      case 0xFF10EF :
        IR_num = 4;
        IR_num2 = 4;
        Serial.print("4");
        break;

      case 0xFF38C7 :
        IR_num = 5;
        IR_num2 = 5;
        Serial.print("5");
        break;

      case 0xFF5AA5 :
        IR_num = 6;
        IR_num2 = 6;
        Serial.print("6");
        break;

      case 0xFF42BD :
        IR_num = 7;
        IR_num2 = 7;
        Serial.print("7");
        break;

      case 0xFF4AB5 :
        IR_num = 8;
        IR_num2 = 8;
        Serial.print("8");
        break;

      case 0xFF52AD :
        IR_num = 9;
        IR_num2 = 9;
        Serial.print("9");
        break;

      case 0xFFA25D :
        Serial.print("ch-");
        break;

      case 0xFF629D :
        Serial.print("ch");
        break;

      case 0xFFE21D :
        Serial.print("ch+");
        break;

      case 0xFF22DD :
        Serial.print("<<");
        break;

      case 0xFF02FD :
        Serial.print(">>");
        break;

      case 0xFFC23D :
        Serial.print(">|");
        break;

      case 0xFFE01F :
        Serial.print("-");
        break;

      case 0xFFA857 :
        Serial.print("+");
        break;

      case 0xFF906F :
        Serial.print("EQ");
        break;

      case 0xFF9867 :
        Serial.print("FL+");
        break;

      case 0xFFB04F :
        Serial.print("FL-");
        break;
    }
  }
}

void SERVO_ON() {
 

}
void loop() {
  if ( digitalRead(swPin) == LOW )  Music_ON();
  LED_ON(LED.count);
  SW_ON();
  FND_ON();
  Matrix_ON();
  Sonic_ON();
  RMC_ON();
  SERVO_ON();

}//loop end
