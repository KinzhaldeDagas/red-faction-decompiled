// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005251A0 rf_geomod_face_decal_polygons_replace_after_split
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, decal polygon ownership/pools,receiver registries,light-space transforms and coverage,original ECX/stack flow and PE bytes): Cdecl oldFace,replacementFacePointerArray,signedCount. Face76 is singly linked DECAL POLYGON head, not spatial AABB leaves. Iterate polygons using nextFace1328 saved BEFORE pool release. Owner decal pointer1316, per-decal circular next1320/prev1324, head atdecal212 and count216. Unlink polygon from owner ring (advance owner head if needed; sole head clears head and links); pool-release1332-byte polygon via525D90 then decrement owner.count216. For every nonNULL replacement in index0..count-1 call5230F0(owner,replacement,byte1) to reclip/attach, which suppresses duplicate owner polygons already on that replacement face. Existing polygon survival does not simply transfer old clipped vertices. If
// owner count still0 after all replacements, recycle whole decal. After original face-chain iteration call535B10 to clear oldFace76 and flags0x100000/0x200000; return oldFace pointer. No flag0x400 exemption in this variant, no AABB-tree node removal, no room/solid-face ownership change or replacement bounds update. count<=0 leads to removal without replacement. Saved face-chain order preserved; relies on pool not invalidating owner/next before saved use.
_DWORD *__cdecl rf_geomod_face_decal_polygons_replace_after_split(_DWORD *a1, int a2, int a3)
{
  _DWORD *v4; // [esp+8h] [ebp-10h]
  _DWORD *v5; // [esp+Ch] [ebp-Ch]
  _DWORD *i; // [esp+10h] [ebp-8h]
  int j; // [esp+14h] [ebp-4h]

  for ( i = (_DWORD *)a1[19]; i; i = v4 )
  {
    v4 = (_DWORD *)i[332];
    v5 = (_DWORD *)i[329];
    if ( (_DWORD *)v5[53] != i )
      goto LABEL_7;
    if ( (_DWORD *)i[330] != i )
    {
      v5[53] = i[330];
LABEL_7:
      *(_DWORD *)(i[331] + 1320) = i[330];
      *(_DWORD *)(i[330] + 1324) = i[331];
      i[330] = 0;
      i[331] = 0;
      goto LABEL_8;
    }
    i[330] = 0;
    i[331] = 0;
    v5[53] = 0;
LABEL_8:
    rf_decal_polygon_pool_release(dword_A70648, i);
    --v5[54];
    for ( j = 0; j < a3; ++j )
    {
      if ( *(_DWORD *)(a2 + 4 * j) )
        rf_world_decal_clip_and_attach_face_polygon((int)v5, *(_DWORD *)(a2 + 4 * j), 1);
    }
    if ( !v5[54] )
      rf_world_decal_remove_spatial_links_and_recycle(v5);
  }
  return rf_geomod_face_clear_decal_polygon_state(a1);
}

