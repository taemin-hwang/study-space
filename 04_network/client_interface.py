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

class ClientInterface:
    def __init__(self, display_id):
        print('Create Client Interface')
        self.display_id = int(display_id)
        self.s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.s.connect((server_address, port))

    def __del__(self):
        self.s.close()

    def SendTouchPacket(self, input_x, input_y):
        touch = touch_packet.TouchPacket(self.display_id)
        TouchData = touch.GetData(int(input_x), int(input_y))
        self.s.send(TouchData)

    def SendDirectionPacket(self, input_direction):
        direction = direction_packet.DirectionPacket(self.display_id)
        DirectionData = direction.GetData(int(input_direction))
        self.s.send(DirectionData)

    def SendGazePacket(self, input_x, input_y):
        gaze = gaze_packet.GazePacket(self.display_id)
        GazeData = gaze.GetData(int(input_x), int(input_y))
        self.s.send(GazeData)

    def SendVoicePacket(self, txt):
        voice = voice_packet.VoicePacket(self.display_id)
        VoiceData = voice.GetData(len(txt)+1, txt)
        self.s.send(VoiceData)

    def SendHandSkeletonPacket(self, input_x, input_y):
        hand_skeleton = hand_skeleton_packet.HandSkeletonPacket(self.display_id)
        HandSkeletonData = hand_skeleton.GetData(int(input_x), int(input_y))
        self.s.send(HandSkeletonData)
