// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004EBFC0 rf_fpgun_custom_action_busy
// UNREALRED VERIFIED [fpgun-action-dispatch]: Returns custom_start active OR custom_leave active.
bool __cdecl rf_fpgun_custom_action_busy(_DWORD *a1)
{
  if ( a1 != (_DWORD *)rf_local_fpgun_player )
    return 0;
  if ( rf_fpgun_action_is_active(a1, 0xAu) )
    return 1;
  return rf_fpgun_action_is_active(a1, 0xBu);
}

