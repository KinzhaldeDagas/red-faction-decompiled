// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00496200 rf_multiplayer_reset_motion_globals_77D6D0
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, scoreboard snapshot ordering and Player ownership, native packet layouts/audiences, inline string-record lifecycle, unreliable queue semantics and false SDK classification): 
// Cdecl no arguments. Clears DWORDs77D6D0/D4/D8/DC/E4/E8 andBYTES77D6E0/E1/E2. Zero vectors77D714/77D720;identity matrices77D6EC/77D738. Disarms
// deadlines77D72C,77D710,77D75C,arms77D734 with0ms,then disarms77D730,returns last delegateEAX. Ordering preserved; no whole-block memset,network send,resource free or guessed
// protocol meaning for individual globals.
_DWORD *rf_multiplayer_reset_motion_globals_77D6D0()
{
  unk_77D6D8 = 0;
  unk_77D6DC = 0;
  byte_77D6E0 = 0;
  byte_77D6E1 = 0;
  dword_77D6E4 = 0;
  dword_77D6E8 = 0;
  byte_77D6E2 = 0;
  rf_vector3_zero_return_destination(unk_77D714);
  rf_identity_orientation_matrix(&flt_77D6EC);
  unk_77D6D0 = 0;
  rf_vector3_zero_return_destination(unk_77D720);
  rf_identity_orientation_matrix(&flt_77D738);
  unk_77D6D4 = 0;
  rf_replicator_reset(&unk_77D72C);
  rf_replicator_reset(&unk_77D710);
  rf_replicator_reset(&unk_77D75C);
  rf_replicator_arm_milliseconds(&unk_77D734, 0);
  return rf_replicator_reset(&unk_77D730);
}

