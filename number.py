# Template Matching Example - Normalized Cross Correlation (NCC)
#
# This example shows off how to use the NCC feature of your OpenMV Cam to match
# image patches to parts of an image... expect for extremely controlled enviorments
# NCC is not all to useful.
#
# WARNING: NCC supports needs to be reworked! As of right now this feature needs
# a lot of work to be made into somethin useful. This script will reamin to show
# that the functionality exists, but, in its current state is inadequate.

import time, sensor, image
from image import SEARCH_EX, SEARCH_DS
from pyb import LED
from pyb import UART

uart = UART(3, 115200)
uart.init(115200, bits=8, parity=None, stop=1)

red_led   = LED(1)
green_led = LED(2)
blue_led  = LED(3)
ir_led    = LED(4)
x = 1 # 赋值整型变量
y = 1
Give_number = 1
turn = 0
# Reset sensor
sensor.reset()

# Set sensor settings
sensor.set_contrast(1)
sensor.set_gainceiling(16)
# Max resolution for template matching with SEARCH_EX is QQVGA
sensor.set_framesize(sensor.QQVGA)
# You can set windowing to reduce the search image.
#sensor.set_windowing(((640-80)//2, (480-60)//2, 80, 60))
sensor.set_pixformat(sensor.GRAYSCALE)

# Load template.
# Template should be a small (eg. 32x32 pixels) grayscale image.
template1 = image.Image("/1.pgm")
template2 = image.Image("/2.pgm")
template_3 = image.Image("/3.pgm")
template_4 = image.Image("/4.pgm")
template_5 = image.Image("/5.pgm")
template_6 = image.Image("/6.pgm")
template_7 = image.Image("/7.pgm")
template_8 = image.Image("/8.pgm")

template3 = ["/3/3_0.pgm","/3/3_1.pgm","/3/3_2.pgm","/3/3_5.pgm","/3/3_6.pgm","/3/3_7.pgm","/3/3_8.pgm","/3/3_9.pgm","/3/3_10.pgm","/3/3_11.pgm","/3/3_12.pgm","/3/3_13.pgm"]
template4 = ["/4/4_0.pgm","/4/4_1.pgm","/4/4_2.pgm","/4/4_3.pgm","/4/4_4.pgm","/4/4_5.pgm","/4/4_6.pgm","/4/4_7.pgm","/4/4_8.pgm"]
template5 = ["/5/5_0.pgm","/5/5_1.pgm","/5/5_2.pgm","/5/5_3.pgm","/5/5_4.pgm","/5/5_5.pgm","/5/5_6.pgm","/5/5_7.pgm","/5/5_8.pgm"]
template6 = ["/6/6_0.pgm","/6/6_1.pgm","/6/6_2.pgm","/6/6_3.pgm","/6/6_4.pgm","/6/6_5.pgm","/6/6_6.pgm","/6/6_7.pgm","/6/6_8.pgm"]
template7 = ["/7/7_0.pgm","/7/7_1.pgm","/7/7_2.pgm","/7/7_3.pgm","/7/7_4.pgm","/7/7_5.pgm","/7/7_6.pgm","/7/7_7.pgm","/7/7_8.pgm"]
template8 = ["/8/8_0.pgm","/8/8_1.pgm","/8/8_2.pgm","/8/8_3.pgm","/8/8_4.pgm","/8/8_5.pgm","/8/8_6.pgm","/8/8_7.pgm","/8/8_8.pgm"]


clock = time.clock()
def sending_data(cx,cy,cw,ch):
    global uart;
    #frame=[0x2C,18,cx%0xff,int(cx/0xff),cy%0xff,int(cy/0xff),0x5B];
    #data = bytearray(frame)
    data = ustruct.pack("<bbhhhhb",      #格式为俩个字符俩个短整型(2字节)
                   0x2C,                      #帧头1
                   0x12,                      #帧头2
                   int(number), # up sample by 4   #数据1
                   int(number), # up sample by 4    #数据2
                   int(number), # up sample by 4    #数据1
                   int(number), # up sample by 4    #数据2
                   0x5B)
    uart.write(data);   #必须要传入一个字节数组

