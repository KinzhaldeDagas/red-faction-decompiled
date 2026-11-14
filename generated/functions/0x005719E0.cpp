// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005719E0 rf_packed_dword_construct_return_self_5719E0
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, renderer/window context, capture ownership across calls, gamma precision and ramp bytes): ECX pointer to4B storage plus one32bit value,RET4. Stores rawDWORD at receiver0 and returns receiver. No channel reorder,clamp,allocation or other fields. Caller5A3F95 constructs0 then copies DWORD into render-options offset12. Generic one-word value constructor contract verified;old unknown_libname_29 runtime label did not describe this behavior.
_DWORD *__thiscall rf_packed_dword_construct_return_self_5719E0(_DWORD *this, int a2)
{
  *this = a2;
  return this;
}

