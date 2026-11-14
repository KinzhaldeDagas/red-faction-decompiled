// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005A68D0 rf_text_entry_set_borrowed_text
// UNREALRED VERIFIED [list-selection-20261029]: Thiscall entry,text pointer. Stores pointer at+48,returns this. Does not copy,allocate,free old storage,validate null or set dirty flag. Used by base-entry vtable when list flag0x400 selects external text; caller must retain text lifetime.
_DWORD *__thiscall rf_text_entry_set_borrowed_text(_DWORD *this, int a2)
{
  *(this + 12) = a2;
  return this;
}

