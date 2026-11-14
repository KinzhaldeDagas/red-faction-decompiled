// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005F6680 rf_ui_staticbox_load_state_animation
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): Args stateIndex,filename;index0 selects normal image908,1 disabled940,others return0. Loads animation via state-image helper0x5F19F0,then gets player+8 via0x5F1DA0 and sets loop1,draw-state flag4=1. Returns1 regardless load success;no NULL check. Existing bitmap mode1 can become combined mode3;other load flags remain helper defaults(reverse0,hold-last1). No ring linking or start here.
int __thiscall rf_ui_staticbox_load_state_animation(_DWORD *this, int a2, char *a3)
{
  _DWORD *v3; // eax
  _DWORD *v4; // eax
  _DWORD *animation_pointer; // eax
  _DWORD *v6; // eax

  if ( a2 )
  {
    if ( a2 != 1 )
      return 0;
    rf_ui_state_image_load_animation((int)(this + 235), a3);
    animation_pointer = (_DWORD *)rf_ui_state_image_get_animation_pointer(this + 235);
    rf_vani_player_set_loop_flag(animation_pointer, 1);
    v6 = (_DWORD *)rf_ui_state_image_get_animation_pointer(this + 235);
    rf_vani_player_set_draw_state_flag4(v6, 1);
  }
  else
  {
    rf_ui_state_image_load_animation((int)(this + 227), a3);
    v3 = (_DWORD *)rf_ui_state_image_get_animation_pointer(this + 227);
    rf_vani_player_set_loop_flag(v3, 1);
    v4 = (_DWORD *)rf_ui_state_image_get_animation_pointer(this + 227);
    rf_vani_player_set_draw_state_flag4(v4, 1);
  }
  return 1;
}

