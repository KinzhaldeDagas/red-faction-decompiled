// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0051E9B0 rf_vector2_copy_return_source
// UNREALRED VERIFIED [renderer-helpers-20261028]: Copies two floats from stack source pointer into this destination and returns SOURCE pointer. Return is not destination. No allocation or additional coordinates copied.
float *__thiscall rf_vector2_copy_return_source(float *this, float *a2)
{
  *this = *a2;
  *(this + 1) = a2[1];
  return a2;
}

