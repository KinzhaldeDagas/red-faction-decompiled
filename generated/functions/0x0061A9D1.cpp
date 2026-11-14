// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0061A9D1 __free_osfhnd
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Descriptor record
// R=DWORD[2021E40+4*ARITHMETIC(fd>>5)]+64*(fd&31); handle DWORD+0, flags BYTE+4, lookahead BYTE+5, lock-init DWORD+8, critical section+12, encoding BYTE+36; fd limit DWORD2021E20.
// Cdecl(fd). Require nonnegative,inrange,flagsopen1,and storedhandle !=-1. Failure errno9,doserrno0,-1 withoutinvalidhandler. Success when664D60==1 andfd0/1/2
// callsSetStdHandle(-10/-11/-12,NULL),IGNORES result; setrecordhandle=-1,return0. Does NOT CloseHandle or clear open/other flags/lock-init field; -2/0 storedhandles pass !=-1 test.
// No own lock or pointer validation.
int __cdecl _free_osfhnd(int a1)
{
  int v1; // esi
  int v2; // eax

  if ( a1 < 0
    || a1 >= MEMORY[0x2021E20]
    || (v1 = (a1 & 0x1F) << 6, v2 = v1 + unk_2021E40[a1 >> 5], (*(_BYTE *)(v2 + 4) & 1) == 0)
    || *(_DWORD *)v2 == -1 )
  {
    *_errno() = 9;
    *__doserrno() = 0;
    return -1;
  }
  else
  {
    if ( dword_664D60 == 1 )
    {
      if ( a1 )
      {
        if ( a1 == 1 )
        {
          SetStdHandle(0xFFFFFFF5, nullptr);
        }
        else if ( a1 == 2 )
        {
          SetStdHandle(0xFFFFFFF4, nullptr);
        }
      }
      else
      {
        SetStdHandle(0xFFFFFFF6, nullptr);
      }
    }
    *(_DWORD *)(v1 + unk_2021E40[a1 >> 5]) = -1;
    return 0;
  }
}

