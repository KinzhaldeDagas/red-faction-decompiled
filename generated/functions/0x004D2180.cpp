// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004D2180 rf_physics_pair_contact_horizontal_radius_approximation
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, pair-contact selection, x87 unordered gates, partial contact writes and bounded near-time contact buckets): Cdecl two object pointers. STRICT ORDERED3D AABB400/412 gate first; lazy shared zero vector87BA90 initialized once under bit0 of87BA9C. For each object scans24-byte sphere records388 for largest ORDERED radius12>current maximum, starting0; ignores sphere center offsets/orientation and NaN/negative radii. Sum max radii defines horizontal circle. Relative current/predicted positions are object2 minus object1; forces Y=0 in both. Normalizes relative displacement with unguarded normalize-return-length, ray6=start+unit direction. Sphere helper against global zero center already returns fraction normalized by original length. After helper success and >=0 OR unordered gate (ordered0 additionally requires
// dot(unitDirection,outPoint)<0 OR unordered), DIVIDES THAT FRACTION BY LENGTH AGAIN and rounds float. Uses G(bound,t)=ordered bound>t OR unordered. If neither bound admits G,returns0; if only one admits, its mask0x40000000 permits setting0x20000000/copying other bound and returns1, otherwise0. Both G: writes common point to BOTH contacts, normal1=-normalizedCopyOrUnitX(relativeHitPoint),normal2=opposite; point=current1+(predicted1-current1)*effectiveT-normal1*maxRadius1. Both fraction460=effectiveT,material464=other508,reciprocal468=1/other152,other vector472=other324 plus resolved-other-entity2208,UID484=other44,raw material488=DWORD-1,face496/extra500=0. Liquid492 untouched. No projectile mirror exclusion, finite/zero reciprocal or effectiveT clamp. The repeated division and unordered-admitting timing gates are native behavior, not a conventional normalized sweep.
char __cdecl rf_physics_pair_contact_horizontal_radius_approximation(int a1, int a2)
{
  int first_dword; // eax
  int element_address_unchecked; // eax
  int v5; // eax
  int v6; // eax
  float *v7; // eax
  float *v8; // eax
  float *v9; // eax
  float *v10; // eax
  float *v11; // eax
  float *v12; // eax
  float *v13; // eax
  float *v14; // eax
  float *v15; // eax
  float *v16; // eax
  int scalar; // [esp+8h] [ebp-148h]
  float v18[3]; // [esp+10h] [ebp-140h] BYREF
  float v19[3]; // [esp+1Ch] [ebp-134h] BYREF
  float v20[3]; // [esp+28h] [ebp-128h] BYREF
  float v21[3]; // [esp+34h] [ebp-11Ch] BYREF
  float v22[3]; // [esp+40h] [ebp-110h] BYREF
  float v23[3]; // [esp+4Ch] [ebp-104h] BYREF
  float v24[3]; // [esp+58h] [ebp-F8h] BYREF
  float sum_result[3]; // [esp+64h] [ebp-ECh] BYREF
  float scaled_result[3]; // [esp+70h] [ebp-E0h] BYREF
  float v27[3]; // [esp+7Ch] [ebp-D4h] BYREF
  float v28[3]; // [esp+88h] [ebp-C8h] BYREF
  float v29[3]; // [esp+94h] [ebp-BCh] BYREF
  _BYTE v30[12]; // [esp+A0h] [ebp-B0h] BYREF
  float v31[3]; // [esp+ACh] [ebp-A4h] BYREF
  float v32[3]; // [esp+B8h] [ebp-98h] BYREF
  float v33[3]; // [esp+C4h] [ebp-8Ch] BYREF
  float v34[3]; // [esp+D0h] [ebp-80h] BYREF
  float copy_result[3]; // [esp+DCh] [ebp-74h] BYREF
  float out_vector[3]; // [esp+E8h] [ebp-68h] BYREF
  int v37; // [esp+F4h] [ebp-5Ch]
  int v38[3]; // [esp+F8h] [ebp-58h] BYREF
  float v39; // [esp+104h] [ebp-4Ch]
  float v40; // [esp+108h] [ebp-48h]
  int v41; // [esp+10Ch] [ebp-44h] BYREF
  float v42; // [esp+110h] [ebp-40h]
  int i; // [esp+114h] [ebp-3Ch]
  float lhs[3]; // [esp+118h] [ebp-38h] BYREF
  float rhs[3]; // [esp+124h] [ebp-2Ch] BYREF
  float destination[3]; // [esp+130h] [ebp-20h] BYREF
  char v47; // [esp+13Fh] [ebp-11h]
  float v48; // [esp+140h] [ebp-10h]
  int v49; // [esp+14Ch] [ebp-4h]

  if ( !rf_aabb_overlap_strict_ordered(
          (float *)(a1 + 400),
          (float *)(a1 + 412),
          (float *)(a2 + 400),
          (float *)(a2 + 412)) )
    return 0;
  rf_vector3_default_construct_noop(v38);
  rf_vector3_default_construct_noop(lhs);
  if ( (dword_87BA9C & 1) == 0 )
  {
    dword_87BA9C |= 1u;
    v49 = 0;
    rf_vector3_set_components_return_destination(flt_87BA90, 0.0, 0.0, 0.0);
    v49 = -1;
  }
  rf_force_sample44_construct_vectors_noop((char *)rhs);
  v47 = 0;
  v48 = 0.0;
  for ( i = 0; ; ++i )
  {
    first_dword = rf_receiver_get_first_dword((void *)(a1 + 388));
    if ( i >= first_dword )
      break;
    element_address_unchecked = rf_array24_get_element_address_unchecked((_DWORD *)(a1 + 388), i);
    if ( v48 < (double)*(float *)(element_address_unchecked + 12) )
      v48 = *(float *)(rf_array24_get_element_address_unchecked((_DWORD *)(a1 + 388), i) + 12);
  }
  v42 = 0.0;
  for ( i = 0; ; ++i )
  {
    v5 = rf_receiver_get_first_dword((void *)(a2 + 388));
    if ( i >= v5 )
      break;
    v6 = rf_array24_get_element_address_unchecked((_DWORD *)(a2 + 388), i);
    if ( v42 < (double)*(float *)(v6 + 12) )
      v42 = *(float *)(rf_array24_get_element_address_unchecked((_DWORD *)(a2 + 388), i) + 12);
  }
  v39 = v48 + v42;
  v7 = rf_vector_subtract((const float *)(a2 + 228), out_vector, (const float *)(a1 + 228));
  rf_vector_copy(rhs, copy_result, v7);
  v8 = rf_vector_subtract((const float *)(a2 + 240), v34, (const float *)(a1 + 240));
  rf_vector_copy(lhs, v33, v8);
  lhs[1] = 0.0;
  rhs[1] = 0.0;
  v9 = rf_vector_subtract(lhs, v32, rhs);
  rf_vector_copy(destination, v31, v9);
  v40 = rf_vector3_normalize_return_length(destination);
  if ( !rf_unit_direction_segment_sphere_hit_fraction((int)v38, (float *)&v41, (int)rhs, v40, (int)flt_87BA90, v39) )
    return 0;
  if ( *(float *)&v41 < 0.0 || *(float *)&v41 == 0.0 && rf_vector_dot(destination, (float *)v38) >= 0.0 )
    return 0;
  *(float *)&v41 = *(float *)&v41 / v40;
  if ( *(float *)(a1 + 460) <= (double)*(float *)&v41 && *(float *)(a2 + 460) <= (double)*(float *)&v41 )
    return 0;
  if ( *(float *)(a1 + 460) <= (double)*(float *)&v41 )
  {
    if ( (*(_DWORD *)(a2 + 424) & 0x40000000) != 0 )
    {
      *(_DWORD *)(a2 + 424) |= 0x20000000u;
      *(float *)(a2 + 460) = *(float *)(a1 + 460);
      return 1;
    }
    return 0;
  }
  if ( *(float *)(a2 + 460) <= (double)*(float *)&v41 )
  {
    if ( (*(_DWORD *)(a1 + 424) & 0x40000000) != 0 )
    {
      *(_DWORD *)(a1 + 424) |= 0x20000000u;
      *(float *)(a1 + 460) = *(float *)(a2 + 460);
      return 1;
    }
    return 0;
  }
  *(float *)(a1 + 460) = *(float *)&v41;
  v10 = (float *)rf_vector3_normalized_copy_or_unit_x((float *)v38, (int)v30);
  v11 = rf_vector_negate(v10, v29);
  rf_vector_copy((float *)(a1 + 448), v28, v11);
  scalar = v41;
  v12 = rf_vector_subtract((const float *)(a1 + 240), v27, (const float *)(a1 + 228));
  v13 = rf_vector_multiply_scalar(v12, scaled_result, *(float *)&scalar);
  v14 = rf_vector_add((const float *)(a1 + 228), sum_result, v13);
  rf_vector_copy((float *)(a1 + 436), v24, v14);
  v15 = rf_vector_multiply_scalar((const float *)(a1 + 448), v23, v48);
  rf_vector_subtract_in_place((float *)(a1 + 436), v15);
  *(_DWORD *)(a1 + 464) = *(_DWORD *)(a2 + 508);
  *(float *)(a1 + 468) = 1.0 / *(float *)(a2 + 152);
  rf_vector_copy((float *)(a1 + 472), v22, (const float *)(a2 + 324));
  v37 = rf_entity_resolve_handle(*(_DWORD *)(a2 + 44));
  if ( v37 )
    rf_vector_accumulate((float *)(a1 + 472), (float *)(v37 + 2208));
  *(_DWORD *)(a1 + 484) = *(_DWORD *)(a2 + 44);
  *(_DWORD *)(a1 + 488) = -1;
  *(_DWORD *)(a1 + 496) = 0;
  *(_DWORD *)(a1 + 500) = 0;
  *(float *)(a2 + 460) = *(float *)&v41;
  v16 = rf_vector_negate((float *)(a1 + 448), v21);
  rf_vector_copy((float *)(a2 + 448), v20, v16);
  rf_vector_copy((float *)(a2 + 436), v19, (const float *)(a1 + 436));
  *(_DWORD *)(a2 + 464) = *(_DWORD *)(a1 + 508);
  *(float *)(a2 + 468) = 1.0 / *(float *)(a1 + 152);
  rf_vector_copy((float *)(a2 + 472), v18, (const float *)(a1 + 324));
  v37 = rf_entity_resolve_handle(*(_DWORD *)(a1 + 44));
  if ( v37 )
    rf_vector_accumulate((float *)(a2 + 472), (float *)(v37 + 2208));
  *(_DWORD *)(a2 + 484) = *(_DWORD *)(a1 + 44);
  *(_DWORD *)(a2 + 488) = -1;
  *(_DWORD *)(a2 + 496) = 0;
  *(_DWORD *)(a2 + 500) = 0;
  return 1;
}

