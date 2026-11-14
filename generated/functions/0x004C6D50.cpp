// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004C6D50 rf_glass_shard_cross_solid_transition
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, persistent shard pool and keyed buckets, launch-delay/damage cadence, first-hit face traversal, native ordered branches and settling ownership): 
// Cdecl(shard,contactFace), canonical ALbool. Portal index helper4CA7C0 called with receiver=face+40 metadata; reads signed16 metadata+12 (overall face52), value<2 ->-1,else value-2.
// Negative index rejects. Otherwise dereferences worldSolid pointer-array180[index] unchecked, reads two owner endpoints at0/4. If first==shard.room104, moves to second; else if
// second==current moves first; neitherfalse. First endpoint has priority even if both equal; same-owner transition still unlink/relinks and returns1. No upper
// index/pair/destinationNULL validation or geometric side test; move return ignored. Owner/bucket mutation precedes recursive sweep and is not rolled back on later failure.
char __cdecl rf_glass_shard_cross_solid_transition(_DWORD *a1, int a2)
{
  int *v3; // [esp+0h] [ebp-8h]
  int v4; // [esp+4h] [ebp-4h]

  v4 = rf_face_metadata_portal_index_signed16((__int16 *)(a2 + 40));
  if ( v4 <= -1 )
    return 0;
  v3 = *(int **)sub_552200((_DWORD *)(rf_world_solid + 180), v4);
  if ( *v3 == a1[26] )
  {
    rf_glass_shard_move_bucket(a1, v3[1]);
  }
  else
  {
    if ( v3[1] != a1[26] )
      return 0;
    rf_glass_shard_move_bucket(a1, *v3);
  }
  return 1;
}

