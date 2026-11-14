// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004915A0 rf_multiplayer_stats32_zero_tail
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, client timeout latch and registry admission, RFString-array ownership, native lag-compensation snapshot/restore asymmetry, geometry contact limits and respawn slots): 
// Cdecl32-byte record pointer. Zeros SEVEN DWORDs at4,8,12,16,20,24,28,leaves DWORD0 unchanged. NoNULL guard,allocation,name reset or linked-list mutation. Native EAX retains
// receiver pointer; splitscreen_match_initialize invokes it for statistics storage. No broader metric labels assigned from offsets alone.
_DWORD *__cdecl rf_multiplayer_stats32_zero_tail(_DWORD *a1)
{
  a1[1] = 0;
  a1[2] = 0;
  a1[3] = 0;
  a1[4] = 0;
  a1[5] = 0;
  a1[6] = 0;
  a1[7] = 0;
  return a1;
}

