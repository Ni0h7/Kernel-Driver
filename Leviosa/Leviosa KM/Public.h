/*++

Module Name:

    public.h

Abstract:

    This module contains the common declarations shared by driver
    and user applications.

Environment:

    user and kernel

--*/

//
// Define an Interface Guid so that apps can find the device and talk to it.
//

DEFINE_GUID (GUID_DEVINTERFACE_Leviosa,
    0x967afe95,0x67a5,0x4d81,0x95,0x84,0xd9,0x4b,0xca,0x31,0x5e,0x0b);
// {967afe95-67a5-4d81-9584-d94bca315e0b}
