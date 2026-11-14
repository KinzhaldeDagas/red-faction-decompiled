// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0055E5C0 rf_affine48_copy_rotation_return_self
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, 48-byte layout permutations, interpolation aliasing, packed3x4 template/stack offsets and wrapped game clocks): ECX affine source plus3x3 destination, RET4. Sequentially copies first9floats, returns SOURCE receiver. Translation9..11 unchanged/unread; partial overlap can affect later source reads, exact same-base alias safe.
float *__thiscall rf_affine48_copy_rotation_return_self(float *this, float *a2)
{
  *a2 = *this;
  a2[1] = *(this + 1);
  a2[2] = *(this + 2);
  a2[3] = *(this + 3);
  a2[4] = *(this + 4);
  a2[5] = *(this + 5);
  a2[6] = *(this + 6);
  a2[7] = *(this + 7);
  a2[8] = *(this + 8);
  return this;
}

