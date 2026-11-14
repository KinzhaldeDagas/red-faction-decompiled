// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005A9670 rf_text_entry_scalar_deleting_destructor
// UNREALRED VERIFIED [list-selection-20261029]: Thiscall entry,flags BYTE. Calls base destructor0x5A6830;flags mask1 then operator delete(this). Other bits ignored. Returns original this pointer even after free. Does not separately delete borrowed text; base body only resets vtable.
_DWORD *__thiscall rf_text_entry_scalar_deleting_destructor(_DWORD *this, char a2)
{
  rf_text_entry_destroy(this);
  if ( (a2 & 1) != 0 )
    operator delete(this);
  return this;
}

