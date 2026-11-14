// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00614EB8 __lseek_nolock
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Descriptor record
// R=DWORD[2021E40+4*ARITHMETIC(fd>>5)]+64*(fd&31); handle DWORD+0, flags BYTE+4, lookahead BYTE+5, lock-init DWORD+8, critical section+12, encoding BYTE+36; fd limit DWORD2021E20.
// Cdecl(fd,raw32-bit distance,raw method), returns low32-bit position/-1. get_osfhandle==-1 ->own errno9/-1, preserving delegate doserrno policy. Otherwise
// SetFilePointer(handle,distance,NULLhigh,method). Only lowresultUINT_MAX triggers GetLastError; otherresults treatedsuccess/error0. Nonzero error dosmaperr/-1; zeroerror clears
// record EOF flag0x2 andreturns rawlowresult, INCLUDING UINT_MAX with LastError0. No pre-clear of LastError, method0..2 validation, own lock/range check or signed-negative-position
// rejection. Successful high-bit positions can look negative to signed callers.
DWORD __cdecl _lseek_nolock(int FileHandle, LONG lDistanceToMove, DWORD dwMoveMethod)
{
  void *osfhandle; // eax
  DWORD v5; // edi
  DWORD LastError; // eax
  _BYTE *v7; // eax

  osfhandle = (void *)_get_osfhandle(FileHandle);
  if ( osfhandle == (void *)-1 )
  {
    *_errno() = 9;
    return -1;
  }
  else
  {
    v5 = SetFilePointer(osfhandle, lDistanceToMove, nullptr, dwMoveMethod);
    if ( v5 == -1 )
      LastError = GetLastError();
    else
      LastError = 0;
    if ( LastError )
    {
      _dosmaperr(LastError);
      return -1;
    }
    else
    {
      v7 = (_BYTE *)(unk_2021E40[FileHandle >> 5] + ((FileHandle & 0x1F) << 6) + 4);
      *v7 &= ~2u;
      return v5;
    }
  }
}

