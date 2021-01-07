#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import rospy
from std_msgs.msg import String

from gtts import gTTS
from playsound import playsound

import rospkg

import os
import time

rospack = rospkg.RosPack()

def callback(data):
	phrase=data.data
	tts = gTTS(text=phrase, lang='es-ES', slow=False)
	filename="speech.wav"
	path=os.path.join(rospack.get_path('interaccion'), 'data/')
	path=os.path.join(path,filename)
	tts.save(path)
	playsound(path)

def tts():
	rospy.init_node('tts',anonymous=False)
	
	rospy.Subscriber('speech', String, callback, queue_size=20)

	rospy.loginfo("Text-to-Speech is ready to talk...")

	rospy.spin()

if __name__ == '__main__':
	tts()