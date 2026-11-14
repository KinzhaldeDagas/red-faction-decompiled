// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00510000 sub_510000
// UNREALRED VERIFIED [combat-selected-drop-20261111]: Selected worldweapon grip accessor: missing50FFA0handle returns-1; otherwise lazycache record+56 via564D60(handle,literalgrip_1) when cache-1. Missinggrip is permitted420020success and skips offset correction; missingworldmodel is a distinct failure.
int __cdecl sub_510000(unsigned int a1)
{
  int v2; // [esp+0h] [ebp-8h]
  char *v3; // [esp+4h] [ebp-4h]

  if ( a1 >= 0x40 )
    return -1;
  v3 = (char *)&rf_weapon_records + 1360 * a1;
  v2 = sub_50FFA0(a1);
  if ( !v2 )
    return -1;
  if ( *((_DWORD *)v3 + 14) == -1 )
    *((_DWORD *)v3 + 14) = rf_model_handle_find_node_adapter(v2, "grip_1");
  return *((_DWORD *)v3 + 14);
}

