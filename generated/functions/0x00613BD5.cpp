// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00613BD5 __isindst
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Cdecl(tmPtr),BOOL EAX.
// Acquirelock6,armEH4scope65ED80; move input toEDI, callisindst_nolock,saveBOOL; normal/unwindfinallyunlock6 via613C0D,return savedresult. No own
// pointer/calendarvalidation,tzset,copying or errno policy; daylight0 helper canreturn0 evenNULLinput.
BOOL __cdecl _isindst(_DWORD *a1)
{
  BOOL v2; // [esp+10h] [ebp-1Ch]

  _lock(6);
  v2 = _isindst_nolock(a1);
  _unlock(6);
  return v2;
}

