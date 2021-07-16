from packet import basic_packet_format
from collections import namedtuple
import struct

TouchPacketFormat = basic_packet_format.BasicPacketFormat
TouchPacketFormat += 'i'  # X-axis
TouchPacketFormat += 'i'  # Y-axis


class TouchPacket:
    def __init__(self, display_id):
        print('Create Touch Packet')
        self.display_id = display_id

    def GetData(self, input_x, input_y):
        TouchStruct = namedtuple("TouchStruct", "tos id len x y")
        TupleToSend = TouchStruct(
            tos=0,
            id=self.display_id,
            len=8,
            x=input_x,
            y=input_y
        )
        #print(TouchPacketFormat)
        #print(TupleToSend)
        #print(*TupleToSend._asdict().values())
        
        StringToSend = struct.pack(TouchPacketFormat, *TupleToSend._asdict().values())
        return StringToSend

