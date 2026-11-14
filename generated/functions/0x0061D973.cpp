// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0061D973 __lseeki64
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Descriptor record
// R=DWORD[2021E40+4*ARITHMETIC(fd>>5)]+64*(fd&31); handle DWORD+0, flags BYTE+4, lookahead BYTE+5, lock-init DWORD+8, critical section+12, encoding BYTE+36; fd limit DWORD2021E20.
// Invalid(E) means errno E plus invalid_parameter(NULL,NULL,NULL,0,0); stated status follows only if that handler returns. Cdecl(fd,64-bit offset,origin),64-bit returnEDX:EAX. Fd-2
// ->doserrno0,errno9,64-bit-1,noinvalidcallback. Other negative/outofrange/notopen ->doserrno0,invalid(9),64-bit-1. Validprecheckcalllock_fhandle,IGNORE BOOL,armSEH,recheckopen.
// Closedafterlock errno9,doserrno0,savebothhalves-1;elseforwardfourrawslots to lseeki64_nolock,savereturnpair. Finallyunlock normal/unwind evenhelperFALSE,restore BOTH returnhalves.
// No originvalidation, FILEflush, ownoffsetbounds or rollback.
__int64 __cdecl _lseeki64(int FileHandle, __int64 Offset, int Origin)
{
  int v4; // esi
  __int64 v5; // [esp+10h] [ebp-24h]

  if ( FileHandle == -2 )
  {
    *__doserrno() = 0;
    *_errno() = 9;
    return -1;
  }
  if ( FileHandle < 0 || FileHandle >= MEMORY[0x2021E20] )
  {
    *__doserrno() = 0;
    *_errno() = 9;
    _invalid_parameter(nullptr, nullptr, nullptr, 0, 0);
    return -1;
  }
  v4 = (FileHandle & 0x1F) << 6;
  if ( (*(_BYTE *)(unk_2021E40[FileHandle >> 5] + v4 + 4) & 1) != 0 )
  {
    __lock_fhandle(FileHandle);
    if ( (*(_BYTE *)(unk_2021E40[FileHandle >> 5] + v4 + 4) & 1) != 0 )
    {
      v5 = _lseeki64_nolock(FileHandle, Offset, SHIDWORD(Offset), Origin);
    }
    else
    {
      *_errno() = 9;
      *__doserrno() = 0;
      v5 = -1;
    }
    _unlock_fhandle(FileHandle);
    return v5;
  }
  else
  {
    *__doserrno() = 0;
    *_errno() = 9;
    _invalid_parameter(nullptr, nullptr, nullptr, 0, 0);
    return -1;
  }
}

