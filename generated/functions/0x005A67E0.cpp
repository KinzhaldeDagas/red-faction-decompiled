// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005A67E0 rf_text_entry_construct
// UNREALRED VERIFIED [list-selection-20261029]: Thiscall60-byte base entry. Installs ui_listbox_entry vtable,zeros indent DWORDs+28/+32,line gap+36,sets font+40=-1,DWORD+52=-1,dirty BYTE+4=0. Leaves links+8/+12,geometry+16..24,line count+44,text pointer+48 and DWORD+56 uninitialized/unchanged. No allocation or borrowed-text ownership; returns this.
_DWORD *__thiscall rf_text_entry_construct(_DWORD *this)
{
  *this = &ui_listbox_entry::`vftable';
  *(this + 7) = 0;
  *(this + 8) = 0;
  *(this + 9) = 0;
  *(this + 10) = -1;
  *(this + 13) = -1;
  *((_BYTE *)this + 4) = 0;
  return this;
}

