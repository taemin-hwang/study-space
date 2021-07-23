#ifndef _MY_PROTOCOL_HEADER_H_
#define _MY_PROTOCOL_HEADER_H_

#pragma pack(push, 1)
struct MyPorotocol {
    uint_8 protocol_version;
    uint_8 length[2];
};
#pragma pack(pop)

#endif
