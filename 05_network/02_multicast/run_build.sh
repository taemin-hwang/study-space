#!/bin/bash

g++ MulticastReceiver.cc DieWithMessage.cc TCPClientUtility.cc -I . -o multicast_client
g++ MulticastSender.cc DieWithMessage.cc TCPServerUtility.cc AddressUtility.cc -I . -o multicast_server
