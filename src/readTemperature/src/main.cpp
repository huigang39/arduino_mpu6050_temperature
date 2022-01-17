// #define USE_USBCON
#include <Arduino.h>
#include <ros.h>
#include <Wire.h>
#include <MPU6050.h>
#include <std_msgs/Float32.h>

// 实例化 MPU6050 对象
MPU6050 mpu;

// 实例化节点句柄
ros::NodeHandle nh;

// 声明温度数据类型
std_msgs::Float32 temperature_msg;

// 实例化发布者
ros::Publisher temperature_pub("temperature", &temperature_msg);

void setup()
{
    // 初始化 Wire 库
    Wire.begin();

    // 初始化 MPU6050
    mpu.begin();

    // 初始化 ROS
    nh.initNode();
    nh.advertise(temperature_pub);
}

void loop()
{
    // 读取温度
    float temperature = mpu.readTemperature();

    // 将温度数据赋值给消息
    temperature_msg.data = temperature;

    // 发布温度数据
    temperature_pub.publish(&temperature_msg);

    // 每隔 100ms 发布一次
    nh.spinOnce();
    delay(100);
}
