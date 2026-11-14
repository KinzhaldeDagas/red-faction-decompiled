// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00556E10 rf_plane_point_from_negative_offset_normal
// UNREALRED VERIFIED [renderer-overlays-20261028]: Treats this as four floats normalXYZ,planeoffsetD; writes output=-D*normal through vector scalar helper,returns output pointer. Produces a point satisfying plane equation only when normal is unit length (or special D0); does not divide by normal squaredlength or normalize.
float *__thiscall rf_plane_point_from_negative_offset_normal(const float *this, float *scaled_result)
{
  float scalar; // [esp+0h] [ebp-8h]

  scalar = -*(this + 3);
  rf_vector_multiply_scalar(this, scaled_result, scalar);
  return scaled_result;
}

