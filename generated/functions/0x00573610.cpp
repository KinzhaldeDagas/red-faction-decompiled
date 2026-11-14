// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00573610 rf_render_record_field28_is_one_or_two
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, fog output widths, channel-sum color filtering, backend dispatch, byte/int return distinctions and context startup): cdecl(recordPointer),returnsbyte1 exactly for DWORD(record+28)==2 OR==1,else0. Reads same field as5735E0 with different membership set;does not normalize or change field. No NULL/enum validation or proven semantic labels for those values.
unsigned __int8 __cdecl rf_render_record_field28_is_one_or_two(const void *record)
{
  return *((_DWORD *)record + 7) == 2 || *((_DWORD *)record + 7) == 1;
}

