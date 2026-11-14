// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0056CBA0 rf_vector3_closest_point_on_segment
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly, x87 return flow and callers): Arguments (point, segmentStart, segmentEnd, outClosest). Computes segment length and unit direction; projects point-start onto the direction and clamps the projection to [0,length]. Writes start+direction*projection and returns the clamped distance along the segment. Degenerate zero-length segment writes start and returns 0.
double __cdecl rf_vector3_closest_point_on_segment(
        const float *point,
        const float *segment_start,
        const float *segment_end,
        float *closest_point)
{
  float *v4; // eax
  float *v6; // eax
  float *v7; // eax
  float *v8; // eax
  float v9; // [esp+8h] [ebp-9Ch]
  float v10[3]; // [esp+Ch] [ebp-98h] BYREF
  float sum_result[3]; // [esp+18h] [ebp-8Ch] BYREF
  float scaled_result[3]; // [esp+24h] [ebp-80h] BYREF
  float v13[3]; // [esp+30h] [ebp-74h] BYREF
  float v14[3]; // [esp+3Ch] [ebp-68h] BYREF
  float v15[3]; // [esp+48h] [ebp-5Ch] BYREF
  float v16[3]; // [esp+54h] [ebp-50h] BYREF
  float copy_result[3]; // [esp+60h] [ebp-44h] BYREF
  float out_vector[3]; // [esp+6Ch] [ebp-38h] BYREF
  float v19[3]; // [esp+78h] [ebp-2Ch] BYREF
  int scalar; // [esp+84h] [ebp-20h] BYREF
  float vector[3]; // [esp+88h] [ebp-1Ch] BYREF
  float v22; // [esp+94h] [ebp-10h]
  float destination[3]; // [esp+98h] [ebp-Ch] BYREF

  rf_vector3_default_construct_noop(destination);
  rf_vector3_default_construct_noop(v19);
  rf_vector3_default_construct_noop(vector);
  v4 = rf_vector_subtract(segment_end, out_vector, segment_start);
  rf_vector_copy(destination, copy_result, v4);
  v22 = rf_vector3_length(destination);
  if ( v22 == 0.0 )
  {
    rf_vector_copy(closest_point, v16, segment_start);
    return 0.0;
  }
  else
  {
    rf_vector_copy(vector, v15, destination);
    v9 = 1.0 / v22;
    rf_vector3_scale_in_place_return_self(vector, v9);
    v6 = rf_vector_subtract(point, v14, segment_start);
    rf_vector_copy(v19, v13, v6);
    *(float *)&scalar = rf_vector_dot(vector, v19);
    rf_float_clamp_in_place((float *)&scalar, 0.0, v22);
    v7 = rf_vector_multiply_scalar(vector, scaled_result, *(float *)&scalar);
    v8 = rf_vector_add(segment_start, sum_result, v7);
    rf_vector_copy(closest_point, v10, v8);
    return *(float *)&scalar;
  }
}

