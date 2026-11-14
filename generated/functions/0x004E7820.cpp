// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004E7820 rf_fpgun_request_state
// UNREALRED VERIFIED [fpgun-state-decode]: Resolves and installs the next state with midpoint-preserving 0.2-second retargeting.
int __cdecl rf_fpgun_request_state(int a1, int a2)
{
  int result; // eax
  double v3; // st7
  float v4; // [esp+0h] [ebp-18h]
  int v5; // [esp+4h] [ebp-14h]
  float v6; // [esp+8h] [ebp-10h]
  int v7; // [esp+Ch] [ebp-Ch]
  char *v8; // [esp+10h] [ebp-8h]

  v6 = 0.2;
  result = a1;
  if ( a1 == rf_local_fpgun_player )
  {
    result = rf_entity_resolve_handle(*(_DWORD *)(a1 + 20));
    if ( result )
    {
      result = rf_player_get_selected_weapon_and_resolve_mesh((_DWORD *)a1);
      v7 = result;
      if ( result >= 0 )
      {
        v8 = (char *)&rf_weapon_records + 1360 * result;
        result = rf_weapon_find_named_animation_entry(result, (char *)rf_fpgun_state_names[a2], 1);
        v5 = result;
        if ( result >= 0 )
        {
          if ( result >= 3 || (result = (int)&rf_weapon_records + 1360 * v7, *(_DWORD *)&v8[28 * v5 + 688] == -1) )
            v5 = 0;
          if ( *(_DWORD *)&v8[28 * v5 + 688] != -1 )
          {
            if ( *(float *)(a1 + 4312) == 0.0 )
            {
              *(_DWORD *)(a1 + 4324) = v5;
              *(float *)(a1 + 4312) = v6;
              *(float *)(a1 + 4316) = 0.0;
              return a1;
            }
            else
            {
              v4 = *(float *)(a1 + 4316) / *(float *)(a1 + 4312);
              if ( v4 <= 0.5 )
              {
                v3 = v6 * v4;
              }
              else
              {
                *(_DWORD *)(a1 + 4320) = *(_DWORD *)(a1 + 4324);
                v3 = (1.0 - v4) * v6;
              }
              *(float *)(a1 + 4316) = v3;
              *(_DWORD *)(a1 + 4324) = v5;
              *(float *)(a1 + 4312) = v6;
              return a1;
            }
          }
        }
      }
    }
  }
  return result;
}

