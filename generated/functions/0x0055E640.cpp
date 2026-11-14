// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0055E640 rf_affine48_set_rotation_return_source
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, 48-byte layout permutations, interpolation aliasing, packed3x4 template/stack offsets and wrapped game clocks): ECX affine destination plus3x3 source, RET4. Sequentially copies9floats into offsets0..32 and returns SOURCE rotation pointer. Leaves destination translation36..44 unchanged; no validation or normalization. Exact same-base source safe, arbitrary partial overlap not protected.
const float *__thiscall rf_affine48_set_rotation_return_source(float *this, const float *a2)
{
  *this = *a2;
  *(this + 1) = a2[1];
  *(this + 2) = a2[2];
  *(this + 3) = a2[3];
  *(this + 4) = a2[4];
  *(this + 5) = a2[5];
  *(this + 6) = a2[6];
  *(this + 7) = a2[7];
  *(this + 8) = a2[8];
  return a2;
}

