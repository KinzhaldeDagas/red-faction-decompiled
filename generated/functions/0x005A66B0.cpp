// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005A66B0 rf_text_entry_buffered_construct
// UNREALRED VERIFIED [list-selection-20261029]: Thiscall316-byte buffered entry. Calls base constructor0x5A67E0,sets ui_listbox_buffered_entry vtable,sets text pointer DWORD+48=this+60,returns this. Does NOT initialize first byte of embedded text buffer; call text setter before use.
_DWORD *__thiscall rf_text_entry_buffered_construct(_DWORD *this)
{
  rf_text_entry_construct(this);
  *this = &ui_listbox_buffered_entry::`vftable';
  *(this + 12) = this + 15;
  return this;
}

