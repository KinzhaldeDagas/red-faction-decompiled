// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004E62A0 rf_fpgun_state_is_resident
// UNREALRED VERIFIED [fpgun-state-decode]: Returns true when a semantic fpgun state is current or pending.
bool __cdecl rf_fpgun_state_is_resident(int a1, int a2)
{
  if ( a1 != rf_local_fpgun_player )
    return 0;
  if ( !a1 )
    return 0;
  return *(_DWORD *)(a1 + 4320) == a2 || *(_DWORD *)(a1 + 4324) == a2;
}

