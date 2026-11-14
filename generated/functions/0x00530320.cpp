// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00530320 rf_collision_face_cache_collect_tree
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, collision cache/traversal,strict AABBs,face/corner ownership,signed area and reset-on-read pool peaks,original ECX/stack flow and PE bytes): Cdecl root,queryMin,queryMax, unsigned-byte residue return. NULL root skips. Fixed1024-DWORD local DFS stack; root is pushed WITHOUT testing its AABB. For each popped node increment diagnosticD55560, process face-list24 in order via5302B0; if bypassBYTE becomes/nonzero, return immediately with last append AL. Then test child32 AABB0/12 strictly through48BE10 before push, followed by child36 (visited first); current-node faces precede child traversal. No stack bound, node dedup, root-bound test or early existing-bypass check before first face. Face duplicates can fill cache; no flags/portal/room eligibility filter. Return last helper/pointer/local-constructor AL, not hit boolean or
// count.
unsigned __int8 __cdecl rf_collision_face_cache_collect_tree(int a1, float *a2, float *a3)
{
  unsigned __int8 result; // al
  float **v4; // [esp+0h] [ebp-1030h]
  int i; // [esp+4h] [ebp-102Ch]
  _BYTE v6[12]; // [esp+8h] [ebp-1028h] BYREF
  int v7; // [esp+14h] [ebp-101Ch]
  _DWORD v8[1024]; // [esp+18h] [ebp-1018h]
  _BYTE v9[12]; // [esp+1018h] [ebp-18h] BYREF
  _BYTE v10[12]; // [esp+1024h] [ebp-Ch] BYREF

  rf_vector3_default_construct_noop(v9);
  rf_vector3_default_construct_noop(v6);
  result = (unsigned __int8)rf_vector3_default_construct_noop(v10);
  v7 = 0;
  if ( a1 )
  {
    result = v7;
    v8[v7++] = a1;
    while ( v7 > 0 )
    {
      v4 = (float **)v8[--v7];
      ++unk_D55560;
      for ( i = rf_receiver_get_first_dword(v4 + 6); i; i = rf_face_next_spatial_node_link(i) )
      {
        result = rf_collision_face_cache_append_if_overlap(i, a2, a3);
        if ( rf_collision_cache_bypass )
          return result;
      }
      if ( v4[8] && rf_aabb_overlap_strict_ordered(v4[8], v4[8] + 3, a2, a3) )
        v8[v7++] = v4[8];
      result = (unsigned __int8)v4;
      if ( v4[9] )
      {
        result = rf_aabb_overlap_strict_ordered(v4[9], v4[9] + 3, a2, a3);
        if ( result )
        {
          result = (unsigned __int8)v4;
          v8[v7++] = v4[9];
        }
      }
    }
  }
  return result;
}

