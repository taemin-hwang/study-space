from packet import basic_packet_format
from collections import namedtuple
import struct

DirectionPacketFormat = basic_packet_format.BasicPacketFormat
DirectionPacketFormat += 'i'  # Direction


class DirectionPacket:
    def __init__(self, display_id):
        print('Create Direction Packet')
        self.display_id = display_id

    def GetData(self, input_direction):
        DirectionStruct = namedtuple("DirectionStruct", "tos id len direction")
        TupleToSend = DirectionStruct(
            tos=1,
            id=self.display_id,
            len=4,
            direction=input_direction
        )
        #print(DirectionPacketFormat)
        #print(TupleToSend)
        #print(*TupleToSend._asdict().values())
        
        StringToSend = struct.pack(DirectionPacketFormat, *TupleToSend._asdict().values())
        return StringToSend
