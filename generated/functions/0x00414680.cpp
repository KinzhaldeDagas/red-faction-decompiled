// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00414680 rf_level_build_clutter_hud_registries
// UNREALRED VERIFIED [hud-world-targets] Walks clutter in intrusive-list order. Class flag 0x40 searches runtime triggers in order and registers the first trigger link as a world HUD target; class flag 0x100 fills a separate capped clutter list.
int rf_level_build_clutter_hud_registries()
{
  int result; // eax
  int j; // [esp+0h] [ebp-10h]
  char v2; // [esp+7h] [ebp-9h]
  int k; // [esp+8h] [ebp-8h]
  int i; // [esp+Ch] [ebp-4h]

  dword_666B78 = 0;
  result = rf_clutter_list_head;
  for ( i = rf_clutter_list_head; (_UNKNOWN *)i != &unk_666D18; i = *(_DWORD *)(i + 652) )
  {
    if ( (*(_DWORD *)(*(_DWORD *)(i + 660) + 116) & 0x40) != 0 )
    {
      v2 = 0;
      for ( j = rf_trigger_runtime_list_head; (_UNKNOWN *)j != &unk_90B510; j = *(_DWORD *)(j + 652) )
      {
        for ( k = 0; k < rf_receiver_get_first_dword((void *)(j + 724)); ++k )
        {
          if ( *(_DWORD *)sub_552200((_DWORD *)(j + 724), k) == *(_DWORD *)(i + 44) )
          {
            v2 = 1;
            rf_hud_world_target_registry_add(*(_DWORD *)(i + 44), *(_DWORD *)(j + 44));
            break;
          }
        }
        if ( v2 == 1 )
          break;
      }
    }
    result = i;
    if ( (*(_DWORD *)(*(_DWORD *)(i + 660) + 116) & 0x100) != 0 && dword_666B78 < 32 )
    {
      unk_666AE0[dword_666B78] = *(_DWORD *)(i + 44);
      result = ++dword_666B78;
    }
  }
  return result;
}

