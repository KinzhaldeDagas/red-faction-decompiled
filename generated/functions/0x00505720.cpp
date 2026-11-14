// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00505720 rf_trigger_scan_auto_linked_entities_for_player_use
// UNREALRED VERIFIED [trigger-use-20261021] Auto flag4 scan walks triggers and linked entity handles in authored order. First eligible mutual target calls505360 DIRECTLY and returns1 regardless commit result: no504B30 shape/InsideTime query. Standalone/server only. Current UnrealRed standalone implementation binds live authored sentient character owners once per generation; runtime-enabled nonsentient/vehicle and network owners remain further work.
char __cdecl rf_trigger_scan_auto_linked_entities_for_player_use(_DWORD *a1)
{
  int *v3; // eax
  int *i; // [esp+0h] [ebp-Ch]
  int v5; // [esp+4h] [ebp-8h]
  int j; // [esp+8h] [ebp-4h]

  if ( rf_multiplayer_runtime_mode == 1 && !rf_multiplayer_server_authority )
    return 0;
  for ( i = (int *)rf_trigger_runtime_list_head; i != (int *)&unk_90B510; i = (int *)i[163] )
  {
    if ( rf_trigger_is_auto((int)i) && rf_trigger_activation_eligible(i, a1, 1) )
    {
      for ( j = 0; j < rf_receiver_get_first_dword(i + 181); ++j )
      {
        v3 = (int *)sub_552200(i + 181, j);
        v5 = rf_entity_resolve_handle(*v3);
        if ( v5 && rf_player_entity_mutual_use_target_test((int)a1, v5) )
        {
          rf_trigger_commit_activation((int)i, a1[11], 0, 0);
          return 1;
        }
      }
    }
  }
  return 0;
}

