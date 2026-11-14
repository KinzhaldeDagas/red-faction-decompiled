// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0054CF00 rf_solid_mark_lightmaps_near_point
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, solid/room construction,primitive topology and centering,lightmap wire/preset/marking paths,shared ownership helpers,original ECX/stack ABI and PE bytes): Thiscall solid,point3f pointer,margin float,RET8. Only proceeds when second DWORD of face-list object(solid+116) is nonzero. If room-array header144 count>=1,walks every room pointer and calls tree marker54D0C0 with room+60 root;otherwise walks flat face head112 via existing face-next helper and calls54CFF0. No transform of point,clearing descriptor flags,early exit on first match or direct lighting/upload. Return kept int: EAX ordinarily0 for no-face/flat path or final room-array count for room path;not a hit count/predicate. External unrecognized wrapper4798CA merely forwards register residue at epilogue. Parameter corrected from false integer point to pointer;no
// unproved void narrowing of outer return.
int __thiscall rf_solid_mark_lightmaps_near_point(void *solid, const float *query_point, float margin)
{
  int result; // eax
  int v4; // eax
  int i; // [esp+14h] [ebp-8h]
  void *face; // [esp+18h] [ebp-4h]

  result = rf_shared_second_dword_getter_518050((_DWORD *)solid + 28);
  if ( result )
  {
    if ( rf_receiver_get_first_dword((char *)solid + 144) >= 1 )
    {
      for ( i = 0; ; ++i )
      {
        result = rf_receiver_get_first_dword((char *)solid + 144);
        if ( i >= result )
          break;
        v4 = sub_552200((_DWORD *)solid + 36, i);
        rf_solid_mark_tree_lightmaps_near_point(query_point, margin, solid, *(void **)(*(_DWORD *)v4 + 60));
      }
    }
    else
    {
      result = rf_receiver_get_first_dword((char *)solid + 112);
      for ( face = (void *)result; face; face = (void *)result )
      {
        rf_solid_mark_face_lightmap_near_point(query_point, margin, solid, face);
        result = rf_solid_face_next_link((int)face);
      }
    }
  }
  return result;
}

