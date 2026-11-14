// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00614F2D __lseek
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Descriptor record
// R=DWORD[2021E40+4*ARITHMETIC(fd>>5)]+64*(fd&31); handle DWORD+0, flags BYTE+4, lookahead BYTE+5, lock-init DWORD+8, critical section+12, encoding BYTE+36; fd limit DWORD2021E20.
// Invalid(E) means errno E plus invalid_parameter(NULL,NULL,NULL,0,0); stated status follows only if that handler returns. Fd==-2: doserrno0,errno9,-1 WITHOUT invalid handler. Other
// negative, unsigned fd>=LIVE limit, or initial flags&1==0: doserrno0,errno9,invalid handler,-1. Admitted path calls lock_fhandle(fd) and IGNORES its BOOL result, arms SEH,
// re-fetches block/flags and rechecks open bit. Normal/unwind finally calls unlock_fhandle even when acquisition helper returnedFALSE. Cdecl(fd,offset,origin), return raw32-bit
// delegate result. Post-lock closed ->errno9,doserrno0,-1 without invalid handler. Open forwards allthree slots to lseek_nolock; save result/finallyunlock. No own origin validation,
// flush, signed-position check or rollback on failure.
int __cdecl _lseek(int FileHandle, int Offset, int Origin)
{
  int v4; // esi
  DWORD v5; // [esp+14h] [ebp-1Ch]

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
    v5 = _lseek_nolock(FileHandle, Offset, Origin);
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

