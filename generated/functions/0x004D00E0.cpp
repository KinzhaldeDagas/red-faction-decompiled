// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004D00E0 rf_solid_face_list_segment_nearest_hit
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, shape-sphere/model/solid sweeps, x87 unordered gates, descriptor constructors and native output mutation): Cdecl solid,ray6(start0,direction12),INOUT endpoint vector,INOUT solid result(count0,fraction4,point8,normal20,face36). Traverses solid face container112 through head getter and next-link helper. Each face: segment-AABB admission against face bounds16/28 with CURRENT endpoint; front-side plane helper yields fraction, then only ORDERED current bound>candidate proceeds (equal/NaN rejected). Writes candidate point=start+direction*fraction to result8 BEFORE projected polygon containment check. Rejected polygon therefore can clobber result point even when function returns0 or an earlier accepted hit remains in fraction/normal/face. Accepted polygon copies face normal0 to result20, fraction to4, face pointer to36, sets
// hit flag and clips endpoint to result point. Continues all faces, no first-hit return. Does NOT initialize count/fraction, increment count0, filter material/face flags or normalize normal. No pointer/list-integrity or alias guard.
char __cdecl rf_solid_face_list_segment_nearest_hit(int a1, float *lhs, float *destination, int a4)
{
  float *v4; // eax
  float *v5; // eax
  float v7[3]; // [esp+4h] [ebp-54h] BYREF
  float v8[3]; // [esp+10h] [ebp-48h] BYREF
  float copy_result[3]; // [esp+1Ch] [ebp-3Ch] BYREF
  float sum_result[3]; // [esp+28h] [ebp-30h] BYREF
  float scaled_result[3]; // [esp+34h] [ebp-24h] BYREF
  float scalar; // [esp+40h] [ebp-18h] BYREF
  char v13; // [esp+47h] [ebp-11h]
  float *source; // [esp+48h] [ebp-10h]
  float v15[3]; // [esp+4Ch] [ebp-Ch] BYREF

  v13 = 0;
  rf_vector3_default_construct_noop(v15);
  for ( source = (float *)rf_receiver_get_first_dword((void *)(a1 + 112));
        source;
        source = (float *)rf_solid_face_next_link((int)source) )
  {
    if ( rf_segment_intersects_aabb(source + 4, source + 7, lhs, destination, v15)
      && rf_segment_plane_front_side_hit_fraction(lhs, lhs + 3, source, &scalar)
      && *(float *)(a4 + 4) > (double)scalar )
    {
      v4 = rf_vector_multiply_scalar(lhs + 3, scaled_result, scalar);
      v5 = rf_vector_add(lhs, sum_result, v4);
      rf_vector_copy((float *)(a4 + 8), copy_result, v5);
      if ( rf_geomod_face_contains_projected_point(source, a4 + 8) )
      {
        rf_vector_copy((float *)(a4 + 20), v8, source);
        *(float *)(a4 + 4) = scalar;
        *(_DWORD *)(a4 + 36) = source;
        v13 = 1;
        rf_vector_copy(destination, v7, (const float *)(a4 + 8));
      }
    }
  }
  return v13;
}

