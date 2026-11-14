// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00595E80 rf_scene_point_track_interpolate_sample
// UNREALRED VERIFIED [transfer-scene-20261028]: Thiscall runtime record, fractional sample index. floor(index) selects definition sample array+176 at stride36; next index=base+1 unless >=count+172, then base. Does not validate negative/base-out-of-range index or null definition. Blends sample vector+0 to runtime+12 unless runtime flag0x20000000 is set. Blends sample scalars+24,+28,+12,+16,+20 into runtime+36,+52,+40,+44,+48. Copies NEXT sample flags DWORD+32 bit0 into runtime bit30, even at zero interpolation fraction. If position updates enabled and runtime bit28 set, queries0x564D80 using runtime+4 and low28 bits of flags, builds transform0x55DEA0 and applies0x55EAC0 to runtime+12. No clamping or time-to-sample conversion; return pointer is incidental.
float *__thiscall rf_scene_point_track_interpolate_sample(float *this, float a2)
{
  float *v2; // eax
  float *v3; // eax
  float *result; // eax
  float *v5; // eax
  float *value; // [esp+8h] [ebp-CCh]
  float v8[3]; // [esp+14h] [ebp-C0h] BYREF
  char v9[12]; // [esp+20h] [ebp-B4h] BYREF
  float copy_result[3]; // [esp+2Ch] [ebp-A8h] BYREF
  float sum_result[3]; // [esp+38h] [ebp-9Ch] BYREF
  float scaled_result[3]; // [esp+44h] [ebp-90h] BYREF
  float v13[3]; // [esp+50h] [ebp-84h] BYREF
  float v14[12]; // [esp+5Ch] [ebp-78h] BYREF
  float v15[9]; // [esp+8Ch] [ebp-48h] BYREF
  float v16[3]; // [esp+B0h] [ebp-24h] BYREF
  int v17; // [esp+BCh] [ebp-18h]
  float scalar; // [esp+C0h] [ebp-14h]
  int v19; // [esp+C4h] [ebp-10h]
  float *vector; // [esp+C8h] [ebp-Ch]
  float v21; // [esp+CCh] [ebp-8h]
  float *v22; // [esp+D0h] [ebp-4h]

  v19 = (int)rf_floor_float(a2);
  v17 = v19 + 1;
  if ( v19 + 1 >= *(_DWORD *)(*(_DWORD *)this + 172) )
    v17 = v19;
  v22 = (float *)(*(_DWORD *)(*(_DWORD *)this + 176) + 36 * v19);
  vector = (float *)(*(_DWORD *)(*(_DWORD *)this + 176) + 36 * v17);
  v21 = a2 - (double)(int)rf_floor_float(a2);
  scalar = 1.0 - v21;
  if ( ((*((_DWORD *)this + 2) >> 29) & 1) == 0 )
  {
    value = rf_vector_multiply_scalar(vector, scaled_result, v21);
    v2 = rf_vector_multiply_scalar(v22, v13, scalar);
    v3 = rf_vector_add(v2, sum_result, value);
    rf_vector_copy(this + 3, copy_result, v3);
  }
  *(this + 9) = v22[6] * scalar + vector[6] * v21;
  *(this + 13) = v22[7] * scalar + vector[7] * v21;
  *(this + 10) = v22[3] * scalar + vector[3] * v21;
  *(this + 11) = v22[4] * scalar + vector[4] * v21;
  *(this + 12) = v22[5] * scalar + vector[5] * v21;
  result = this;
  *((_DWORD *)this + 2) = (((_DWORD)vector[8] & 1) << 30) | *(_DWORD *)(this + 2) & 0xBFFFFFFF;
  if ( ((*((_DWORD *)this + 2) >> 29) & 1) == 0 )
  {
    result = this;
    if ( ((*((_DWORD *)this + 2) >> 28) & 1) != 0 )
    {
      rf_vector3_default_construct_noop(v16);
      rf_matrix3_construct((char *)v15);
      rf_model_handle_get_node_transform_adapter(*((_DWORD **)this + 1), v16, v15, *(_DWORD *)(this + 2) & 0xFFFFFFF);
      rf_affine3x4_set_rotation_translation(v14, v16, v15);
      v5 = rf_affine3x4_transform_point(v14, (float *)v9, this + 3);
      return rf_vector_copy(this + 3, v8, v5);
    }
  }
  return result;
}

