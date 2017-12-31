# robosys
2017年度ロボットシステム学第一課題 デバイスドライバ

# 概要
7セグLEDを使い、入力した0～9、.を表示させる
またtを入力することで0から順番に数字を点灯させる

# デモ動画

https://youtu.be/HEd2FFKmutM

# 使用機材
7セグメントLEDはカソードコモンを使用


# 使用方法
        
        
        $ git clone https://github.com/RyomaAoki/robosys.git
        $ cd robosys
        $ make
        $ sudo insmod myled.ko
        $ sudo chmod 666 /dev/myled0
        
        
例えば2を光らせたい場合

        $ echo 2 > /dev/myled0
順番に数字を光らせる場合


        $ echo r > /dev/myled0


