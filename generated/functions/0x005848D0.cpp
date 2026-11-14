// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005848D0 rf_short_quaternion_copy_words_return_this
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): Thiscall destination inECX,source fourWORDs. Forward scalar copy of8 bytes,returns destination. No scale,normalization,allocation or alias validation;distinct compiled identical assignment/copy wrappers used by key getter/interpolator.
_WORD *__thiscall rf_short_quaternion_copy_words_return_this(_WORD *this, _WORD *a2)
{
  *this = *a2;
  *(this + 1) = a2[1];
  *(this + 2) = a2[2];
  *(this + 3) = a2[3];
  return this;
}

