// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00566BC0 rf_float4_copy_return_destination
// UNREALRED VERIFIED [transfer-scene-20261028]: Thiscall destination,source pointer. Copies four float components sequentially and returns destination. No null or overlap guard; performs no quaternion/matrix math or normalization.
float *__thiscall rf_float4_copy_return_destination(float *this, float *a2)
{
  *this = *a2;
  *(this + 1) = a2[1];
  *(this + 2) = a2[2];
  *(this + 3) = a2[3];
  return this;
}

