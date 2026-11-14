// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005BF380 rf_particle_instance_sample_emitter_key
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, particle pool allocation, emission/integration branches, definition loader and original-PE math/constants): Uses floor(frame),next index and52-byte definition keys. Before last interval,linearly interpolates width+28,depth+32,size+36,speed+40,spread+44 into runtime+120/+124/+128/+132/+136. Unless runtime flags+20 mask0x20000000,also interpolates local position+92 and quaternion+104 through wrapped quaternion helper. Last/above-last selects final key; negative frame is NOT clamped. Evaluates material alpha into runtime+140. Unless manual-transform flag,mask0x10000000 resolves attachment via owner+24/low28-bit index,transforms local position and derives orientation through affine composition. No frame-count-zero,key index,material,owner or attachment validation; return register incidental.
float *__thiscall rf_particle_instance_sample_emitter_key(float *this, float a2)
{
  float *v2; // eax
  float *v3; // eax
  double v4; // st7
  float *result; // eax
  float *v6; // eax
  float *value; // [esp+8h] [ebp-118h]
  char v9[16]; // [esp+14h] [ebp-10Ch] BYREF
  float v10[3]; // [esp+24h] [ebp-FCh] BYREF
  char v11[12]; // [esp+30h] [ebp-F0h] BYREF
  float v12[3]; // [esp+3Ch] [ebp-E4h] BYREF
  float sum_result[3]; // [esp+48h] [ebp-D8h] BYREF
  float scaled_result[3]; // [esp+54h] [ebp-CCh] BYREF
  float v15[3]; // [esp+60h] [ebp-C0h] BYREF
  float copy_result[3]; // [esp+6Ch] [ebp-B4h] BYREF
  char v17[48]; // [esp+78h] [ebp-A8h] BYREF
  float v18[12]; // [esp+A8h] [ebp-78h] BYREF
  float v19[9]; // [esp+D8h] [ebp-48h] BYREF
  float v20[3]; // [esp+FCh] [ebp-24h] BYREF
  float *vector; // [esp+108h] [ebp-18h]
  float v22; // [esp+10Ch] [ebp-14h]
  float scalar; // [esp+110h] [ebp-10h]
  float *v24; // [esp+114h] [ebp-Ch]
  int v25; // [esp+118h] [ebp-8h]
  int v26; // [esp+11Ch] [ebp-4h]

  v26 = (int)rf_floor_float(a2);
  v25 = v26 + 1;
  if ( v26 + 1 < *(_DWORD *)(*(_DWORD *)this + 204) )
  {
    v24 = (float *)(*(_DWORD *)(*(_DWORD *)this + 208) + 52 * v26);
    vector = (float *)(*(_DWORD *)(*(_DWORD *)this + 208) + 52 * v25);
    v22 = a2 - (double)(int)rf_floor_float(a2);
    scalar = 1.0 - v22;
    if ( ((*((_DWORD *)this + 5) >> 29) & 1) == 0 )
    {
      value = rf_vector_multiply_scalar(vector, scaled_result, v22);
      v2 = rf_vector_multiply_scalar(v24, v15, scalar);
      v3 = rf_vector_add(v2, sum_result, value);
      rf_vector_copy(this + 23, v12, v3);
      rf_quaternion_interpolate(this + 26, v24 + 3, vector + 3, v22);
    }
    *(this + 32) = v24[9] * scalar + vector[9] * v22;
    *(this + 30) = v24[7] * scalar + vector[7] * v22;
    *(this + 31) = v24[8] * scalar + vector[8] * v22;
    *(this + 33) = v24[10] * scalar + vector[10] * v22;
    *(this + 34) = v24[11] * scalar + vector[11] * v22;
  }
  else
  {
    if ( ((*((_DWORD *)this + 5) >> 29) & 1) == 0 )
    {
      rf_vector_copy(
        this + 23,
        copy_result,
        (const float *)(*(_DWORD *)(*(_DWORD *)this + 208) + 52 * (*(_DWORD *)(*(_DWORD *)this + 204) - 1)));
      rf_float4_copy_return_destination(
        this + 26,
        (float *)(*(_DWORD *)(*(_DWORD *)this + 208) + 52 * (*(_DWORD *)(*(_DWORD *)this + 204) - 1) + 12));
    }
    *(this + 32) = *(float *)(*(_DWORD *)(*(_DWORD *)this + 208) + 52 * (*(_DWORD *)(*(_DWORD *)this + 204) - 1) + 36);
    *(this + 30) = *(float *)(*(_DWORD *)(*(_DWORD *)this + 208) + 52 * (*(_DWORD *)(*(_DWORD *)this + 204) - 1) + 28);
    *(this + 31) = *(float *)(*(_DWORD *)(*(_DWORD *)this + 208) + 52 * (*(_DWORD *)(*(_DWORD *)this + 204) - 1) + 32);
    *(this + 33) = *(float *)(*(_DWORD *)(*(_DWORD *)this + 208) + 52 * (*(_DWORD *)(*(_DWORD *)this + 204) - 1) + 40);
    *(this + 34) = *(float *)(*(_DWORD *)(*(_DWORD *)this + 208) + 52 * (*(_DWORD *)(*(_DWORD *)this + 204) - 1) + 44);
  }
  v4 = rf_material_evaluate_alpha(
         (int *)(*(_DWORD *)(*(_DWORD *)(*(_DWORD *)this + 132) + 140) + 200 * *(_DWORD *)(*(_DWORD *)this + 196)),
         a2);
  result = this;
  *(this + 35) = v4;
  if ( ((*((_DWORD *)this + 5) >> 29) & 1) == 0 )
  {
    result = this;
    if ( ((*((_DWORD *)this + 5) >> 28) & 1) != 0 )
    {
      rf_affine3x4_default_construct_noop(v18);
      rf_vector3_default_construct_noop(v20);
      rf_matrix3_construct((char *)v19);
      rf_model_handle_get_node_transform_adapter(*((_DWORD **)this + 6), v20, v19, *(_DWORD *)(this + 5) & 0xFFFFFFF);
      rf_affine3x4_set_rotation_translation((float *)v17, v20, v19);
      v6 = rf_affine3x4_transform_point((float *)v17, (float *)v11, this + 23);
      rf_vector_copy(this + 23, v10, v6);
      rf_affine3x4_set_quaternion_translation(v18, this + 26, this + 23);
      rf_affine3x4_multiply_second_by_first(v18, (int)v18, (float *)v17);
      rf_quaternion_from_matrix3x3((float *)v9, v18);
      return rf_float4_copy_return_destination(this + 26, (float *)v9);
    }
  }
  return result;
}

