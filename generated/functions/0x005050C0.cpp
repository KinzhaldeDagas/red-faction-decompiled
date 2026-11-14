// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005050C0 rf_trigger_weapon_point_activation
// UNREALRED VERIFIED [hud-trigger-lifecycle] Tests a weapon impact point against weapon-enabled trigger shape, commits it with no activating entity, and reverse-disables that trigger after success.
void __cdecl rf_trigger_weapon_point_activation(int a1, float *point)
{
  int v3; // [esp+0h] [ebp-Ch]
  float v4; // [esp+4h] [ebp-8h]

  if ( (rf_multiplayer_runtime_mode != 1 || rf_multiplayer_server_authority)
    && *(_DWORD *)(a1 + 708) == 5
    && (*(_DWORD *)(a1 + 688) & 0x10) == 0 )
  {
    v3 = *(_DWORD *)(a1 + 660);
    if ( !v3 )
    {
      v4 = rf_vector_distance_squared((const float *)(a1 + 60), point);
      if ( v4 > *(float *)(a1 + 120) * *(float *)(a1 + 120) )
        return;
      goto LABEL_11;
    }
    if ( v3 != 1
      || rf_oriented_box_contains_point(
           point,
           (const float *)(a1 + 60),
           (const float *)(a1 + 72),
           (const float *)(a1 + 712)) )
    {
LABEL_11:
      if ( rf_trigger_commit_activation(a1, -1, 0, 0) == 1 )
        *(_DWORD *)(a1 + 688) |= 0x10u;
    }
  }
}

