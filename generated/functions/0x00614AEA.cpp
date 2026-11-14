// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00614AEA __read
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): R=DWORD[2021E40+4*ARITHMETIC(fd>>5)]+64*(fd&31);
// handle0,flagsBYTE4,lookaheadBYTE5,CSinitDWORD8,CS12,encodingBYTE36,extraLookahead37/38,positionLow/High40/44,conversionDWORD48,pendingConsoleBYTE52/pendingDWORD56. Kind is SIGNED
// low7 encoding bits, normally0 ANSI,1 UTF8-backed UTF16,2 UTF16LE; flags80 controls text separately. Invalid(E) below means errno E plus invalid_parameter(NULL,NULL,NULL,0,0);
// stated return follows only if handler returns. Cdecl(fd,buffer,count),publicread. Fd-2:dos0/errno9/-1,nohandler. Othernegative/outofrange/notopen:dos0/invalid(9)/-1.
// Count>INT_MAX:dos0/invalid(22)/-1 BEFORElock. Calllock_fhandle,IGNOREBOOL,armSEH,re-fetchblock/openflag; stillopen callread_nolock andsaveEAX; closedafterlock errno9/dos0/-1
// withoutinvalidcallback. Finallyunlock_fhandle onnormal/unwind evenlock-helperFALSE;return savedresult. No ownNULLbuffer/parity/zero-count shortcut, seek, conversion or rollback;
// thosechecks delegated afterfdvalidation.
int __cdecl _read(int FileHandle, void *DstBuf, unsigned int MaxCharCount)
{
  int v4; // edi
  unsigned int nolock; // [esp+14h] [ebp-1Ch]

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
LABEL_7:
    _invalid_parameter(nullptr, nullptr, nullptr, 0, 0);
    return -1;
  }
  if ( MaxCharCount > 0x7FFFFFFF )
  {
    *__doserrno() = 0;
    *_errno() = 22;
    goto LABEL_7;
  }
  __lock_fhandle(FileHandle);
  if ( (*(_BYTE *)(unk_2021E40[FileHandle >> 5] + v4 + 4) & 1) != 0 )
  {
    nolock = _read_nolock(FileHandle, (CHAR *)DstBuf, MaxCharCount);
  }
  else
  {
    *_errno() = 9;
    *__doserrno() = 0;
    nolock = -1;
  }
  _unlock_fhandle(FileHandle);
  return nolock;
}

