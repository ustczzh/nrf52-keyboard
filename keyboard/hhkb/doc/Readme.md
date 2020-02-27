# nrf52-hhkb

## 设计思路

使用Nordic nRF52840（ARM 32-bit Cortex-M4 core @64MHz）单芯片，同时支持BLE 5.0和USB。

测试板：DFRobot Xenon。带锂电充放电。

## 硬件架构

nRF52840
nRF52840 + MAX3421e

## 软件框架

nRF5 SDK v16.0.0 + tmk

## 工作模式

1. 上电后优先初始化keyboard。
2. 总是初始化ble。