// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00510B50 rf_weapon_resolve_reload_clip_prop
// UNREALRED VERIFIED [reload-clip-physics-20261013] Reload clip prop resolver. WeaponInfo+0x4C8 caches the first-person clip_eject_1 prop; a missing clip prop falls back exactly to shell_eject_1. Returns -1 for null weapon info. Separate from shell resolver at0x5109A0 and its special machine-pistol shell_eject_2 behavior.
int __cdecl rf_weapon_resolve_reload_clip_prop(int a1, int a2)
{
  if ( !a2 )
    return -1;
  if ( *(int *)(a2 + 1224) < 0 )
  {
    *(_DWORD *)(a2 + 1224) = rf_model_handle_find_node_adapter(*(_DWORD *)(a1 + 52), "clip_eject_1");
    if ( *(int *)(a2 + 1224) < 0 )
      *(_DWORD *)(a2 + 1224) = rf_model_handle_find_node_adapter(*(_DWORD *)(a1 + 52), "shell_eject_1");
  }
  return *(_DWORD *)(a2 + 1224);
}

