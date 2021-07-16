from packet import basic_packet_format
from collections import namedtuple
import struct

GazePacketFormat = basic_packet_format.BasicPacketFormat
GazePacketFormat += 'i'  # X-axis
GazePacketFormat += 'i'  # Y-axis


class GazePacket:
    def __init__(self, display_id):
        print('Create Gaze Packet')
        self.display_id = display_id

    def GetData(self, input_x, input_y):
        GazeStruct = namedtuple("GazeStruct", "tos id len x y")
        TupleToSend = GazeStruct(
            tos=2,
            id=self.display_id,
            len=8,
            x=input_x,
            y=input_y
        )
        StringToSend = struct.pack(GazePacketFormat, *TupleToSend._asdict().values())
        return StringToSend

