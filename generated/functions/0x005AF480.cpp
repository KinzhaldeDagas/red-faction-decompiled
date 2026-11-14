// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005AF480 rf_ui_window_invalidate_bitmap_handles
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, UI window construction/navigation/parsing/drawing/cleanup, exact flag and list operations, original stack ABI and call sites): Thiscall no stack args; sets mask handle1232 and background handle1236 to-1 independently ONLY when current signed handle>=0,returns receiver. Other negative sentinels preserved. No bitmap release/unlock,heap free or other object writes.
_DWORD *__thiscall rf_ui_window_invalidate_bitmap_handles(_DWORD *this)
{
  _DWORD *result; // eax

  result = this;
  if ( (int)*(this + 308) >= 0 )
    *(this + 308) = -1;
  if ( (int)*(this + 309) >= 0 )
  {
    *(this + 309) = -1;
    return this;
  }
  return result;
}

