#! /usr/local/bin/python3
import zmq
import time
import random
import sys

port = "12346"

# Socket to talk to server
context = zmq.Context()
socket = context.socket(zmq.REQ)

socket.connect ("tcp://localhost:%s" % port)

total_value = 0
while True:
    socket.send(b"Hello")
    message = socket.recv()
    print("Received reply [%s]" % (message))
