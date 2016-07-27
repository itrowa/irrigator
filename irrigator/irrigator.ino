// auto irrigation system
// by Huang He

const int LED = 13;
const int RELAY = 12;
const int DIGIHUMI = 11;
int isIrrigated = 0;
int humiCnt = 0;
int isThirsty = 0;
int timeCnt = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(LED, OUTPUT);
  pinMode(RELAY, OUTPUT);
  pinMode(DIGIHUMI, INPUT);
}

// 闪灯一次
void blinkOnce() {
  digitalWrite(LED, HIGH);
  delay(200);
  digitalWrite(LED, LOW);
}

//闭合继电器以浇水.
void runRelay() {
  int t = 4000;               // 继电器闭合的持续时间
  digitalWrite(RELAY, HIGH);
  delay(t);
  digitalWrite(RELAY, LOW);
}

// 读取传感器并更新全局变量humiCnt的值.当humiCnt积累到一定程度就把
// isThirsty的值翻转.
void updateHumidState() {
  // 读出低电平表示不缺水(传感器灯亮), 读出高电平表示缺水.
  if (digitalRead(DIGIHUMI) == HIGH) { // 应改成high!
    humiCnt++;
  }
  if (humiCnt >= 5) {
    humiCnt = 0;
    isThirsty = 1;
  }
}

void loop() {
  // put your main code here, to run repeatedly:

  // 当积累了一定时间就更新饥渴状态, 并将记录时间的计数器归零
  if (timeCnt >= 10) {
    timeCnt = 0;
    isIrrigated = 0;
  }

  // 更新湿度状态
  updateHumidState();
 
  if (isThirsty == 1 && isIrrigated == 0) {
    blinkOnce();
    runRelay();
    isIrrigated = 1;
    isThirsty = 0;
  }

  
  delay(60000);              // wait for amount of time
  timeCnt++;
}
