/*
    Copyright (C) 2017 Ryoma Aoki
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <asm/uaccess.h>
#include <linux/io.h>
#include <linux/delay.h>

MODULE_AUTHOR("Ryoma Aoki");
MODULE_DESCRIPTION("driver for7 seg  LED control");
MODULE_LICENSE("GPL");
MODULE_VERSION("0.1");

static dev_t dev;
static struct cdev cdv;
static struct class *cls = NULL;

static volatile u32 *gpio_base = NULL;
static int gpio_pin[8] = {17,4,23,24,25,27,22,18};

static ssize_t led_write(struct file* filp, const char* buf, size_t count, loff_t* pos)
#define TIME 1000
{
    char c;
    if(copy_from_user(&c,buf,sizeof(char)))
        return -EFAULT;

    if(c == '0'){
        gpio_base[7] = 1 << gpio_pin[0];//a
        gpio_base[7] = 1 << gpio_pin[1];//b
        gpio_base[7] = 1 << gpio_pin[2];//c
        gpio_base[7] = 1 << gpio_pin[3];//d
        gpio_base[7] = 1 << gpio_pin[4];//e
        gpio_base[7] = 1 << gpio_pin[5];//f
        gpio_base[10] = 1 << gpio_pin[6];//g
        gpio_base[10] = 1 << gpio_pin[7];//D.P
    }else if(c == '1'){
        gpio_base[10] = 1 << gpio_pin[0];//a
        gpio_base[7] = 1 << gpio_pin[1];//b
        gpio_base[7] = 1 << gpio_pin[2];//c
        gpio_base[10] = 1 << gpio_pin[3];//d
        gpio_base[10] = 1 << gpio_pin[4];//e
        gpio_base[10] = 1 << gpio_pin[5];//f
        gpio_base[10] = 1 << gpio_pin[6];//g
        gpio_base[10] = 1 << gpio_pin[7];//D.P
    }else if(c == '2'){
        gpio_base[7] = 1 << gpio_pin[0];//a
        gpio_base[7] = 1 << gpio_pin[1];//b
        gpio_base[10] = 1 << gpio_pin[2];//c
        gpio_base[7] = 1 << gpio_pin[3];//d
        gpio_base[7] = 1 << gpio_pin[4];//e
        gpio_base[10] = 1 << gpio_pin[5];//f
        gpio_base[7] = 1 << gpio_pin[6];//g
        gpio_base[10] = 1 << gpio_pin[7];//D.P
    }else if(c == '3'){
        gpio_base[7] = 1 << gpio_pin[0];//a
        gpio_base[7] = 1 << gpio_pin[1];//b
        gpio_base[7] = 1 << gpio_pin[2];//c
        gpio_base[7] = 1 << gpio_pin[3];//d
        gpio_base[10] = 1 << gpio_pin[4];//e
        gpio_base[10] = 1 << gpio_pin[5];//f
        gpio_base[7] = 1 << gpio_pin[6];//g
        gpio_base[10] = 1 << gpio_pin[7];//D.P
    }else if(c == '4'){
        gpio_base[10] = 1 << gpio_pin[0];//a
        gpio_base[7] = 1 << gpio_pin[1];//b
        gpio_base[7] = 1 << gpio_pin[2];//c
        gpio_base[10] = 1 << gpio_pin[3];//d
        gpio_base[10] = 1 << gpio_pin[4];//e
        gpio_base[7] = 1 << gpio_pin[5];//f
        gpio_base[7] = 1 << gpio_pin[6];//g
        gpio_base[10] = 1 << gpio_pin[7];//D.P
    }else if(c == '5'){
        gpio_base[7] = 1 << gpio_pin[0];//a
        gpio_base[10] = 1 << gpio_pin[1];//b
        gpio_base[7] = 1 << gpio_pin[2];//c
        gpio_base[7] = 1 << gpio_pin[3];//d
        gpio_base[10] = 1 << gpio_pin[4];//e
        gpio_base[7] = 1 << gpio_pin[5];//f
        gpio_base[7] = 1 << gpio_pin[6];//g
        gpio_base[10] = 1 << gpio_pin[7];//D.P
    }else if(c == '6'){
        gpio_base[7] = 1 << gpio_pin[0];//a
        gpio_base[10] = 1 << gpio_pin[1];//b
        gpio_base[7] = 1 << gpio_pin[2];//c
       gpio_base[7] = 1 << gpio_pin[3];//d
        gpio_base[7] = 1 << gpio_pin[4];//e
        gpio_base[7] = 1 << gpio_pin[5];//f
        gpio_base[7] = 1 << gpio_pin[6];//g
        gpio_base[10] = 1 << gpio_pin[7];//D.P
    }else if(c == '7'){
        gpio_base[7] = 1 << gpio_pin[0];//a
        gpio_base[7] = 1 << gpio_pin[1];//b
        gpio_base[7] = 1 << gpio_pin[2];//c
        gpio_base[10] = 1 << gpio_pin[3];//d
        gpio_base[10] = 1 << gpio_pin[4];//e
        gpio_base[7] = 1 << gpio_pin[5];//f
        gpio_base[10] = 1 << gpio_pin[6];//g
        gpio_base[10] = 1 << gpio_pin[7];//D.P
    }else if(c == '8'){
        gpio_base[7] = 1 << gpio_pin[0];//a
        gpio_base[7] = 1 << gpio_pin[1];//b
        gpio_base[7] = 1 << gpio_pin[2];//c
        gpio_base[7] = 1 << gpio_pin[3];//d
        gpio_base[7] = 1 << gpio_pin[4];//e
        gpio_base[7] = 1 << gpio_pin[5];//f
        gpio_base[7] = 1 << gpio_pin[6];//g
        gpio_base[10] = 1 << gpio_pin[7];//D.P
    }else if(c == '9'){
        gpio_base[7] = 1 << gpio_pin[0];//a
        gpio_base[7] = 1 << gpio_pin[1];//b
        gpio_base[7] = 1 << gpio_pin[2];//c
        gpio_base[7] = 1 << gpio_pin[3];//d
        gpio_base[10] = 1 << gpio_pin[4];//e
        gpio_base[7] = 1 << gpio_pin[5];//f
        gpio_base[7] = 1 << gpio_pin[6];//g
        gpio_base[10] = 1 << gpio_pin[7];//D.P
    }else if(c == '.'){
        gpio_base[10] = 1 << gpio_pin[0];//a
        gpio_base[10] = 1 << gpio_pin[1];//b
        gpio_base[10] = 1 << gpio_pin[2];//c
        gpio_base[10] = 1 << gpio_pin[3];//d
        gpio_base[10] = 1 << gpio_pin[4];//e
        gpio_base[10] = 1 << gpio_pin[5];//f
        gpio_base[10] = 1 << gpio_pin[6];//g
        gpio_base[7] = 1 << gpio_pin[7];//D.P
    }else if(c == '/'){
        gpio_base[10] = 1 << gpio_pin[0];//a
        gpio_base[10] = 1 << gpio_pin[1];//b
        gpio_base[10] = 1 << gpio_pin[2];//c
        gpio_base[10] = 1 << gpio_pin[3];//d
        gpio_base[10] = 1 << gpio_pin[4];//e
        gpio_base[10] = 1 << gpio_pin[5];//f
        gpio_base[10] = 1 << gpio_pin[6];//g
        gpio_base[10] = 1 << gpio_pin[7];//D.P
    }else if(c == 't'){
        int i;
        for(i=0;i<10;i++){

            gpio_base[7] = 1 << gpio_pin[0];//a
            gpio_base[7] = 1 << gpio_pin[1];//b
            gpio_base[7] = 1 << gpio_pin[2];//c
            gpio_base[7] = 1 << gpio_pin[3];//d
            gpio_base[7] = 1 << gpio_pin[4];//e
            gpio_base[7] = 1 << gpio_pin[5];//f
            gpio_base[10] = 1 << gpio_pin[6];//g
            gpio_base[10] = 1 << gpio_pin[7];//D.P
            msleep(TIME);

            gpio_base[10] = 1 << gpio_pin[0];//a
            gpio_base[7] = 1 << gpio_pin[1];//b
            gpio_base[7] = 1 << gpio_pin[2];//c
            gpio_base[10] = 1 << gpio_pin[3];//d
            gpio_base[10] = 1 << gpio_pin[4];//e
            gpio_base[10] = 1 << gpio_pin[5];//f
            gpio_base[10] = 1 << gpio_pin[6];//g
            gpio_base[10] = 1 << gpio_pin[7];//D.P
            msleep(TIME);

            gpio_base[7] = 1 << gpio_pin[0];//a
            gpio_base[7] = 1 << gpio_pin[1];//b
            gpio_base[10] = 1 << gpio_pin[2];//c
            gpio_base[7] = 1 << gpio_pin[3];//d
            gpio_base[7] = 1 << gpio_pin[4];//e
            gpio_base[10] = 1 << gpio_pin[5];//f
            gpio_base[7] = 1 << gpio_pin[6];//g
            gpio_base[10] = 1 << gpio_pin[7];//D.P
            msleep(TIME);
            gpio_base[7] = 1 << gpio_pin[0];//a
            gpio_base[7] = 1 << gpio_pin[1];//b
            gpio_base[7] = 1 << gpio_pin[2];//c
            gpio_base[7] = 1 << gpio_pin[3];//d
            gpio_base[10] = 1 << gpio_pin[4];//e
            gpio_base[10] = 1 << gpio_pin[5];//f
            gpio_base[7] = 1 << gpio_pin[6];//g
            gpio_base[10] = 1 << gpio_pin[7];//D.P
            msleep(TIME);

            gpio_base[10] = 1 << gpio_pin[0];//a
            gpio_base[7] = 1 << gpio_pin[1];//b
            gpio_base[7] = 1 << gpio_pin[2];//c
            gpio_base[10] = 1 << gpio_pin[3];//d
            gpio_base[10] = 1 << gpio_pin[4];//e
            gpio_base[7] = 1 << gpio_pin[5];//f
            gpio_base[7] = 1 << gpio_pin[6];//g
            gpio_base[10] = 1 << gpio_pin[7];//D.P
            msleep(TIME);

            gpio_base[7] = 1 << gpio_pin[0];//a
            gpio_base[10] = 1 << gpio_pin[1];//b
            gpio_base[7] = 1 << gpio_pin[2];//c
            gpio_base[7] = 1 << gpio_pin[3];//d
            gpio_base[10] = 1 << gpio_pin[4];//e
            gpio_base[7] = 1 << gpio_pin[5];//f
            gpio_base[7] = 1 << gpio_pin[6];//g
            gpio_base[10] = 1 << gpio_pin[7];//D.P
            msleep(TIME);


            gpio_base[7] = 1 << gpio_pin[0];//a
            gpio_base[10] = 1 << gpio_pin[1];//b
            gpio_base[7] = 1 << gpio_pin[2];//c
            gpio_base[7] = 1 << gpio_pin[3];//d
            gpio_base[7] = 1 << gpio_pin[4];//e
            gpio_base[7] = 1 << gpio_pin[5];//f
            gpio_base[7] = 1 << gpio_pin[6];//g
            gpio_base[10] = 1 << gpio_pin[7];//D.P
            msleep(TIME);

            gpio_base[7] = 1 << gpio_pin[0];//a
            gpio_base[7] = 1 << gpio_pin[1];//b
            gpio_base[7] = 1 << gpio_pin[2];//c
            gpio_base[10] = 1 << gpio_pin[3];//d
            gpio_base[10] = 1 << gpio_pin[4];//e
            gpio_base[7] = 1 << gpio_pin[5];//f
            gpio_base[10] = 1 << gpio_pin[6];//g
            gpio_base[10] = 1 << gpio_pin[7];//D.P
            msleep(TIME);

            gpio_base[7] = 1 << gpio_pin[0];//a
            gpio_base[7] = 1 << gpio_pin[1];//b
            gpio_base[7] = 1 << gpio_pin[2];//c
            gpio_base[7] = 1 << gpio_pin[3];//d
            gpio_base[7] = 1 << gpio_pin[4];//e
            gpio_base[7] = 1 << gpio_pin[5];//f
            gpio_base[7] = 1 << gpio_pin[6];//g
            gpio_base[10] = 1 << gpio_pin[7];//D.P
            msleep(TIME);

            gpio_base[7] = 1 << gpio_pin[0];//a
            gpio_base[7] = 1 << gpio_pin[1];//b
            gpio_base[7] = 1 << gpio_pin[2];//c
            gpio_base[7] = 1 << gpio_pin[3];//d
            gpio_base[10] = 1 << gpio_pin[4];//e
            gpio_base[7] = 1 << gpio_pin[5];//f
            gpio_base[7] = 1 << gpio_pin[6];//g
            gpio_base[10] = 1 << gpio_pin[7];//D.P
            msleep(TIME);
        }

    }

        return 1;
}

static struct file_operations led_fops = {
    .owner = THIS_MODULE,
    .write = led_write
};

static int __init init_mod(void)
{
    int retval;
    int i;
    
    gpio_base = ioremap_nocache(0x3f200000, 0xA0);

    for(i = 0;i < 8;i++){
    const u32 led = gpio_pin[i];
    const u32 index = led/10;//GPFSEL2
    const u32 shift = (led%10)*3;//15bit
    const u32 mask = ~(0x7 << shift);//11111111111111000111111111111111
    gpio_base[index] = (gpio_base[index] & mask) | (0x1 << shift);//001: output flag
    //11111111111111001111111111111111
    }
    retval =  alloc_chrdev_region(&dev, 0, 1, "myled");
    if(retval < 0){
        printk(KERN_ERR "alloc_chrdev_region failed.\n");
        return retval;
    }
    printk(KERN_INFO "%s is loaded. major:%d\n",__FILE__,MAJOR(dev));

    cdev_init(&cdv, &led_fops);
    cdv.owner = THIS_MODULE;
    retval = cdev_add(&cdv, dev, 1);
    if(retval < 0){
        printk(KERN_ERR "cdev_add failed. major:%d, minor:%d",MAJOR(dev),MINOR(dev));
        return retval;
    }

    cls = class_create(THIS_MODULE,"myled");
    if(IS_ERR(cls)){
        printk(KERN_ERR "class_create failed.");
        return PTR_ERR(cls);
    }
    device_create(cls, NULL, dev, NULL, "myled%d",MINOR(dev));

    return 0;
}

static void __exit cleanup_mod(void)
{
    cdev_del(&cdv);
    device_destroy(cls, dev);
    class_destroy(cls);
    unregister_chrdev_region(dev, 1);
    printk(KERN_INFO "%s is unloaded. major:%d\n",__FILE__,MAJOR(dev));
    iounmap(gpio_base);
}

module_init(init_mod);
module_exit(cleanup_mod);
