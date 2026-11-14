// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004D8640 rf_physics_body_integrate
// UNREALRED VERIFIED [trigger-geometry-20261020] Physics integration writes predicted position at object+0xF0 and builds swept bounds from current+0xE4 to predicted+0xF0. These exact two vectors feed ordinary box-trigger geometry. UE movement samples are committed movement segments; they do not reconstruct RF collision-free prediction or residual-step scheduling.
int __cdecl rf_physics_body_integrate(int a1)
{
  float *v1; // eax
  float *v2; // eax
  float *v3; // eax
  float *v4; // eax
  float *v5; // eax
  float *v6; // eax
  float *v7; // eax
  float *v8; // eax
  float *v9; // eax
  float *v10; // eax
  float *v11; // eax
  float *v12; // eax
  float *v13; // eax
  float *v14; // eax
  float *v15; // eax
  float *v17; // [esp+8h] [ebp-1B0h]
  float v18; // [esp+10h] [ebp-1A8h]
  float v19; // [esp+14h] [ebp-1A4h]
  float v20; // [esp+18h] [ebp-1A0h]
  double v21; // [esp+1Ch] [ebp-19Ch]
  float v22; // [esp+24h] [ebp-194h]
  float v23; // [esp+28h] [ebp-190h]
  double v24; // [esp+2Ch] [ebp-18Ch]
  float v25; // [esp+34h] [ebp-184h]
  double v26; // [esp+38h] [ebp-180h]
  float v27[9]; // [esp+40h] [ebp-178h] BYREF
  float v28[3]; // [esp+64h] [ebp-154h] BYREF
  float v29[3]; // [esp+70h] [ebp-148h] BYREF
  float v30[3]; // [esp+7Ch] [ebp-13Ch] BYREF
  float v31[3]; // [esp+88h] [ebp-130h] BYREF
  int v32[3]; // [esp+94h] [ebp-124h] BYREF
  float v33[3]; // [esp+A0h] [ebp-118h] BYREF
  float v34[3]; // [esp+ACh] [ebp-10Ch] BYREF
  float out_vector[3]; // [esp+B8h] [ebp-100h] BYREF
  float v36[3]; // [esp+C4h] [ebp-F4h] BYREF
  float v37[3]; // [esp+D0h] [ebp-E8h] BYREF
  float v38[3]; // [esp+DCh] [ebp-DCh] BYREF
  float v39[3]; // [esp+E8h] [ebp-D0h] BYREF
  float v40[3]; // [esp+F4h] [ebp-C4h] BYREF
  int v41[3]; // [esp+100h] [ebp-B8h] BYREF
  int v42[3]; // [esp+10Ch] [ebp-ACh] BYREF
  float v43[3]; // [esp+118h] [ebp-A0h] BYREF
  float v44[3]; // [esp+124h] [ebp-94h] BYREF
  float sum_result[3]; // [esp+130h] [ebp-88h] BYREF
  float v46[3]; // [esp+13Ch] [ebp-7Ch] BYREF
  float scaled_result[3]; // [esp+148h] [ebp-70h] BYREF
  float v48[3]; // [esp+154h] [ebp-64h] BYREF
  int v49[3]; // [esp+160h] [ebp-58h] BYREF
  int v50[3]; // [esp+16Ch] [ebp-4Ch] BYREF
  float copy_result[3]; // [esp+178h] [ebp-40h] BYREF
  float v52[9]; // [esp+184h] [ebp-34h] BYREF
  float v53; // [esp+1A8h] [ebp-10h]
  int v54; // [esp+1B4h] [ebp-4h]

  if ( (dword_87BF84 & 1) == 0 )
  {
    dword_87BF84 |= 1u;
    rf_vector3_default_construct_noop(&flt_87BF78);
    v54 = -1;
  }
  if ( (dword_87BF84 & 2) == 0 )
  {
    dword_87BF84 |= 2u;
    rf_vector3_default_construct_noop(unk_87BF6C);
    v54 = -1;
  }
  if ( (dword_87BF84 & 4) == 0 )
  {
    dword_87BF84 |= 4u;
    rf_vector3_set_components_return_destination(&flt_87BF60, 0.0, 0.0, 0.0);
    v54 = -1;
  }
  if ( ((unsigned int)&unk_1000000 & *(_DWORD *)(a1 + 424)) == 0 )
  {
    rf_vector_copy(&flt_87BF78, copy_result, (const float *)(a1 + 360));
    if ( (*(_DWORD *)(a1 + 424) & 2) != 0 && (*(_DWORD *)(a1 + 124) & 0x80000) != 0 )
    {
      v26 = 2.0 * *(float *)(a1 + 140);
      v25 = rf_vector3_length((float *)(a1 + 324)) * v26;
      v1 = rf_vector_scale((float *)v50, v25, (float *)(a1 + 324));
      rf_vector_subtract_in_place(&flt_87BF78, v1);
    }
    v2 = rf_vector_divide(&flt_87BF78, (float *)v49, *(float *)(a1 + 152));
    rf_vector_copy(&flt_87BF60, v48, v2);
    if ( (*(_DWORD *)(a1 + 424) & 1) != 0 )
      unk_87BF64 = unk_87BF64 - rf_physics_gravity_acceleration;
    v3 = rf_vector_multiply_scalar(&flt_87BF60, scaled_result, *(float *)(a1 + 432));
    v4 = rf_vector_multiply_scalar(v3, v46, 0.5);
    v5 = rf_vector_add((const float *)(a1 + 324), sum_result, v4);
    rf_vector_copy(unk_87BF6C, v44, v5);
    rf_vector_copy(&flt_87BF78, v43, (const float *)(a1 + 360));
    if ( (*(_DWORD *)(a1 + 424) & 2) != 0 && (*(_DWORD *)(a1 + 124) & 0x80000) != 0 )
    {
      v24 = 2.0 * *(float *)(a1 + 140);
      v23 = rf_vector3_length(unk_87BF6C) * v24;
      v6 = rf_vector_scale((float *)v42, v23, unk_87BF6C);
      rf_vector_subtract_in_place(&flt_87BF78, v6);
    }
    v7 = rf_vector_divide(&flt_87BF78, (float *)v41, *(float *)(a1 + 152));
    rf_vector_copy(&flt_87BF60, v40, v7);
    if ( (*(_DWORD *)(a1 + 424) & 1) != 0 )
      unk_87BF64 = unk_87BF64 - rf_physics_gravity_acceleration;
    v8 = rf_vector_multiply_scalar(&flt_87BF60, v39, *(float *)(a1 + 432));
    rf_vector_accumulate((float *)(a1 + 324), v8);
  }
  v22 = *(float *)(a1 + 432) * 0.5 * *(float *)(a1 + 432);
  v17 = rf_vector_multiply_scalar(&flt_87BF60, v36, v22);
  v9 = rf_vector_multiply_scalar((const float *)(a1 + 324), v38, *(float *)(a1 + 432));
  v10 = rf_vector_add((const float *)(a1 + 228), v37, v9);
  v11 = rf_vector_subtract(v10, out_vector, v17);
  rf_vector_copy((float *)(a1 + 240), v34, v11);
  if ( ((unsigned int)&unk_1000000 & *(_DWORD *)(a1 + 424)) == 0 )
  {
    rf_vector_copy(&flt_87BF78, v33, (const float *)(a1 + 372));
    if ( (*(_DWORD *)(a1 + 424) & 2) != 0 )
    {
      v21 = 1.0 * *(float *)(a1 + 140);
      v20 = rf_vector3_length((float *)(a1 + 336)) * v21;
      v12 = rf_vector_scale((float *)v32, v20, (float *)(a1 + 336));
      rf_vector_subtract_in_place(&flt_87BF78, v12);
    }
    v13 = rf_vector_multiply_scalar(&flt_87BF78, v31, *(float *)(a1 + 432));
    rf_vector_accumulate((float *)(a1 + 348), v13);
  }
  rf_vector_copy((float *)(a1 + 336), v30, (const float *)(a1 + 348));
  rf_matrix3_inverse_rotate_vector((float *)(a1 + 336), (float *)(a1 + 192));
  v53 = rf_vector3_length((float *)(a1 + 336));
  if ( v53 > 15.0 )
  {
    v19 = 15.0 / v53;
    rf_vector3_scale_in_place_return_self((float *)(a1 + 336), v19);
    v18 = 15.0 / v53;
    rf_vector3_scale_in_place_return_self((float *)(a1 + 348), v18);
  }
  v14 = rf_vector_multiply_scalar((const float *)(a1 + 336), v29, *(float *)(a1 + 432));
  rf_vector_copy(&flt_87BF78, v28, v14);
  rf_matrix3_inverse_rotate_vector(&flt_87BF78, (float *)(a1 + 252));
  v53 = rf_vector3_length(&flt_87BF78);
  if ( v53 > 0.0 )
  {
    flt_87BF78 = flt_87BF78 / v53;
    unk_87BF7C = unk_87BF7C / v53;
    unk_87BF80 = unk_87BF80 / v53;
  }
  rf_matrix3_construct_from_axis_angle((int)v52, &flt_87BF78, v53);
  v15 = rf_matrix3_argument_times_receiver_to_output((const float *)(a1 + 252), v27, v52);
  rf_matrix3_copy((float *)(a1 + 288), v15);
  rf_matrix3_rebuild_basis_from_forward_in_place((char *)(a1 + 288));
  rf_segment_bounds_build((float *)(a1 + 400), (float *)(a1 + 412), (float *)(a1 + 228), (float *)(a1 + 240));
  rf_vector3_subtract_scalar_in_place((float *)(a1 + 400), *(float *)(a1 + 384));
  rf_vector3_add_scalar_in_place((float *)(a1 + 412), *(float *)(a1 + 384));
  *(float *)(a1 + 460) = 1.0;
  *(_DWORD *)(a1 + 484) = -1;
  rf_vector3_zero_return_destination((float *)(a1 + 360));
  rf_vector3_zero_return_destination((float *)(a1 + 372));
  *(_DWORD *)(a1 + 424) |= (unsigned int)&unk_1000000;
  return a1;
}

