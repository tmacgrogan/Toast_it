import pigpio

import time

import json

import math

#down: 900
#up:2500

pi = pigpio.pi();

lowerservo_left_ch = 12;
lowerservo_right_ch= 13;
upperservo_left_ch = 14;
upperservo_right_ch = 15;

speed = 100;
refresh_rate = 0.1; #seconds

pi.set_mode(13, pigpio.OUTPUT);


def servo(channel, percent):
	x = 700 + (18 * percent);
	pi.set_servo_pulsewidth(channel, x);


def lower_cart(y): # direction to be tested
	
	servo(lowerservo_left_ch, y);
	servo(lowerservo_right_ch, -y);

def upper_cart(x): #test direction
	
	servo(upperservo_left_ch, x);
	servo(upperservo_right_ch, -x);

def drive_line(point1, point2):
	print("draw a line!");
	x1 = point1["X"];
	y1 = point1["Y"];
	x2 = point2["X"];
	y2 = point2["Y"];
	dx = x2 - x1;
	dy = y2 - y1;
	length = math.sqrt( dx ** 2 + dy ** 2);
	duration = length/speed; #in seconds
	for t in range(duration/refresh_rate):
		
	


def write_letter (char, local_origin):
	curr_pos = {"X":0, "Y":0);
	f = open("filename.json", r).read()
	j = json.parse(f);
	if type(char) != "str" or len(char) > 1:
	
		print("input was no char you stupid asshole. try again");
		return
	else:
		letter = j[char]
		for point in letter:
			drive_line(curr_pos, point);		
	







while True:
	
	servo(13, 0);
	
	time.sleep(1);
	
	servo(13, 50);
	time.sleep(1);
	
	servo(13, 100);
	time.sleep(1);

