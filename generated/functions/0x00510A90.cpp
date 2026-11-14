// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00510A90 rf_weapon_get_silencer_node_index
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, projectile lifetime and attachments,weapon selectors,near-miss unordered branches,model and animation caches,original ECX/stack flow and PE bytes): Requires signed weapon index0..63, not global count; invalid returns EAX0 without reading model owner. If record DWORD+1268 is negative, looks up literal silencer on supplied owner DWORD+52 through564D60 and caches result. Returns cache including negative failure; any negative cache is retried. Per-weapon cache has no model identity key/invalidation. No owner/model NULL guard.
int __cdecl rf_weapon_get_silencer_node_index(int a1, unsigned int a2)
{
  char *v3; // [esp+0h] [ebp-4h]

  if ( a2 >= 0x40 )
    return 0;
  v3 = (char *)&rf_weapon_records + 1360 * a2;
  if ( *((int *)v3 + 317) < 0 )
    *((_DWORD *)v3 + 317) = rf_model_handle_find_node_adapter(*(_DWORD *)(a1 + 52), "silencer");
  return *((_DWORD *)v3 + 317);
}

