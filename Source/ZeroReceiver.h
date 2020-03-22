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
        context = zmq::context_t(1);
        receiver = new zmq::socket_t(context, ZMQ_REQ);
        receiver->connect("tcp://localhost:12346");

        //receiver = new zmq::socket_t(context, ZMQ_SUB);
        //receiver->setsockopt(ZMQ_SUBSCRIBE, "", 0);

        freq = 0.0;
        DBG("Init zero done");
    }

    double recMsg()
    {
        // SUB
        //zmq::message_t rx_msg;
        //receiver->recv(&rx_msg);
        //std::string rx_str;
        //rx_str.assign(static_cast<char*>(rx_msg.data()), rx_msg.size());
        //DBG(rx_msg);
        
        // REQ
        zmq::message_t request(5);
        zmq::message_t reply;
        std::string rx_str;
        std::string::size_type sz;     // alias of size_t

        memcpy(request.data(), "Hello", 5);
        receiver->send(request);
        receiver->recv(&reply);

        rx_str.assign(static_cast<char*>(reply.data()), reply.size());
        std::cout << "Received: " << rx_str << std::endl;

        
        //double acc = std::stod(rx_str.substr(sz));

        int position = rx_str.find(","); // find first space
        while (position != string::npos)
        {
            rx_str.replace(position, 1, ".");
            position = rx_str.find(" ", position + 1);
        }

        double speed = std::stod(rx_str);

        
        DBG(rx_str);
        DBG(speed);
        return speed*7 + 55.0; //TODO return 0 if nothing there
    }

private:
    double freq;
    zmq::context_t context;
    zmq::socket_t* receiver;

};