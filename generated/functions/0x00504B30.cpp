// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00504B30 rf_trigger_test_entity_activation
// UNREALRED VERIFIED [trigger-geometry-20261020] Box/sphere geometry is evaluated after ordinary eligibility, with dedicated auto triggers bypassing shape only on their separate route. InsideTime arms rounded milliseconds on first accepted shape, commits after elapsed, and disarms on failed eligibility/shape. One-way geometry is therefore not a persistent inside-volume predicate. Airlock branches remain separate from the geometry implementation.
// UNREALRED VERIFIED [trigger-inside-time-20261021] InsideTime at+0x2F8 and its single embedded deadline at+0x2FC belong to the trigger, with no per-activator handle or stored explicit-Use mode. First admitted query arms round(seconds*1000) and returns0; later admitted query from ANY actor waits or resets-before-commit once elapsed. Any query failing common eligibility/shape resets the shared deadline if InsideTime>0. Thus another actor can complete or cancel this interval. No query is not an implicit failed query, and expiry alone does not dispatch. Editor class/display names are never used to choose this branch.
// UNREALRED VERIFIED [trigger-use-20261021] After shape/InsideTime/airlock admission, attempts505360 then returns1 even if commit returns0. A handled query is not an effect receipt. UnrealRed separates admitted and committed counts so a rejected mission-action implementation cannot incorrectly enable auto fallback.
// UNREALRED VERIFIED [trigger-airlock-20261022] Standalone airlock admission follows ordinary shape and shared InsideTime. +0x2C0 is room UID (-1 or unresolved -> ordinary commit). Only the first OTHER trigger with this UID and its first resolvable type8 mover gate entry: mover target+0x2FC!=-1 OR sibling cycle timer+0x2E0 armed rejects. A sibling timer without a resolvable mover does not reject. Own cycle timer then rejects. Room query belongs to global player681E38, not the activator. Player outside chamber supplies adjacent room; player inside uses first linked mover with a room, then its first two portal pairs, excluding chamber/mover room. One portal always requests cycling. Otherwise adjacent outside+66 equal to chamber pressure+68 requests cycle. Plays positional event31 at player, arms1000ms at trigger+0x2E0, saves activator handle+0x2E4, returns handled1 without committing. Multiplayer bypasses this branch.
char __cdecl rf_trigger_test_entity_activation(int a1, _DWORD *a2, char a3)
{
  int *v3; // eax
  char v5; // al
  int *v6; // eax
  int *v7; // eax
  int v8; // [esp+Ch] [ebp-68h]
  int v9[3]; // [esp+10h] [ebp-64h] BYREF
  int *v10; // [esp+1Ch] [ebp-58h]
  int v11; // [esp+20h] [ebp-54h]
  int *v12; // [esp+24h] [ebp-50h]
  int v13; // [esp+28h] [ebp-4Ch]
  int v14; // [esp+2Ch] [ebp-48h]
  int v15; // [esp+30h] [ebp-44h]
  int v16; // [esp+34h] [ebp-40h]
  void *v17; // [esp+38h] [ebp-3Ch]
  int m; // [esp+3Ch] [ebp-38h]
  int v19; // [esp+40h] [ebp-34h]
  int v20; // [esp+44h] [ebp-30h]
  int k; // [esp+48h] [ebp-2Ch]
  int v22; // [esp+4Ch] [ebp-28h]
  int first_dword; // [esp+50h] [ebp-24h]
  int j; // [esp+54h] [ebp-20h]
  char v25; // [esp+5Ah] [ebp-1Ah]
  char v26; // [esp+5Bh] [ebp-19h]
  int v27; // [esp+5Ch] [ebp-18h]
  int v28; // [esp+60h] [ebp-14h]
  int v29; // [esp+64h] [ebp-10h]
  int v30; // [esp+68h] [ebp-Ch]
  int i; // [esp+6Ch] [ebp-8h]
  char v32; // [esp+73h] [ebp-1h]

  if ( rf_multiplayer_runtime_mode == 1 && !rf_multiplayer_server_authority )
  {
    v29 = 0;
    for ( i = 0; i < rf_receiver_get_first_dword((void *)(a1 + 724)); ++i )
    {
      v3 = (int *)sub_552200((_DWORD *)(a1 + 724), i);
      v30 = rf_object_resolve_handle(*v3);
      if ( v30 && *(_DWORD *)(v30 + 36) == 8 )
      {
        v28 = v30;
        if ( *(_DWORD *)(v30 + 748) )
          ++v29;
      }
    }
    if ( v29 != rf_receiver_get_first_dword((void *)(a1 + 724)) )
      return 0;
  }
  v32 = 0;
  if ( rf_trigger_activation_eligible((int *)a1, a2, a3) )
  {
    if ( rf_trigger_is_auto(a1) )
    {
      v32 = 1;
    }
    else
    {
      v8 = *(_DWORD *)(a1 + 660);
      if ( v8 )
      {
        if ( v8 == 1 )
          v32 = rf_trigger_volume_contains_entity(a1, (int)a2);
      }
      else
      {
        rf_trigger_sphere_contains_entity(a1, (int)a2);
        v32 = v5;
      }
    }
  }
  if ( v32 )
  {
    if ( *(float *)(a1 + 760) > 0.0 )
    {
      if ( !rf_replicator_is_armed((_DWORD *)(a1 + 764)) )
      {
        rf_replicator_arm_milliseconds((int *)(a1 + 764), (int)(*(float *)(a1 + 760) * 1000.0 + 0.5));
        return 0;
      }
      if ( !rf_replicator_has_elapsed((int *)(a1 + 764)) )
        return 0;
      rf_replicator_reset((_DWORD *)(a1 + 764));
    }
    if ( rf_multiplayer_runtime_mode )
      goto LABEL_86;
    v27 = 0;
    if ( *(_DWORD *)(a1 + 704) != -1 )
      v27 = sub_479EC0(*(_DWORD *)(a1 + 704));
    if ( !v27 )
    {
LABEL_86:
      if ( !rf_trigger_commit_activation(a1, a2[11], 0, 0) && a3 == 1 )
        rf_gamesound_play_event(2, 0, 0.0, 1.0);
      return 1;
    }
    else
    {
      v26 = 0;
      for ( j = rf_trigger_runtime_list_head; (_UNKNOWN *)j != &unk_90B510; j = *(_DWORD *)(j + 652) )
      {
        if ( j != a1 && *(_DWORD *)(j + 704) == *(_DWORD *)(a1 + 704) )
        {
          v26 = 1;
          break;
        }
      }
      if ( v26 == 1 )
      {
        for ( k = 0; k < rf_receiver_get_first_dword((void *)(j + 724)); ++k )
        {
          v6 = (int *)sub_552200((_DWORD *)(j + 724), k);
          v20 = rf_object_resolve_handle(*v6);
          if ( v20 && *(_DWORD *)(v20 + 36) == 8 )
          {
            v19 = v20;
            if ( *(_DWORD *)(v20 + 764) != -1 || rf_replicator_is_armed((_DWORD *)(j + 736)) )
              return 0;
            break;
          }
        }
      }
      if ( rf_replicator_is_armed((_DWORD *)(a1 + 736)) )
      {
        return 0;
      }
      else
      {
        first_dword = rf_receiver_get_first_dword((void *)dword_681E38);
        v22 = 0;
        v25 = 0;
        if ( first_dword == v27 )
        {
          for ( m = 0; m < rf_receiver_get_first_dword((void *)(a1 + 724)); ++m )
          {
            v7 = (int *)sub_552200((_DWORD *)(a1 + 724), m);
            v17 = (void *)rf_object_resolve_handle(*v7);
            if ( v17 )
            {
              if ( *((_DWORD *)v17 + 9) == 8 )
              {
                v16 = rf_receiver_get_first_dword(v17);
                if ( v16 )
                {
                  if ( rf_receiver_get_first_dword((void *)(v16 + 48)) == 1 )
                  {
                    v25 = 1;
                  }
                  else
                  {
                    v12 = *(int **)sub_552200((_DWORD *)(v16 + 48), 0);
                    v10 = *(int **)sub_552200((_DWORD *)(v16 + 48), 1);
                    v11 = *v12;
                    v13 = v12[1];
                    v14 = *v10;
                    v15 = v10[1];
                    if ( v11 == v16 || v11 == v27 )
                    {
                      if ( v13 == v16 || v13 == v27 )
                      {
                        if ( v14 == v16 || v14 == v27 )
                        {
                          if ( v15 != v16 && v15 != v27 )
                            v22 = v15;
                        }
                        else
                        {
                          v22 = v14;
                        }
                      }
                      else
                      {
                        v22 = v13;
                      }
                    }
                    else
                    {
                      v22 = v11;
                    }
                  }
                  break;
                }
              }
            }
          }
        }
        else
        {
          v22 = first_dword;
        }
        if ( v25 == 1
          || v22 && *(_BYTE *)(v22 + 66) == 1 && *(_BYTE *)(v27 + 68) == 1
          || v22 && !*(_BYTE *)(v22 + 66) && !*(_BYTE *)(v27 + 68) )
        {
          rf_vector3_copy_return_destination((float *)v9, (float *)(dword_681E38 + 60));
          rf_gamesound_play_positional_event(31, (float *)v9, 1.0, (int)flt_17F10B0, 0);
          rf_replicator_arm_milliseconds((int *)(a1 + 736), 1000);
          *(_DWORD *)(a1 + 740) = a2[11];
          return 1;
        }
        else
        {
          rf_trigger_commit_activation(a1, a2[11], 0, 0);
          return 1;
        }
      }
    }
  }
  else
  {
    if ( *(float *)(a1 + 760) > 0.0 )
      rf_replicator_reset((_DWORD *)(a1 + 764));
    return 0;
  }
}

