// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00611606 __dosmaperr
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Cdecl OS-errorDWORD. First get doserrno slot and store original raw OS error. Call get_errno_from_oserr(error),save mapped valueESI; get errno slot and write
// mapped result. Return final errno SLOT POINTER EAX,not mapped integer/status0; restoreESI. No own mapping table/Windows call, callback or original-error restoration.
int *__cdecl _dosmaperr(unsigned int a1)
{
  int errno_from_oserr; // esi
  int *result; // eax

  *__doserrno() = a1;
  errno_from_oserr = _get_errno_from_oserr(a1);
  result = _errno();
  *result = errno_from_oserr;
  return result;
}

