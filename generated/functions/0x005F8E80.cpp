// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005F8E80 rf_scene_frame_channel_state_update
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): Arg float frame. If prior lastSample12>0,copies current position16/quaternion28 to previous44/56 BEFORE update. Unless flags8 bit29 set,gets i=floor(frame),j=i+1. If j<definition.frameCount216,lerps raw frame positions(i,j) byfraction frame-floor(frame),interpolates raw quaternions using rf_quaternion_interpolate;otherwise copies final raw frame. NO lower-frame or zero-count guard (negative i/last=-1 can read before pool). If bit30 set,gets attachment position/matrix via0x564D80(attachment4,index=flags&0x1FFFFFFF),builds affine transform,transforms current point,builds affine from current quaternion/position,composes via0x55E420,extracts quaternion via0x582420. Attachment getter status ignored. If OLD lastSample12<=0,copies updated current to previous AFTER update. Finally stores
// lastSample=frame ifframe<count,else count-1;negative frame remains negative. Freeze bit29 skips current/attachment update but still history/time updates. No output scalar sampling,allocation or normalization here.
void __thiscall rf_scene_frame_channel_state_update(float *this, float a2)
{
  float *v2; // eax
  float *v3; // eax
  float *v4; // eax
  float *value; // [esp+8h] [ebp-134h]
  float v7[3]; // [esp+18h] [ebp-124h] BYREF
  float v8[4]; // [esp+24h] [ebp-118h] BYREF
  float v9[3]; // [esp+34h] [ebp-108h] BYREF
  float v10[3]; // [esp+40h] [ebp-FCh] BYREF
  float v11[3]; // [esp+4Ch] [ebp-F0h] BYREF
  float sum_result[3]; // [esp+58h] [ebp-E4h] BYREF
  float scaled_result[3]; // [esp+64h] [ebp-D8h] BYREF
  float v14[3]; // [esp+70h] [ebp-CCh] BYREF
  float v15[3]; // [esp+7Ch] [ebp-C0h] BYREF
  float copy_result[3]; // [esp+88h] [ebp-B4h] BYREF
  float v17[12]; // [esp+94h] [ebp-A8h] BYREF
  float v18[12]; // [esp+C4h] [ebp-78h] BYREF
  float v19[9]; // [esp+F4h] [ebp-48h] BYREF
  float v20[3]; // [esp+118h] [ebp-24h] BYREF
  float scalar; // [esp+124h] [ebp-18h]
  float *vector; // [esp+128h] [ebp-14h]
  float v23; // [esp+12Ch] [ebp-10h]
  float *v24; // [esp+130h] [ebp-Ch]
  int v25; // [esp+134h] [ebp-8h]
  int v26; // [esp+138h] [ebp-4h]

  if ( *(this + 3) > 0.0 )
  {
    rf_vector_copy(this + 11, copy_result, this + 4);
    rf_float4_copy_return_destination(this + 14, this + 7);
  }
  if ( ((*((_DWORD *)this + 2) >> 29) & 1) == 0 )
  {
    v26 = (int)rf_floor_float(a2);
    v25 = v26 + 1;
    if ( v26 + 1 < *(_DWORD *)(*(_DWORD *)this + 216) )
    {
      v24 = (float *)(*(_DWORD *)(*(_DWORD *)this + 220) + 48 * v26);
      vector = (float *)(*(_DWORD *)(*(_DWORD *)this + 220) + 48 * v25);
      v23 = a2 - (double)(int)rf_floor_float(a2);
      scalar = 1.0 - v23;
      value = rf_vector_multiply_scalar(vector, scaled_result, v23);
      v2 = rf_vector_multiply_scalar(v24, v14, scalar);
      v3 = rf_vector_add(v2, sum_result, value);
      rf_vector_copy(this + 4, v11, v3);
      rf_quaternion_interpolate(this + 7, v24 + 3, vector + 3, v23);
    }
    else
    {
      rf_vector_copy(
        this + 4,
        v15,
        (const float *)(*(_DWORD *)(*(_DWORD *)this + 220) + 48 * (*(_DWORD *)(*(_DWORD *)this + 216) - 1)));
      rf_float4_copy_return_destination(
        this + 7,
        (float *)(*(_DWORD *)(*(_DWORD *)this + 220) + 48 * (*(_DWORD *)(*(_DWORD *)this + 216) - 1) + 12));
    }
    if ( ((*((_DWORD *)this + 2) >> 30) & 1) != 0 )
    {
      rf_vector3_default_construct_noop(v20);
      rf_matrix3_construct((char *)v19);
      rf_affine3x4_default_construct_noop(v18);
      rf_model_handle_get_node_transform_adapter(*((_DWORD **)this + 1), v20, v19, *(_DWORD *)(this + 2) & 0x1FFFFFFF);
      rf_affine3x4_set_rotation_translation(v17, v20, v19);
      v4 = rf_affine3x4_transform_point(v17, v10, this + 4);
      rf_vector_copy(this + 4, v9, v4);
      rf_affine3x4_set_quaternion_translation(v18, this + 7, this + 4);
      rf_affine3x4_multiply_second_by_first(v18, (int)v17, v18);
      rf_quaternion_from_matrix3x3(v8, v18);
      rf_float4_copy_return_destination(this + 7, v8);
    }
  }
  if ( *(this + 3) <= 0.0 )
  {
    rf_vector_copy(this + 11, v7, this + 4);
    rf_float4_copy_return_destination(this + 14, this + 7);
  }
  if ( a2 < (double)*(int *)(*(_DWORD *)this + 216) )
    *(this + 3) = a2;
  else
    *(this + 3) = (float)(*(_DWORD *)(*(_DWORD *)this + 216) - 1);
}

