// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00438750 rf_entity_body_state_is_resident
// UNREALRED VERIFIED [death-animation-decode]: Returns true when the requested body state is current or pending.
bool __cdecl rf_entity_body_state_is_resident(int a1, int a2)
{
  if ( !a1 )
    return 0;
  return *(_DWORD *)(a1 + 5004) == a2 || *(_DWORD *)(a1 + 5008) == a2;
}

