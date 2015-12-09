import pigpio

import time

import json

#down: 900
#up:2500

pi = pigpio.pi();

lowerservo_left_ch = 12;
lowerservo_right_ch= 13;
upperservo_left_ch = 14;
upperservo_right_ch = 15;



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

def draw_line(point1, point2):
	print("draw a line!");

def write_letter (char):
	curr_pos = {"X":0, "Y":0);
	f = open("filename.json", r).read()
	j = json.parse(f);
	if type(char) != "str" or len(char) > 1:
	
		print("input was no char you stupid asshole. try again");
		return
	else:
		letter = j[char]
		for point in letter:
			draw_line(curr_pos, point);		








while True:
	
	servo(13, 0);
	
	time.sleep(1);
	
	servo(13, 50);
	time.sleep(1);
	
	servo(13, 100);
	time.sleep(1);

