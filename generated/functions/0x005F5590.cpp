// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005F5590 rf_ui_inputbox_load_cursor_animation
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): Releases prior cursor animation via0x5F56A0;allocates408-byte VANI,constructs and loads metadata(filename,0),sets loop1,reverse0,draw flag4=0,hold-last0. Stores player1440;sets cursorWidth1432/cursorHeight1436 from player dimensions68/72. No allocation/load success guard;does not start playback or alter cursor bitmap1444. Returns this.
int *__thiscall rf_ui_inputbox_load_cursor_animation(int *this, char *a2)
{
  _DWORD *v3; // [esp+4h] [ebp-1Ch]
  _DWORD *v5; // [esp+Ch] [ebp-14h]

  rf_ui_inputbox_release_cursor_animation((int **)this);
  v5 = operator new(0x198u);
  if ( v5 )
    v3 = rf_vani_player_construct(v5);
  else
    v3 = nullptr;
  *(this + 360) = (int)v3;
  rf_vani_player_load_metadata(*(this + 360), a2, 0);
  rf_vani_player_set_loop_flag((_DWORD *)*(this + 360), 1);
  rf_vani_player_set_reverse_flag((_DWORD *)*(this + 360), 0);
  rf_vani_player_set_draw_state_flag4((_DWORD *)*(this + 360), 0);
  rf_vani_player_set_hold_last_flag((_DWORD *)*(this + 360), 0);
  *(this + 358) = *(_DWORD *)(*(this + 360) + 68);
  *(this + 359) = *(_DWORD *)(*(this + 360) + 72);
  return this;
}

