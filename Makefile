obj-m:= sw_dev.o

mysw.ko: myled.c
	make -C /usr/src/linux M=`pwd` V=1 modules
clean:
	make -C /usr/src/linux M=`pwd` V=1 clean
