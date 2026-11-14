// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004E27A0 rf_player_hud_damage_tint_red
// UNREALRED VERIFIED [hud-late-pass] Applies the local player's exact damage screen tint RGB(255,0,0) with initial alpha 128.
_BYTE *rf_player_hud_damage_tint_red()
{
  return rf_player_hud_screen_tint_set(rf_local_fpgun_player, 255, 0, 0, 128);
}

