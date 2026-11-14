// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0046A040 rf_performance_toggle_decals
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, video/performance/gameplay call chains, original gamma constants and compiled labels, native
// x87/byte/stack/callback ABI): Noarg. Normalize logical-not checkboxBYTE6F77F0,write playerBYTE3907/globalBYTE663F04;apply_preset(3) marks Custom and commits all UI fields. Sound44
// if new decals nonzero else45. Native builder Decals label/callback verified. No player/capability/input checks,file save or rollback;all writes occur immediately.
int rf_performance_toggle_decals()
{
  byte_6F77F0[0] = byte_6F77F0[0] == 0;
  *(_BYTE *)(rf_local_fpgun_player + 3907) = byte_6F77F0[0];
  byte_663F04 = byte_6F77F0[0];
  rf_performance_options_apply_preset(3);
  if ( byte_6F77F0[0] )
    return rf_gamesound_play_event(44, 0, 0.0, 1.0);
  else
    return rf_gamesound_play_event(45, 0, 0.0, 1.0);
}

