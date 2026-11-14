// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0055EB80 rf_affine3x4_copy_rotation_zero_translation
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, character-cache callers, resource readers and constructor/destructor paths): Copies source9 rotation floats into destination[0..8], then writes destination[9..11]=0. Returns destination. Does not transpose, normalize or preserve prior translation. Sequential stores make identical input/output safe; arbitrary partial overlap is not specially handled.
float *__thiscall rf_affine3x4_copy_rotation_zero_translation(float *this, float *a2)
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
  *(this + 9) = 0.0;
  *(this + 10) = 0.0;
  *(this + 11) = 0.0;
  return this;
}

