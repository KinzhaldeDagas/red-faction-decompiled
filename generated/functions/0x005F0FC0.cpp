// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005F0FC0 rf_ui_base_construct
// UNREALRED VERIFIED [ui-properties-20261029]: Installs ui_base vtable,sets live BYTE+4=0,auxiliary list next+292 and previous+296=this+292,returns this. Does NOT initialize rectangle,ID,callback,disabled/other flags or subtype fields. No allocation.
char *__thiscall rf_ui_base_construct(char *this)
{
  *(_DWORD *)this = &ui_base::`vftable';
  *(this + 4) = 0;
  *((_DWORD *)this + 73) = this + 292;
  *((_DWORD *)this + 74) = this + 292;
  return this;
}

