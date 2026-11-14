// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00469FC0 rf_performance_toggle_shadows
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, video/performance/gameplay call chains, original gamma constants and compiled labels, native
// x87/byte/stack/callback ABI): Noarg. Normalize logical-not checkboxBYTE6F7550,write unchecked playerBYTE3906 and rf_projected_shadows_enabled. Call apply_preset(3),marking
// Custom/committing all current UI tuple;then play44 if new shadowsBYTE nonzero else45. No capability/player/input checks,file save or rollback. Other pending chooser changes are
// also committed by apply_preset,even when unrelated to this toggle.
int rf_performance_toggle_shadows()
{
  byte_6F7550[0] = byte_6F7550[0] == 0;
  *(_BYTE *)(rf_local_fpgun_player + 3906) = byte_6F7550[0];
  rf_projected_shadows_enabled = byte_6F7550[0];
  rf_performance_options_apply_preset(3);
  if ( byte_6F7550[0] )
    return rf_gamesound_play_event(44, 0, 0.0, 1.0);
  else
    return rf_gamesound_play_event(45, 0, 0.0, 1.0);
}

