// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00490300 rf_multiplayer_registry_update_rate_is_nonzero
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, client timeout latch and registry admission, RFString-array ownership, native lag-compensation snapshot/restore asymmetry, geometry contact limits and respawn slots): 
// Cdecl no arguments,normalized full EAX Boolean. Reads registry optional-sectionNULL,key UpdateRate,DWORD output,fallback0. Returns1 iff helper status signed>=0 AND output DWORD
// unsigned>0 (ANY nonzero including high-bit values). Registry helper returns0 on query success,-1 on failure/fallback; no numeric range or recommended-rate validation,writeback or
// integer-string parsing.
BOOL rf_multiplayer_registry_update_rate_is_nonzero()
{
  BYTE Data[4]; // [esp+0h] [ebp-8h] BYREF
  int dword_or_default; // [esp+4h] [ebp-4h]

  dword_or_default = rf_registry_read_dword_or_default(nullptr, "UpdateRate", Data, 0);
  return dword_or_default >= 0 && *(_DWORD *)Data;
}

