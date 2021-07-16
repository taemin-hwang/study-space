import socket
from time import sleep
import client_interface

display_id = input('enter display id : ')

client_interface = client_interface.ClientInterface(int(display_id))
client_interface.SendTouchPacket(1, 2)
client_interface.SendDirectionPacket(0)
client_interface.SendGazePacket(11, 22)
client_interface.SendHandSkeletonPacket(3, 4)
client_interface.SendVoicePacket('hello world')
client_interface.SendTouchPacket(1, 2)