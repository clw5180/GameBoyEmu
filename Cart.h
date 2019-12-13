#ifndef CART_H_INCLUDED
#define CART_H_INCLUDED
#include "CartHeader.h"

class Cart
{
public:

    virtual uint8_t Read(uint16_t)=0;
    virtual void Write(uint16_t, uint8_t)=0;
    virtual uint8_t* GetPointer(uint16_t)=0;

    static uint8_t CartRead(uint16_t Address, void* P);
    static void CartWrite(uint16_t Address, uint8_t Value, void* P);
    uint8_t* Rom;
    size_t RomSize;
    uint8_t* Ram;
    size_t RamSize;

    CartHeader Head;
};


#include "MBC.h"
#include "RomOnly.h"

#endif // CART_H_INCLUDED