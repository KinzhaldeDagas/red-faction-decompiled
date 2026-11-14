// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004C0080 rf_collision_pair_reject_projectile_facing
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, four-slot emitter lifecycle, allocation and constructor layouts, native ordered lifetime gates, attachment transforms and paused rendering): 
// Cdecl pair-record pointer: next0,A4,B8,flags12. Canonical AL1 means skip/reject, AL0 continue. Only when pair flags12&1: if A.type36==2, calls projectile-target gate4BFAC0(A,B,0),
// otherwise if B.type==2 calls gate(B,A,0); gate false rejects. Both-projectile pair tests A ONLY, even if it passes. Guard BYTE0 still performs common-position/common-forward facing
// check, rejecting ordered negative binary32 dot; it bypasses friendliness and global-plane tests. Flag clear or neither projectile returns0. No pair/object/null validation, flag
// rewrite, unlink or freeing.
char __cdecl rf_collision_pair_reject_projectile_facing(int *a1)
{
  if ( (a1[3] & 1) != 0 )
  {
    if ( *(_DWORD *)(a1[1] + 36) == 2 )
    {
      if ( !rf_projectile_target_passes_pair_gate(a1[1], a1[2], 0) )
        return 1;
    }
    else if ( *(_DWORD *)(a1[2] + 36) == 2 && !rf_projectile_target_passes_pair_gate(a1[2], a1[1], 0) )
    {
      return 1;
    }
  }
  return 0;
}

