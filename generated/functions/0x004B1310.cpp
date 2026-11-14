// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004B1310 rf_multiplayer_copy_team_rgba
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, tracker packet widths, signed endpoint counts, fixed pools, DNS/clock gates, receive ABI and team-score byte
// semantics): Recovered4B1310..4B1338,lastRET4B1337. Cdecl(destinationDWORD*,signed team), bool AL. Signed team0..1 only; invalid returnsAL0 without touching destination. Valid copy
// raw RGBA DWORD7B25F8+12*team to destination, returnAL1. No destination NULL/runtime admission, color conversion or string copy. Captures four bytes, including stored alpha; does
// not substitute default color.
bool __cdecl rf_multiplayer_copy_team_rgba(unsigned int *destination, int team)
{
  if ( (unsigned int)team >= 2 )
    return 0;
  *destination = dword_7B25F8[3 * team];
  return 1;
}

