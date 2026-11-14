// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060D0A6 _getenv
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Invalid(E) means errno=E then
// invalid_parameter(NULL,NULL,NULL,0,0); any stated subsequent return requires that handler to return. Cdecl(name), borrowed value pointer/NULL. NULLname OR
// strnlen(name,32767)>=32767 invalid22/NULL, no own dos reset; empty name allowed. Acquire lock7/arm EH4 scope65EA90, getenv_helper_nolock(name), save borrowed pointer, finally
// unlock7 normal/unwind via60D120, return pointer. No copy/lifetime guarantee after lock release; conversion/lookup delegated.
char *__cdecl getenv(const char *VarName)
{
  char *v2; // [esp+14h] [ebp-1Ch]

  if ( VarName && strnlen(VarName, 0x7FFFu) < 0x7FFF )
  {
    _lock(7);
    v2 = (char *)_getenv_helper_nolock((char *)VarName);
    _unlock(7);
    return v2;
  }
  else
  {
    *_errno() = 22;
    _invalid_parameter(nullptr, nullptr, nullptr, 0, 0);
    return nullptr;
  }
}

