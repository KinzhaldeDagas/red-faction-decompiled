// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00525AF0 rf_vector2_accumulate
// UNREALRED VERIFIED [decal-updates-20261028]: Adds two supplied float components into destination this[0]/this[1] and returns this. No alias guard, clamping or normalization.
float *__thiscall rf_vector2_accumulate(float *this, float *a2)
{
  *this = *this + *a2;
  *(this + 1) = *(this + 1) + a2[1];
  return this;
}

