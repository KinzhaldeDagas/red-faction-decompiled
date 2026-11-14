// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0041CA80 rf_plane_construct_from_normal_point
// UNREALRED VERIFIED [projected-shadow-cone-20260903]: Constructs a plane from a supplied normal and point; the scalar is -dot(normal, point).
void *__thiscall rf_plane_construct_from_normal_point(void *this, float *a2, int a3)
{
  rf_vector3_default_construct_noop(this);
  rf_plane4_construct_normal_point((float *)this, a2, a3);
  return this;
}

