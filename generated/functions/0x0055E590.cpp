// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0055E590 rf_affine48_copy_translation_return_self
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, 48-byte layout permutations, interpolation aliasing, packed3x4 template/stack offsets and wrapped game clocks): ECX affine source plus XYZ destination, RET4. Copies floats9/10/11 (offset36/40/44) into destination0/1/2, returns SOURCE affine receiver, not destination. No rotation read or normalization.
float *__thiscall rf_affine48_copy_translation_return_self(float *this, float *a2)
{
  *a2 = *(this + 9);
  a2[1] = *(this + 10);
  a2[2] = *(this + 11);
  return this;
}

