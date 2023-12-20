#include "web.h"
#include "display.h"

ESP8266WebServer server(80);

void handleRoot()//处理根路径请求 
{
    String htmlContent = "<!DOCTYPE html>"
                    "<html>"
                    "<head>"
                    "<style>"
                    "body { font-family: Arial, sans-serif; background-color: black; color: white; text-align: center; margin: 0; display: flex; flex-direction: column; justify-content: center; align-items: center; height: 100vh; }"
                    ".container { display: flex; justify-content: space-between; align-items: center; padding: 20px; width: 80%; margin: 20px auto; }"
                    ".column { flex: 1; }"
                    "h1 { color: white; font-size: 56px; margin: 0; }"
                    ".icon { color: red; font-size: 96px; margin-bottom: 20px; }"
                    ".data { font-size: 48px; }"
                    "</style>"
                    "</head>"
                    "<body>";

    
    //获取步数、心率数据
    int stepCount = getStep();
    int heartRate = getHeartRate();

    //构建 HTML 内容
    htmlContent += "<h1>NodeMCU Health Data</h1>";
    htmlContent += "<div class='container'>";
    htmlContent += "<div class='column'>";
    htmlContent += "<div class='icon'>&#10084;</div>";
    htmlContent += "<p class='data'>Heart Rate: " + String(heartRate) + " bpm</p>";
    htmlContent += "</div>";
    htmlContent += "<div class='column'>";
    htmlContent += "<div class='icon'>&#128094;</div>";
    htmlContent += "<p class='data'>Step Count: " + String(stepCount) + "</p>";
    htmlContent += "</div>";
    htmlContent += "</div>";
    htmlContent += "</body>"
                   "</html>";
    
    //发送 HTTP 响应
    server.send(200, "text/html", htmlContent);
}



void setupWebServer()//设置 Web 服务器
{
  
  WiFi.begin("nova 8 SE", "wanzhe2003");//连接到 Wi-Fi 网络

  //等待连接成功
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  //打印连接信息和 IP 地址
  Serial.println("Connected to WiFi");
  Serial.println(WiFi.localIP());
  
  //根路径处理
  server.on("/", handleRoot);
  
  //启动服务器
  server.begin();
  Serial.println("HTTP server started");
}

void handleWebServer() 
{
  server.handleClient();
}

boolean wifiConnected()
{
    return WiFi.status() != WL_CONNECTED;
}
