// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00517E20 rf_face_is_invisible
// UNREALRED VERIFIED [sky-face-render-contract] Returns Face+0x28 flag bit 0x2000. The retail room renderer excludes this face unless its explicit debug override is active.
bool __thiscall rf_face_is_invisible(_DWORD *this)
{
  return (*this & 0x2000) != 0;
}

