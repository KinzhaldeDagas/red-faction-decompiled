// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0040A1B0 rf_ai_numeric_mode_write
// UNREALRED VERIFIED [ai-goto-completion-20261028] Current-mode writes at AI+0x280 do not update saved mode+0x284 or saved secondary+0x2B8. Script Goto must preserve the authored saved state for route-completion restoration; do not derive the saved state from the overwritten current mode.
// UNREALRED VERIFIED [combat-reaction-target-wait-20261111]: Every multiplayer OR split mode-write masks AI+530 withF07FFFFF, regardless of requestedmode; only requested2 is remapped3. Standalone preserves that flagword. Current mode writes leave authored savedmode/savedsecondary separate.
int __cdecl rf_ai_numeric_mode_write(_DWORD *a1, int a2, int a3, int a4)
{
  if ( rf_splitscreen_runtime_active | rf_multiplayer_runtime_mode )
  {
    if ( a2 == 2 )
      a2 = 3;
    a1[332] &= 0xF07FFFFF;
  }
  a1[160] = a2;
  a1[162] = (int)*(float *)&dword_6FC428;
  a1[163] = a3;
  a1[164] = a4;
  return a3;
}

