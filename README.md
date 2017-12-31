# robosys
2017年度ロボットシステム学第一課題 デバイスドライバ

# Description
7セグLEDを使い、0～9、.を表示させる
またtを入力することで0から順番に数字を点灯させる

# Deomo

https://youtu.be/HEd2FFKmutM

# Usage
        $ git clone https://github.com/RyomaAoki/robosys.git
        $ cd robosys
        $ make
        $ sudo insmod myled.ko
        $ sudo chmod 666 /dev/myled0
        
        
        
2を光らせたい場合


        $ echo 2 > /dev/myled0



