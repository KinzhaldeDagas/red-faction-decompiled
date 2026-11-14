// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00456000 rf_inline_dword_array6_append_exact_limit
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Thiscall(receiver,raw DWORD value), RET4. Only exact countDWORD0==6 rejects with fullEAX-1 and no stores. Otherwise saves old count, increments/stores count
// first with32-bit wrap, stores value atreceiver+4+4*oldCount, returns oldCount. Does NOT reject negative or greater-than-limit count, validate storage/pointers, allocate/grow, or
// roll back on invalid write. Equality guard is not a general capacity>= check; no type/ownership interpretation of appended DWORD.
int __thiscall rf_inline_dword_array6_append_exact_limit(_DWORD *this, int a2)
{
  int v3; // [esp+4h] [ebp-4h]

  if ( *this == 6 )
    return -1;
  v3 = (*this)++;
  *(this + v3 + 1) = a2;
  return v3;
}

