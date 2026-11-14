// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004EEBB0 rf_fplegs_state_is_resident
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, model cache fallback, material replacement, leg animation transitions and native caller ABI): Cdecl state integer. Returns AL true if equal to global current66303C OR pending663040. No enum range, handle availability, timer or asset check and no side effects.
bool __cdecl rf_fplegs_state_is_resident(int a1)
{
  return dword_66303C == a1 || dword_663040 == a1;
}

