// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005BC660 rf_particle_instance_spawn_one
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, particle pool allocation, emission/integration branches, definition loader and original-PE math/constants): Thiscall runtime,particle index,fraction,deltaSeconds,emitterVelocity. Instance flags+16 mask1 disables spawn entirely. Particle36: age0,lifetime4,angle8,position12,velocity24. Shape definition+168=0: local velocity around negativeY with independent spread,rotated by emitter quaternion then world orientation; rectangular XZ position within width/depth,rotated/offset. Shape1: random sphere direction,speed+random spread; uses width as radius and rotates/offsets position. Both optionally add emitter velocity for definition flags+172 mask8; interpolate previous/current origin by fraction,randomize initial age in[0,fraction*delta],advance position by velocity*age,randomize
// lifetime=(baseTicks+random(+/-baseTicks*variation))/4800. Mask0x10 randomizes angle[0,2pi],otherwise0. Increments live count. Unknown shape leaves age/position/velocity/lifetime untouched but STILL sets angle/increments live count. No index,live capacity,lifetime or finite guards; return incidental receiver.
char *__thiscall rf_particle_instance_spawn_one(char *this, int a2, float scalar, float a4, float *a5)
{
  char *result; // eax
  float *v6; // eax
  double v7; // st7
  double v8; // st7
  double v9; // st7
  float *v10; // eax
  float *v11; // eax
  float *v12; // eax
  double v13; // st7
  float *v14; // eax
  float *v15; // eax
  double v16; // st7
  float *v17; // eax
  float *v18; // eax
  float *v19; // eax
  float *v20; // eax
  double v21; // st7
  float *v22; // eax
  float *v23; // eax
  double v24; // st7
  double v25; // st7
  float v26; // [esp+4h] [ebp-144h]
  float v27; // [esp+4h] [ebp-144h]
  float v28; // [esp+4h] [ebp-144h]
  float v29; // [esp+4h] [ebp-144h]
  float v30; // [esp+4h] [ebp-144h]
  float v31; // [esp+4h] [ebp-144h]
  float v32; // [esp+4h] [ebp-144h]
  double v33; // [esp+Ch] [ebp-13Ch]
  float v34; // [esp+14h] [ebp-134h]
  double v35; // [esp+18h] [ebp-130h]
  float v36; // [esp+20h] [ebp-128h]
  float v37; // [esp+24h] [ebp-124h]
  float v38; // [esp+28h] [ebp-120h]
  float v39; // [esp+2Ch] [ebp-11Ch]
  double v40; // [esp+30h] [ebp-118h]
  int v41; // [esp+38h] [ebp-110h]
  float v43[3]; // [esp+40h] [ebp-108h] BYREF
  float v44[3]; // [esp+4Ch] [ebp-FCh] BYREF
  float v45[3]; // [esp+58h] [ebp-F0h] BYREF
  float v46[3]; // [esp+64h] [ebp-E4h] BYREF
  float v47[3]; // [esp+70h] [ebp-D8h] BYREF
  float v48[3]; // [esp+7Ch] [ebp-CCh] BYREF
  float v49[3]; // [esp+88h] [ebp-C0h] BYREF
  float v50[3]; // [esp+94h] [ebp-B4h] BYREF
  float v51[3]; // [esp+A0h] [ebp-A8h] BYREF
  float v52[3]; // [esp+ACh] [ebp-9Ch] BYREF
  float v53[3]; // [esp+B8h] [ebp-90h] BYREF
  float sum_result[3]; // [esp+C4h] [ebp-84h] BYREF
  float scaled_result[3]; // [esp+D0h] [ebp-78h] BYREF
  float out_vector[3]; // [esp+DCh] [ebp-6Ch] BYREF
  float copy_result[3]; // [esp+E8h] [ebp-60h] BYREF
  float v58[3]; // [esp+F4h] [ebp-54h] BYREF
  float v59[9]; // [esp+100h] [ebp-48h] BYREF
  _BYTE v60[12]; // [esp+124h] [ebp-24h] BYREF
  float lhs[3]; // [esp+130h] [ebp-18h] BYREF
  float v62; // [esp+13Ch] [ebp-Ch]
  float v63; // [esp+140h] [ebp-8h]
  float *v64; // [esp+144h] [ebp-4h]

  rf_vector3_default_construct_noop(v60);
  rf_vector3_default_construct_noop(lhs);
  v63 = scalar * a4;
  result = this;
  if ( (*((_DWORD *)this + 4) & 1) == 0 )
  {
    v64 = (float *)(*((_DWORD *)this + 36) + 36 * a2);
    rf_matrix3_construct((char *)v59);
    v41 = *(_DWORD *)(*(_DWORD *)this + 168);
    if ( v41 )
    {
      if ( v41 == 1 )
      {
        rf_random_unit_vector_from_z_and_azimuth(lhs);
        v31 = -*((float *)this + 34);
        v34 = rf_random_float_range(v31, *((float *)this + 34)) + *((float *)this + 33);
        v17 = rf_vector_multiply_scalar(lhs, v50, v34);
        rf_vector_copy(v64 + 6, v49, v17);
        rf_vector_rotate_by_matrix3(v64 + 6, (float *)this + 14);
        if ( (*(_DWORD *)(*(_DWORD *)this + 172) & 8) != 0 )
          rf_vector_accumulate(v64 + 6, a5);
        rf_vector3_scale_in_place_return_self(lhs, *((float *)this + 30));
        rf_vector_accumulate(lhs, (float *)this + 23);
        rf_vector_rotate_by_matrix3(lhs, (float *)this + 14);
        v18 = rf_vector_subtract((const float *)this + 8, v48, (const float *)this + 11);
        v19 = rf_vector_multiply_scalar(v18, v47, scalar);
        v20 = rf_vector_add((const float *)this + 11, v46, v19);
        rf_vector_accumulate(lhs, v20);
        v21 = rf_random_float_range(0.0, v63);
        *v64 = v21;
        v22 = rf_vector_multiply_scalar(v64 + 6, v45, *v64);
        v23 = rf_vector_add(lhs, v44, v22);
        rf_vector_copy(v64 + 3, v43, v23);
        v62 = (double)*(int *)(*(_DWORD *)this + 160) * *(float *)(*(_DWORD *)this + 164);
        v32 = -v62;
        v33 = (double)*(int *)(*(_DWORD *)this + 160);
        v24 = rf_random_float_range(v32, v62);
        v64[1] = (v24 + v33) / 4800.0;
      }
    }
    else
    {
      if ( *((float *)this + 34) == 0.0 )
      {
        v26 = -*((float *)this + 33);
        v6 = rf_vector3_set_components_return_destination(v58, 0.0, v26, 0.0);
        rf_vector_copy(v64 + 6, copy_result, v6);
      }
      else
      {
        v27 = -*((float *)this + 34);
        v7 = rf_random_float_range(v27, *((float *)this + 34));
        v64[6] = v7;
        v28 = -*((float *)this + 34);
        v8 = rf_random_float_range(v28, *((float *)this + 34));
        v64[8] = v8;
        v29 = -*((float *)this + 34);
        v40 = -*((float *)this + 33);
        v9 = rf_random_float_range(v29, *((float *)this + 34));
        v64[7] = v9 + v40;
      }
      rf_quaternion_to_matrix3_rows((float *)this + 26, v59);
      rf_vector_rotate_by_matrix3(v64 + 6, v59);
      rf_vector_rotate_by_matrix3(v64 + 6, (float *)this + 14);
      if ( (*(_DWORD *)(*(_DWORD *)this + 172) & 8) != 0 )
        rf_vector_accumulate(v64 + 6, a5);
      v39 = *((float *)this + 30) / 2.0;
      v38 = -*((float *)this + 30) / 2.0;
      lhs[0] = rf_random_float_range(v38, v39);
      v37 = *((float *)this + 31) / 2.0;
      v36 = -*((float *)this + 31) / 2.0;
      lhs[2] = rf_random_float_range(v36, v37);
      lhs[1] = 0.0;
      rf_vector_rotate_by_matrix3(lhs, v59);
      rf_vector_accumulate(lhs, (float *)this + 23);
      rf_vector_rotate_by_matrix3(lhs, (float *)this + 14);
      v10 = rf_vector_subtract((const float *)this + 8, out_vector, (const float *)this + 11);
      v11 = rf_vector_multiply_scalar(v10, scaled_result, scalar);
      v12 = rf_vector_add((const float *)this + 11, sum_result, v11);
      rf_vector_accumulate(lhs, v12);
      v13 = rf_random_float_range(0.0, v63);
      *v64 = v13;
      v14 = rf_vector_multiply_scalar(v64 + 6, v53, *v64);
      v15 = rf_vector_add(lhs, v52, v14);
      rf_vector_copy(v64 + 3, v51, v15);
      v62 = (double)*(int *)(*(_DWORD *)this + 160) * *(float *)(*(_DWORD *)this + 164);
      v30 = -v62;
      v35 = (double)*(int *)(*(_DWORD *)this + 160);
      v16 = rf_random_float_range(v30, v62);
      v64[1] = (v16 + v35) / 4800.0;
    }
    if ( (*(_DWORD *)(*(_DWORD *)this + 172) & 0x10) != 0 )
    {
      v25 = rf_random_float_range(0.0, 6.2831855);
      v64[2] = v25;
    }
    else
    {
      v64[2] = 0.0;
    }
    ++*((_DWORD *)this + 37);
    return this;
  }
  return result;
}

