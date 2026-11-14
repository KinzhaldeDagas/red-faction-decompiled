// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0040B690 rf_ai_primary_flag20_without_secondary
// UNREALRED VERIFIED [combat-transition-weapon-20261029] Returns true only when AI primary weapon id+4!=-1, secondary+8==-1 and primary weapon table flags (base0x912264,stride0x550) include0x20.40B2D0 uses this predicate to select initial secondary3 instead of2; it is not an arbitrary equipped-weapon-valid test.
bool __cdecl rf_ai_primary_flag20_without_secondary(int a1)
{
  return *(_DWORD *)(a1 + 4) != -1 && *(_DWORD *)(a1 + 8) == -1 && (unk_912264[340 * *(_DWORD *)(a1 + 4)] & 0x20) != 0;
}

