// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004913B0 rf_multiplayer_slots16_initialize
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, client timeout latch and registry admission, RFString-array ownership, native lag-compensation snapshot/restore asymmetry, geometry contact limits and respawn slots): 
// Cdecl no arguments. Exactly16 records at757668,stride84. Writes each DWORD0=0 and DWORD80=pointer table662890[i]; remaining76 bytes unchanged. Copies pointers,does not
// duplicate/free names or construct a player. Source table verified original64 bytes. Does not clear global registry count or scoreboard resources; precise record role beyond
// observed slots is not inferred from names. Normal EAX=16 loop artifact.
int rf_multiplayer_slots16_initialize()
{
  int result; // eax
  int i; // [esp+0h] [ebp-4h]

  for ( i = 0; i < 16; ++i )
  {
    unk_757668[21 * i] = 0;
    unk_7576B8[21 * i] = (int)off_662890[i];
    result = i + 1;
  }
  return result;
}

