# robosys
2017年度ロボットシステム学第一課題 デバイスドライバ

# Description
7セグLEDを使い、0～9、.を表示させる
またtで0から順番点灯させる

# Deomo

# Usage
        $ git clone https://github.com/RyomaAoki/robosys.git
        $ cd robosys
        $ make
        $ sudo insmod myled.ko
        $ sudo chmod 666 /dev/myled0
        
        
        
2を光らせたい場合


        $ echo 2 > /dev/myled0



