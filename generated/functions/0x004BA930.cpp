// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004BA930 rf_world_object_admitted_for_room_submission
// UNREALRED VERIFIED [impact-callbacks-20261028]: Rejects object flags+124 mask0x10 or null room pointer returned by shared first-dword accessor. Matching caller room returns true. Otherwise third byteargument must be nonzero and current view player entity(handle global0x87C640+20) must resolve; admits if object runtime handle+44 equals view entity+2220 OR attached handle+512. No position/frustum/respawn check here.
bool __cdecl rf_world_object_admitted_for_room_submission(_DWORD *a1, int a2, char a3)
{
  int first_dword; // [esp+0h] [ebp-8h]
  int v5; // [esp+4h] [ebp-4h]

  if ( (a1[31] & 0x10) != 0 )
    return 0;
  first_dword = rf_receiver_get_first_dword(a1);
  if ( !first_dword )
    return 0;
  if ( first_dword == a2 )
    return 1;
  if ( !a3 )
    return 0;
  v5 = rf_entity_resolve_handle(*(_DWORD *)(unk_87C640 + 20));
  if ( !v5 )
    return 0;
  if ( a1[11] == *(_DWORD *)(v5 + 2220) )
    return 1;
  return a1[11] == *(_DWORD *)(v5 + 512);
}

