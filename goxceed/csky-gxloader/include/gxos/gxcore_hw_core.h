#ifndef GXCORE_HW_CORE
#define GXCORE_HW_CORE

/*
** Port API
*/
int32 GxCore_PortRead8         (uint32 PortAddress, uint8 *ByteValue);
int32 GxCore_PortWrite8        (uint32 PortAddress, uint8 ByteValue);
int32 GxCore_PortRead16        (uint32 PortAddress, uint16 *uint16Value);
int32 GxCore_PortWrite16       (uint32 PortAddress, uint16 uint16Value);
int32 GxCore_PortRead32        (uint32 PortAddress, uint32 *uint32Value);
int32 GxCore_PortWrite32       (uint32 PortAddress, uint32 uint32Value);
int32 GxCore_PortSetAttributes (uint32 key, uint32 value);
int32 GxCore_PortGetAttributes (uint32 key, uint32 *value);

/*
** Memory API
*/
int32 GxCore_MemRead8          (uint32 MemoryAddress, uint8 *ByteValue);
int32 GxCore_MemWrite8         (uint32 MemoryAddress, uint8 ByteValue);
int32 GxCore_EepromWrite8      (uint32 MemoryAddress, uint8 ByteValue);
int32 GxCore_MemRead16         (uint32 MemoryAddress, uint16 *uint16Value);
int32 GxCore_MemWrite16        (uint32 MemoryAddress, uint16 uint16Value);
int32 GxCore_EepromWrite16     (uint32 MemoryAddress, uint16 uint16Value);
int32 GxCore_MemRead32         (uint32 MemoryAddress, uint32 *uint32Value);
int32 GxCore_MemWrite32        (uint32 MemoryAddress, uint32 uint32Value);
int32 GxCore_MemCpy            (void *dest, void *src, uint32 n);
int32 GxCore_MemSet            (void *dest, uint8 value, uint32 n);
int32 GxCore_MemCheckRange     (uint32 Address, uint32 Size);
int32 GxCore_MemSetAttributes  (uint32 key, uint32 value);
int32 GxCore_MemGetAttributes  (uint32 key, uint32 *value);

#endif

