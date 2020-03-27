@echo off
chcp 65001
mode con cols=80 lines=20
title=设置窗口标题
::目的：交换两个变量的值，但是不使用临时变量
::Code by JM 2007-1-24 [email=CMD@XP]CMD@XP[/email]
::出处：http://www.cn-dos.net/forum/viewthread.php?tid=27078
:loop
set var1=abc
set var2=123
echo 交换前： var1=%var1% var2=%var2%
echo=
set var1=%var2%& set var2=%var1%
echo=
echo 交换后： var1=%var1% var2=%var2%

pause
goto:loop