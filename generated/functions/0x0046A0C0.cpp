// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0046A0C0 rf_performance_toggle_dynamic_lighting
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, video/performance/gameplay call chains, original gamma constants and compiled labels, native
// x87/byte/stack/callback ABI): Noarg. Normalize logical-not checkboxBYTE6F77A0,write unchecked playerBYTE3908,call category_light_allow_byte with ZERO-EXTENDED newBYTE,then
// apply_preset(3) commits all UI tuple/Custom and calls lighting setter again. Sound selection tests DIFFERENT checkboxBYTE6F77F0 (DECALS),not newly toggled lighting:decals
// nonzero44,zero45. Preserve native mismatch. No player/capability/input admission,save or rollback.
int rf_performance_toggle_dynamic_lighting()
{
  byte_6F77A0[0] = byte_6F77A0[0] == 0;
  *(_BYTE *)(rf_local_fpgun_player + 3908) = byte_6F77A0[0];
  rf_renderer_set_category_light_allow_byte(byte_6F77A0[0]);
  rf_performance_options_apply_preset(3);
  if ( byte_6F77F0[0] )
    return rf_gamesound_play_event(44, 0, 0.0, 1.0);
  else
    return rf_gamesound_play_event(45, 0, 0.0, 1.0);
}

