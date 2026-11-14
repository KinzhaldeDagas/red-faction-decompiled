// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0041CAB0 rf_plane4_construct_normal_point
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, unowned renderer entry recovery, camera-plane beam geometry and original PE bytes): Thiscall output plane,float3 normal,float3 point. Copies normal into first3 output floats via vector-copy helper,then sets fourthfloat D=-dot(normal,point),returns output. No normalization,degenerate-normal/finite checks or ownership changes. Copy occurs BEFORE dot computation,so arbitrary output/source aliasing is not protected by a full snapshot. Used by beam helper to define camera-facing plane.
float *__thiscall rf_plane4_construct_normal_point(float *this, float *source, float *a3)
{
  double v3; // st7
  float copy_result[3]; // [esp+4h] [ebp-Ch] BYREF

  rf_vector_copy(this, copy_result, source);
  v3 = rf_vector_dot(source, a3);
  *(this + 3) = v3 * -1.0;
  return this;
}

