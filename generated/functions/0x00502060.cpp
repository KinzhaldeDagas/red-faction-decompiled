// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00502060 rf_mission_preload_file_animation_events
// UNREALRED VERIFIED [mission-play-animation-file-20261013] Preloads type12 file animations across linked entity handles with entity+0x24==0. Obtains model via0x565EC0 and calls rf_animation_registry_load(model,filename,action_byte==0,1); stores result in event+0x2C4 for each qualifying target. Hence the file loop/action role is provided by the event, not inferred from filename or MVF suffix. The last qualifying load overwrites the event index.
int rf_mission_preload_file_animation_events()
{
  int result; // eax
  int *v1; // eax
  const char *v2; // eax
  unsigned __int8 v3; // [esp-8h] [ebp-20h]
  _DWORD *definition_pointer; // [esp+0h] [ebp-18h]
  int v5; // [esp+4h] [ebp-14h]
  int v6; // [esp+8h] [ebp-10h]
  int j; // [esp+Ch] [ebp-Ch]
  int i; // [esp+14h] [ebp-4h]

  for ( i = 0; ; ++i )
  {
    result = rf_receiver_get_first_dword(unk_90B0E0);
    if ( i >= result )
      break;
    if ( *(_DWORD *)(*(_DWORD *)sub_552200(unk_90B0E0, i) + 656) == 12 )
    {
      v6 = *(_DWORD *)sub_552200(unk_90B0E0, i);
      for ( j = 0; j < rf_receiver_get_first_dword((void *)(v6 + 668)); ++j )
      {
        v1 = (int *)sub_552200((_DWORD *)(v6 + 668), j);
        v5 = rf_object_find_by_saved_identifier(*v1);
        if ( v5 )
        {
          if ( !*(_DWORD *)(v5 + 36) )
          {
            definition_pointer = (_DWORD *)rf_model_handle_get_definition_pointer(*(_DWORD *)(v5 + 128));
            v3 = *(_BYTE *)(v6 + 704) == 0;
            v2 = rf_string_object_c_str_or_empty((const void *)(v6 + 696));
            *(_DWORD *)(v6 + 708) = rf_animation_registry_load(definition_pointer, (int)v2, v3, 1);
          }
        }
      }
    }
  }
  return result;
}

