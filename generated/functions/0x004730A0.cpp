// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004730A0 rf_item_render_model
// UNREALRED VERIFIED [item-pickups-20261028]: Skips respawn-inactive item. In multiplayer may hide carried red/blue flag for local player when camera predicate0x4118B0==0. Builds render params, copies item+636; fading item writes alpha=trunc(lifetime+692*255+0.5) without local clamp. In MP with definition flags+68 mask2, builds identity-based rotation and if unpaused advances angle+704 by frame_delta*0.75*pi, subtracting2*pi only once if greater. Otherwise uses authored matrix+72. Calls0x564BB0(model+128,position+60,matrix,params). Return register is branch dependent.
char __cdecl rf_item_render_model(int a1)
{
  int dword8; // eax
  float v3[9]; // [esp+4h] [ebp-74h] BYREF
  char v4[8]; // [esp+28h] [ebp-50h] BYREF
  int v5; // [esp+30h] [ebp-48h]
  int v6; // [esp+44h] [ebp-34h]

  LOBYTE(dword8) = rf_object_has_respawn_inactive_flag(a1);
  if ( (unsigned __int8)dword8 != 1
    && (!rf_multiplayer_runtime_mode
     || ((*(_DWORD *)(a1 + 700) & 0x20) == 0
      || rf_ctf_red_carrier_get() != rf_local_fpgun_player
      || (dword8 = rf_view_wrapper_get_dword8(*(_DWORD *)(rf_local_fpgun_player + 196))) != 0)
     && ((*(_DWORD *)(a1 + 700) & 0x40) == 0
      || rf_ctf_blue_carrier_get() != rf_local_fpgun_player
      || (dword8 = rf_view_wrapper_get_dword8(*(_DWORD *)(rf_local_fpgun_player + 196))) != 0)) )
  {
    rf_model_render_options_construct(v4);
    v6 = *(_DWORD *)(a1 + 636);
    if ( rf_item_is_fading(a1) )
      v5 = (int)(*(float *)(a1 + 692) / 1.0 * 255.0 + 0.5);
    if ( rf_multiplayer_runtime_mode && (*(_DWORD *)(*(_DWORD *)(a1 + 660) + 68) & 2) != 0 )
    {
      rf_matrix3_construct((char *)v3);
      rf_identity_orientation_matrix(v3);
      if ( !rf_game_pause_gate_query() )
      {
        *(float *)(a1 + 704) = rf_frame_delta_seconds * 0.75 * 3.141592741012573 + *(float *)(a1 + 704);
        if ( *(float *)(a1 + 704) > 6.283185482025146 )
          *(float *)(a1 + 704) = *(float *)(a1 + 704) - 6.283185482025146;
      }
      rf_matrix3_rotate_forward_about_up_axis(v3, *(float *)(a1 + 704));
      LOBYTE(dword8) = rf_model_handle_render_all_adapter(*(_DWORD *)(a1 + 128), a1 + 60, (int)v3, (int)v4);
    }
    else
    {
      LOBYTE(dword8) = rf_model_handle_render_all_adapter(*(_DWORD *)(a1 + 128), a1 + 60, a1 + 72, (int)v4);
    }
  }
  return dword8;
}

