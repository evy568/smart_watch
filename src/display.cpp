#include "display.h"

SSD1306Wire display(0x3c, SDA, SCL, GEOMETRY_128_64);
OLEDDisplayUi ui(&display);

int displayBPM = 0;
int displayStep = 0;

void setStep(int step)
{
    displayStep=step;
}

void setHeartRate(int BPM)
{
    displayBPM = BPM; 
}
void drawBpm() //显示 BPM
{
    //黑色矩形填充，覆盖上一次显示数据
    display.setColor(BLACK);
    display.fillRect(18, 33, 110, 32);
    
    //显示BMP
    display.setColor(WHITE);
    display.setFont(ArialMT_Plain_16);
    display.setTextAlignment(TEXT_ALIGN_CENTER);
    display.drawString(64, 40, "BMP : " + String(displayBPM));

    //刷新
    display.display();
}
void drawSteps()   //显示 steps
{
    //黑色矩形填充，覆盖上一次显示数据
    display.setColor(BLACK);
    display.fillRect(27, 14, 100, 18);
    
    //显示步数
    display.setColor(WHITE);
    display.setFont(ArialMT_Plain_16);
    display.setTextAlignment(TEXT_ALIGN_CENTER);
    display.drawString(64, 13, "Steps: " + String(displayStep));

    //刷新
    display.display();
}

void initDispaly()   //显示 "booting"
{
    display.init();   
    display.flipScreenVertically();
    display.setFont(ArialMT_Plain_16);
    display.setTextAlignment(TEXT_ALIGN_CENTER);
    display.drawString(64, 32, "Booting...");
    display.display();
}

void initUI()
{
    ui.setTargetFPS(60);
    ui.disableAutoTransition();
    ui.disableAllIndicators();
    ui.setFrameAnimation(SLIDE_LEFT);
    ui.init();
    display.flipScreenVertically();
}

