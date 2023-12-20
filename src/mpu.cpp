#include "mpu.h"
Adafruit_MPU6050 mpu;


int step_cnt=0;
int lasttime = 0;
int thistime=260;
float xx=0;
float yy=0;
float zz=0;


void setupMPU()//启动陀螺仪
{
    Serial.println("find MPU6050 chip");
    
    //初始化失败
    if (!mpu.begin())
    {
        Serial.println("Failed to find MPU6050 chip");
        while (1)
        {
            delay(10);
        }
    }  

    //配置 MPU6050 参数
    mpu.setAccelerometerRange(MPU6050_RANGE_16_G);
    mpu.setGyroRange(MPU6050_RANGE_250_DEG);
    mpu.setFilterBandwidth(MPU6050_BAND_21_HZ); 

    //初始化计步
    step_cnt=0;

    delay(100);
}


void stepCalculate()//计步
{
    sensors_event_t a, g, temp;

    //获取加速度计数据
    mpu.getEvent(&a, &g, &temp);
    xx = a.acceleration.x;
    yy = a.acceleration.y;
    zz = a.acceleration.z;
    
    //计算合成加速度大小
    float accelerationMagnitude = sqrt(xx * xx + yy * yy + zz * zz);
    
    //检测到一个步伐
    if (accelerationMagnitude > 10 && (thistime - lasttime > 250)) 
    {
        lasttime = thistime; //更新时间
        step_cnt = step_cnt + 1; //更新步数
    }
  
    thistime = millis();//更新时间
}

int getStep()
{
    return step_cnt;
}
