# AiThinker_A6
An ESP8266/Arduino library for communicating with the Ai-Thinker A6 ( A7 ) GSM module

Arduino的GSM手机模块的库，适用于Ai-Thinker A6 A7 A20系列芯片，理论上也支持其他使用AT指令的设备。

提供短信，通话，GPRS联网（TCP UDP TCP数据透传）等功能。

```
#include "AiThinker_A6.h"

#define GPRS_Serial_RX 3
#define GPRS_Serial_TX 2
#define GPRS_Power_pin 4
#define GPRS_Reset_pin 5

AiThinker_A6 Board(GPRS_Serial_RX, GPRS_Serial_TX,GPRS_Power_pin,GPRS_Reset_pin); // RX, TX

void setup() {
  Serial.begin(115200);

  //Board.debug();
  Board.begin(9600);
  //启动网络
  Board.GPRS_Start();
  
  //1、发送一次数据:
  Board.Send_once("www.fengpiao.net","9001","I'm Data");
  
  //2、发送多次数据:
  //建立连接
  Board.TCP("www.fengpiao.net","9001");
  for (size_t i = 0; i < 10; i++) {
    Board.Send("I'm Data");
    delay(2000);
  }
  //关闭连接
  Board.Close();
  
  
  //3、使用透传模式:
  //建立连接
  Board.TCP("www.fengpiao.net","9001");
  //启用心跳包，每60秒一次
  Board.heartbeat("60");
  //开启透传
  Board.TC_Start();

  for (size_t i = 0; i < 10; i++) {
    Board.TC_Send("I'm Data");
    delay(2000);
  }
  //退出透传模式
  Board.TC_Stop();
  
  
  //4、发送UDP数据
  Board.UDP("www.fengpiao.net","9001");
  for (size_t i = 0; i < 10; i++) {
    Board.Send("I'm Data");
    delay(2000);
  }
  //关闭
  Board.Close();
  
}


```
