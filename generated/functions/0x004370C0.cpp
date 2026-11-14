// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004370C0 rf_entity_enable_headlamp_recursive
// UNREALRED VERIFIED [generic-mission-event-continuation-20261027] Null-safe enable: OR entity+0x810 bit0x4000. When0x438AC0 predicate true, resolve/play sound from descriptor+0x12C via0x446F60(...,0) and common event playback(group0,offset0,gain1). Iterate emitter vector entity+0x1418, enabling only entries accepted by0x41BB10. If signed association id entity+0x200>-1, resolve entity and recurse. Repeated enable does not test prior bit and may replay sound; no visited-set or mission dispatch in body.
void __cdecl rf_entity_enable_headlamp_recursive(_DWORD *a1)
{
  int sound_by_index; // eax
  int *v2; // eax
  _BYTE **v3; // eax
  _DWORD *v4; // eax
  int i; // [esp+8h] [ebp-4h]

  if ( a1 )
  {
    a1[516] |= 0x4000u;
    if ( sub_438AC0((int)a1) )
    {
      sound_by_index = rf_foley_get_sound_by_index(*(_DWORD *)(a1[165] + 300), 0);
      rf_gamesound_play_event(sound_by_index, 0, 0.0, 1.0);
    }
    for ( i = 0; i < rf_receiver_get_first_dword(a1 + 1286); ++i )
    {
      v2 = (int *)sub_552200(a1 + 1286, i);
      if ( rf_glare_runtime_flags692_has_mask2(*v2) )
      {
        v3 = (_BYTE **)sub_552200(a1 + 1286, i);
        rf_emitter_enable(*v3);
      }
    }
    if ( (int)a1[128] > -1 )
    {
      v4 = (_DWORD *)rf_entity_resolve_handle(a1[128]);
      rf_entity_enable_headlamp_recursive(v4);
    }
  }
}

