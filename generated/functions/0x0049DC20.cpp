// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0049DC20 rf_multiplayer_hud_tick_team_highlight_alpha
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, item/cutscene/HUD caller chains, original float constants, RFString ownership and false SDK classifications
// and native signed/x87/stack/callback ABI): No arguments; NULL local player returns with no changes. DirectionBYTE662918 nonzero: stores binary32(alpha662914-frameDelta*500);
// ordered alpha<=50 clamps50 and clears direction. Direction0: stores binary32(alpha+frameDelta*500); ordered alpha>=255 clamps255 and sets direction1. Exactly50/255 trigger
// direction reversal; unordered values do not clamp or reverse. No local team/game-mode check here (caller49D0B0 chooses mode1), drawing, elapsed timer or alpha return.
void rf_multiplayer_hud_tick_team_highlight_alpha()
{
  if ( rf_local_fpgun_player )
  {
    if ( byte_662918 )
    {
      flt_662914 = flt_662914 - rf_frame_delta_seconds * 500.0;
      if ( flt_662914 <= 50.0 )
      {
        flt_662914 = 50.0;
        byte_662918 = 0;
      }
    }
    else
    {
      flt_662914 = rf_frame_delta_seconds * 500.0 + flt_662914;
      if ( flt_662914 >= 255.0 )
      {
        flt_662914 = 255.0;
        byte_662918 = 1;
      }
    }
  }
}

