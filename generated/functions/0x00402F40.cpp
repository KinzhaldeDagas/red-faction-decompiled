// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00402F40 rf_ai_maybe_seek_ammo_waypoints
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI movement-state/route/association/reaction chains, independently reviewed native branches and original
// float/dispatch constants and native signed/x87/stack/callback ABI): One AI block. Requires any-nonzero runtime/splitscreen, signed primary DWORD+4>=0, and flags+1328 mask0x800000
// clear. Weapon record stride1360: signed ammo-pool index from912024+1360*weapon, signed threshold from912088+1360*weapon divided by3 using truncating SIGNED IDIV. Signed loaded
// counter AI+140+4*poolIndex must be STRICTLY below threshold; then consumes rand(), signed result<511 delegates402B20(block) to ammo-prefixed waypoint search. No upper weapon bound
// or negative/upper pool-index guard, no reserve comparison, no direct ammo change, no clamping negative threshold. Return EAX incidental.
int __cdecl rf_ai_maybe_seek_ammo_waypoints(int Character)
{
  int result; // eax
  int v2; // [esp+4h] [ebp-4h]

  result = rf_multiplayer_runtime_mode;
  if ( rf_multiplayer_runtime_mode || rf_splitscreen_runtime_active )
  {
    result = *(_DWORD *)(Character + 4);
    v2 = result;
    if ( result >= 0 && ((unsigned int)&unk_800000 & *(_DWORD *)(Character + 1328)) == 0 )
    {
      result = unk_912088[340 * result] / 3;
      if ( *(_DWORD *)(Character + 4 * dword_912024[340 * v2] + 140) < result )
      {
        result = rand();
        if ( result < 511 )
          return rf_ai_seek_ammo_waypoint_list(Character);
      }
    }
  }
  return result;
}

