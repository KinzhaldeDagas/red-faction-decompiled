// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004FA290 rf_event_message_build_from_generic_fields
// UNREALRED VERIFIED [serialized-event-bool-20260923]: Creates event type 15 (Message). Retains integer message key at +0x2BC, integer persona index at +0x2C8, argument byte at +0x2CC, and entity identifier at +0x2D0. Loader case 15 supplies trunc-converted generic float 0 as persona index and normalized generic boolean 0 as the byte. Constructor does not normalize an arbitrary direct byte argument.
int __cdecl rf_event_message_build_from_generic_fields(float *a1, unsigned int a2, int a3, char a4, int a5)
{
  int v6; // [esp+0h] [ebp-4h]

  v6 = rf_mission_event_create_at_position(a1, 0xFu);
  if ( v6 )
  {
    *(_DWORD *)(v6 + 696) = -1;
    rf_level_text_get_string_and_sound(a2, (_DWORD *)(v6 + 704), (_DWORD *)(v6 + 696));
    *(_DWORD *)(v6 + 700) = a2;
    *(_DWORD *)(v6 + 712) = a3;
    *(_BYTE *)(v6 + 716) = a4;
    *(_DWORD *)(v6 + 720) = a5;
    *(_DWORD *)(v6 + 724) = -1;
    if ( *(_DWORD *)(v6 + 696) != -1 )
      rf_gamesound_resolve_and_load(*(_DWORD *)(v6 + 696));
  }
  return v6;
}

