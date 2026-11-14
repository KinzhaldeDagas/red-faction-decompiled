// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005211D0 rf_face_is_see_through
// UNREALRED VERIFIED [sky-face-render-contract] Returns Face+0x28 flag bit 0x40. The retail room renderer uses it to split accepted faces into the see-through queue rather than to decide topology ownership.
bool __thiscall rf_face_is_see_through(_DWORD *this)
{
  return (*this & 0x40) != 0;
}

