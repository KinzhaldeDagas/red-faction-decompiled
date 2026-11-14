// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005279D0 rf_renderer_light_set_enabled
// VERIFIED: Sets renderer enabled byte +0x4C, increments light-change serial 0x00D035E0, and spatially relinks category-1 lights (+0x4D).
// UNREALRED VERIFIED [rfl-light-decode]: Writes the enabled byte, advances the renderer-light change serial, and spatially relinks category-1 lights.
int __cdecl rf_renderer_light_set_enabled(int a1, char a2)
{
  int result; // eax
  int *v3; // [esp+0h] [ebp-4h]

  v3 = rf_renderer_light_resolve_handle(a1);
  *((_BYTE *)v3 + 76) = a2;
  result = ++rf_renderer_light_change_serial;
  if ( *((_BYTE *)v3 + 77) )
    return rf_light_refresh_receiver_coverage((int)v3, 0);
  return result;
}

