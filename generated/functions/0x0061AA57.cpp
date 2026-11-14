// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0061AA57 __get_osfhandle
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Descriptor record
// R=DWORD[2021E40+4*ARITHMETIC(fd>>5)]+64*(fd&31); handle DWORD+0, flags BYTE+4, lookahead BYTE+5, lock-init DWORD+8, critical section+12, encoding BYTE+36; fd limit DWORD2021E20.
// Invalid(E) means errno E plus invalid_parameter(NULL,NULL,NULL,0,0); stated status follows only if that handler returns. Cdecl(fd),returns raw storedHANDLE. Fd-2
// clearsdoserrno,errno9,-1 withoutinvalidhandler. Other negative/outofrange/notopen ->doserrno0,invalid(9),-1. Validrecordopen returns DWORDhandle unchanged, including0,-1,-2, with
// no further OS validity test. No lock, GetStdHandle, allocation, duplicate or ownership transfer.
intptr_t __cdecl _get_osfhandle(int FileHandle)
{
  int v2; // eax

  if ( FileHandle == -2 )
  {
    *__doserrno() = 0;
    *_errno() = 9;
    return -1;
  }
  else if ( FileHandle >= 0
         && FileHandle < MEMORY[0x2021E20]
         && (v2 = unk_2021E40[FileHandle >> 5] + ((FileHandle & 0x1F) << 6), (*(_BYTE *)(v2 + 4) & 1) != 0) )
  {
    return *(_DWORD *)v2;
  }
  else
  {
    *__doserrno() = 0;
    *_errno() = 9;
    _invalid_parameter(nullptr, nullptr, nullptr, 0, 0);
    return -1;
  }
}

