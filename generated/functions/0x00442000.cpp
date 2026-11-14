// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00442000 rf_player_control_clear_vectors_and_fields1C20
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, split-match render/update/pause gates, score comparisons, announcer policy, ignored extra audio arguments and
// x87 fade thresholds): Cdecl pointer to control block. Zero vector at+12 then vector+0 using vector helper, then float+28=0 and+32=0; return original pointer in EAX. Leaves
// DWORD/float+24 and all other fields intact, so not a full36-byte clear. No NULL/runtime guard, allocations or callbacks besides vectorzero. Split frame passes Entity+1800 or
// view-target+1800 to suppress the nonselected player's movement/control data.
float *__cdecl rf_player_control_clear_vectors_and_fields1C20(float *a1)
{
  rf_vector3_zero_return_destination(a1 + 3);
  rf_vector3_zero_return_destination(a1);
  a1[7] = 0.0;
  a1[8] = 0.0;
  return a1;
}

