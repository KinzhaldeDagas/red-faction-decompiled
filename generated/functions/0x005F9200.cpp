// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005F9200 rf_scene_frame_channel_build_sample44
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): This72-byte state,args destination44bytes,float frame. i=floor(frame),j=i+1. If j<definition.count216,usesfraction frame-floor(frame) to blend CACHED previous position44 with current16,and cached previous quaternion56 to current28;raw neighboring frame positions/quaternions are NOT used in this branch. Converts resulting quaternion to matrix,rotates unitY(0,1,0),normalizes,destination direction12..23;destination position0..11. Separately linearly blends five RAW frame scalars at28..44 into destination24..40. If j>=count,bypasses caches/attachment state and copies position/quat/scalars from LAST raw frame instead,still derives normalized unitY direction. No lower-bound/zero-count/output-capacity checks;negative frame can read before pool. Does not update state. Return incidental frame
// pointer,not output/status. Called by scene simulation0x5BCC60/0x5BD420 with arrays of44-byte samples.
float *__thiscall rf_scene_frame_channel_build_sample44(const float *this, float *destination, float a3)
{
  float *v3; // eax
  float *result; // eax
  float *v5; // eax
  float *v6; // eax
  float *v7; // eax
  float *value; // [esp+8h] [ebp-C4h]
  float v10[3]; // [esp+14h] [ebp-B8h] BYREF
  float v11[3]; // [esp+20h] [ebp-ACh] BYREF
  float v12[3]; // [esp+2Ch] [ebp-A0h] BYREF
  float sum_result[3]; // [esp+38h] [ebp-94h] BYREF
  float scaled_result[3]; // [esp+44h] [ebp-88h] BYREF
  float v15[3]; // [esp+50h] [ebp-7Ch] BYREF
  float v16[3]; // [esp+5Ch] [ebp-70h] BYREF
  float v17[3]; // [esp+68h] [ebp-64h] BYREF
  float copy_result[3]; // [esp+74h] [ebp-58h] BYREF
  float scalar; // [esp+80h] [ebp-4Ch]
  float *v20; // [esp+84h] [ebp-48h]
  float v21; // [esp+88h] [ebp-44h]
  float *v22; // [esp+8Ch] [ebp-40h]
  int v23; // [esp+90h] [ebp-3Ch]
  float v24[9]; // [esp+94h] [ebp-38h] BYREF
  int v25[4]; // [esp+B8h] [ebp-14h] BYREF
  int v26; // [esp+C8h] [ebp-4h]

  v26 = (int)rf_floor_float(a3);
  v23 = v26 + 1;
  rf_float4_construct_zero_zero_zero_one((float *)v25);
  rf_matrix3_construct((char *)v24);
  if ( v23 < *(_DWORD *)(*(_DWORD *)this + 216) )
  {
    v22 = (float *)(*(_DWORD *)(*(_DWORD *)this + 220) + 48 * v26);
    v20 = (float *)(*(_DWORD *)(*(_DWORD *)this + 220) + 48 * v23);
    v21 = a3 - (double)(int)rf_floor_float(a3);
    scalar = 1.0 - v21;
    value = rf_vector_multiply_scalar(this + 4, scaled_result, v21);
    v5 = rf_vector_multiply_scalar(this + 11, v15, scalar);
    v6 = rf_vector_add(v5, sum_result, value);
    rf_vector_copy(destination, v12, v6);
    rf_quaternion_interpolate((float *)v25, (float *)this + 14, (float *)this + 7, v21);
    rf_quaternion_to_matrix3_rows((float *)v25, v24);
    v7 = rf_vector3_set_components_return_destination(v11, 0.0, 1.0, 0.0);
    rf_vector_copy(destination + 3, v10, v7);
    rf_vector_rotate_by_matrix3(destination + 3, v24);
    rf_vector_normalize(destination + 3);
    destination[6] = v22[7] * scalar + v20[7] * v21;
    destination[7] = v22[8] * scalar + v20[8] * v21;
    destination[8] = v22[9] * scalar + v20[9] * v21;
    destination[9] = v22[10] * scalar + v20[10] * v21;
    result = v22;
    destination[10] = v22[11] * scalar + v20[11] * v21;
  }
  else
  {
    rf_vector_copy(
      destination,
      copy_result,
      (const float *)(*(_DWORD *)(*(_DWORD *)this + 220) + 48 * (*(_DWORD *)(*(_DWORD *)this + 216) - 1)));
    rf_float4_copy_return_destination(
      (float *)v25,
      (float *)(*(_DWORD *)(*(_DWORD *)this + 220) + 48 * (*(_DWORD *)(*(_DWORD *)this + 216) - 1) + 12));
    rf_quaternion_to_matrix3_rows((float *)v25, v24);
    v3 = rf_vector3_set_components_return_destination(v17, 0.0, 1.0, 0.0);
    rf_vector_copy(destination + 3, v16, v3);
    rf_vector_rotate_by_matrix3(destination + 3, v24);
    rf_vector_normalize(destination + 3);
    destination[6] = *(float *)(*(_DWORD *)(*(_DWORD *)this + 220) + 48 * (*(_DWORD *)(*(_DWORD *)this + 216) - 1) + 28);
    destination[7] = *(float *)(*(_DWORD *)(*(_DWORD *)this + 220) + 48 * (*(_DWORD *)(*(_DWORD *)this + 216) - 1) + 32);
    destination[8] = *(float *)(*(_DWORD *)(*(_DWORD *)this + 220) + 48 * (*(_DWORD *)(*(_DWORD *)this + 216) - 1) + 36);
    destination[9] = *(float *)(*(_DWORD *)(*(_DWORD *)this + 220) + 48 * (*(_DWORD *)(*(_DWORD *)this + 216) - 1) + 40);
    result = *(float **)(*(_DWORD *)this + 220);
    destination[10] = result[12 * *(_DWORD *)(*(_DWORD *)this + 216) - 1];
  }
  return result;
}

