// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0041C9E0 rf_vector3_components_equal
// UNREALRED VERIFIED [decal-face-links-20261028]: Returns true only when all three corresponding float components compare equal. No tolerance or distance test. IEEE ordinary equality semantics: signed zeros equal; NaN does not compare equal. No pointer validity checks.
bool __thiscall rf_vector3_components_equal(float *this, float *a2)
{
  return *a2 == *this && a2[1] == *(this + 1) && a2[2] == *(this + 2);
}

