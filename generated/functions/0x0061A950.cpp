// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0061A950 __set_osfhnd
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Descriptor record
// R=DWORD[2021E40+4*ARITHMETIC(fd>>5)]+64*(fd&31); handle DWORD+0, flags BYTE+4, lookahead BYTE+5, lock-init DWORD+8, critical section+12, encoding BYTE+36; fd limit DWORD2021E20.
// Cdecl(fd,new rawHANDLE). Require fd>=0,fd<LIVElimit unsigned,and currentrecord handle EXACT-1; flags/open bit NOT tested. Failure errno9,doserrno0,-1 without invalid handler.
// Success if global664D60==1 andfd0/1/2, callSetStdHandle(-10/-11/-12,newHandle),IGNORE APIresult; then write record handle andreturn0. No validity check of newHandle (0/-1/-2
// accepted), OS duplicate/close, flag-bit update, lock or initialized-blockNULL check.
int __cdecl _set_osfhnd(int a1, HANDLE hHandle)
{
  int v2; // esi

  if ( a1 >= 0 && a1 < MEMORY[0x2021E20] && (v2 = (a1 & 0x1F) << 6, *(_DWORD *)(v2 + unk_2021E40[a1 >> 5]) == -1) )
  {
    if ( dword_664D60 == 1 )
    {
      if ( a1 )
      {
        if ( a1 == 1 )
        {
          SetStdHandle(0xFFFFFFF5, hHandle);
        }
        else if ( a1 == 2 )
        {
          SetStdHandle(0xFFFFFFF4, hHandle);
        }
      }
      else
      {
        SetStdHandle(0xFFFFFFF6, hHandle);
      }
    }
    *(_DWORD *)(v2 + unk_2021E40[a1 >> 5]) = hHandle;
    return 0;
  }
  else
  {
    *_errno() = 9;
    *__doserrno() = 0;
    return -1;
  }
}

