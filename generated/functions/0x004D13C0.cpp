// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004D13C0 rf_physics_shape_sweep_movers_and_static_world
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, shape-sphere/model/solid sweeps, x87 unordered gates, descriptor constructors and native output mutation): Cdecl start,end,shape,INOUT68-byte physics hit. Solid query flags80=shape DWORD292|4 (bypass query-pose transform); adds0x100 ONLY for ORDERED shape radius248<double0.05000000074505806. Seeds solid-result fraction4 ONCE from caller hit24. Builds segment bounds expanded by shape248. First moving-solid ring head704BCC/sentinel704940,next652: skips object flags124 mask0x40000 and requires STRICT ORDERED expanded bounds overlap with object400/412. For each sphere collection252,24-byte stride, rotates offset by shape matrix116, adds start/end relative to mover physics position228, then inverse-rotates by mover COMMON orientation72; sets radius76 from sphere12, explicitly count0=0, calls mover solid660 with
// initializeByte0. Backend resets count/edge/face but preserves fraction. On count>0 writes normal12/point0 rotated by mover72, adds mover228 to point, fraction24, mapped material index28 from face48, scalar32=0, vector36 from mover324, mover UID44->48, raw face material48->52, normalized face-liquid predicate->56, face pointer->60, DWORD64=0. Shrinks later mover broad-phase bounds to start..start+(end-start)*bound, again expanded by shape248. Does not build/clear cache before mover pass. Afterwards, only if signed sphere count>1 builds global STATIC-world face cache over current expanded bounds. Static per-sphere start=rotate(offset,shape116)+start, direction=end-start,radius=record12; calls global solid with initializeByte0. Positive hit writes full same fields, but point/normal need no mover transform, vector36=zero, UID48=RAW DWORD-1 (not float NaN). Always clears global face cache at
// end, even if never built or no spheres. No entity/clutter/corpse model sweep in this function, own pointer/count/index/finite validation or normal renormalization. ReturnsAL1 if any positive-count call; misses preserve caller hit, but query serial/cache state still changes through delegates.
char __cdecl rf_physics_shape_sweep_movers_and_static_world(float *lhs, float *a2, int a3, float *a4)
{
  int first_dword; // eax
  float *element_address_unchecked; // eax
  float *v6; // eax
  float *v7; // eax
  float *v8; // eax
  float *v9; // eax
  float *v10; // eax
  float *v11; // eax
  int v12; // eax
  float *v13; // eax
  float *v14; // eax
  float *v15; // eax
  float scalar; // [esp+0h] [ebp-1A8h]
  float v18[3]; // [esp+4h] [ebp-1A4h] BYREF
  float v19[3]; // [esp+10h] [ebp-198h] BYREF
  float v20[3]; // [esp+1Ch] [ebp-18Ch] BYREF
  float v21[3]; // [esp+28h] [ebp-180h] BYREF
  float v22[3]; // [esp+34h] [ebp-174h] BYREF
  float v23[3]; // [esp+40h] [ebp-168h] BYREF
  float scaled_result[3]; // [esp+4Ch] [ebp-15Ch] BYREF
  float v25[3]; // [esp+58h] [ebp-150h] BYREF
  float v26[3]; // [esp+64h] [ebp-144h] BYREF
  float v27[3]; // [esp+70h] [ebp-138h] BYREF
  float v28[3]; // [esp+7Ch] [ebp-12Ch] BYREF
  float v29[3]; // [esp+88h] [ebp-120h] BYREF
  float v30[3]; // [esp+94h] [ebp-114h] BYREF
  float v31[3]; // [esp+A0h] [ebp-108h] BYREF
  float out_vector[3]; // [esp+ACh] [ebp-FCh] BYREF
  float copy_result[3]; // [esp+B8h] [ebp-F0h] BYREF
  float v34[3]; // [esp+C4h] [ebp-E4h] BYREF
  float sum_result[3]; // [esp+D0h] [ebp-D8h] BYREF
  float v36[3]; // [esp+DCh] [ebp-CCh] BYREF
  int v37; // [esp+E8h] [ebp-C0h] BYREF
  float v38; // [esp+ECh] [ebp-BCh]
  float v39[3]; // [esp+F0h] [ebp-B8h] BYREF
  float source[4]; // [esp+FCh] [ebp-ACh] BYREF
  int v41; // [esp+10Ch] [ebp-9Ch]
  char v42[52]; // [esp+110h] [ebp-98h] BYREF
  float rhs[3]; // [esp+144h] [ebp-64h] BYREF
  float destination[3]; // [esp+150h] [ebp-58h] BYREF
  float v45; // [esp+15Ch] [ebp-4Ch]
  int v46; // [esp+160h] [ebp-48h]
  int j; // [esp+184h] [ebp-24h]
  float v48[3]; // [esp+188h] [ebp-20h] BYREF
  int i; // [esp+194h] [ebp-14h]
  float v50[3]; // [esp+198h] [ebp-10h] BYREF
  char v51; // [esp+1A7h] [ebp-1h]

  rf_solid_collision_query_construct_clear_face_hint(v42);
  rf_solid_collision_result_construct_noop((int)&v37);
  rf_vector3_default_construct_noop(v50);
  rf_vector3_default_construct_noop(v48);
  v51 = 0;
  v46 = *(_DWORD *)(a3 + 292);
  v46 |= 4u;
  if ( *(float *)(a3 + 248) < 0.05000000074505806 )
    v46 |= 0x100u;
  v38 = a4[6];
  rf_segment_bounds_build(v50, v48, lhs, a2);
  rf_vector3_subtract_scalar_in_place(v50, *(float *)(a3 + 248));
  rf_vector3_add_scalar_in_place(v48, *(float *)(a3 + 248));
  for ( i = unk_704BCC; (_UNKNOWN *)i != &unk_704940; i = *(_DWORD *)(i + 652) )
  {
    if ( (*(_DWORD *)(i + 124) & 0x40000) == 0
      && rf_aabb_overlap_strict_ordered(v50, v48, (float *)(i + 400), (float *)(i + 412)) )
    {
      for ( j = 0; ; ++j )
      {
        first_dword = rf_receiver_get_first_dword((void *)(a3 + 252));
        if ( j >= first_dword )
          break;
        element_address_unchecked = (float *)rf_array24_get_element_address_unchecked((_DWORD *)(a3 + 252), j);
        v6 = rf_matrix3_rotate_vector(element_address_unchecked, v34, (float *)(a3 + 116));
        rf_vector_copy(rhs, copy_result, v6);
        rf_vector3_copy_return_destination(v36, rhs);
        v7 = rf_vector_subtract(lhs, out_vector, (const float *)(i + 228));
        rf_vector_accumulate(rhs, v7);
        rf_matrix3_inverse_rotate_vector(rhs, (float *)(i + 72));
        v8 = rf_vector_subtract(a2, v31, (const float *)(i + 228));
        rf_vector_accumulate(v36, v8);
        rf_matrix3_inverse_rotate_vector(v36, (float *)(i + 72));
        v9 = rf_vector_subtract(v36, v30, rhs);
        rf_vector_copy(destination, v29, v9);
        v45 = *(float *)(rf_array24_get_element_address_unchecked((_DWORD *)(a3 + 252), j) + 12);
        v37 = 0;
        rf_world_collision_sweep(*(char **)(i + 660), (int)v42, (int)&v37, 0);
        if ( v37 > 0 )
        {
          rf_vector_copy(a4 + 3, v28, source);
          rf_vector_rotate_by_matrix3(a4 + 3, (float *)(i + 72));
          rf_vector_copy(a4, v27, v39);
          rf_vector_rotate_by_matrix3(a4, (float *)(i + 72));
          rf_vector_accumulate(a4, (float *)(i + 228));
          a4[6] = v38;
          *((_DWORD *)a4 + 7) = rf_bitmap_material_to_index(*(_DWORD *)(v41 + 48));
          a4[8] = 0.0;
          rf_vector_copy(a4 + 9, v26, (const float *)(i + 324));
          a4[12] = *(float *)(i + 44);
          a4[13] = *(float *)(v41 + 48);
          *((_DWORD *)a4 + 14) = rf_face_is_liquid((_DWORD *)(v41 + 40));
          *((_DWORD *)a4 + 15) = v41;
          a4[16] = 0.0;
          scalar = v38;
          v10 = rf_vector_subtract(a2, v25, lhs);
          v11 = rf_vector_multiply_scalar(v10, scaled_result, scalar);
          rf_vector_add(lhs, sum_result, v11);
          rf_segment_bounds_build(v50, v48, lhs, sum_result);
          rf_vector3_subtract_scalar_in_place(v50, *(float *)(a3 + 248));
          rf_vector3_add_scalar_in_place(v48, *(float *)(a3 + 248));
          v51 = 1;
        }
      }
    }
  }
  if ( rf_receiver_get_first_dword((void *)(a3 + 252)) > 1 )
    rf_collision_face_cache_build((_DWORD *)rf_world_solid, v50, v48, 0);
  for ( j = 0; ; ++j )
  {
    v12 = rf_receiver_get_first_dword((void *)(a3 + 252));
    if ( j >= v12 )
      break;
    v13 = (float *)rf_array24_get_element_address_unchecked((_DWORD *)(a3 + 252), j);
    v14 = rf_matrix3_rotate_vector(v13, v23, (float *)(a3 + 116));
    rf_vector_copy(rhs, v22, v14);
    rf_vector_accumulate(rhs, lhs);
    v15 = rf_vector_subtract(a2, v21, lhs);
    rf_vector_copy(destination, v20, v15);
    v45 = *(float *)(rf_array24_get_element_address_unchecked((_DWORD *)(a3 + 252), j) + 12);
    rf_world_collision_sweep((char *)rf_world_solid, (int)v42, (int)&v37, 0);
    if ( v37 > 0 )
    {
      rf_vector_copy(a4 + 3, v19, source);
      rf_vector_copy(a4, v18, v39);
      a4[6] = v38;
      *((_DWORD *)a4 + 7) = rf_bitmap_material_to_index(*(_DWORD *)(v41 + 48));
      a4[8] = 0.0;
      rf_vector3_zero_return_destination(a4 + 9);
      a4[12] = NAN;
      a4[13] = *(float *)(v41 + 48);
      *((_DWORD *)a4 + 14) = rf_face_is_liquid((_DWORD *)(v41 + 40));
      *((_DWORD *)a4 + 15) = v41;
      a4[16] = 0.0;
      v51 = 1;
    }
  }
  rf_collision_face_cache_clear();
  return v51;
}

