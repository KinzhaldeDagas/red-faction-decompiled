// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00520EF0 rf_world_find_first_authored_sky_room
// UNREALRED VERIFIED [authored-sky-renderer] Returns null when the renderer sky-enable byte is clear; otherwise scans the world room list in authored order and returns the first room accepted by the verified sky-room predicate.
_BYTE *__cdecl rf_world_find_first_authored_sky_room(int a1)
{
  _BYTE *v2; // [esp+0h] [ebp-Ch]
  int first_dword; // [esp+4h] [ebp-8h]
  int i; // [esp+8h] [ebp-4h]

  if ( !rf_renderer_authored_sky_enabled )
    return nullptr;
  first_dword = rf_receiver_get_first_dword((void *)(a1 + 156));
  for ( i = 0; i < first_dword; ++i )
  {
    v2 = *(_BYTE **)sub_552200((_DWORD *)(a1 + 156), i);
    if ( rf_room_is_authored_sky(v2) )
      return v2;
  }
  return nullptr;
}

