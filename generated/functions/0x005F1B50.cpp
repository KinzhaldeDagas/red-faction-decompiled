// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005F1B50 rf_ui_state_image_stop_animation_only
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): Only mode2 calls rf_vani_player_stop_clear_pause(player+8);mode3 bitmap+animation is NOT stopped. All other modes no-op. Return incidental this/player result.
_DWORD *__thiscall rf_ui_state_image_stop_animation_only(_DWORD *this)
{
  _DWORD *result; // eax

  result = this;
  if ( *this == 2 )
    return rf_vani_player_stop_clear_pause((_DWORD *)*(this + 2));
  return result;
}

