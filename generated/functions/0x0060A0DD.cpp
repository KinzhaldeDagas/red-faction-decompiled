// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060A0DD ___time64_t_from_ft
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Cdecl(FILETIME*), signed64 result in EDX:EAX
// (corrected from false int). No own NULL check. All-zero FILETIME returns -1LL; otherwise FileTimeToLocalFileTime then FileTimeToSystemTime, either BOOL failure returns -1LL without
// own errno/doserrno mapping. Success zero-extends SYSTEMTIME year/month/day/hour/minute/second WORDs, passes them plus DST=-1 to loctotime64_t, and forwards its full EDX:EAX result,
// including -1LL. No direct epoch arithmetic or output allocation. All six findfirst/findnext callers store both return halves.
__int64 __cdecl __time64_t_from_ft(FILETIME *lpFileTime)
{
  struct _SYSTEMTIME SystemTime; // [esp+0h] [ebp-18h] BYREF
  struct _FILETIME LocalFileTime; // [esp+10h] [ebp-8h] BYREF

  if ( (lpFileTime->dwLowDateTime || lpFileTime->dwHighDateTime)
    && FileTimeToLocalFileTime(lpFileTime, &LocalFileTime)
    && FileTimeToSystemTime(&LocalFileTime, &SystemTime) )
  {
    return __loctotime64_t(
             SystemTime.wYear,
             SystemTime.wMonth,
             SystemTime.wDay,
             SystemTime.wHour,
             SystemTime.wMinute,
             SystemTime.wSecond,
             -1);
  }
  else
  {
    return -1;
  }
}

