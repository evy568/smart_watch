#include <Arduino.h>
#include "main.h"


void setup()
{
  
  Serial.begin(115200);
  Serial.println("Starting...");

  setupWebServer();//连网
  initDispaly();//初始化OLED屏幕
  delay(100);

  setupMPU();//设置MPU6050
  setupHeartRateSensor();//设置心率传感器

  while (wifiConnected())//连网
  ;
  initUI(); 
}

void loop()
{
  
  stepCalculate();//计步

  loopHeartRateSensor();//测心率
  
  handleWebServer();//处理网页

  //显示步数和心率数据
  setStep(getStep());
  setHeartRate(getHeartRate());
  drawBpm();
  drawSteps();

}
