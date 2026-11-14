// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005FB2C0 rf_scene_transform_track_state_update
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): Arg float frame;definition at0,frame pointerdefinition168,packedSIGNED15count164. i=floor(frame),j=i+1. Only if j<count and stateflags8 bit30clear,lerps raw positions/quaternions into state12/24. If at/after final interval,does NOT copy last frame;retains prior state (or constructor zero/identity). Negative i can read before frame array. If bit30clear and bit29set,queries attachment(pointer4,index=low29bits),ignores status,builds affine,transforms current position12. Builds quaternion/position affine,composes attachment using0x55E420,then BUG at0x5FB505 calls quaternion-TO-affine0x582CD0 with existing statequaternion24 asSOURCE,temporary composed matrix asDESTINATION. Overwrites composed temporary and never updates statequaternion from attachment. Thus attachment affects position but composed
// orientation is discarded. No final frame/time storage or scalar output. Return incidental pointer/flag;freeze bit30 bypasses both interpolation and attachment.
float *__thiscall rf_scene_transform_track_state_update(float *this, float a2)
{
  float *v2; // eax
  float *v3; // eax
  float *result; // eax
  float *v5; // eax
  float *value; // [esp+8h] [ebp-12Ch]
  float v8[3]; // [esp+14h] [ebp-120h] BYREF
  float v9[3]; // [esp+20h] [ebp-114h] BYREF
  float copy_result[3]; // [esp+2Ch] [ebp-108h] BYREF
  float sum_result[3]; // [esp+38h] [ebp-FCh] BYREF
  float scaled_result[3]; // [esp+44h] [ebp-F0h] BYREF
  float v13[3]; // [esp+50h] [ebp-E4h] BYREF
  float v14[12]; // [esp+5Ch] [ebp-D8h] BYREF
  float v15[9]; // [esp+8Ch] [ebp-A8h] BYREF
  float v16[3]; // [esp+B0h] [ebp-84h] BYREF
  float scalar; // [esp+BCh] [ebp-78h]
  float *vector; // [esp+C0h] [ebp-74h]
  float v19; // [esp+C4h] [ebp-70h]
  float *v20; // [esp+C8h] [ebp-6Ch]
  int v21; // [esp+CCh] [ebp-68h]
  _BYTE v22[48]; // [esp+D0h] [ebp-64h] BYREF
  float v23[12]; // [esp+100h] [ebp-34h] BYREF
  int v24; // [esp+130h] [ebp-4h]

  v24 = (int)rf_floor_float(a2);
  v21 = v24 + 1;
  if ( v24 + 1 < (__int16)(2 * *(_WORD *)(*(_DWORD *)this + 164)) >> 1 )
  {
    v20 = (float *)(*(_DWORD *)(*(_DWORD *)this + 168) + 28 * v24);
    vector = (float *)(*(_DWORD *)(*(_DWORD *)this + 168) + 28 * v21);
    v19 = a2 - (double)(int)rf_floor_float(a2);
    scalar = 1.0 - v19;
    if ( ((*((_DWORD *)this + 2) >> 30) & 1) == 0 )
    {
      value = rf_vector_multiply_scalar(vector, scaled_result, v19);
      v2 = rf_vector_multiply_scalar(v20, v13, scalar);
      v3 = rf_vector_add(v2, sum_result, value);
      rf_vector_copy(this + 3, copy_result, v3);
      rf_quaternion_interpolate(this + 6, v20 + 3, vector + 3, v19);
    }
  }
  else
  {
    v21 = v24;
  }
  rf_affine3x4_default_construct_noop(v22);
  rf_affine3x4_default_construct_noop(v23);
  result = this;
  if ( ((*((_DWORD *)this + 2) >> 30) & 1) == 0 )
  {
    result = (float *)((*((_DWORD *)this + 2) >> 29) & 1);
    if ( result )
    {
      rf_vector3_default_construct_noop(v16);
      rf_matrix3_construct((char *)v15);
      rf_model_handle_get_node_transform_adapter(*((_DWORD **)this + 1), v16, v15, *(_DWORD *)(this + 2) & 0x1FFFFFFF);
      rf_affine3x4_set_rotation_translation(v14, v16, v15);
      v5 = rf_affine3x4_transform_point(v14, v9, this + 3);
      rf_vector_copy(this + 3, v8, v5);
      rf_affine3x4_set_quaternion_translation(v23, this + 6, this + 3);
      rf_affine3x4_multiply_second_by_first(v23, (int)v14, v23);
      return rf_quaternion_to_affine3x4_zero_translation(this + 6, v23);
    }
  }
  return result;
}

