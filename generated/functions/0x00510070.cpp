// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00510070 rf_weapon_get_muzzle_1_bone_index
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, projectile lifetime and attachments,weapon selectors,near-miss unordered branches,model and animation caches,original ECX/stack flow and PE bytes): Requires fixed signed range0..63, not global count; obtains cached world model through50FFA0 (nonempty record RFString+40 then handle+48). Missing model returns-1. Only cache DWORD+52 EXACTLY -1 triggers node lookup for muzzle_1; stores and returns result. Failed -1 is retried, other negatives are returned unchanged. Cache is per weapon with no model identity key or invalidation.
int __cdecl rf_weapon_get_muzzle_1_bone_index(unsigned int a1)
{
  int v2; // [esp+0h] [ebp-8h]
  char *v3; // [esp+4h] [ebp-4h]

  if ( a1 >= 0x40 )
    return -1;
  v3 = (char *)&rf_weapon_records + 1360 * a1;
  v2 = sub_50FFA0(a1);
  if ( !v2 )
    return -1;
  if ( *((_DWORD *)v3 + 13) == -1 )
    *((_DWORD *)v3 + 13) = rf_model_handle_find_node_adapter(v2, "muzzle_1");
  return *((_DWORD *)v3 + 13);
}

