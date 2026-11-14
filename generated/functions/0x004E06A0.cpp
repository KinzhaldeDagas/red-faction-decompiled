// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004E06A0 rf_player_or_direction_nibble_into_flags
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, player view/movement/light/shield/score contracts and owned RFString native ABI): For nonNULL player, OR (DWORD argument&15)<<13 into player flags DWORD+16, return updated flags in EAX. Accumulates bits13..16; does not replace the previous nibble. NULL player skips write with no initialized EAX return; not a reliable boolean.
int __cdecl rf_player_or_direction_nibble_into_flags(int a1, char a2)
{
  int result; // eax

  if ( a1 )
  {
    result = *(_DWORD *)(a1 + 16) | ((a2 & 0xF) << 13);
    *(_DWORD *)(a1 + 16) = result;
  }
  return result;
}

