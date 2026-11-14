// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00530650 rf_geomod_face_destroy
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, solid/room construction,primitive topology and centering,lightmap wire/preset/marking paths,shared ownership helpers,original ECX/stack ABI and PE bytes): Cdecl face pointer,caller pops4. Calls face decal-polygon removal helper525460 first;walks circular corner list64 using next20 saved BEFORE release. For each corner removes FIRST occurrence of face pointer from vertex incident-face array(vertex+32),then returns corner to pool through corner-release helper. If face node owner72 nonNULL,removes face from node face-list+24;if room owner68 nonNULL,detaches from room list+40. Finally returns raw face-pool release result using shared pool descriptor. This body does not delete vertex records or receive a solid pointer;solid-list removal is explicitly performed by51A090 caller. Does not clear dangling caller references,validate
// pointers/ring,update bounds/tree or allocate replacement geometry. Existing generic ownership note replaced with exact operations.
_DWORD *__cdecl rf_geomod_face_destroy(_DWORD *a1)
{
  _DWORD *v2; // [esp+0h] [ebp-Ch]
  _DWORD *i; // [esp+8h] [ebp-4h]

  rf_geomod_face_decal_polygons_remove(a1);
  for ( i = (_DWORD *)a1[16]; i; i = v2 )
  {
    if ( i[5] == a1[16] )
      v2 = nullptr;
    else
      v2 = (_DWORD *)i[5];
    rf_pointer_array_remove_first((int *)(*i + 32), (int)a1);
    rf_geomod_corner_release((int)i);
  }
  if ( a1[18] )
    rf_geomod_spatial_node_face_list_remove((int *)(a1[18] + 24), (int)a1);
  if ( a1[17] )
    rf_geomod_room_face_detach((int *)(a1[17] + 40), (int)a1);
  return rf_geomod_face_pool_release_raw(rf_geomod_face_pool_descriptor, a1);
}

