// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00525460 rf_geomod_face_decal_polygons_remove
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, decal polygon ownership/pools,receiver registries,light-space transforms and coverage,original ECX/stack flow and PE bytes): Cdecl face. Iterate face76 decal polygons through1328, saved before any release. Read owner decal1316. Owner flags80&0x400 skips polygon COMPLETELY: no ring unlink, pool release or count decrement for it. Others unlink from owner circular polygon ring1320/1324 (head212 advances or becomesNULL for sole polygon), clear ring links, return1332-byte polygon to pool525D90, decrement owner count216, recycle decal only if count becomes EXACT0. Regardless of skipped protected polygons, final535B10 clears face head76 and metadata bits0x100000/0x200000; skipped polygon may still have owner/face reference. Does not walk spatial leaves or modify face spatial owner72 / node list24, nor solid/room links. Return
// same face pointer through final helper. No free of face/corners here. Earlier spatial-backlink naming/comments were incorrect; separate530650 performs actual node/room detachment.
_DWORD *__cdecl rf_geomod_face_decal_polygons_remove(_DWORD *a1)
{
  _DWORD *v2; // [esp+8h] [ebp-Ch]
  _DWORD *v3; // [esp+Ch] [ebp-8h]
  _DWORD *i; // [esp+10h] [ebp-4h]

  for ( i = (_DWORD *)a1[19]; i; i = v2 )
  {
    v2 = (_DWORD *)i[332];
    v3 = (_DWORD *)i[329];
    if ( (v3[20] & 0x400) != 0 )
      continue;
    if ( (_DWORD *)v3[53] == i )
    {
      if ( (_DWORD *)i[330] == i )
      {
        i[330] = 0;
        i[331] = 0;
        v3[53] = 0;
        goto LABEL_9;
      }
      v3[53] = i[330];
    }
    *(_DWORD *)(i[331] + 1320) = i[330];
    *(_DWORD *)(i[330] + 1324) = i[331];
    i[330] = 0;
    i[331] = 0;
LABEL_9:
    rf_decal_polygon_pool_release(dword_A70648, i);
    if ( !--v3[54] )
      rf_world_decal_remove_spatial_links_and_recycle(v3);
  }
  return rf_geomod_face_clear_decal_polygon_state(a1);
}

