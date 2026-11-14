// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0054CBE0 rf_plane4_copy_normal_scalar
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, quaternion arithmetic, signed integer normalization, matrix conversion and custom variadic formatting): Copies first3 floats through vector-copy helper then fourth scalar from source+12 into receiver,returns receiver. No normalization,sign change or allocation. Exact self-copy works;arbitrary partially overlapping source/output not protected by a full four-component snapshot.
float *__thiscall rf_plane4_copy_normal_scalar(float *this, float *a2)
{
  rf_vector3_copy_return_destination(this, a2);
  *(this + 3) = a2[3];
  return this;
}

