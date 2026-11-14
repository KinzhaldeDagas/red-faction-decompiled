// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005F19F0 rf_ui_state_image_load_animation
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): If current mode!=1,resets record first;mode1 preserves bitmap handle. Allocates408-byte VANI player,constructs and loads metadata(filename,0),sets loop0,reverse0,draw-state flag4 iff prior mode1,hold-last1;stores player+8 and ownership BYTE+28=1. Final mode3 when prior mode1(bitmap+animation),else2(animation only). Returns player pointer. No allocation or load success guard;new mode/ownership set even if loading fails.
int __thiscall rf_ui_state_image_load_animation(int this, char *a2)
{
  _DWORD *v3; // [esp+4h] [ebp-1Ch]
  _DWORD *v5; // [esp+Ch] [ebp-14h]

  if ( *(_DWORD *)this != 1 )
    rf_ui_state_image_reset((_DWORD *)this);
  v5 = operator new(0x198u);
  if ( v5 )
    v3 = rf_vani_player_construct(v5);
  else
    v3 = nullptr;
  *(_DWORD *)(this + 8) = v3;
  rf_vani_player_load_metadata(*(_DWORD *)(this + 8), a2, 0);
  rf_vani_player_set_loop_flag(*(_DWORD **)(this + 8), 0);
  rf_vani_player_set_reverse_flag(*(_DWORD **)(this + 8), 0);
  rf_vani_player_set_draw_state_flag4(*(_DWORD **)(this + 8), *(_DWORD *)this == 1);
  rf_vani_player_set_hold_last_flag(*(_DWORD **)(this + 8), 1);
  *(_BYTE *)(this + 28) = 1;
  if ( *(_DWORD *)this == 1 )
    *(_DWORD *)this = 3;
  else
    *(_DWORD *)this = 2;
  return *(_DWORD *)(this + 8);
}

