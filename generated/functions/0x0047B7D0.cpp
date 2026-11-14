// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0047B7D0 rf_rfl_light_profile_decode
// VERIFIED: Decodes RFL light profile: bits 4..7 -> renderer shape; bits 8..11 -> intensity mode; bit 0x1 -> spatial category flag; 0x2 -> interpolation; 0x4/0x2000 -> priority-selected renderer category value; 0x8 -> runtime enabled state.
// UNREALRED VERIFIED [rfl-light-decode]: Decodes the authored light shape, intensity, enabled state, interpolation mode, and category bits; unresolved source labels remain unnamed.
int __thiscall rf_rfl_light_profile_decode(int this, __int16 a2)
{
  *(_DWORD *)(this + 64) = (a2 & 0xF0) >> 4;
  *(_DWORD *)(this + 60) = (a2 & 0xF00) >> 8;
  *(_BYTE *)(this + 134) = (a2 & 1) != 0;
  *(_BYTE *)(this + 135) = (a2 & 2) != 0;
  *(_BYTE *)(this + 132) = (a2 & 4) != 0;
  *(_BYTE *)(this + 145) = (a2 & 8) != 0;
  *(_BYTE *)(this + 133) = (a2 & 0x2000) != 0;
  return this;
}

