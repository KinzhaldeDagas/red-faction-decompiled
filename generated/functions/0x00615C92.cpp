// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00615C92 __write
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): R=DWORD[2021E40+4*ARITHMETIC(fd>>5)]+64*(fd&31);
// handle0,flagsBYTE4,lookaheadBYTE5,CSinitDWORD8,CS12,encodingBYTE36,extraLookahead37/38,positionLow/High40/44,conversionDWORD48,pendingConsoleBYTE52/pendingDWORD56. Kind is SIGNED
// low7 encoding bits, normally0 ANSI,1 UTF8-backed UTF16,2 UTF16LE; flags80 controls text separately. Invalid(E) below means errno E plus invalid_parameter(NULL,NULL,NULL,0,0);
// stated return follows only if handler returns. Cdecl(fd,source,count),publicwrite. Fd-2 dos0/errno9/-1 withoutinvalidhandler; othernegative/outofrange/notopen dos0/invalid(9)/-1.
// NO read-style count>INT_MAXprecheck. Calllock_fhandle,IGNOREBOOL,armSEH,re-fetchopenflag; open delegateswrite_nolock/savesstatus,closedafterlock errno9/dos0/-1
// withoutinvalidcallback. Normal/unwindfinallyunlock_fhandle evenhelperFALSE. Count0stillrequiresvalidopenfdandgoesthroughlock;NULLsource/parity/translationdelegated. No
// automaticretry/partialcountnormalization or rollback.
int __cdecl _write(int FileHandle, const void *Buf, unsigned int MaxCharCount)
{
  int v4; // esi
  int v5; // [esp+14h] [ebp-1Ch]

  if ( FileHandle == -2 )
  {
    *__doserrno() = 0;
    *_errno() = 9;
    return -1;
  }
  if ( FileHandle < 0
    || FileHandle >= MEMORY[0x2021E20]
    || (v4 = (FileHandle & 0x1F) << 6, (*(_BYTE *)(unk_2021E40[FileHandle >> 5] + v4 + 4) & 1) == 0) )
  {
    *__doserrno() = 0;
    *_errno() = 9;
    _invalid_parameter(nullptr, nullptr, nullptr, 0, 0);
    return -1;
  }
  __lock_fhandle(FileHandle);
  if ( (*(_BYTE *)(unk_2021E40[FileHandle >> 5] + v4 + 4) & 1) != 0 )
  {
    v5 = _write_nolock(FileHandle, Buf, MaxCharCount);
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

