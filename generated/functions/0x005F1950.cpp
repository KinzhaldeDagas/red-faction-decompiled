// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005F1950 rf_ui_state_image_reset
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): If player DWORD+8!=0 AND ownership BYTE+28!=0,calls VANI deleting destructor0x5F1DC0 with flag1,then clears player and ownership. Always sets mode0. If either test false,leaves player/ownership fields unchanged. Preserves bitmap+4,ring+24 and other bytes;does not release bitmap or detach ring. Returns this.
_DWORD *__thiscall rf_ui_state_image_reset(_DWORD *this)
{
  _DWORD *result; // eax

  result = this;
  if ( *(this + 2) && *((_BYTE *)this + 28) )
  {
    if ( *(this + 2) )
      rf_vani_player_scalar_deleting_destructor((int *)*(this + 2), 1);
    result = this;
    *(this + 2) = 0;
    *((_BYTE *)this + 28) = 0;
  }
  *this = 0;
  return result;
}

