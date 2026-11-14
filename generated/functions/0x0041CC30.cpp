// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0041CC30 rf_player_hud_screen_tint_render_decay
// UNREALRED VERIFIED [hud-late-pass] Draws Player+0x10D0 RGB with Player+0x10D4 alpha over the viewport, then decreases alpha by trunc(frame_delta*170) only while the game is not paused.
char __cdecl rf_player_hud_screen_tint_render_decay(int a1)
{
  int v1; // eax
  int viewport_width; // eax
  int viewport_height; // [esp-8h] [ebp-Ch]
  int v5; // [esp-4h] [ebp-8h]

  LOBYTE(v1) = a1;
  if ( *(int *)(a1 + 4308) > 0 )
  {
    rf_render_color_set_rgba8(
      *(unsigned __int8 *)(a1 + 4304),
      *(unsigned __int8 *)(a1 + 4305),
      *(unsigned __int8 *)(a1 + 4306),
      *(_DWORD *)(a1 + 4308));
    v5 = dword_182ABB8;
    viewport_height = rf_renderer_get_viewport_height();
    viewport_width = rf_renderer_get_viewport_width();
    rf_renderer_fill_rectangle_clipped(0, 0, viewport_width, viewport_height, v5);
    LOBYTE(v1) = rf_game_pause_gate_query();
    if ( !(_BYTE)v1 )
    {
      v1 = (int)(rf_frame_delta_seconds * 255.0 * 0.6666666865348816);
      if ( v1 >= *(_DWORD *)(a1 + 4308) )
      {
        *(_DWORD *)(a1 + 4308) = 0;
      }
      else
      {
        *(_DWORD *)(a1 + 4308) -= v1;
        LOBYTE(v1) = a1;
      }
    }
  }
  return v1;
}

