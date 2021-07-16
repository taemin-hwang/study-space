import struct
import socket
from time import sleep
from packet import touch_packet
from packet import gaze_packet
from packet import direction_packet
from packet import voice_packet
#from packet import body_skeleton_packet
from packet import hand_skeleton_packet

server_address = '127.0.0.1'  # Need to be changed to 192.168.0.2
port = 50001

class ServerInterface:
    def __init__(self):
        print('Create Server Interface')
        self.s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.s.bind((server_address, port))
        self.s.listen()
        self.client, self.address = self.s.accept()
        
    def __del__(self):
        self.s.close()
        
    def run(self):
        while True:
            header = self.client.recv(12)
            type_of_service = int.from_bytes(header[:4], 'little')
            display_id = int.from_bytes(header[4:8], 'little')
            length = int.from_bytes(header[8:12], 'little')
            print('type of service : {0}'.format(type_of_service))
            print('display id      : {0}'.format(display_id))
            print('payload length  : {0}'.format(length))
            
            if(type_of_service == 0):
                recv_byte = self.client.recv(length)
                self.TouchHander(recv_byte)
            elif(type_of_service == 1):
                recv_byte = self.client.recv(length)
                self.DirectionHandler(recv_byte)
            elif(type_of_service == 2):
                recv_byte = self.client.recv(length)
                self.GazeHandler(recv_byte)
            elif(type_of_service == 3):
                recv_byte = self.client.recv(1012)
                self.VoiceHandler(recv_byte)
            elif(type_of_service == 4):
                recv_byte = self.client.recv(length)
                #self.BodySkeletonhandler(recv_byte)
                print('Todo!')
            elif(type_of_service == 5):
                recv_byte = self.client.recv(length)
                self.HandSkeletonHandler(recv_byte)
            else:
                print('out of scope!')
            print('===============================================')
            
            if not header:
                break
                        
    def TouchHander(self, recv_byte):
        x_axis = int.from_bytes(recv_byte[:4], 'little')
        y_axis = int.from_bytes(recv_byte[4:8], 'little')
        print('x-axis, y-axis : {0}, {1}'.format(x_axis, y_axis))
        
    def DirectionHandler(self, recv_byte):
        direction = int.from_bytes(recv_byte[:4], 'little')
        print('direction : {0}'.format(direction))
        
    def GazeHandler(self, recv_byte):
        x_axis = int.from_bytes(recv_byte[:4], 'little')
        y_axis = int.from_bytes(recv_byte[4:8], 'little')
        print('x-axis, y-axis : {0}, {1}'.format(x_axis, y_axis))
        
    def VoiceHandler(self, recv_byte):
        message = str(recv_byte, 'utf-8')
        print('message : ' + message)
        
    def HandSkeletonHandler(self, recv_byte):
        x_axis = int.from_bytes(recv_byte[:4], 'little')
        y_axis = int.from_bytes(recv_byte[4:8], 'little')
        print('x-axis, y-axis : {0}, {1}'.format(x_axis, y_axis))