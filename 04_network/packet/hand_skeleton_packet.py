from packet import basic_packet_format
from collections import namedtuple
import struct

HandSkeletonPacketFormat = basic_packet_format.BasicPacketFormat
HandSkeletonPacketFormat += 'i'  # X-axis
HandSkeletonPacketFormat += 'i'  # Y-axis


class HandSkeletonPacket:
    def __init__(self, display_id):
        print('Create Hand Skeleton Packet')
        self.display_id = display_id

    def GetData(self, input_x, input_y):
        HandSkeletonStruct = namedtuple("HandSkeletonStruct", "tos id len x y")
        TupleToSend = HandSkeletonStruct(
            tos=5,
            id=self.display_id,
            len=8,
            x=input_x,
            y=input_y
        )
        StringToSend = struct.pack(HandSkeletonPacketFormat, *TupleToSend._asdict().values())
        return StringToSend

