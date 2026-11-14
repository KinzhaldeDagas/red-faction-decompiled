// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00525B20 rf_face_flags_test_bit80
// UNREALRED VERIFIED [decal-face-links-20261028]: Returns bool(*flags_word &0x80). Caller passes Face+40 flags address, not full face; decal face projector rejects set bit. Editor-facing meaning not inferred here.
bool __thiscall rf_face_flags_test_bit80(_DWORD *this)
{
  return (*this & 0x80) != 0;
}

