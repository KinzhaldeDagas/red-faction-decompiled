// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0040CE30 rf_vector3_copy_return_destination
// UNREALRED VERIFIED [renderer-overlays-20261028]: Copies exactly three float components from source to this destination,returns destination pointer. No allocation or normalization.
float *__thiscall rf_vector3_copy_return_destination(float *this, float *a2)
{
  *this = *a2;
  *(this + 1) = a2[1];
  *(this + 2) = a2[2];
  return this;
}

