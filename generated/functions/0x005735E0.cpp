// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005735E0 rf_render_record_field28_is_zero_or_one
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, fog output widths, channel-sum color filtering, backend dispatch, byte/int return distinctions and context startup): cdecl(recordPointer),returnsbyte1 exactly when DWORD(record+28)==0 OR==1,else0. Two equality branches;negative bit patterns such asFFFFFFFF reject,so do not reinterpret as signed value<=1. No pointer validation,global access or writes. Record class and enumeration labels not proven by available callers.
unsigned __int8 __cdecl rf_render_record_field28_is_zero_or_one(const void *record)
{
  return *((_DWORD *)record + 7) < 2u;
}

