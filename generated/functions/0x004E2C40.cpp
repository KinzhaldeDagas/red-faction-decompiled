// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004E2C40 rf_player_get_attached_cockpit_model_handle
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, cockpit material/animation, vehicle camera nodes and integer gauge ABI): Assumes player nonNULL. Resolve own entity UID+20 then its linked entity UID+512; either missing returns0. Otherwise return linked entity DWORD+2124 unchanged. No vehicle-class/use check or model-handle validity validation; -1 is forwarded if stored. This is cockpit model handle, not linked entity pointer.
int __cdecl rf_player_get_attached_cockpit_model_handle(int a1)
{
  int v2; // [esp+0h] [ebp-8h]
  int v3; // [esp+4h] [ebp-4h]

  v3 = rf_entity_resolve_handle(*(_DWORD *)(a1 + 20));
  if ( !v3 )
    return 0;
  v2 = rf_entity_resolve_handle(*(_DWORD *)(v3 + 512));
  if ( v2 )
    return *(_DWORD *)(v2 + 2124);
  else
    return 0;
}

