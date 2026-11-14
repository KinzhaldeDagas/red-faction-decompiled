// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005A96C0 rf_text_entry_buffered_scalar_deleting_destructor
// UNREALRED VERIFIED [list-selection-20261029]: Thiscall buffered entry,flags BYTE. Calls0x5A96F0 then operator delete(this) when mask1 set;returns original pointer even after free. Embedded text is part of object,no separate allocation release in called destructor.
_DWORD *__thiscall rf_text_entry_buffered_scalar_deleting_destructor(_DWORD *this, char a2)
{
  rf_text_entry_buffered_destroy(this);
  if ( (a2 & 1) != 0 )
    operator delete(this);
  return this;
}

