// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004D27A0 rf_physics_pair_contact_against_model
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, pair-contact selection, x87 unordered gates, partial contact writes and bounded near-time contact buckets): Cdecl source,target object pointers; STRICT ORDERED AABB gate. Physics P=object+136. Either flags424 mask0x400: writes ONLY source fraction460=0,reciprocal468=1/target152,UID484=target44,returns1. Computes minimum existing fraction460 via native minimum helper. If target UID44 resolves entity, predicate43BFA0 succeeds, and source type36==2: queries source current..predicted center against sphere radius1 at target CURRENT center, writing directly to source contact point436. This special helper can report1 while copying start for an out-of-segment entry; zero-length failure also copies start, so AL0 can mutate point. Special-query miss returns0 WITHOUT model fallback. Success sets
// fraction=distance(current,hit)/motionLength only when source radius384<motionLength OR unordered,otherwise0; does not enforce old minimum. Normal=uncheckedNormalize(hit-current),not target radial normal; copies target vector324,UID44,material508,raw488=-1,face496/extra500=0,reciprocal468=1; liquid492 untouched, no mirror. General model path: query identity pose,zero position,flags76=2,result fraction1,initializeByte0 shared across spheres. Current/predicted source sphere offsets and relative source-target positions transformed through corresponding target current/predicted matrices. Only ORDERED minOldFraction>model fraction accepts. Writes source point=target CURRENT matrix*localHit+targetCurrentPosition+(targetPredicted-targetCurrentPosition)*t; normal rotated by target CURRENT matrix without extra normalization. Material464=target508,reciprocal468=1/target152,other
// vector472=target324,UID484=target44,raw488=-1,face496=0,extra500=raw model result28,liquid492 untouched. Mirrors point/opposite normal/metadata into target only if ORDERED target152<2*source152 OR target use-classification==1; unordered scalar requires classification path. No own model-kind/NULL/index/finite guards,entity2208 velocity addition or time/orientation interpolation beyond stated operations.
char __cdecl rf_physics_pair_contact_against_model(float *a1, float *a2)
{
  float *v3; // eax
  int first_dword; // eax
  const float *element_address_unchecked; // eax
  float *v6; // eax
  const float *v7; // eax
  float *v8; // eax
  float *v9; // eax
  float *v10; // eax
  float *v11; // eax
  float *v12; // eax
  float v13[3]; // [esp+8h] [ebp-1B0h] BYREF
  float v14[3]; // [esp+14h] [ebp-1A4h] BYREF
  float v15[3]; // [esp+20h] [ebp-198h] BYREF
  char v16[12]; // [esp+2Ch] [ebp-18Ch] BYREF
  float v17[3]; // [esp+38h] [ebp-180h] BYREF
  float sum_result[3]; // [esp+44h] [ebp-174h] BYREF
  float scaled_result[3]; // [esp+50h] [ebp-168h] BYREF
  float v20[3]; // [esp+5Ch] [ebp-15Ch] BYREF
  float v21[3]; // [esp+68h] [ebp-150h] BYREF
  float v22[3]; // [esp+74h] [ebp-144h] BYREF
  float v23[3]; // [esp+80h] [ebp-138h] BYREF
  float v24[3]; // [esp+8Ch] [ebp-12Ch] BYREF
  float v25[3]; // [esp+98h] [ebp-120h] BYREF
  float v26[3]; // [esp+A4h] [ebp-114h] BYREF
  float v27[3]; // [esp+B0h] [ebp-108h] BYREF
  float v28[3]; // [esp+BCh] [ebp-FCh] BYREF
  float v29[3]; // [esp+C8h] [ebp-F0h] BYREF
  float copy_result[3]; // [esp+D4h] [ebp-E4h] BYREF
  float out_vector[3]; // [esp+E0h] [ebp-D8h] BYREF
  int i; // [esp+ECh] [ebp-CCh]
  float v33; // [esp+F0h] [ebp-C8h]
  float *v34; // [esp+F4h] [ebp-C4h]
  float v35; // [esp+F8h] [ebp-C0h]
  int v36; // [esp+FCh] [ebp-BCh]
  float rhs[3]; // [esp+100h] [ebp-B8h] BYREF
  char v38; // [esp+10Fh] [ebp-A9h]
  float v39[3]; // [esp+110h] [ebp-A8h] BYREF
  char v40[36]; // [esp+11Ch] [ebp-9Ch] BYREF
  float destination[3]; // [esp+140h] [ebp-78h] BYREF
  float v42[11]; // [esp+14Ch] [ebp-6Ch] BYREF
  float *v43; // [esp+178h] [ebp-40h]
  float scalar; // [esp+17Ch] [ebp-3Ch] BYREF
  float v45[3]; // [esp+180h] [ebp-38h] BYREF
  float source[4]; // [esp+18Ch] [ebp-2Ch] BYREF
  float vector[3]; // [esp+19Ch] [ebp-1Ch] BYREF
  float lhs[3]; // [esp+1A8h] [ebp-10h] BYREF
  char v49; // [esp+1B7h] [ebp-1h]

  rf_vector3_default_construct_noop(rhs);
  rf_vector3_default_construct_noop(lhs);
  v49 = 0;
  v38 = 0;
  v34 = a1 + 34;
  v43 = a2 + 34;
  if ( !rf_aabb_overlap_strict_ordered(a1 + 100, a1 + 103, a2 + 100, a2 + 103) )
    return 0;
  if ( ((_DWORD)v34[72] & 0x400) != 0 || ((_DWORD)v43[72] & 0x400) != 0 )
  {
    v34[83] = 1.0 / v43[4];
    v34[87] = a2[11];
    v34[81] = 0.0;
    return 1;
  }
  else
  {
    v35 = rf_float_minimum_two_values(v34[81], v43[81]);
    v36 = rf_entity_resolve_handle(*((_DWORD *)a2 + 11));
    if ( v36 && rf_entity_class_flag2000000_positive_scalar56(v36) && *((_DWORD *)a1 + 9) == 2 )
    {
      if ( rf_segment_sphere_intersection((int)(v34 + 75), (int)(v34 + 23), (int)(v34 + 26), (int)(v43 + 23), 1.0) )
      {
        v33 = rf_vector_distance(v34 + 23, v34 + 26);
        if ( v34[62] < (double)v33 )
          v34[81] = rf_vector_distance(v34 + 23, v34 + 75) / v33;
        else
          v34[81] = 0.0;
        v3 = rf_vector_subtract(v34 + 75, out_vector, v34 + 23);
        rf_vector_copy(v34 + 78, copy_result, v3);
        rf_vector_normalize_reciprocal_sqrt(v34 + 78);
        rf_vector_copy(v34 + 84, v29, v43 + 47);
        v34[87] = a2[11];
        v34[88] = NAN;
        v34[82] = a2[127];
        v34[90] = 0.0;
        v34[91] = 0.0;
        v34[83] = 1.0;
        return 1;
      }
      else
      {
        return 0;
      }
    }
    else
    {
      rf_model_collision_query_construct_noop((char *)v39);
      rf_model_collision_result_construct_noop((int)&scalar);
      rf_vector_subtract(v43 + 26, vector, v43 + 23);
      LODWORD(v42[4]) = 2;
      rf_identity_orientation_matrix((float *)v40);
      rf_vector3_zero_return_destination(v39);
      scalar = 1.0;
      for ( i = 0; ; ++i )
      {
        first_dword = rf_receiver_get_first_dword(v34 + 63);
        if ( i >= first_dword )
          break;
        v42[3] = *(float *)(rf_array24_get_element_address_unchecked((_DWORD *)v34 + 63, i) + 12);
        element_address_unchecked = (const float *)rf_array24_get_element_address_unchecked((_DWORD *)v34 + 63, i);
        rf_vector_copy(rhs, v28, element_address_unchecked);
        rf_vector_rotate_by_matrix3(rhs, v34 + 29);
        v6 = rf_vector_subtract(v34 + 23, v27, v43 + 23);
        rf_vector_accumulate(rhs, v6);
        rf_matrix3_inverse_rotate_vector(rhs, v43 + 29);
        rf_vector_copy(destination, v26, rhs);
        v7 = (const float *)rf_array24_get_element_address_unchecked((_DWORD *)v34 + 63, i);
        rf_vector_copy(lhs, v25, v7);
        rf_vector_rotate_by_matrix3(lhs, v34 + 38);
        v8 = rf_vector_subtract(v34 + 26, v24, v43 + 26);
        rf_vector_accumulate(lhs, v8);
        rf_matrix3_inverse_rotate_vector(lhs, v43 + 38);
        v9 = rf_vector_subtract(lhs, v23, rhs);
        rf_vector_copy(v42, v22, v9);
        if ( rf_model_handle_collide_all_adapter(*((_DWORD **)a2 + 32), (int)v39, (int)&scalar, 0) )
        {
          if ( v35 > (double)scalar )
          {
            v35 = scalar;
            v49 = 1;
            v34[81] = scalar;
            rf_vector_copy(v34 + 78, v21, source);
            rf_vector_rotate_by_matrix3(v34 + 78, v43 + 29);
            rf_vector_copy(v34 + 75, v20, v45);
            rf_vector_rotate_by_matrix3(v34 + 75, v43 + 29);
            v10 = rf_vector_multiply_scalar(vector, scaled_result, scalar);
            v11 = rf_vector_add(v43 + 23, sum_result, v10);
            rf_vector_accumulate(v34 + 75, v11);
            v34[82] = a2[127];
            v34[83] = 1.0 / v43[4];
            rf_vector_copy(v34 + 84, v17, v43 + 47);
            v34[87] = a2[11];
            v34[88] = NAN;
            v34[90] = 0.0;
            v34[91] = source[3];
            if ( v43[4] < v34[4] + v34[4] || rf_object_get_use_classification(a2) == 1 )
            {
              v43[81] = v34[81];
              v12 = rf_vector_negate(v34 + 78, (float *)v16);
              rf_vector_copy(v43 + 78, v15, v12);
              rf_vector_copy(v43 + 75, v14, v34 + 75);
              v43[82] = a1[127];
              v43[83] = 1.0 / v34[4];
              rf_vector_copy(v43 + 84, v13, v34 + 47);
              v43[87] = a1[11];
              v43[88] = NAN;
              v43[90] = 0.0;
              v43[91] = 0.0;
            }
          }
        }
      }
      return v49;
    }
  }
}

