// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00525AD0 rf_face_flags_test_bit10
// UNREALRED VERIFIED [decal-projection-20261028]: Returns boolean(*flags_word &0x10). Caller supplies Face+40 flags address, not full face. Exact authored/editor meaning of bit remains unproven here.
bool __thiscall rf_face_flags_test_bit10(_DWORD *this)
{
  return (*this & 0x10) != 0;
}

