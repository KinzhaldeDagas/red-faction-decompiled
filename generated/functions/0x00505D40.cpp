// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00505D40 rf_trigger_filter_flag8_links
// UNREALRED VERIFIED [trigger-attachment-20261020] Iterates flag8 triggers and disables those whose links include neither a rotating common type8 mover nor event kind48,59,44,49. Called from5052B0 when global90B508==1; do not confuse this selection pass with attachment UID-to-handle binding in47C6C0.
int rf_trigger_filter_flag8_links()
{
  int result; // eax
  int *v1; // eax
  int *v2; // eax
  int v3; // [esp+4h] [ebp-14h]
  int v4; // [esp+8h] [ebp-10h]
  unsigned __int8 v5; // [esp+Eh] [ebp-Ah]
  char v6; // [esp+Fh] [ebp-9h]
  int j; // [esp+10h] [ebp-8h]
  int i; // [esp+14h] [ebp-4h]

  result = rf_trigger_runtime_list_head;
  for ( i = rf_trigger_runtime_list_head; (_UNKNOWN *)i != &unk_90B510; i = *(_DWORD *)(i + 652) )
  {
    result = i;
    if ( (*(_DWORD *)(i + 688) & 8) != 0 )
    {
      v5 = 0;
      v6 = 0;
      for ( j = 0; j < rf_receiver_get_first_dword((void *)(i + 724)); ++j )
      {
        v1 = (int *)sub_552200((_DWORD *)(i + 724), j);
        v4 = rf_object_find_by_saved_identifier(*v1);
        if ( v4 && *(_DWORD *)(v4 + 36) == 8 && rf_mover_is_rotating(v4) )
          v5 = 1;
        v2 = (int *)sub_552200((_DWORD *)(i + 724), j);
        v3 = rf_mission_event_registry_find_by_saved_uid(*v2);
        if ( v3
          && (*(_DWORD *)(v3 + 656) == 48
           || *(_DWORD *)(v3 + 656) == 59
           || *(_DWORD *)(v3 + 656) == 44
           || *(_DWORD *)(v3 + 656) == 49) )
        {
          v6 = 1;
        }
      }
      result = v5;
      if ( !v5 && !v6 )
        result = rf_trigger_set_reverse_disabled(i);
    }
  }
  return result;
}

