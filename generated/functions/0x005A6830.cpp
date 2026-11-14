// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005A6830 rf_text_entry_destroy
// UNREALRED VERIFIED [list-selection-20261029]: Thiscall base destructor body only reinstalls ui_listbox_entry vtable and returns this. Does not free object,borrowed text or links. Deleting wrapper0x5A9670 handles object release.
_DWORD *__thiscall rf_text_entry_destroy(_DWORD *this)
{
  *this = &ui_listbox_entry::`vftable';
  return this;
}

