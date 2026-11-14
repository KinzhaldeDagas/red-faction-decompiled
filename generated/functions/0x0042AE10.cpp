// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0042AE10 rf_entity_select_contextual_death_action
// UNREALRED VERIFIED [death-selector-decode]: Selects and validates crouch, cower, directional, or random death actions with generic fallback.
int __cdecl rf_entity_select_contextual_death_action(int a1)
{
  int v2; // [esp+0h] [ebp-10h]
  int v3; // [esp+Ch] [ebp-4h]

  v3 = *(_DWORD *)(a1 + 2084);
  if ( rf_entity_is_crouched_state810(a1) || rf_entity_body_state_is_resident(a1, 13) )
  {
    v3 = 16;
  }
  else
  {
    switch ( *(_DWORD *)(a1 + 2084) )
    {
      case 6:
      case 8:
      case 0xB:
        if ( !rf_entity_test_directional_death_clearance(a1, 1) )
          v3 = -1;
        break;
      case 7:
      case 9:
      case 0xC:
        if ( !rf_entity_test_directional_death_clearance(a1, 0) )
          v3 = -1;
        break;
      default:
        break;
    }
  }
  if ( v3 == -1 || v3 == 12 && !(rand() % 2) )
  {
    v2 = rand() % 3;
    if ( v2 )
    {
      if ( v2 == 1 )
      {
        v3 = 14;
      }
      else if ( v2 == 2 )
      {
        v3 = 15;
      }
    }
    else
    {
      v3 = 5;
    }
  }
  if ( *(_DWORD *)(a1 + 16 * v3 + 2644) == -1 )
  {
    if ( *(_DWORD *)(a1 + 2724) == -1 )
      return -1;
    else
      return 5;
  }
  return v3;
}

