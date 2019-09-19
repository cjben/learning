## 基于Blink demo的简单跑马灯程序
### 概述  
**在developerkit板子上将Alios Things developer分支下的blink例程跑起来之后，我改变了它的一些代码实现了一个操纵板子上三个LED灯的一个跑马灯程序。**  
### 原Blink  
#### 原blink代码 ->[blink.c](https://github.com/cjben/learning/blob/master/blink.c)  
原代码实现了developerkit板子上的LED1间隔1S的闪烁以及按下板子上M键LED2保持点亮，松开M键后LED2熄灭。这是因为源代码中对于LED2状态翻转的实现是双沿触发，当你按下M键时下降沿触发点亮LED2，松开按键时上升沿触发熄灭LED2。  
* PS.如果快速按M键多次会出现LED2常亮的情况，笔者猜测是由于板子的M键不够灵敏导致。  
#### 具体实现  
![original_blink.gif](https://github.com/cjben/learning/blob/master/images/original_blink.gif?raw=true)  
### 我的direct_blink demo  
#### direct_blink代码 -> [direct_blink.c](https://github.com/cjben/learning/blob/master/direct_blink.c)  
我在例程代码的基础上做了修改，从而实现通电后后LED1-LED3分别延时点亮。  
#### 具体实现  
![direct_blink.gif](https://github.com/cjben/learning/blob/master/images/direct_blink.gif?raw=true)  
### 我的trigger_blink demo  
#### trigger_blink代码 -> [trigger_blink.c](https://github.com/cjben/learning/blob/master/trigger_blink.c)  
在我的direct_blink demo上进一步做了一个改变。实现了在通电后板子无反应，B键被按下后LED1-LED3延时点亮形成一个跑马灯。  
#### 具体实现  
![trigger_blink.gif?raw=true](https://github.com/cjben/learning/blob/master/images/trigger_blink.gif?raw=true)  
* PS.这个代码存在问题。当跑马灯工作一定次数后会出现LED1-LED3的点亮时间不再与先前的一致，会出现下图情况。**目前还不知道原因**  
![problem_trigger_blink.gif](https://github.com/cjben/learning/blob/master/images/problem_trigger_blink.gif?raw=true)  
