// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005395D0 rf_world_face_is_fullbright
// UNREALRED VERIFIED [general-gap-20260830]: Returns whether authored world-face flags contain 0x20. Its sole direct caller records this for static lightmap construction; the dynamic additive-light pass does not use it as a receiver exclusion.
bool __thiscall rf_world_face_is_fullbright(_DWORD *this)
{
  return (*this & 0x20) != 0;
}

