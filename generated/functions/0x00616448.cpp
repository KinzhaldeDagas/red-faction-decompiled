// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00616448 __commit
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Descriptor record
// R=DWORD[2021E40+4*ARITHMETIC(fd>>5)]+64*(fd&31); handle DWORD+0, flags BYTE+4, lookahead BYTE+5, lock-init DWORD+8, critical section+12, encoding BYTE+36; fd limit DWORD2021E20.
// Invalid(E) means errno E plus invalid_parameter(NULL,NULL,NULL,0,0); stated status follows only if that handler returns. Cdecl(fd), commit status0/-1. Fd-2 sets errno9/-1, no
// doserrno reset/invalid callback. Other invalidrange/closed beforelock ->errno9/invalid(9)/-1, no doserrno reset. Calllock_fhandle andIGNORE BOOL,armSEH,recheckopen. Closedafterlock
// ->errno9/-1, doserrnounchanged. Open: FlushFileBuffers(get_osfhandle(fd)); API success or API false with GetLastError0 ->0. Nonzero lastError stored RAWdoserrno, then errno9/-1,
// NOT dosmaperr mapping. Finallyunlock onnormal/unwind regardlesslock-helperBOOL. No flush of FILEuserbuffer, retry or own handle=-1 guard after getter.
int __cdecl _commit(int FileHandle)
{
  int v2; // esi
  void *osfhandle; // eax
  DWORD LastError; // [esp+14h] [ebp-1Ch]

  if ( FileHandle == -2 )
  {
    *_errno() = 9;
    return -1;
  }
  if ( FileHandle < 0
    || FileHandle >= MEMORY[0x2021E20]
    || (v2 = (FileHandle & 0x1F) << 6, (*(_BYTE *)(v2 + unk_2021E40[FileHandle >> 5] + 4) & 1) == 0) )
  {
    *_errno() = 9;
    _invalid_parameter(nullptr, nullptr, nullptr, 0, 0);
    return -1;
  }
  __lock_fhandle(FileHandle);
  if ( (*(_BYTE *)(v2 + unk_2021E40[FileHandle >> 5] + 4) & 1) != 0 )
  {
    osfhandle = (void *)_get_osfhandle(FileHandle);
    if ( FlushFileBuffers(osfhandle) )
      LastError = 0;
    else
      LastError = GetLastError();
    if ( !LastError )
      goto $good$28866;
    *__doserrno() = LastError;
  }
  *_errno() = 9;
  LastError = -1;
$good$28866:
  _unlock_fhandle(FileHandle);
  return LastError;
}

