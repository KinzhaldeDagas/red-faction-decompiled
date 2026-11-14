// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004D2F10 rf_physics_pair_contact_against_backing_solid
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, pair-contact selection, x87 unordered gates, partial contact writes and bounded near-time contact buckets): Cdecl source,target object pointers. Requires target backing solid660 nonNULL and STRICT ORDERED AABB overlap; no own type3 admission check. If source sphere count388>1, builds face cache for TARGET solid using SOURCE stored bounds400/412 directly (no target-space bounds conversion here). Solid query target current position228/matrix252,flags80=0; seeded fraction=min(existing source460,target460),initializeByte0 preserves bound across spheres and resets count/edge/face per call. Source sphere start=currentOffset rotated by current matrix252 +current position228; direction=predictedOffset rotated by predicted matrix288 +predicted position240-start. Target predicted pose/motion not included in query. Any positive
// count writes source point/normal rotated by target CURRENT matrix,point translated by current target position; fraction460,material464=target508 (not contacted face material),reciprocal468=1/target152,other vector472=target324,UID484=target44,raw material488=DWORD-1,face496=actual result face36,extra500=0. Liquid492 untouched; no normal renormalization/entity2208 vector addition. Unless source type36==2, mirrors point/opposite normal and other metadata into target,with face496/extra500 zero. Always clears global face cache on processed path,even when not built; early NULL-solid/AABB miss returns without clear. No own pointer,scalar reciprocal,finite/index or type validation; AL1 iff any positive-count sweep.
char __cdecl rf_physics_pair_contact_against_backing_solid(float *a1, float *a2)
{
  int first_dword; // eax
  const float *element_address_unchecked; // eax
  const float *v5; // eax
  float *v6; // eax
  float *v7; // eax
  float v8[3]; // [esp+8h] [ebp-148h] BYREF
  float v9[3]; // [esp+14h] [ebp-13Ch] BYREF
  float v10[3]; // [esp+20h] [ebp-130h] BYREF
  char v11[12]; // [esp+2Ch] [ebp-124h] BYREF
  float v12[3]; // [esp+38h] [ebp-118h] BYREF
  float v13[3]; // [esp+44h] [ebp-10Ch] BYREF
  float v14[3]; // [esp+50h] [ebp-100h] BYREF
  float out_vector[3]; // [esp+5Ch] [ebp-F4h] BYREF
  float v16[3]; // [esp+68h] [ebp-E8h] BYREF
  float v17[3]; // [esp+74h] [ebp-DCh] BYREF
  float copy_result[3]; // [esp+80h] [ebp-D0h] BYREF
  int i; // [esp+8Ch] [ebp-C4h]
  float *v20; // [esp+90h] [ebp-C0h]
  char v21[12]; // [esp+94h] [ebp-BCh] BYREF
  char v22[4]; // [esp+A0h] [ebp-B0h] BYREF
  float destination[3]; // [esp+A4h] [ebp-ACh] BYREF
  float v24[9]; // [esp+B0h] [ebp-A0h] BYREF
  float rhs[3]; // [esp+D4h] [ebp-7Ch] BYREF
  float v26[13]; // [esp+E0h] [ebp-70h] BYREF
  int v27; // [esp+114h] [ebp-3Ch] BYREF
  float v28; // [esp+118h] [ebp-38h]
  float v29[3]; // [esp+11Ch] [ebp-34h] BYREF
  float source[5]; // [esp+128h] [ebp-28h] BYREF
  char v31[12]; // [esp+13Ch] [ebp-14h] BYREF
  float *v32; // [esp+148h] [ebp-8h]
  char v33; // [esp+14Fh] [ebp-1h]

  if ( !*((_DWORD *)a2 + 165) )
    return 0;
  rf_vector3_default_construct_noop(v21);
  rf_vector3_default_construct_noop(v31);
  v33 = 0;
  v20 = a1 + 34;
  v32 = a2 + 34;
  if ( !rf_aabb_overlap_strict_ordered(a1 + 100, a1 + 103, a2 + 100, a2 + 103) )
    return 0;
  if ( rf_receiver_get_first_dword(v20 + 63) > 1 )
    rf_collision_face_cache_build(*((_DWORD **)a2 + 165), v20 + 66, v20 + 69, 0);
  rf_solid_collision_query_construct_clear_face_hint(v22);
  rf_solid_collision_result_construct_noop((int)&v27);
  v26[4] = 0.0;
  rf_matrix3_copy(v24, v32 + 29);
  rf_vector_copy(destination, copy_result, v32 + 23);
  v28 = rf_float_minimum_two_values(v20[81], v32[81]);
  for ( i = 0; ; ++i )
  {
    first_dword = rf_receiver_get_first_dword(v20 + 63);
    if ( i >= first_dword )
      break;
    v26[3] = *(float *)(rf_array24_get_element_address_unchecked((_DWORD *)v20 + 63, i) + 12);
    element_address_unchecked = (const float *)rf_array24_get_element_address_unchecked((_DWORD *)v20 + 63, i);
    rf_vector_copy(rhs, v17, element_address_unchecked);
    rf_vector_rotate_by_matrix3(rhs, v20 + 29);
    rf_vector_accumulate(rhs, v20 + 23);
    v5 = (const float *)rf_array24_get_element_address_unchecked((_DWORD *)v20 + 63, i);
    rf_vector_copy(v26, v16, v5);
    rf_vector_rotate_by_matrix3(v26, v20 + 38);
    v6 = rf_vector_subtract(v20 + 26, out_vector, rhs);
    rf_vector_accumulate(v26, v6);
    rf_world_collision_sweep(*((char **)a2 + 165), (int)v22, (int)&v27, 0);
    if ( v27 > 0 )
    {
      v33 = 1;
      v20[81] = v28;
      rf_vector_copy(v20 + 78, v14, source);
      rf_vector_rotate_by_matrix3(v20 + 78, v32 + 29);
      rf_vector_copy(v20 + 75, v13, v29);
      rf_vector_rotate_by_matrix3(v20 + 75, v32 + 29);
      rf_vector_accumulate(v20 + 75, v32 + 23);
      v20[82] = a2[127];
      v20[83] = 1.0 / v32[4];
      rf_vector_copy(v20 + 84, v12, v32 + 47);
      v20[87] = a2[11];
      v20[88] = NAN;
      v20[90] = source[4];
      v20[91] = 0.0;
      if ( *((_DWORD *)a1 + 9) != 2 )
      {
        v32[81] = v20[81];
        v7 = rf_vector_negate(v20 + 78, (float *)v11);
        rf_vector_copy(v32 + 78, v10, v7);
        rf_vector_copy(v32 + 75, v9, v20 + 75);
        v32[82] = a1[127];
        v32[83] = 1.0 / v20[4];
        rf_vector_copy(v32 + 84, v8, v20 + 47);
        v32[87] = a1[11];
        v32[88] = NAN;
        v32[90] = 0.0;
        v32[91] = 0.0;
      }
    }
  }
  rf_collision_face_cache_clear();
  return v33;
}

