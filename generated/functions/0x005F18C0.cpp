// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005F18C0 rf_ui_state_image_construct
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): 32-byte record initialization:mode DWORD0=0,bitmap DWORD4=-1,player DWORD8=0,ring-next DWORD24=this,ownership BYTE28=0. Bytes12..23 and29..31 untouched. Returns this.
_DWORD *__thiscall rf_ui_state_image_construct(_DWORD *this)
{
  *this = 0;
  *(this + 2) = 0;
  *((_BYTE *)this + 28) = 0;
  *(this + 6) = this;
  *(this + 1) = -1;
  return this;
}

