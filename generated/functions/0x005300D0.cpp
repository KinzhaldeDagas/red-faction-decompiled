// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005300D0 rf_collision_face_cache_build
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, collision cache/traversal,strict AABBs,face/corner ownership,signed area and reset-on-read pool peaks,original ECX/stack flow and PE bytes): Cdecl solid,queryMin,queryMax,optionalRoom returns global cached count. Reset countD5556C=0 and bypassBYTE D55570=0 first. If authored-room array144.count<1, scan solid face-list112, append strict-overlapping faces via5302B0, stop after bypass. Otherwise optionalRoomnonnull traverses ONLY room.root60, with no roomAABB/sky test. With no explicit room, iterate array156 in order, skip authored-sky rooms, require STRICT ORDERED room bounds8/20 overlap with query, then collect its root60. Root collection setting bypass returns from whole builder. Next scan accepted parent room child-array108, test each child bounds8/20 strictly, collect root; child overflow breaks ONLY child loop, then
// outer room loop can continue until next qualifying root/termination. Child sky flag not separately tested; child bounds considered only after parent admission. No dedup, portal/liquid/face flag admission or query-serial change here. The1024th appended face sets bypass; cache consumers fall back instead of treating the truncated prefix as complete.
int __cdecl rf_collision_face_cache_build(_DWORD *a1, float *a2, float *a3, int a4)
{
  int v5; // [esp+0h] [ebp-14h]
  int j; // [esp+4h] [ebp-10h]
  int v7; // [esp+8h] [ebp-Ch]
  int i; // [esp+Ch] [ebp-8h]
  int k; // [esp+10h] [ebp-4h]

  rf_collision_cached_face_count = 0;
  rf_collision_cache_bypass = 0;
  if ( rf_receiver_get_first_dword(a1 + 36) >= 1 )
  {
    if ( a4 )
    {
      rf_collision_face_cache_collect_tree(*(_DWORD *)(a4 + 60), (int)a2, (int)a3);
    }
    else
    {
      for ( i = 0; i < rf_receiver_get_first_dword(a1 + 39); ++i )
      {
        v7 = *(_DWORD *)sub_552200(a1 + 39, i);
        if ( !rf_room_is_authored_sky((_BYTE *)v7)
          && rf_aabb_overlap_strict_ordered((float *)(v7 + 8), (float *)(v7 + 20), a2, a3) )
        {
          rf_collision_face_cache_collect_tree(*(_DWORD *)(v7 + 60), (int)a2, (int)a3);
          if ( rf_collision_cache_bypass )
            return rf_collision_cached_face_count;
          for ( j = 0; j < rf_receiver_get_first_dword((void *)(v7 + 108)); ++j )
          {
            v5 = *(_DWORD *)sub_552200((_DWORD *)(v7 + 108), j);
            if ( rf_aabb_overlap_strict_ordered((float *)(v5 + 8), (float *)(v5 + 20), a2, a3) )
            {
              rf_collision_face_cache_collect_tree(*(_DWORD *)(v5 + 60), (int)a2, (int)a3);
              if ( rf_collision_cache_bypass )
                break;
            }
          }
        }
      }
    }
  }
  else
  {
    for ( k = rf_receiver_get_first_dword(a1 + 28); k; k = rf_solid_face_next_link(k) )
    {
      rf_collision_face_cache_append_if_overlap(k, a2, a3);
      if ( rf_collision_cache_bypass )
        break;
    }
  }
  return rf_collision_cached_face_count;
}

