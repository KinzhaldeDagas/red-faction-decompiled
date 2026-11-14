// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0055DD60 rf_transform48_construct_rotation_zero_translation
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, matrix multiplication order, degenerate basis repair, inverse behavior, scalar motion profiles and x87 intrinsic identity): ECX48-byte output plus3x3 rotation pointer, RET4. Sequentially copies9floats into first36bytes, writes float0 to fields36/40/44, returns receiver. Layout is contiguous3x3 plus zero trailing XYZ. Does not copy incoming translation or validate rotation; exact self source safe, other partial overlap can overwrite later source reads.
float *__thiscall rf_transform48_construct_rotation_zero_translation(float *this, const float *a2)
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

