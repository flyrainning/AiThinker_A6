//
//    FILE: AiThinker_A6.h
//  AUTHOR: Flyrainning
// VERSION: 0.1.0
// PURPOSE: Ai-Thinker A6 A7 A20 lib for Arduino
//     URL: http://www.fengpiao.net
//
//


#include <Arduino.h>
#include <SoftwareSerial.h>

#ifndef AiThinker_A6_h
#define AiThinker_A6_h


#define AT_OK 1
#define AT_NO 0
#define AT_TIMEOUT 3
#define AT_RST 2

class AiThinker_A6{

private:
  int PIN_Power;
  int PIN_Reset;
  int PIN_RX;
  int PIN_TX;


  char buffer[100];
  char end_c[2];

  bool debug_on=false;

public:
  SoftwareSerial* BoardSerial=NULL;
  AiThinker_A6();
  ~AiThinker_A6();
  AiThinker_A6(int RX,int TX,int Power=0,int Reset=0);

  //取得SIM卡的ccid
  String CCID();
  //pin设置
  void setup(int RX,int TX,int Power=0,int Reset=0);
  /*
  启动模块
  baudrate 与模块通讯的波特率
  reset 是否调用_start()重置模块设置
  */
  void begin(long baudrate=9600,bool reset=true);
  //启动模块，需设置power pin才有效
  void power_on();
  /*
  重置模块，需设置Reset pin才有效
  重置后需调用bigin重新初始化模块
  */
  void reset();
  /*
  进入串口透传调试模式，可以通过串口直接透传命令到模块
  用于调试，进入后无退出
  */
  void serial_debug();
  //启动调试信息输出，输出到串口
  void debug(bool is_on=true);
  //执行一个命令
  byte cmd(String command, String response1, String response2, int timeOut=500, int repetitions=2);
  byte waitFor(String response1, String response2, unsigned long timeOut);
  String BoardRead();
  //初始化A6模块，准备at环境
  bool _start();
  //初始化GPRS环境，启动GPRS
  bool GPRS_Start();
  //建立一个TCP链接
  bool TCP(String host,String port);
  //建立一个UDP链接
  bool UDP(String host,String port);
  //建立链接(TCP或UDP)以后，发送一段数据
  bool Send(String data);
  //断开链接(TCP或UDP)
  bool Close();
  //一次性发送数据，包括以下动作：链接，发送，关闭
  bool Send_once(String host,String port,String data);
  //单纯向模块发送一条at指令，不等待返回
  void at(String cmd);
  /*
  启动心跳包
  time 心跳发送间隔，单位秒，time=0停止心跳包
  send 心跳包发送内容，以16进制标示，长度不能低于3个字节
  get 设置接受回应包内容，长度不能低于3个字节，16进制格式

  该命令只能在连接服务器成功以后用
  */
  bool heartbeat(String time="30",String send="FF00FF",String get="FF00FF");
  /*
  开启透明传输
  times表示最大尝试发送失败次数 0-5
  delay是重发延时，单位毫秒 0-3000
  max_size是触发发送的包长度 10-100
  wait_timeout是触发发送时间，单位毫秒 1000-8000，从输入最后一个字符算起，延至超过，系统也会自动发送数据

  该命令只能在连接服务器成功以后用
  超过1分钟以上没有数据传输，网关可能自动切断连接，如果透传数据频率太低，应先开启心跳包
  */
  bool TC_Start(String times="3",String delay="300",int max_size=100,int wait_timeout=1000);
  //停止透传
  bool TC_Stop();
  //透传发送数据
  bool TC_Send(String data);
  //透传发送数据，自动换行版本
  //注意：换行只是附加回车后等待发送，并不会直接触发发送，仍然需要等待TC_Start中的触发条件达到后才会发送数据
  bool TC_Sendln(String data);

  //发送手机短信
  bool SendTextMessage(String Number,String msg);
  //拨打电话
  bool Call_Number(String Number);
  //挂断电话
  bool Call_Number_Off();


  //高级函数

  //通过域名查询出IP，域名查询也需要流量，需要多连接的情况，可以先查询出ip，通过ip建立连接
  String NameToIP(String ServerName);
  //通过阿里云的HTTPDNS获取服务器ip
  String AliHTTPDNS(String ServerName);
  //先尝试从阿里云HTTPDNS获取，失败以后使用常规DNS获取
  String NameToIP_Plus(String ServerName);
  /*
  HTTP的get，返回服务器发送的内容
  一次性连接，会断开之前的连接
  */
  String HTTP_GET(String URL);
  /*
  HTTP的post，返回服务器发送的内容
  一次性连接，会断开之前的连接
  */
  String HTTP_POST(String URL,String data);
};











#endif
