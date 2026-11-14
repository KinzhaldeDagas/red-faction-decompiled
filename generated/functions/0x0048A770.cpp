// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0048A770 rf_mover_key1_gate_is_satisfied
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, mover UID and handle queries, detachment and member ownership, original console packet serialization, native team-byte sentinel and authority comparisons): 
// Cdecl mover pointer, normalized AL Boolean. NULL returns1; mover without flag2 atDWORD792 returns1. For flag2 mover returns1 if current indexDWORD760==1 AND targetDWORD764==-1, OR
// if flag1 at792 is set AND target==1. Otherwise0. Does not require current==1 on latter active-target path, evaluate geometry/door aperture, change motion or set a key. Called by AI
// route update and mover activation.
bool __cdecl rf_mover_key1_gate_is_satisfied(_DWORD *a1)
{
  if ( !a1 )
    return 1;
  if ( !rf_mover_flag2_is_set((int)a1) )
    return 1;
  if ( a1[190] == 1 && a1[191] == -1 )
    return 1;
  return (a1[198] & 1) != 0 && a1[191] == 1;
}

