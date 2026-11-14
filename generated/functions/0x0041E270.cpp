// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0041E270 rf_corpse_flag10_when_common_collision_flag_clear
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, corpse factory/support/drop lifecycle, fixed-stride snapshot boundaries and existing-object restoration, record24 ownership and native decal ABI): Walks corpse list; for each record whose common flags124 mask0x10 is CLEAR, ORs corpse flags668 mask0x10. Others unchanged. Does not clear that corpse flag, hide/unlink/delete, reset count or return uniform status; EAX depends on last processed/skipped record or sentinel.
int rf_corpse_flag10_when_common_collision_flag_clear()
{
  int result; // eax
  int i; // [esp+0h] [ebp-4h]

  result = rf_corpse_list_head;
  for ( i = rf_corpse_list_head; (_UNKNOWN *)i != &unk_681AF8; i = *(_DWORD *)(i + 652) )
  {
    result = i;
    if ( (*(_DWORD *)(i + 124) & 0x10) == 0 )
    {
      result = *(_DWORD *)(i + 668) | 0x10;
      *(_DWORD *)(i + 668) = result;
    }
  }
  return result;
}

