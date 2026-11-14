// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00417140 rf_clutter_skin108_assign
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, clutter registry grammar/default retention,108-byte skin ownership, allocator cookies, native stack aliases and original flag-table strings): Thiscall existing destination plus source pointer,RET4. RFString assignment name0,raw DWORDcount8 copy,then assignments of ALL12 texture RFStrings at12+8*i (unsigned loop i<12),independent of activecount. Returnsdestination;existingstringbuffers reused/released byassignment helpers. Exact self-assignment of each string is guarded by helper;no full-record overlap protection,pointer/range validation or glare-array mutation.
_DWORD *__thiscall rf_clutter_skin108_assign(_DWORD *this, int a2)
{
  unsigned int i; // [esp+4h] [ebp-4h]

  rf_string_assign_from_object(this, a2);
  *(this + 2) = *(_DWORD *)(a2 + 8);
  for ( i = 0; i < 0xC; ++i )
    rf_string_assign_from_object(this + 2 * i + 3, a2 + 8 * i + 12);
  return this;
}

