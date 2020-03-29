/*
  ==============================================================================

    SynthSound.h
    Created: 24 Feb 2020 8:23:49pm
    Author:  timmy

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include <string>
#include <zmq.h>


class ZeroReceiver

{
public:
    void initZero()
    {
        // connect to server
        context = zmq::context_t(1);
        receiver = new zmq::socket_t(context, ZMQ_REQ);
        receiver->connect("tcp://localhost:12346");
        //DBG("Init zero done");
    }

    double recMsg()
    {     
        // REQ - REPLY
        zmq::message_t request(5);
        zmq::message_t reply;
        std::string rx_str;

        // send request
        memcpy(request.data(), "Hello", 5);
        receiver->send(request);

        // receive reply and convert to string
        receiver->recv(&reply);
        rx_str.assign(static_cast<char*>(reply.data()), reply.size());
        
        // find commas, replace with points and convert to double
        int position = rx_str.find(","); 
        while (position != string::npos)
        {
            rx_str.replace(position, 1, ".");
            position = rx_str.find(" ", position + 1);
        }
        double speed = std::stod(rx_str);

        // log
        //DBG(rx_str);
        //DBG(speed);
        return speed*7 + 55.0;
    }

private:
    zmq::context_t context;
    zmq::socket_t* receiver;
};