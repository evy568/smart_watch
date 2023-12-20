#include "sensor.h"

MAX30105 particleSensor;

const byte RATE_SIZE = 4; 
byte rates[RATE_SIZE]; 
byte rateSpot = 0;
long lastBeat = 0; //上次心跳发生时间
float beatsPerMinute;
int beatAvg = 0;

void setupHeartRateSensor()//设置心率传感器
{

  Serial.begin(115200);
  Serial.println("Initializing...");
  
  //启动 MAX30105 传感器失败
  if (!particleSensor.begin(Wire, I2C_SPEED_FAST))
  {
    Serial.println("MAX30105 was not found. Please check wiring/power. ");
    while (1);
  }

  Serial.println("Place your index finger on the sensor with steady pressure.");

  //配置传感器默认设置
  particleSensor.setup(); //Configure sensor with default settings
  particleSensor.setPulseAmplitudeRed(0x0A); //Turn Red LED to low to indicate sensor is running
  particleSensor.setPulseAmplitudeGreen(0); //Turn off Green LED
}

void loopHeartRateSensor()//读取心率
{
  
  long irValue = particleSensor.getIR();//获取红外光传感器的值

  //检测到心跳信号
  if (checkForBeat(irValue) == true)
  {

    long delta = millis() - lastBeat; //计算时间间隔
    lastBeat = millis();//更新时间

    beatsPerMinute = 60 / (delta / 1000.0);//计算心率

    if (beatsPerMinute < 255 && beatsPerMinute > 20)//计算出的心率值在合理范围内
    {

      rates[rateSpot++] = (byte)beatsPerMinute; //将心率值存储在 rates 数组中

      rateSpot %= RATE_SIZE; //循环包装

      //计算心率平均值
      beatAvg = 0;
      for (byte x = 0 ; x < RATE_SIZE ; x++)
        beatAvg += rates[x];
      beatAvg /= RATE_SIZE;

    }
  }

  //传感器没有检测到手指
  if (irValue < 50000)
    Serial.print(" No finger?");

  Serial.println();
  
}

int getHeartRate()
{
    return beatAvg;
}