# Run template matching
while (True):
    clock.tick()

    # find_template(template, threshold, [roi, step, search])
    # ROI: The region of interest tuple (x, y, w, h).
    # Step: The loop step used (y+=step, x+=step) use a bigger step to make it faster.
    # Search is either image.SEARCH_EX for exhaustive search or image.SEARCH_DS for diamond search
    #
    # Note1: ROI has to be smaller than the image and bigger than the template.
    # Note2: In diamond search, step and ROI are both ignored.
    #find_template(template, threshold, [roi, step, search]),threshold中
    #的0.7是相似度阈值,roi是进行匹配的区域（左上顶点为（10，0），长80宽60的矩形），
    #注意roi的大小要比模板图片大，比frambuffer小。
    #把匹配到的图像标记出来
      #  if r:
      #      print(3) #打印模板名字
      #      print(r[1])
      #      uart.write("number 3!\r")
    while (Give_number == 1):
        img = sensor.snapshot()
        b = img.find_template(template2, 0.70, step=4, search=SEARCH_EX)
        if b:
            img.draw_rectangle(b)
            number = 2
            FH = bytearray([0x2C,0x12,number,0,number,number,0x5B])
            uart.write(FH)
            print(FH)
            Give_number = 0

        a = img.find_template(template1, 0.70, step=4, search=SEARCH_EX)
        if a:
            img.draw_rectangle(a)
            number = 1
            FH = bytearray([0x2C,0x12,number,0,number,number,0x5B])
            uart.write(FH)
            print(FH)
            Give_number = 0

        c = img.find_template(template_3, 0.70, step=4, search=SEARCH_EX)
        if c:
            img.draw_rectangle(c)
            number = 3
            FH = bytearray([0x2C,0x12,number,0,number,number,0x5B])
            uart.write(FH)
            print(FH)
            Give_number = 0

        d = img.find_template(template_4, 0.70, step=4, search=SEARCH_EX)
        if d:
            img.draw_rectangle(d)
            number = 4
            FH = bytearray([0x2C,0x12,number,0,number,number,0x5B])
            uart.write(FH)
            print(FH)
            Give_number = 0

        f = img.find_template(template_5, 0.70, step=4, search=SEARCH_EX)
        if f:
            img.draw_rectangle(f)
            number = 5
            FH = bytearray([0x2C,0x12,number,0,number,number,0x5B])
            uart.write(FH)
            print(FH)
            Give_number = 0

        g = img.find_template(template_6, 0.70, step=4, search=SEARCH_EX)
        if g:
            img.draw_rectangle(g)
            number = 6
            FH = bytearray([0x2C,0x12,number,0,number,number,0x5B])
            uart.write(FH)
            print(FH)
            Give_number = 0

        h = img.find_template(template_7, 0.70, step=4, search=SEARCH_EX)
        if h:
            img.draw_rectangle(h)
            number = 7
            FH = bytearray([0x2C,0x12,number,0,number,number,0x5B])
            uart.write(FH)
            print(FH)
            Give_number = 0

        i = img.find_template(template_8, 0.70, step=4, search=SEARCH_EX)
        if i:
            img.draw_rectangle(i)
            number = 8
            FH = bytearray([0x2C,0x12,number,0,number,number,0x5B])
            uart.write(FH)
            print(FH)
            Give_number = 0

    while (number == 3):
        for t in template3:
            img = sensor.snapshot()
            n_3 = image.Image(t)
            #对每个模板遍历进行模板匹配
            number_3 = img.find_template(n_3, 0.6, step=4, search=SEARCH_EX)

        if number_3:
            img.draw_rectangle(number_3)
            x = number_3[0] + number_3[2]   #相对中心点x坐标
            print(x)
            if (x < 80):
                turn = 1
            if (x > 80):
                turn = 2
            FH = bytearray([0x2C,0x12,3,turn,number,number,0x5B])
            uart.write(FH)
            print(FH)

    while (number == 4):
        for t in template4:
            img = sensor.snapshot()
            n_4 = image.Image(t)
            #对每个模板遍历进行模板匹配
            number_4 = img.find_template(n_4, 0.6, step=4, search=SEARCH_EX)

        if number_4:
            img.draw_rectangle(number_4)
            x = number_4[0] + number_4[2]   #相对中心点x坐标
            print(x)
            if (x < 80):
                turn = 1
            if (x > 80):
                turn = 2
            FH = bytearray([0x2C,0x12,4,turn,number,number,0x5B])
            uart.write(FH)
            print(FH)

    while (number == 5):
        for t in template5:
            img = sensor.snapshot()
            n_5 = image.Image(t)
            #对每个模板遍历进行模板匹配
            number_5 = img.find_template(n_5, 0.6, step=4, search=SEARCH_EX)

        if number_5:
            img.draw_rectangle(number_5)
            x = number_5[0] + number_5[2]   #相对中心点x坐标
            print(x)
            if (x < 80):
                turn = 1
            if (x > 80):
                turn = 2
            FH = bytearray([0x2C,0x12,5,turn,number,number,0x5B])
            uart.write(FH)
            print(FH)


    while (number == 6):
        for t in template6:
            img = sensor.snapshot()
            n_6 = image.Image(t)
            #对每个模板遍历进行模板匹配
            number_6 = img.find_template(n_6, 0.6, step=4, search=SEARCH_EX)

        if number_6:
            img.draw_rectangle(number_6)
            x = number_6[0] + number_6[2]   #相对中心点x坐标
            print(x)
            if (x < 80):
                turn = 1
            if (x > 80):
                turn = 2
            FH = bytearray([0x2C,0x12,6,turn,number,number,0x5B])
            uart.write(FH)
            print(FH)

    while (number == 7):
        for t in template7:
            img = sensor.snapshot()
            n_7 = image.Image(t)
            #对每个模板遍历进行模板匹配
            number_7 = img.find_template(n_7, 0.6, step=4, search=SEARCH_EX)

        if number_7:
            img.draw_rectangle(number_7)
            x = number_7[0] + number_7[2]   #相对中心点x坐标
            print(x)
            if (x < 80):
                turn = 1
            if (x >80):
                turn = 2
            FH = bytearray([0x2C,0x12,7,turn,number,number,0x5B])
            uart.write(FH)
            print(FH)

    while (number == 8):
        for t in template8:
            img = sensor.snapshot()
            n_8 = image.Image(t)
            #对每个模板遍历进行模板匹配
            number_8 = img.find_template(n_8, 0.6, step=4, search=SEARCH_EX)

        if number_8:
            img.draw_rectangle(number_8)
            x = number_8[0] + number_8[2]   #相对中心点x坐标
            print(x)
            if (x < 80):
                turn = 1
            if (x > 80):
                turn = 2
            FH = bytearray([0x2C,0x12,8,turn,number,number,0x5B])
            uart.write(FH)
            print(FH)
