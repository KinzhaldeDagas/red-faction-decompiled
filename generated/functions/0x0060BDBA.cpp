// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060BDBA __getcwd
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Cdecl(buffer,signedCount), pointer/NULL. Acquire CRT
// lock7, arm EH4 finally (scope65E990,handler60BDFA), call getdcwd_nolock(0,buffer,count), save result, normal/unwind unlock7, return saved pointer. No own count/NULL validation,
// allocation or path conversion; delegated helper behavior preserved.
char *__cdecl _getcwd(char *DstBuf, int SizeInBytes)
{
  char *v3; // [esp+10h] [ebp-1Ch]

  _lock(7);
  v3 = _getdcwd_nolock(0, DstBuf, SizeInBytes);
  _unlock(7);
  return v3;
}

