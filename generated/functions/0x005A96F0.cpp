// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005A96F0 rf_text_entry_buffered_destroy
// UNREALRED VERIFIED [list-selection-20261029]: Thiscall buffered entry. Directly returns base destructor0x5A6830 result. No text copy,heap release or dirty/link reset; scalar deleting wrapper decides object free.
_DWORD *__thiscall rf_text_entry_buffered_destroy(_DWORD *this)
{
  return rf_text_entry_destroy(this);
}

