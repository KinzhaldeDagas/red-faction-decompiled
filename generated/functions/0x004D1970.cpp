// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004D1970 rf_physics_pair_contact_sphere_samples
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, pair-contact selection, x87 unordered gates, partial contact writes and bounded near-time contact buckets): Cdecl two common-object pointers; physics P=object+136, contact fields point436,normal448,fraction460,material464,reciprocal scalar468,other vector472,UID484,raw material488,liquid492,face496,extra500. Requires STRICT ORDERED AABB400/412 overlap. Chooses source with fewer signed sphere records388; equal counts choose object2 when radius384(object2)<=radius384(object1) OR unordered, otherwise object1. Records are24 bytes(center0,radius12), matrices current252/predicted288,positions228/240. Either object flags424 mask0x400: writes ONLY chosen source fraction460=0,468=1/other152,UID484=other44,returns1. Ordinary path transforms source sphere endpoints relative to BOTH target current/predicted pose; local ray6 has
// normalized direction,only ordered float length>0 enters pair loop. Unit-direction sphere helper uses sum radii. Fraction gate admits >=0 OR unordered; ordered fraction0 additionally requires dot(unitDirection,hitPoint-targetSphereCenter)<0 OR unordered. Let G(bound,t) mean ordered bound>t OR unordered: proceeds if either current fraction admits G, commits full contact only if BOTH admit G. Otherwise, when eligible side flags424 mask0x40000000 set, ORs0x20000000 and copies OTHER current fraction into that side, but returns0 unless another pair committed. Full source contact normal=(local hit-target center) rotated by target CURRENT matrix then unchecked-normalized; point=source current world sphere center+source world sphere displacement*t-normal*source radius. Sets fraction,other material508,reciprocal1/other152,other vector324 plus resolved-other-entity vector2208 when present,other
// UID44,raw material488=DWORD-1,face496/extra500=0; leaves liquid492 untouched. Unless CHOSEN source type36==2, mirrors same point/opposite normal and corresponding other-body metadata into target. No finite/zero reciprocal, pointer,collection or fraction upper1 guards. AL1 means full contact OR special mask0x400 path; AL0 can still change flags/fractions.
char __cdecl rf_physics_pair_contact_sphere_samples(float *a1, float *a2)
{
  int first_dword; // esi
  int v4; // esi
  float *v5; // eax
  float *v6; // eax
  int v7; // eax
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
  int v21; // eax
  float *v22; // eax
  float *v23; // eax
  float *v24; // eax
  float *v25; // eax
  float *scalar; // [esp+8h] [ebp-1C0h]
  float v27; // [esp+10h] [ebp-1B8h]
  float v28[3]; // [esp+14h] [ebp-1B4h] BYREF
  float v29[3]; // [esp+20h] [ebp-1A8h] BYREF
  float v30[3]; // [esp+2Ch] [ebp-19Ch] BYREF
  float v31[3]; // [esp+38h] [ebp-190h] BYREF
  float v32[3]; // [esp+44h] [ebp-184h] BYREF
  float v33[3]; // [esp+50h] [ebp-178h] BYREF
  float v34[3]; // [esp+5Ch] [ebp-16Ch] BYREF
  float scaled_result[3]; // [esp+68h] [ebp-160h] BYREF
  float v36[3]; // [esp+74h] [ebp-154h] BYREF
  float v37[3]; // [esp+80h] [ebp-148h] BYREF
  float v38[3]; // [esp+8Ch] [ebp-13Ch] BYREF
  float v39[3]; // [esp+98h] [ebp-130h] BYREF
  float v40[3]; // [esp+A4h] [ebp-124h] BYREF
  float v41[3]; // [esp+B0h] [ebp-118h] BYREF
  float v42[3]; // [esp+BCh] [ebp-10Ch] BYREF
  float v43[3]; // [esp+C8h] [ebp-100h] BYREF
  float v44[3]; // [esp+D4h] [ebp-F4h] BYREF
  float v45[3]; // [esp+E0h] [ebp-E8h] BYREF
  float v46[3]; // [esp+ECh] [ebp-DCh] BYREF
  float v47[3]; // [esp+F8h] [ebp-D0h] BYREF
  float sum_result[3]; // [esp+104h] [ebp-C4h] BYREF
  float v49[3]; // [esp+110h] [ebp-B8h] BYREF
  float v50[3]; // [esp+11Ch] [ebp-ACh] BYREF
  float v51[3]; // [esp+128h] [ebp-A0h] BYREF
  float copy_result[3]; // [esp+134h] [ebp-94h] BYREF
  float out_vector[3]; // [esp+140h] [ebp-88h] BYREF
  int v54; // [esp+14Ch] [ebp-7Ch]
  int j; // [esp+150h] [ebp-78h]
  int i; // [esp+154h] [ebp-74h]
  float *v57; // [esp+158h] [ebp-70h]
  float lhs[3]; // [esp+15Ch] [ebp-6Ch] BYREF
  float destination[3]; // [esp+168h] [ebp-60h] BYREF
  float vector[3]; // [esp+174h] [ebp-54h] BYREF
  float v61; // [esp+180h] [ebp-48h]
  int v62; // [esp+184h] [ebp-44h]
  int v63; // [esp+188h] [ebp-40h] BYREF
  int v64; // [esp+18Ch] [ebp-3Ch]
  float v65[3]; // [esp+190h] [ebp-38h] BYREF
  float v66[3]; // [esp+19Ch] [ebp-2Ch] BYREF
  float v67[3]; // [esp+1A8h] [ebp-20h] BYREF
  float *v68; // [esp+1B4h] [ebp-14h]
  float rhs[3]; // [esp+1B8h] [ebp-10h] BYREF
  char v70; // [esp+1C7h] [ebp-1h]

  rf_vector3_default_construct_noop(destination);
  rf_vector3_default_construct_noop(v65);
  v70 = 0;
  if ( !rf_aabb_overlap_strict_ordered(a1 + 100, a1 + 103, a2 + 100, a2 + 103) )
    return 0;
  first_dword = rf_receiver_get_first_dword(a1 + 97);
  if ( first_dword == rf_receiver_get_first_dword(a2 + 97) )
  {
    if ( a2[96] <= (double)a1[96] )
    {
      v64 = (int)a2;
      v68 = a2 + 34;
      v62 = (int)a1;
      v57 = a1 + 34;
    }
    else
    {
      v64 = (int)a1;
      v68 = a1 + 34;
      v62 = (int)a2;
      v57 = a2 + 34;
    }
  }
  else
  {
    v4 = rf_receiver_get_first_dword(a1 + 97);
    if ( v4 >= rf_receiver_get_first_dword(a2 + 97) )
    {
      v64 = (int)a2;
      v68 = a2 + 34;
      v62 = (int)a1;
      v57 = a1 + 34;
    }
    else
    {
      v64 = (int)a1;
      v68 = a1 + 34;
      v62 = (int)a2;
      v57 = a2 + 34;
    }
  }
  if ( (*(_DWORD *)(v64 + 424) & 0x400) != 0 || (*(_DWORD *)(v62 + 424) & 0x400) != 0 )
  {
    v68[83] = 1.0 / v57[4];
    v68[87] = *(float *)(v62 + 44);
    v68[81] = 0.0;
    return 1;
  }
  else
  {
    rf_vector3_default_construct_noop(lhs);
    rf_vector3_default_construct_noop(rhs);
    rf_vector3_default_construct_noop(vector);
    rf_force_sample44_construct_vectors_noop((char *)v66);
    v5 = rf_vector_subtract(v68 + 23, out_vector, v57 + 23);
    rf_vector_copy(destination, copy_result, v5);
    v6 = rf_vector_subtract(v68 + 26, v51, v57 + 26);
    rf_vector_copy(v65, v50, v6);
    for ( i = 0; ; ++i )
    {
      v7 = rf_receiver_get_first_dword(v68 + 63);
      if ( i >= v7 )
        break;
      element_address_unchecked = (const float *)rf_array24_get_element_address_unchecked((_DWORD *)v68 + 63, i);
      rf_vector_copy(v66, v49, element_address_unchecked);
      rf_vector_rotate_by_matrix3(v66, v68 + 29);
      v9 = rf_vector_add(v66, sum_result, v68 + 23);
      rf_vector_copy(rhs, v47, v9);
      rf_vector_accumulate(v66, destination);
      rf_matrix3_inverse_rotate_vector(v66, v57 + 29);
      v10 = (const float *)rf_array24_get_element_address_unchecked((_DWORD *)v68 + 63, i);
      rf_vector_copy(lhs, v46, v10);
      rf_vector_rotate_by_matrix3(lhs, v68 + 38);
      v11 = rf_vector_add(lhs, v45, v68 + 26);
      v12 = rf_vector_subtract(v11, v44, rhs);
      rf_vector_copy(vector, v43, v12);
      rf_vector_accumulate(lhs, v65);
      rf_matrix3_inverse_rotate_vector(lhs, v57 + 38);
      v13 = rf_vector_subtract(lhs, v42, v66);
      rf_vector_copy(v67, v41, v13);
      v61 = rf_vector3_length(v67);
      if ( v61 > 0.0 )
      {
        rf_vector3_divide_in_place_reciprocal(v67, v61);
        for ( j = 0; ; ++j )
        {
          v14 = rf_receiver_get_first_dword(v57 + 63);
          if ( j >= v14 )
            break;
          v15 = rf_array24_get_element_address_unchecked((_DWORD *)v57 + 63, j);
          v27 = *(float *)(v15 + 12) + *(float *)(rf_array24_get_element_address_unchecked((_DWORD *)v68 + 63, i) + 12);
          v16 = rf_array24_get_element_address_unchecked((_DWORD *)v57 + 63, j);
          if ( rf_unit_direction_segment_sphere_hit_fraction((int)lhs, (float *)&v63, (int)v66, v61, v16, v27) )
          {
            if ( *(float *)&v63 >= 0.0 )
            {
              if ( *(float *)&v63 != 0.0
                || (v17 = (const float *)rf_array24_get_element_address_unchecked((_DWORD *)v57 + 63, j),
                    v18 = rf_vector_subtract(lhs, v40, v17),
                    rf_vector_dot(v67, v18) < 0.0) )
              {
                if ( v68[81] > (double)*(float *)&v63 || v57[81] > (double)*(float *)&v63 )
                {
                  if ( v68[81] > (double)*(float *)&v63 )
                  {
                    if ( v57[81] > (double)*(float *)&v63 )
                    {
                      v70 = 1;
                      v68[81] = *(float *)&v63;
                      v19 = (const float *)rf_array24_get_element_address_unchecked((_DWORD *)v57 + 63, j);
                      v20 = rf_vector_subtract(lhs, v39, v19);
                      rf_vector_copy(v68 + 78, v38, v20);
                      rf_vector_rotate_by_matrix3(v68 + 78, v57 + 29);
                      rf_vector_normalize_reciprocal_sqrt(v68 + 78);
                      v21 = rf_array24_get_element_address_unchecked((_DWORD *)v68 + 63, i);
                      scalar = rf_vector_multiply_scalar(v68 + 78, scaled_result, *(float *)(v21 + 12));
                      v22 = rf_vector_multiply_scalar(vector, v37, *(float *)&v63);
                      v23 = rf_vector_add(rhs, v36, v22);
                      v24 = rf_vector_subtract(v23, v34, scalar);
                      rf_vector_copy(v68 + 75, v33, v24);
                      v68[82] = *(float *)(v62 + 508);
                      v68[83] = 1.0 / v57[4];
                      rf_vector_copy(v68 + 84, v32, v57 + 47);
                      v54 = rf_entity_resolve_handle(*(_DWORD *)(v62 + 44));
                      if ( v54 )
                        rf_vector_accumulate((float *)(v64 + 472), (float *)(v54 + 2208));
                      v68[87] = *(float *)(v62 + 44);
                      v68[88] = NAN;
                      v68[90] = 0.0;
                      v68[91] = 0.0;
                      if ( *(_DWORD *)(v64 + 36) != 2 )
                      {
                        v57[81] = *(float *)&v63;
                        v25 = rf_vector_negate(v68 + 78, v31);
                        rf_vector_copy(v57 + 78, v30, v25);
                        rf_vector_copy(v57 + 75, v29, v68 + 75);
                        v57[82] = *(float *)(v64 + 508);
                        v57[83] = 1.0 / v68[4];
                        rf_vector_copy(v57 + 84, v28, v68 + 47);
                        v54 = rf_entity_resolve_handle(*(_DWORD *)(v64 + 44));
                        if ( v54 )
                          rf_vector_accumulate((float *)(v62 + 472), (float *)(v54 + 2208));
                        v57[87] = *(float *)(v64 + 44);
                        v57[88] = NAN;
                        v57[90] = 0.0;
                        v57[91] = 0.0;
                      }
                    }
                    else if ( ((_DWORD)v68[72] & 0x40000000) != 0 )
                    {
                      *((_DWORD *)v68 + 72) |= 0x20000000u;
                      v68[81] = v57[81];
                    }
                  }
                  else if ( ((_DWORD)v57[72] & 0x40000000) != 0 )
                  {
                    *((_DWORD *)v57 + 72) |= 0x20000000u;
                    v57[81] = v68[81];
                  }
                }
              }
            }
          }
        }
      }
    }
    return v70;
  }
}

