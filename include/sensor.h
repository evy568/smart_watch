#include "display.h"
#include <Wire.h>
#include "MAX30105.h"
#include "heartRate.h"

void setupHeartRateSensor();

void loopHeartRateSensor();

int getHeartRate();
