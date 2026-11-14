// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004ED9F0 rf_player_reset_fpgun_fields4228_4236_4240
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, player configuration packing/file I/O, fpgun type records and parser ECX/stack ABI): Cdecl player, no NULL guard: BYTE4228=0,DWORD4236=2,DWORD4240=-1, in order. Return same player pointer EAX. Used by reset/init paths6C60/6D70; no other fields, timestamps, model handles or memory release. Broader source-level names of these three fields are not assigned.
int __cdecl rf_player_reset_fpgun_fields4228_4236_4240(int a1)
{
  *(_BYTE *)(a1 + 4228) = 0;
  *(_DWORD *)(a1 + 4236) = 2;
  *(_DWORD *)(a1 + 4240) = -1;
  return a1;
}

