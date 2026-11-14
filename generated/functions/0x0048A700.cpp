// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0048A700 rf_mover_flag2_is_set
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, mover UID and handle queries, detachment and member ownership, original console packet serialization, native team-byte sentinel and authority comparisons): 
// Cdecl mover pointer, normalized AL Boolean for (DWORD792 &2)!=0. No NULL guard or state change. Used by motion,sound,trigger-hold and key1 gate paths; this body alone does not
// establish an additional geometric open/closed state.
bool __cdecl rf_mover_flag2_is_set(int a1)
{
  return (*(_DWORD *)(a1 + 792) & 2) != 0;
}

