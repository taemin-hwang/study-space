from packet import basic_packet_format
from collections import namedtuple
import struct

VoicePacketFormat = basic_packet_format.BasicPacketFormat
VoicePacketFormat += '1012s'


class VoicePacket:
    def __init__(self, display_id):
        print('Create Voice Packet')
        self.display_id = display_id
        self.type_of_service = 3

    def GetData(self, input_len, input_txt):
        VoiceStruct = namedtuple("VoiceStruct", "tos id len txt")
        TupleToSend = VoiceStruct(
            tos=self.type_of_service,
            id=self.display_id,
            len=input_len,
            txt=input_txt.encode("ascii")
        )
        StringToSend = struct.pack(VoicePacketFormat, *TupleToSend._asdict().values())
        return StringToSend

