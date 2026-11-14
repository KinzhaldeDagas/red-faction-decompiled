// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005109A0 rf_weapon_resolve_shell_eject_prop
// UNREALRED VERIFIED [weapon-shell-ejection-20261008] For valid weapon index <64, lazily caches prop index at WeaponInfo+1188. Exact machine pistol special (global0x911C98, assigned by 0x50D2E0) uses shell_eject_2; all other weapons use shell_eject_1. Do not infer this choice from alternate fire alone.
int __cdecl rf_weapon_resolve_shell_eject_prop(int a1, unsigned int a2)
{
  int node_adapter; // eax
  char *v4; // [esp+0h] [ebp-4h]

  if ( a2 >= 0x40 )
    return -1;
  v4 = (char *)&rf_weapon_records + 1360 * a2;
  if ( *((int *)v4 + 297) < 0 )
  {
    if ( a2 == unk_911C98 )
      node_adapter = rf_model_handle_find_node_adapter(*(_DWORD *)(a1 + 52), "shell_eject_2");
    else
      node_adapter = rf_model_handle_find_node_adapter(*(_DWORD *)(a1 + 52), "shell_eject_1");
    *((_DWORD *)v4 + 297) = node_adapter;
  }
  return *((_DWORD *)v4 + 297);
}

