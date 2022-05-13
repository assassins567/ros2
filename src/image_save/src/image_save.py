#!/usr/bin/env python
# -*- coding: utf-8 -*-

import cv2
import rclpy
from rclpy.node import Node
#from geometry_msgs.msg import Twist

import  select, termios, tty
from sensor_msgs.msg import Image
from cv_bridge import CvBridge, CvBridgeError

import cv2
import numpy as np
bridge = CvBridge()
img=[]
#def vels(speed,turn):
#    return "currently:\tspeed %s\tturn %s " % (speed,turn)

class Image_Save(Node):

    def __init__(self):
        super().__init__("image_save")
    self.self = self.creat_subscription(
        Image, 
        '/cam0',
        self.image_callback, 
        queue_size=10)
    self.subcription
    
    def image_callback(self, msg):
        print("Received an image!")
            # Convert your ROS Image message to OpenCV
        try:
            cv_image = self.bridge.imgmsg_to_cv2(msg,"bgr8")
        except CvBridgeError as e:
            print e
        timestr = "%.0f" %  msg.header.stamp.to_sec()
        path = "/media/wy/7089b057-a6d2-459b-a158-eae994447d5b/MA/data/Image_que/cam0"
        #%.6f表示小数点后带有6位，可根据精确度需要修改；
        image_name = path + timestr + ".jpg" #图像命名：时间戳.jpg
        cv2.imwrite(image_name, cv_image)  #保存；


def main(args=None):
    rclpy.init(args=args)

    image_save = Image_Save()
    
    rclpy.spin(image_save)

    image_save.destroy_node()
    rclpy.shutdown

if __name__=="__main__":
    main()