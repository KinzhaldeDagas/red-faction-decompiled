// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004FC670 rf_event_remove_object_apply
// UNREALRED VERIFIED [mission-event-remove-object]: Remove_Object type 2: for every authored target, marks a resolved common object for deferred deletion or disables a matching particle emitter, bolt emitter, ambient sound, or RFL light.
int __cdecl rf_event_remove_object_apply(int a1)
{
  int result; // eax
  int *v2; // eax
  int *v3; // eax
  int *v4; // eax
  int *v5; // eax
  int *v6; // eax
  int v7; // [esp+0h] [ebp-18h]
  float *v8; // [esp+4h] [ebp-14h]
  _BYTE *v9; // [esp+8h] [ebp-10h]
  int v10; // [esp+Ch] [ebp-Ch]
  int *v11; // [esp+10h] [ebp-8h]
  int i; // [esp+14h] [ebp-4h]

  for ( i = 0; ; ++i )
  {
    result = rf_receiver_get_first_dword((void *)(a1 + 668));
    if ( i >= result )
      break;
    v2 = (int *)sub_552200((_DWORD *)(a1 + 668), i);
    v7 = rf_object_resolve_handle(*v2);
    if ( v7 )
    {
      rf_object_mark_for_deferred_delete(v7);
    }
    else
    {
      v3 = (int *)sub_552200((_DWORD *)(a1 + 668), i);
      v9 = (_BYTE *)rf_particle_emitter_find_by_uid(*v3);
      if ( v9 )
      {
        rf_particle_emitter_disable(v9);
      }
      else
      {
        v4 = (int *)sub_552200((_DWORD *)(a1 + 668), i);
        v8 = (float *)rf_bolt_emitter_find_by_uid(*v4);
        if ( v8 )
        {
          rf_bolt_emitter_disable(v8);
        }
        else
        {
          v5 = (int *)sub_552200((_DWORD *)(a1 + 668), i);
          v11 = rf_ambient_sound_find_by_uid(*v5);
          if ( v11 )
          {
            rf_ambient_sound_disable_by_uid(v11[2]);
          }
          else
          {
            v6 = (int *)sub_552200((_DWORD *)(a1 + 668), i);
            v10 = rf_rfl_light_find_by_uid(*v6);
            if ( v10 )
              rf_rfl_light_set_enabled(v10, 0);
          }
        }
      }
    }
  }
  return result;
}

