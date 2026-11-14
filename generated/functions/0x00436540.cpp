// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00436540 rf_entity_body_action_is_active
// VERIFIED: Queries whether the resolved animation record stored in one of 45 owner slots at +2644 with stride 16 is active; invalid indices above 44 or a -1 record index return false.
// UNREALRED VERIFIED [body-action-decode]: Resolves a body-action slot and tests whether its VMesh action has nonzero remaining time.
bool __cdecl rf_entity_body_action_is_active(int a1, unsigned int a2)
{
  if ( a2 > 0x2C )
    return 0;
  if ( *(int *)(a1 + 16 * a2 + 2644) >= 0 )
    return rf_vfx_get_remaining_time((const void *)*(_DWORD *)(a1 + 128), *(_DWORD *)(a1 + 16 * a2 + 2644)) != 0.0;
  return 0;
}

