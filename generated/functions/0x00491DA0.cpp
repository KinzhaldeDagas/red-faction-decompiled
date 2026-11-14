// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00491DA0 rf_respawn_select_reordered_arguments
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, scoreboard snapshot ordering and Player ownership, native packet layouts/audiences, inline string-record lifecycle, unreliable queue semantics and false SDK classification): 
// Cdecl three raw arguments(a,b,c); forwards respawn_point_select(b,c,a),cleans12 stack bytes,returns delegate EAX. No extra candidate filtering,random sampling or count validation.
// Splitscreen player-entity creation calls this adapter.
int __cdecl rf_respawn_select_reordered_arguments(int a1, float *a2, float *a3)
{
  return rf_respawn_point_select(a2, a3, a1);
}

