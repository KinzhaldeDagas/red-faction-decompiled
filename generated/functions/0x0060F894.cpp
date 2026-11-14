// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060F894 ?what@exception@@UBEPBDXZ
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Thiscall exception receiver, no stack args. Return stored message pointer+self4 when nonNULL; NULL returns fixed originalPE literal Unknown exception. No
// allocation, message copy, ownership/extent check or cache mutation. Caller receives borrowed pointer; no NULL receiver guard.
const char *__thiscall exception::what(exception *this)
{
  const char *result; // eax

  result = *((const char **)this + 1);
  if ( !result )
    return "Unknown exception";
  return result;
}

