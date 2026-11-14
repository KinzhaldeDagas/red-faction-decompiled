// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0048B500 rf_mover_compose_child_transforms
// UNREALRED VERIFIED [mission-mover-geometry-20261013] Builds a table by child handle across all movers, then composes each contributing mover in list order. Both solid handles (+0x2CC) and general object handles (+0x2C0) participate. Linear contribution uses displacement relative to first key; rotating contribution rotates orientation and position about key0 using derived axis. A child can belong to multiple movers; single-parent actor attachment is not equivalent. Initial placement and per-frame displacement/velocity commit paths differ.
// UNREALRED VERIFIED [mission-mover-runtime-20261013] Composition correction from explicit ECX/stack dataflow: start from saved child base position+0x238 and base orientation+0x244. Each linear contribution adds predicted mover position minus key0. Each rotor adds (rotated authored-base offset about its pivot)-(authored-base offset), without rotating earlier contributors displacement. Each rotor rotates saved BASE rows and replaces accumulated orientation; last orientation-producing contributor wins. Position contributions add; do not apply ordinary hierarchical transform multiplication.
// UNREALRED VERIFIED [mission-mover-world-20261013] Per-frame ordering/commit: traverses each mover in list order, SOLID handle array+0x2CC first, then generic handle array+0x2C0 (excluding common flag0x08000000). Initial=true processes every collected child, sets published/current/predicted position through0x4BC330, and zeroes velocity+0x144. Ordinary frame path computes velocity=(composedPosition-currentPosition)/frameDelta and sets predicted position before physics. Saved base position+0x238 and orientation+0x244 remain distinct from current pose. No deduplication of a child repeated across both lists.
// UNREALRED VERIFIED [combat-native-pickup-dependencies-20261111]: Mover child frame composition finally rebuilds common outerAABB190/19C from min/max of physicscurrent+E4 and predicted+F0 via5B11F0, then subtracts/adds common+180 scalar via483900/4838C0. Pickup4D0220 prunes type9 against this current AABB BEFORE raw solid intersection. Host query cannot silently omit this recoverable producer or infer it from render geometry.
int __cdecl rf_mover_compose_child_transforms(char a1)
{
  int result; // eax
  int *v2; // eax
  int *v3; // eax
  int *v4; // eax
  int *v5; // eax
  float *v6; // eax
  float *v7; // eax
  float *v8; // eax
  int v9; // eax
  int v10; // eax
  float *v11; // eax
  float *v12; // eax
  int scalar; // [esp+Ch] [ebp-614Ch]
  int scalara; // [esp+Ch] [ebp-614Ch]
  int scalarb; // [esp+Ch] [ebp-614Ch]
  float v16[3]; // [esp+10h] [ebp-6148h] BYREF
  float sum_result[3]; // [esp+1Ch] [ebp-613Ch] BYREF
  float scaled_result[3]; // [esp+28h] [ebp-6130h] BYREF
  float v19[3]; // [esp+34h] [ebp-6124h] BYREF
  float copy_result[3]; // [esp+40h] [ebp-6118h] BYREF
  float v21[3]; // [esp+4Ch] [ebp-610Ch] BYREF
  float v22[3]; // [esp+58h] [ebp-6100h] BYREF
  float v23[3]; // [esp+64h] [ebp-60F4h] BYREF
  float source[3]; // [esp+70h] [ebp-60E8h] BYREF
  int v25; // [esp+7Ch] [ebp-60DCh]
  float v26[3]; // [esp+80h] [ebp-60D8h] BYREF
  int v27; // [esp+8Ch] [ebp-60CCh]
  float v28[3]; // [esp+90h] [ebp-60C8h] BYREF
  int v29[3]; // [esp+9Ch] [ebp-60BCh] BYREF
  float out_vector[3]; // [esp+A8h] [ebp-60B0h] BYREF
  int v31[3]; // [esp+B4h] [ebp-60A4h] BYREF
  int v32[3]; // [esp+C0h] [ebp-6098h] BYREF
  float v33[9]; // [esp+CCh] [ebp-608Ch] BYREF
  int v34; // [esp+F0h] [ebp-6068h]
  int k; // [esp+F4h] [ebp-6064h]
  int v36; // [esp+F8h] [ebp-6060h]
  float v37[3]; // [esp+FCh] [ebp-605Ch] BYREF
  float lhs[3]; // [esp+108h] [ebp-6050h] BYREF
  float v39[9]; // [esp+114h] [ebp-6044h] BYREF
  int v40; // [esp+138h] [ebp-6020h]
  int first_dword; // [esp+140h] [ebp-6018h]
  int v43; // [esp+144h] [ebp-6014h] BYREF
  _BYTE v44[24580]; // [esp+148h] [ebp-6010h] BYREF
  int i; // [esp+614Ch] [ebp-Ch]
  _BYTE *v46; // [esp+6150h] [ebp-8h]
  int j; // [esp+6154h] [ebp-4h]

  v43 = 0;
  result = unk_70489C;
  for ( i = unk_70489C; (_UNKNOWN *)i != &unk_704610; i = *(_DWORD *)(i + 652) )
  {
    first_dword = rf_receiver_get_first_dword((void *)(i + 716));
    for ( j = 0; j < first_dword; ++j )
    {
      v2 = (int *)sub_552200((_DWORD *)(i + 716), j);
      if ( rf_object_resolve_handle(*v2) )
      {
        v3 = (int *)sub_552200((_DWORD *)(i + 716), j);
        rf_mover_collect_child_contributor(&v43, (int)v44, i, *v3);
      }
    }
    result = rf_receiver_get_first_dword((void *)(i + 704));
    first_dword = result;
    for ( j = 0; j < first_dword; ++j )
    {
      v4 = (int *)sub_552200((_DWORD *)(i + 704), j);
      v40 = rf_object_resolve_handle(*v4);
      if ( v40 && (*(_DWORD *)(v40 + 124) & 0x8000000) == 0 )
      {
        v5 = (int *)sub_552200((_DWORD *)(i + 704), j);
        rf_mover_collect_child_contributor(&v43, (int)v44, i, *v5);
      }
      result = j + 1;
    }
  }
  v46 = v44;
  j = 0;
  while ( j < v43 )
  {
    v36 = rf_object_resolve_handle(*(_DWORD *)v46);
    if ( v36 && (a1 || v46[5]) )
    {
      *(_DWORD *)(v36 + 124) |= 0x4000000u;
      rf_matrix3_copy_construct((int)v39, (const void *)(v36 + 580));
      rf_vector3_copy_return_destination(lhs, (float *)(v36 + 568));
      rf_vector3_set_components_return_destination(v37, 0.0, 0.0, 0.0);
      for ( k = 0; k < (unsigned __int8)v46[4]; ++k )
      {
        v34 = *(_DWORD *)&v46[4 * k + 8];
        if ( rf_mover_is_rotating(v34) )
        {
          rf_vector3_default_construct_noop(v29);
          rf_vector3_default_construct_noop(v32);
          rf_vector3_default_construct_noop(v31);
          scalar = *(_DWORD *)sub_552200((_DWORD *)(v34 + 668), 0) + 88;
          v6 = rf_vector3_set_components_return_destination(v23, 0.0, 0.0, 0.0);
          rf_point_rotate_about_axis_pivot((int)v32, v36 + 580, *(float *)(v34 + 752), (int)v6, scalar);
          scalara = *(_DWORD *)sub_552200((_DWORD *)(v34 + 668), 0) + 88;
          v7 = rf_vector3_set_components_return_destination(v22, 0.0, 0.0, 0.0);
          rf_point_rotate_about_axis_pivot((int)v31, v36 + 592, *(float *)(v34 + 752), (int)v7, scalara);
          scalarb = *(_DWORD *)sub_552200((_DWORD *)(v34 + 668), 0) + 88;
          v8 = rf_vector3_set_components_return_destination(v21, 0.0, 0.0, 0.0);
          rf_point_rotate_about_axis_pivot((int)v29, v36 + 604, *(float *)(v34 + 752), (int)v8, scalarb);
          rf_matrix3_construct_from_three_rows((int)v33, (float *)v32, (float *)v31, (float *)v29);
          v9 = sub_552200((_DWORD *)(v34 + 668), 0);
          rf_vector_subtract((const float *)(v36 + 568), out_vector, (const float *)(*(_DWORD *)v9 + 4));
          rf_vector_subtract_in_place(lhs, out_vector);
          rf_matrix3_inverse_rotate_vector(out_vector, (float *)(v36 + 580));
          rf_vector_rotate_by_matrix3(out_vector, v33);
          rf_matrix3_copy(v39, v33);
          rf_vector_accumulate(lhs, out_vector);
        }
        else
        {
          v10 = sub_552200((_DWORD *)(v34 + 668), 0);
          rf_vector_subtract((const float *)(v34 + 240), v28, (const float *)(*(_DWORD *)v10 + 4));
          rf_vector_accumulate(lhs, v28);
          rf_vector_accumulate(v37, (float *)(v34 + 324));
          if ( (*(_DWORD *)(v34 + 792) & 0x800) != 0 )
          {
            v25 = *(_DWORD *)sub_552200((_DWORD *)(v34 + 668), *(_DWORD *)(v34 + 760));
            v27 = *(_DWORD *)sub_552200((_DWORD *)(v34 + 668), *(_DWORD *)(v34 + 764));
            rf_vector_subtract((const float *)(v27 + 4), v26, (const float *)(v25 + 4));
            rf_vector_normalize_reciprocal_sqrt(v26);
            rf_orientation_matrix_from_normalized_direction(v39, v26);
          }
        }
      }
      if ( a1 )
      {
        rf_vector_copy((float *)(v36 + 240), copy_result, lhs);
        rf_matrix3_copy((float *)(v36 + 288), v39);
        rf_matrix3_copy((float *)(v36 + 72), v39);
        rf_matrix3_copy((float *)(v36 + 252), v39);
        rf_object_publish_position_and_bounds(v36, lhs);
        rf_vector3_zero_return_destination((float *)(v36 + 324));
      }
      else
      {
        rf_vector_subtract(lhs, source, (const float *)(v36 + 228));
        rf_vector_copy((float *)(v36 + 324), v19, source);
        *(float *)(v36 + 324) = *(float *)(v36 + 324) / rf_frame_delta_seconds;
        *(float *)(v36 + 328) = *(float *)(v36 + 328) / rf_frame_delta_seconds;
        *(float *)(v36 + 332) = *(float *)(v36 + 332) / rf_frame_delta_seconds;
        v11 = rf_vector_multiply_scalar((const float *)(v36 + 324), scaled_result, rf_frame_delta_seconds);
        v12 = rf_vector_add((const float *)(v36 + 228), sum_result, v11);
        rf_vector_copy((float *)(v36 + 240), v16, v12);
        rf_matrix3_copy((float *)(v36 + 288), v39);
        rf_matrix3_copy((float *)(v36 + 72), v39);
        rf_matrix3_copy((float *)(v36 + 252), v39);
      }
      rf_segment_bounds_build((float *)(v36 + 400), (float *)(v36 + 412), (float *)(v36 + 228), (float *)(v36 + 240));
      rf_vector3_subtract_scalar_in_place((float *)(v36 + 400), *(float *)(v36 + 384));
      rf_vector3_add_scalar_in_place((float *)(v36 + 412), *(float *)(v36 + 384));
    }
    result = ++j;
    v46 += 24;
  }
  return result;
}

