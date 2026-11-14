// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004B7C00 rf_point_nearest_live_player_distance_float
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, object lifetime/free-slot/attachment/render chains, original dispatch tables and field widths and native
// signed/x87/stack/callback ABI): One cdecl candidate-position pointer (caller4B98B0 passes object+60, not the object base). Calls respawn-point safety score with exactly three stack
// arguments (NULL, candidate, NULL). Rounds returned x87 value through a four-byte local FSTP and reloads it to ST0; no clamp or extra distance filtering. The local is initially
// zeroed but overwritten by the score. Preserve the explicit float32 rounding even though stored prototype reports double.
double __cdecl rf_point_nearest_live_player_distance_float(float *a1)
{
  return (float)rf_respawn_point_safety_score(nullptr, a1, nullptr);
}

