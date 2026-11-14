// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00436FC0 rf_entity_disable_headlamp_recursive
// UNREALRED VERIFIED [generic-mission-event-continuation-20261027] Null-safe disable: clear entity+0x810 bit0x4000. With0x438AC0 predicate true, play descriptor+0x130 sound through0x446F60(...,0). Disable qualifying emitter-vector+0x1418 entries using0x41BB10/rf_emitter_disable, and recurse through signed association id+0x200>-1. Does not query old headlamp bit before sound or restore emitter prior enabled states.
void __cdecl rf_entity_disable_headlamp_recursive(_DWORD *a1)
{
  int sound_by_index; // eax
  int *v2; // eax
  _BYTE **v3; // eax
  _DWORD *v4; // eax
  int i; // [esp+8h] [ebp-4h]

  if ( a1 )
  {
    a1[516] &= ~0x4000u;
    if ( sub_438AC0((int)a1) )
    {
      sound_by_index = rf_foley_get_sound_by_index(*(_DWORD *)(a1[165] + 304), 0);
      rf_gamesound_play_event(sound_by_index, 0, 0.0, 1.0);
    }
    for ( i = 0; i < rf_receiver_get_first_dword(a1 + 1286); ++i )
    {
      v2 = (int *)sub_552200(a1 + 1286, i);
      if ( rf_glare_runtime_flags692_has_mask2(*v2) )
      {
        v3 = (_BYTE **)sub_552200(a1 + 1286, i);
        rf_emitter_disable(*v3);
      }
    }
    if ( (int)a1[128] > -1 )
    {
      v4 = (_DWORD *)rf_entity_resolve_handle(a1[128]);
      rf_entity_disable_headlamp_recursive(v4);
    }
  }
}

