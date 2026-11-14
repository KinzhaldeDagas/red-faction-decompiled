// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0047B7A0 rf_rfl_light_set_enabled
// UNREALRED VERIFIED [world-uid-ownership]: Applies one enabled byte to the renderer-light handle at +0x94 and mirrors it into the RFL runtime-light state at +0x91.
int __thiscall rf_rfl_light_set_enabled(int this, char a2)
{
  rf_renderer_light_set_enabled(*(_DWORD *)(this + 148), a2);
  *(_BYTE *)(this + 145) = a2;
  return this;
}

