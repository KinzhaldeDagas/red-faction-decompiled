// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004D0B80 rf_physics_shape_sweep_spheres_against_shape
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, shape-sphere/model/solid sweeps, x87 unordered gates, descriptor constructors and native output mutation): Cdecl moving start,end,moving physics shape,target physics shape,INOUT68-byte physics hit. Both shape collections252 use signed count and24-byte records(center0,radius12), bases+8; matrices116, target origin92. For each moving sphere: rotate offset by moving matrix, compute world start center and world displacement via separate vector operations; translate endpoints relative to target origin and inverse-rotate into target matrix. Contiguous local ray at EBP-28h is start3 plus direction3 at-1Ch; only ORDERED float displacement length>0 is normalized and tested, so stationary/NaN motion skips pairs. For each target sphere call unit-direction sphere helper(outLocalPoint,outFraction,ray6,length,target center,float(sum
// radii)). Helper success any nonzero; fraction exactly ordered0 additionally requires dot(unitDirection,targetCenter-hitPoint)>=0 OR unordered. Then rejects negative OR unordered fraction, and requires ORDERED old hit fraction24>candidate. Copies UNNORMALIZED local radial normal(hitPoint-targetCenter) into caller normal12 BEFORE final admission. Final dot(radialNormal,unitDirection)<double-0.5 OR unordered accepts; threshold is NOT a normalized angular cosine. Rejected candidate can overwrite normal even after an earlier accepted hit, leaving old point/fraction paired with new local,unnormalized normal. Accepted: hit flag1, fraction24=candidate; recompute radial normal, unchecked-normalize then rotate by target matrix; contact point=world moving-sphere start+world displacement*candidate-world normal*moving radius. Clears DWORD60/64 only; other material/velocity/UID/liquid metadata
// untouched. Bound persists across pairs, no own upper1/finite/NULL/radius/index validation. ReturnsAL1 iff any pair accepted, not a guarantee all result fields stayed coherent.
char __cdecl rf_physics_shape_sweep_spheres_against_shape(float *lhs, float *a2, int a3, int a4, float *a5)
{
  float *v5; // eax
  float *v6; // eax
  int first_dword; // eax
  const float *element_address_unchecked; // eax
  float *v9; // eax
  const float *v10; // eax
  float *v11; // eax
  float *v12; // eax
  float *v13; // eax
  int v14; // eax
  int v15; // esi
  int v16; // eax
  const float *v17; // eax
  float *v18; // eax
  const float *v19; // eax
  float *v20; // eax
  const float *v21; // eax
  float *v22; // eax
  int v23; // eax
  float *v24; // eax
  float *v25; // eax
  float *v26; // eax
  float *scalar; // [esp+8h] [ebp-188h]
  float v29; // [esp+10h] [ebp-180h]
  float v30[3]; // [esp+14h] [ebp-17Ch] BYREF
  float v31[3]; // [esp+20h] [ebp-170h] BYREF
  float scaled_result[3]; // [esp+2Ch] [ebp-164h] BYREF
  float v33[3]; // [esp+38h] [ebp-158h] BYREF
  float v34[3]; // [esp+44h] [ebp-14Ch] BYREF
  float v35[3]; // [esp+50h] [ebp-140h] BYREF
  float v36[3]; // [esp+5Ch] [ebp-134h] BYREF
  float v37[3]; // [esp+68h] [ebp-128h] BYREF
  float v38[3]; // [esp+74h] [ebp-11Ch] BYREF
  float v39[3]; // [esp+80h] [ebp-110h] BYREF
  float v40[3]; // [esp+8Ch] [ebp-104h] BYREF
  float v41[3]; // [esp+98h] [ebp-F8h] BYREF
  float v42[3]; // [esp+A4h] [ebp-ECh] BYREF
  float v43[3]; // [esp+B0h] [ebp-E0h] BYREF
  float v44[3]; // [esp+BCh] [ebp-D4h] BYREF
  float v45[3]; // [esp+C8h] [ebp-C8h] BYREF
  float v46[3]; // [esp+D4h] [ebp-BCh] BYREF
  float sum_result[3]; // [esp+E0h] [ebp-B0h] BYREF
  float v48[3]; // [esp+ECh] [ebp-A4h] BYREF
  float v49[3]; // [esp+F8h] [ebp-98h] BYREF
  float v50[3]; // [esp+104h] [ebp-8Ch] BYREF
  float copy_result[3]; // [esp+110h] [ebp-80h] BYREF
  float out_vector[3]; // [esp+11Ch] [ebp-74h] BYREF
  int j; // [esp+128h] [ebp-68h]
  float v54[3]; // [esp+12Ch] [ebp-64h] BYREF
  float vector[3]; // [esp+138h] [ebp-58h] BYREF
  float destination[3]; // [esp+144h] [ebp-4Ch] BYREF
  float v57; // [esp+150h] [ebp-40h]
  int v58; // [esp+154h] [ebp-3Ch] BYREF
  int i; // [esp+158h] [ebp-38h]
  float v60[3]; // [esp+15Ch] [ebp-34h] BYREF
  float v61[3]; // [esp+168h] [ebp-28h] BYREF
  float v62[3]; // [esp+174h] [ebp-1Ch] BYREF
  float rhs[3]; // [esp+180h] [ebp-10h] BYREF
  char v64; // [esp+18Fh] [ebp-1h]

  rf_vector3_default_construct_noop(v54);
  rf_vector3_default_construct_noop(rhs);
  rf_vector3_default_construct_noop(vector);
  rf_vector3_default_construct_noop(destination);
  rf_vector3_default_construct_noop(v60);
  rf_force_sample44_construct_vectors_noop((char *)v61);
  v64 = 0;
  v5 = rf_vector_subtract(lhs, out_vector, (const float *)(a4 + 92));
  rf_vector_copy(destination, copy_result, v5);
  v6 = rf_vector_subtract(a2, v50, (const float *)(a4 + 92));
  rf_vector_copy(v60, v49, v6);
  for ( i = 0; ; ++i )
  {
    first_dword = rf_receiver_get_first_dword((void *)(a3 + 252));
    if ( i >= first_dword )
      break;
    element_address_unchecked = (const float *)rf_array24_get_element_address_unchecked((_DWORD *)(a3 + 252), i);
    rf_vector_copy(v61, v48, element_address_unchecked);
    rf_vector_rotate_by_matrix3(v61, (float *)(a3 + 116));
    v9 = rf_vector_add(v61, sum_result, lhs);
    rf_vector_copy(rhs, v46, v9);
    rf_vector_accumulate(v61, destination);
    rf_matrix3_inverse_rotate_vector(v61, (float *)(a4 + 116));
    v10 = (const float *)rf_array24_get_element_address_unchecked((_DWORD *)(a3 + 252), i);
    rf_vector_copy(v54, v45, v10);
    rf_vector_rotate_by_matrix3(v54, (float *)(a3 + 116));
    v11 = rf_vector_add(v54, v44, a2);
    v12 = rf_vector_subtract(v11, v43, rhs);
    rf_vector_copy(vector, v42, v12);
    rf_vector_accumulate(v54, v60);
    rf_matrix3_inverse_rotate_vector(v54, (float *)(a4 + 116));
    v13 = rf_vector_subtract(v54, v41, v61);
    rf_vector_copy(v62, v40, v13);
    v57 = rf_vector3_length(v62);
    if ( v57 > 0.0 )
    {
      rf_vector3_divide_in_place_reciprocal(v62, v57);
      for ( j = 0; ; ++j )
      {
        v14 = rf_receiver_get_first_dword((void *)(a4 + 252));
        if ( j >= v14 )
          break;
        v15 = rf_array24_get_element_address_unchecked((_DWORD *)(a4 + 252), j);
        v29 = *(float *)(v15 + 12) + *(float *)(rf_array24_get_element_address_unchecked((_DWORD *)(a3 + 252), i) + 12);
        v16 = rf_array24_get_element_address_unchecked((_DWORD *)(a4 + 252), j);
        if ( rf_unit_direction_segment_sphere_hit_fraction((int)v54, (float *)&v58, (int)v61, v57, v16, v29) )
        {
          if ( *(float *)&v58 != 0.0
            || (v17 = (const float *)rf_array24_get_element_address_unchecked((_DWORD *)(a4 + 252), j),
                v18 = rf_vector_subtract(v17, v39, v54),
                rf_vector_dot(v62, v18) >= 0.0) )
          {
            if ( *(float *)&v58 >= 0.0 && a5[6] > (double)*(float *)&v58 )
            {
              v19 = (const float *)rf_array24_get_element_address_unchecked((_DWORD *)(a4 + 252), j);
              v20 = rf_vector_subtract(v54, v38, v19);
              rf_vector_copy(a5 + 3, v37, v20);
              if ( rf_vector_dot(a5 + 3, v62) < -0.5 )
              {
                v64 = 1;
                a5[6] = *(float *)&v58;
                v21 = (const float *)rf_array24_get_element_address_unchecked((_DWORD *)(a4 + 252), j);
                v22 = rf_vector_subtract(v54, v36, v21);
                rf_vector_copy(a5 + 3, v35, v22);
                rf_vector_normalize_reciprocal_sqrt(a5 + 3);
                rf_vector_rotate_by_matrix3(a5 + 3, (float *)(a4 + 116));
                v23 = rf_array24_get_element_address_unchecked((_DWORD *)(a3 + 252), i);
                scalar = rf_vector_multiply_scalar(a5 + 3, scaled_result, *(float *)(v23 + 12));
                v24 = rf_vector_multiply_scalar(vector, v34, *(float *)&v58);
                v25 = rf_vector_add(rhs, v33, v24);
                v26 = rf_vector_subtract(v25, v31, scalar);
                rf_vector_copy(a5, v30, v26);
                a5[15] = 0.0;
                a5[16] = 0.0;
              }
            }
          }
        }
      }
    }
  }
  return v64;
}

