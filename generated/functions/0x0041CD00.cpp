// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0041CD00 rf_player_hud_screen_tint_set
// UNREALRED VERIFIED [hud-late-pass] Stores the caller's exact RGB bytes at Player+0x10D0 and exact integer alpha at Player+0x10D4; producers own color and initial opacity.
_BYTE *__cdecl rf_player_hud_screen_tint_set(int a1, char a2, char a3, char a4, int a5)
{
  _BYTE *result; // eax

  result = rf_color4_set_bytes_return_destination((_BYTE *)(a1 + 4304), a2, a3, a4, a5);
  *(_DWORD *)(a1 + 4308) = a5;
  return result;
}

