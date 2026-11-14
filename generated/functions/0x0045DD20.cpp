// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0045DD20 rf_rfstring_array8_clear_and_release
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, multiplayer level catalog/control call chains, native header/string ABI, original setup tables, slider
// arithmetic, callback stack reuse and RFString array ownership): ECX array {count0,capacity4,data8}. Set count0/capacity0 BEFORE cleanup. If backing pointer nonNULL
// invoke45DF10(backing,3),then set dataNULL. No inline extent loop,partial-used-only destruction claim or failure rollback;delegate owns vector/scalar delete details. EAX destination
// on normal return,existing prototype retained. Other object fields untouched;does not free array object itself here.
_DWORD *__thiscall rf_rfstring_array8_clear_and_release(_DWORD *this)
{
  _DWORD *result; // eax

  result = this;
  *this = 0;
  *(this + 1) = 0;
  if ( *(this + 2) )
  {
    rf_rfstring_delete_with_scalar_or_vector_flags((char *)*(this + 2), 3);
    *(this + 2) = 0;
    return this;
  }
  return result;
}

