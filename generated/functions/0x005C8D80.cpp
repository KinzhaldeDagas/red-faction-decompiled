// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C8D80 rf_plane_classify_point_offset_epsilon
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, input remapping,text wrapping,Bink playback/default records,archive metadata,projection/aperture/classification and glass submission): Cdecl plane*,point*,offset float,caller pops12 bytes. Stores signed plane distance to float local. Returns1 for ORDERED distance>offset+double epsilon;otherwise returns3 for ordered distance>=offset-epsilon OR UNORDERED;else2. Epsilon literals are double +/-0.00009999999747378752. Upper/lower equality both classify3. Raw5C8DBF TEST AH,5/JP admits unordered as3,so NaN in distance/offset is NOT rejected despite decompiled >= expression. Threshold addition occurs in x87 without a float-store before compare. No absolute-distance test,normal normalization,pointer validation or side effects besides local stack.
int __cdecl rf_plane_classify_point_offset_epsilon(float *a1, float *a2, float a3)
{
  float v4; // [esp+0h] [ebp-4h]

  v4 = rf_plane_point_signed_distance(a1, a2);
  if ( v4 > a3 + 0.00009999999747378752 )
    return 1;
  if ( v4 >= a3 + -0.00009999999747378752 )
    return 3;
  return 2;
}

