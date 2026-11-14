// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00573250 rf_renderer_set_auxiliary_mode_clamped_0_16
// UNREALRED VERIFIED [renderer-polygons-20261028]: Clamps integer argument0..16. If differs from global0x187CD18,stores it and,only for backend selector0x187CC9C==102,calls0x5D2C30. That backend callback body is empty; no device state application occurs there. Equal value produces no call. Numeric mode semantics left unspecified.
void __cdecl rf_renderer_set_auxiliary_mode_clamped_0_16(int a1)
{
  rf_integer_clamp_in_place(&a1, 0, 16);
  if ( a1 != unk_187CD18 )
  {
    unk_187CD18 = a1;
    if ( dword_187CC9C == 102 )
      rf_renderer_auxiliary_mode_change_noop();
  }
}

