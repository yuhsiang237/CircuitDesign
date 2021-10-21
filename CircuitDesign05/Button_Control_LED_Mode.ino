#define BUTTON_PIN 7
#define LED_PIN 8
#define DATA_RATE 115200


// LED控制
unsigned long ledTime = millis();
int ledMode = 2; // LED閃爍模式 (閃爍間隔 模式1:0.1秒；模式2:1秒)
bool ledBlinkFlag = false; // LED閃爍
// 按鈕控制
unsigned long buttonTime = millis();
bool isButtonPressed = false; // 按鈕按壓


void setup() 
{
  Serial.begin(DATA_RATE); // 設定序列埠監控
  pinMode(LED_PIN, OUTPUT);   // 初始化LED PIN腳為輸出
  pinMode(BUTTON_PIN, INPUT); // 初始化按鈕 PIN腳為輸入
}

void loop() 
{
  blinkLedMode(ledMode); // LED閃爍模式
  scanMode(); // 掃描套用模式
}

// 掃描套用模式
void scanMode()
{
  int buttonState = digitalRead(BUTTON_PIN);
  if(buttonState == LOW) // 按下按鈕
  {
    if(isButtonPressed == false) 
    {
      buttonTime = millis(); // 紀錄按下時間
      isButtonPressed = true;
    }
  }
  else if(buttonState == HIGH) // 放開按鈕
  { 
    if(isButtonPressed)
    {
      unsigned long currentTime = millis();
      unsigned long duration = currentTime - buttonTime; // 按壓時間
      
      Serial.print("按壓時間:");
      Serial.print(duration);
      Serial.print("\n");
      
      // 設定LED模式
      if(duration <= 3000)  
      {
        ledMode = 1;
      }
      else
      {
        ledMode = 2;
      }
      isButtonPressed = false;
    }
  }
}

// LED 閃爍模式
void blinkLedMode(int mode)
{
  if(mode == 1)
  {
    blinkLed(100); // 0.1秒閃一下
  }
  if(mode == 2)
  {
    blinkLed(1000); // 1秒閃一下
  }
}

// LED閃爍
void blinkLed(int millisecond)
{
  unsigned long currentTime = millis();
  unsigned long interval = currentTime - ledTime; // 間隔時間
  if(interval > millisecond)
  {
    ledTime = currentTime; // 更新LED時間
    if(ledBlinkFlag)
    {
      digitalWrite(LED_PIN, HIGH);
      ledBlinkFlag = false; 
    }
    else
    {
      digitalWrite(LED_PIN, LOW); 
      ledBlinkFlag = true; 
    }
  }
}
