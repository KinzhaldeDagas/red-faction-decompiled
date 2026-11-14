// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00491880 rf_respawn_reset_counts
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, client timeout latch and registry admission, RFString-array ownership, native lag-compensation snapshot/restore asymmetry, geometry contact limits and respawn slots): 
// Cdecl no arguments. Writes loaded respawn count0 and auxiliaryDWORD757BA8=0 only. Leaves32 slot names,poses,tags,flags and timestamp fields untouched. Does not release string
// buffers or invoke exit cleanup.
void rf_respawn_reset_counts()
{
  rf_respawn_point_count = 0;
  unk_757BA8 = 0;
}

