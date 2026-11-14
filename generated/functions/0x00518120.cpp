// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00518120 rf_pointer_array_clear_count_keep_storage
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, volume segment integration, clipping, renderer bridges and original call sites): Thiscall sets count DWORD0 to0 and returns receiver;does not change capacity/backing pointer or free/destroy stored elements. Used to clear borrowed active-volume list before visibility rebuild. Former unknown_libname_19 classification replaced by exact behavior.
_DWORD *__thiscall rf_pointer_array_clear_count_keep_storage(_DWORD *this)
{
  *this = 0;
  return this;
}

