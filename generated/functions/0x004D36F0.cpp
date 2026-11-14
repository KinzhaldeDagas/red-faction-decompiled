// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004D36F0 rf_physics_world_contacts_sweep
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, pair-contact selection, x87 unordered gates, partial contact writes and bounded near-time contact buckets): Cdecl object; NULL or flags424 mask0x10 absent returnsfalse BEFORE resetting global candidates/cache. P=object+136. Tolerance float0.009999999776482582 except type36==2 uses0. Lazy bit0 guard87BEE8 constructs16 records of68 bytes at87BAA8 with NO-OP constructors,so does not clear storage; constructor unwind cleanup clears init bit. Query flags=P292|4,adds0x100 only ORDERED enclosing radiusP248<double0.05000000074505806. Seeds local bound and slot0 fraction from P324,sets global count87BAA0=0; no whole-record clear. Moving-solid list704BCC/sentinel704940,next652: flags124 mask0x40000 rejects EXCEPT source type2,then STRICT ORDERED stored P264/276 bounds overlap target400/412. Computes
// ratio=float(1-P296/target432), interpolated target-start position=current228+(predicted240-current228)*ratio,without zero/time/finite clamp. Each sphere current/predicted offset rotated by source current/predicted matrices; relative starts use interpolated target-start,ends target predicted240; both inverse-rotate target COMMON matrix72. Solid sweep initializeByte0 shares bound. Positive count computes delta=float(hitT-slot0T): ONLY ordered delta<-tolerance replaces slot0 and sets count1; delta>=-tolerance OR unordered appends only if count>0 AND count<16. Therefore first near-initial-bound hit may be DISCARDED with count0; full bucket discards later grouped hits. Every mover hit still shortens source stored boundsP264/276 to current..current+(predicted-current)*hitT,expanded byP248,even if discarded. Stored mover point/normal transformed by target72,point translated by interpolated
// target-start; metadata mapped face material,vector324,UID44,raw face material,liquid,face. After movers only sphere count>1 builds static-world cache over current source bounds. Static queries use current/predicted sphere pose; EACH sphere resets bound=min(1,float(slot0T+tolerance)),same grouping rule,zero velocity/UID-1 for static records. This is a capped near-time bucket,NOT a sorted closest16 list. If count>0, sums points/normals,minimum fraction starting1 (ORDERED comparisons only); count>1 unit-X-fallback-normalizes summed normal and averages points. Publishes point436,normal448 then ALWAYS unchecked-normalizes normal; fraction460=min,material464/vector472/UID484/raw488/liquid492/face496 from SLOT0,scalar468=0,extra500=0. Metadata need not belong to minimum-fraction record. No candidates leaves prior object contact fields unchanged,though mover bounds/global query/cache state may
// already change. Always clears face cache at processed exit; returns signed count>0. No dedup,owned allocation,reentrancy guard or own pointer/zero reciprocal/finite checks.
// UNREALRED VERIFIED [combat-original-physics-20261112]: Native hit-record field separation is essential:4D42BA stores SLOT0 mapped material to object464 (P+328),4D42FC stores raw bitmap/material to488,468 and500 get literal0. This routine does NOT write entity current material4992;4D9410 independently writes4992 at4D985D and4D8D00 can clear it. Native moving-solid hits shorten object400/412 at every positive solid result, even when the near-initial-bound hit is discarded with bucket count0 or a grouped bucket is full. A final false AL therefore does not imply no bounds writes. Static per-sphere bound is min(1,float(slot0T+tolerance)); metadata remains slot0 even when reduction selects another fraction. Do not replace this with constructor4D13C0 nearest-hit logic or infer that no contact means unchanged bounds.
bool __cdecl rf_physics_world_contacts_sweep(int a1)
{
  float *v2; // eax
  float *v3; // eax
  int first_dword; // eax
  float *element_address_unchecked; // eax
  float *v6; // eax
  float *v7; // eax
  float *v8; // eax
  float *v9; // eax
  float *v10; // eax
  float *v11; // eax
  float *v12; // eax
  float *v13; // eax
  int v14; // eax
  const float *v15; // eax
  const float *v16; // eax
  float *v17; // eax
  float scalar; // [esp+4h] [ebp-270h]
  float *scalara; // [esp+4h] [ebp-270h]
  float *scalarb; // [esp+4h] [ebp-270h]
  float scalarc; // [esp+4h] [ebp-270h]
  float scalard; // [esp+4h] [ebp-270h]
  float v23; // [esp+Ch] [ebp-268h]
  float v24[3]; // [esp+10h] [ebp-264h] BYREF
  float v25[3]; // [esp+1Ch] [ebp-258h] BYREF
  float v26[3]; // [esp+28h] [ebp-24Ch] BYREF
  float v27[3]; // [esp+34h] [ebp-240h] BYREF
  float v28[3]; // [esp+40h] [ebp-234h] BYREF
  float v29[3]; // [esp+4Ch] [ebp-228h] BYREF
  float v30[3]; // [esp+58h] [ebp-21Ch] BYREF
  float v31[3]; // [esp+64h] [ebp-210h] BYREF
  float v32[3]; // [esp+70h] [ebp-204h] BYREF
  float v33[3]; // [esp+7Ch] [ebp-1F8h] BYREF
  float v34[3]; // [esp+88h] [ebp-1ECh] BYREF
  float v35[3]; // [esp+94h] [ebp-1E0h] BYREF
  float v36[3]; // [esp+A0h] [ebp-1D4h] BYREF
  float v37[3]; // [esp+ACh] [ebp-1C8h] BYREF
  float v38[3]; // [esp+B8h] [ebp-1BCh] BYREF
  float v39[3]; // [esp+C4h] [ebp-1B0h] BYREF
  float v40[3]; // [esp+D0h] [ebp-1A4h] BYREF
  float v41[3]; // [esp+DCh] [ebp-198h] BYREF
  float v42[3]; // [esp+E8h] [ebp-18Ch] BYREF
  float v43[3]; // [esp+F4h] [ebp-180h] BYREF
  float v44[3]; // [esp+100h] [ebp-174h] BYREF
  float v45[3]; // [esp+10Ch] [ebp-168h] BYREF
  float v46[3]; // [esp+118h] [ebp-15Ch] BYREF
  float v47[3]; // [esp+124h] [ebp-150h] BYREF
  float v48[3]; // [esp+130h] [ebp-144h] BYREF
  float v49[3]; // [esp+13Ch] [ebp-138h] BYREF
  float v50[3]; // [esp+148h] [ebp-12Ch] BYREF
  float copy_result[3]; // [esp+154h] [ebp-120h] BYREF
  float v52[3]; // [esp+160h] [ebp-114h] BYREF
  float scaled_result[3]; // [esp+16Ch] [ebp-108h] BYREF
  float out_vector[3]; // [esp+178h] [ebp-FCh] BYREF
  float v55; // [esp+184h] [ebp-F0h]
  float v56; // [esp+188h] [ebp-ECh]
  float sum_result[3]; // [esp+18Ch] [ebp-E8h] BYREF
  float v58; // [esp+198h] [ebp-DCh]
  float rhs[3]; // [esp+19Ch] [ebp-D8h] BYREF
  int i; // [esp+1A8h] [ebp-CCh]
  int v61; // [esp+1ACh] [ebp-C8h] BYREF
  float v62; // [esp+1B0h] [ebp-C4h]
  float v63[3]; // [esp+1B4h] [ebp-C0h] BYREF
  float source[4]; // [esp+1C0h] [ebp-B4h] BYREF
  int v65; // [esp+1D0h] [ebp-A4h]
  float lhs[3]; // [esp+1D4h] [ebp-A0h] BYREF
  char v67[52]; // [esp+1E0h] [ebp-94h] BYREF
  float v68[3]; // [esp+214h] [ebp-60h] BYREF
  float v69[3]; // [esp+220h] [ebp-54h] BYREF
  float v70; // [esp+22Ch] [ebp-48h]
  int v71; // [esp+230h] [ebp-44h]
  float v72; // [esp+250h] [ebp-24h]
  int j; // [esp+254h] [ebp-20h]
  float destination[3]; // [esp+258h] [ebp-1Ch] BYREF
  int v75; // [esp+264h] [ebp-10h]
  int v76; // [esp+270h] [ebp-4h]

  if ( !a1 )
    return 0;
  v72 = 0.0099999998;
  if ( *(_DWORD *)(a1 + 36) == 2 )
    v72 = 0.0;
  v75 = a1 + 136;
  if ( (*(_DWORD *)(a1 + 424) & 0x10) == 0 )
    return 0;
  if ( (dword_87BEE8[0] & 1) == 0 )
  {
    dword_87BEE8[0] |= 1u;
    rf_vector_construct_no_unwind(
      (char *)flt_87BAA8,
      0x44u,
      16,
      (void *(__thiscall *)(void *))rf_physics_hit_record_construct_noop);
    v76 = -1;
  }
  rf_solid_collision_query_construct_clear_face_hint(v67);
  rf_solid_collision_result_construct_noop((int)&v61);
  rf_vector3_default_construct_noop(destination);
  rf_vector3_default_construct_noop(lhs);
  v71 = *(_DWORD *)(v75 + 292) | 4;
  if ( *(float *)(v75 + 248) < 0.05000000074505806 )
    v71 |= 0x100u;
  v62 = *(float *)(v75 + 324);
  unk_87BAA0 = 0;
  unk_87BAC0[0] = *(float *)(v75 + 324);
  for ( i = unk_704BCC; (_UNKNOWN *)i != &unk_704940; i = *(_DWORD *)(i + 652) )
  {
    if ( ((*(_DWORD *)(i + 124) & 0x40000) == 0 || *(_DWORD *)(a1 + 36) == 2)
      && rf_aabb_overlap_strict_ordered(
           (float *)(v75 + 264),
           (float *)(v75 + 276),
           (float *)(i + 400),
           (float *)(i + 412)) )
    {
      v58 = 1.0 - *(float *)(v75 + 296) / *(float *)(i + 432);
      scalar = v58;
      v2 = rf_vector_subtract((const float *)(i + 240), out_vector, (const float *)(i + 228));
      v3 = rf_vector_multiply_scalar(v2, scaled_result, scalar);
      rf_vector_add((const float *)(i + 228), rhs, v3);
      for ( j = 0; ; ++j )
      {
        first_dword = rf_receiver_get_first_dword((void *)(v75 + 252));
        if ( j >= first_dword )
          break;
        scalara = (float *)(v75 + 116);
        element_address_unchecked = (float *)rf_array24_get_element_address_unchecked((_DWORD *)(v75 + 252), j);
        v6 = rf_matrix3_rotate_vector(element_address_unchecked, v52, scalara);
        rf_vector_copy(destination, copy_result, v6);
        v7 = rf_vector_subtract((const float *)(v75 + 92), v50, rhs);
        rf_vector_accumulate(destination, v7);
        rf_matrix3_inverse_rotate_vector(destination, (float *)(i + 72));
        scalarb = (float *)(v75 + 152);
        v8 = (float *)rf_array24_get_element_address_unchecked((_DWORD *)(v75 + 252), j);
        v9 = rf_matrix3_rotate_vector(v8, v49, scalarb);
        rf_vector_copy(lhs, v48, v9);
        v10 = rf_vector_subtract((const float *)(v75 + 104), v47, (const float *)(i + 240));
        rf_vector_accumulate(lhs, v10);
        rf_matrix3_inverse_rotate_vector(lhs, (float *)(i + 72));
        rf_vector_copy(v68, v46, destination);
        v11 = rf_vector_subtract(lhs, v45, destination);
        rf_vector_copy(v69, v44, v11);
        v70 = *(float *)(rf_array24_get_element_address_unchecked((_DWORD *)(v75 + 252), j) + 12);
        v61 = 0;
        rf_world_collision_sweep(*(char **)(i + 660), (int)v67, (int)&v61, 0);
        if ( v61 > 0 )
        {
          v56 = v62 - unk_87BAC0[0];
          if ( v56 >= -v72 )
          {
            if ( unk_87BAA0 < 16 && unk_87BAA0 > 0 )
            {
              rf_vector_copy(&flt_87BAB4[17 * unk_87BAA0], v40, source);
              rf_vector_rotate_by_matrix3(&flt_87BAB4[17 * unk_87BAA0], (float *)(i + 72));
              rf_vector_copy(&flt_87BAA8[17 * unk_87BAA0], v39, v63);
              rf_vector_rotate_by_matrix3(&flt_87BAA8[17 * unk_87BAA0], (float *)(i + 72));
              rf_vector_accumulate(&flt_87BAA8[17 * unk_87BAA0], rhs);
              unk_87BAC0[17 * unk_87BAA0] = v62;
              unk_87BAC4[17 * unk_87BAA0] = rf_bitmap_material_to_index(*(_DWORD *)(v65 + 48));
              rf_vector_copy(&flt_87BACC[17 * unk_87BAA0], v38, (const float *)(i + 324));
              unk_87BAD8[17 * unk_87BAA0] = *(_DWORD *)(i + 44);
              unk_87BADC[17 * unk_87BAA0] = *(_DWORD *)(v65 + 48);
              unk_87BAE0[17 * unk_87BAA0] = rf_face_is_liquid((_DWORD *)(v65 + 40));
              unk_87BAE4[17 * unk_87BAA0++] = v65;
            }
          }
          else
          {
            rf_vector_copy(flt_87BAB4, v43, source);
            rf_vector_rotate_by_matrix3(flt_87BAB4, (float *)(i + 72));
            rf_vector_copy(flt_87BAA8, v42, v63);
            rf_vector_rotate_by_matrix3(flt_87BAA8, (float *)(i + 72));
            rf_vector_accumulate(flt_87BAA8, rhs);
            unk_87BAC0[0] = v62;
            unk_87BAC4[0] = rf_bitmap_material_to_index(*(_DWORD *)(v65 + 48));
            rf_vector_copy(flt_87BACC, v41, (const float *)(i + 324));
            unk_87BAD8[0] = *(_DWORD *)(i + 44);
            unk_87BADC[0] = *(_DWORD *)(v65 + 48);
            unk_87BAE0[0] = rf_face_is_liquid((_DWORD *)(v65 + 40));
            unk_87BAE4[0] = v65;
            unk_87BAA0 = 1;
          }
          scalarc = v62;
          v12 = rf_vector_subtract((const float *)(v75 + 104), v37, (const float *)(v75 + 92));
          v13 = rf_vector_multiply_scalar(v12, v36, scalarc);
          rf_vector_add((const float *)(v75 + 92), sum_result, v13);
          rf_segment_bounds_build((float *)(v75 + 264), (float *)(v75 + 276), (float *)(v75 + 92), sum_result);
          rf_vector3_subtract_scalar_in_place((float *)(v75 + 264), *(float *)(v75 + 248));
          rf_vector3_add_scalar_in_place((float *)(v75 + 276), *(float *)(v75 + 248));
        }
      }
    }
  }
  if ( rf_receiver_get_first_dword((void *)(v75 + 252)) > 1 )
    rf_collision_face_cache_build((_DWORD *)rf_world_solid, (float *)(v75 + 264), (float *)(v75 + 276), 0);
  for ( j = 0; ; ++j )
  {
    v14 = rf_receiver_get_first_dword((void *)(v75 + 252));
    if ( j >= v14 )
      break;
    v15 = (const float *)rf_array24_get_element_address_unchecked((_DWORD *)(v75 + 252), j);
    rf_vector_copy(destination, v35, v15);
    rf_vector_rotate_by_matrix3(destination, (float *)(v75 + 116));
    rf_vector_accumulate(destination, (float *)(v75 + 92));
    v16 = (const float *)rf_array24_get_element_address_unchecked((_DWORD *)(v75 + 252), j);
    rf_vector_copy(lhs, v34, v16);
    rf_vector_rotate_by_matrix3(lhs, (float *)(v75 + 152));
    rf_vector_accumulate(lhs, (float *)(v75 + 104));
    rf_vector_copy(v68, v33, destination);
    v17 = rf_vector_subtract(lhs, v32, destination);
    rf_vector_copy(v69, v31, v17);
    v70 = *(float *)(rf_array24_get_element_address_unchecked((_DWORD *)(v75 + 252), j) + 12);
    v23 = unk_87BAC0[0] + v72;
    v62 = rf_float_minimum_two_values(1.0, v23);
    rf_world_collision_sweep((char *)rf_world_solid, (int)v67, (int)&v61, 0);
    if ( v61 > 0 )
    {
      v55 = v62 - unk_87BAC0[0];
      if ( v55 >= -v72 )
      {
        if ( unk_87BAA0 < 16 && unk_87BAA0 > 0 )
        {
          rf_vector_copy(&flt_87BAB4[17 * unk_87BAA0], v28, source);
          rf_vector_copy(&flt_87BAA8[17 * unk_87BAA0], v27, v63);
          unk_87BAC0[17 * unk_87BAA0] = v62;
          unk_87BAC4[17 * unk_87BAA0] = rf_bitmap_material_to_index(*(_DWORD *)(v65 + 48));
          rf_vector3_zero_return_destination(&flt_87BACC[17 * unk_87BAA0]);
          unk_87BAD8[17 * unk_87BAA0] = -1;
          unk_87BADC[17 * unk_87BAA0] = *(_DWORD *)(v65 + 48);
          unk_87BAE0[17 * unk_87BAA0] = rf_face_is_liquid((_DWORD *)(v65 + 40));
          unk_87BAE4[17 * unk_87BAA0++] = v65;
        }
      }
      else
      {
        rf_vector_copy(flt_87BAB4, v30, source);
        rf_vector_copy(flt_87BAA8, v29, v63);
        unk_87BAC0[0] = v62;
        unk_87BAC4[0] = rf_bitmap_material_to_index(*(_DWORD *)(v65 + 48));
        rf_vector3_zero_return_destination(flt_87BACC);
        unk_87BAD8[0] = -1;
        unk_87BADC[0] = *(_DWORD *)(v65 + 48);
        unk_87BAE0[0] = rf_face_is_liquid((_DWORD *)(v65 + 40));
        unk_87BAE4[0] = v65;
        unk_87BAA0 = 1;
      }
    }
  }
  if ( unk_87BAA0 > 0 )
  {
    rf_vector3_zero_return_destination(&flt_87BF0C);
    rf_vector3_zero_return_destination(&flt_87BF00);
    unk_87BF18 = 1.0;
    for ( j = 0; j < unk_87BAA0; ++j )
    {
      if ( unk_87BF18 > (double)unk_87BAC0[17 * j] )
        unk_87BF18 = unk_87BAC0[17 * j];
      rf_vector_accumulate(&flt_87BF0C, &flt_87BAB4[17 * j]);
      rf_vector_accumulate(&flt_87BF00, &flt_87BAA8[17 * j]);
    }
    if ( unk_87BAA0 > 1 )
    {
      rf_vector_normalize(&flt_87BF0C);
      scalard = (float)unk_87BAA0;
      rf_vector3_divide_in_place_reciprocal(&flt_87BF00, scalard);
    }
    rf_vector_copy((float *)(v75 + 300), v26, &flt_87BF00);
    rf_vector_copy((float *)(v75 + 312), v25, &flt_87BF0C);
    rf_vector_normalize_reciprocal_sqrt((float *)(v75 + 312));
    *(float *)(v75 + 324) = unk_87BF18;
    *(_DWORD *)(v75 + 328) = unk_87BAC4[0];
    rf_vector_copy((float *)(v75 + 336), v24, flt_87BACC);
    *(float *)(v75 + 332) = 0.0;
    *(_DWORD *)(v75 + 348) = unk_87BAD8[0];
    *(_DWORD *)(v75 + 352) = unk_87BADC[0];
    *(_DWORD *)(v75 + 356) = unk_87BAE0[0];
    *(_DWORD *)(v75 + 360) = unk_87BAE4[0];
    *(_DWORD *)(v75 + 364) = 0;
  }
  rf_collision_face_cache_clear();
  return unk_87BAA0 > 0;
}

