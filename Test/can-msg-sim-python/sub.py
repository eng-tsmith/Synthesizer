#! /usr/local/bin/python3
import zmq
import time
import random
import sys

port = "12346"

# Socket to talk to server
context = zmq.Context()
socket = context.socket(zmq.SUB)

socket.connect ("tcp://localhost:%s" % port)

# Subscribe to zipcode, default is NYC, 10001
topicfilter = "speed"
socket.setsockopt_string(zmq.SUBSCRIBE, topicfilter)

total_value = 0
while True:
    try:
        #check for a message, this will not block
        topic = socket.recv(flags=zmq.NOBLOCK)
        #messagedata = socket.recv(flags=zmq.NOBLOCK)
        # topic, messagedata = string.split()
        # total_value += int(messagedata)

        #a message has been received
        print (topic)
    except zmq.Again as e:
        print ("No message received yet")
