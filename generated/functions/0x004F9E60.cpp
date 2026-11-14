// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004F9E60 rf_event_sound_create_from_fields
// UNREALRED VERIFIED [event-registry-crc-20261028]: Creates event subtype0 through0x4F7780. On success assigns RF strings at E+696/+704, stores distance E+724, float E+728, byte E+732, caller dword E+740; resets replicator E+736, sets E+720=-1, clears bytes E+733/E+712. Loads sound resource from source name with distance and unit scales into E+716; resolves/loads gamesound only if resource!=-1. Returns E even if resource load failed.
int __cdecl rf_event_sound_create_from_fields(
        float *a1,
        char *Source,
        char *a3,
        float distance,
        float a5,
        char a6,
        int a7)
{
  int v8; // [esp+Ch] [ebp-4h]

  v8 = rf_mission_event_create_at_position(a1, 0);
  if ( v8 )
  {
    rf_string_assign_from_cstr((_DWORD *)(v8 + 696), Source);
    rf_string_assign_from_cstr((_DWORD *)(v8 + 704), a3);
    *(float *)(v8 + 724) = distance;
    *(float *)(v8 + 728) = a5;
    rf_replicator_reset((_DWORD *)(v8 + 736));
    *(_BYTE *)(v8 + 732) = a6;
    *(_DWORD *)(v8 + 720) = -1;
    *(_BYTE *)(v8 + 733) = 0;
    *(_DWORD *)(v8 + 740) = a7;
    *(_BYTE *)(v8 + 712) = 0;
    *(_DWORD *)(v8 + 716) = rf_sound_resource_load(Source, distance, 1.0, 1.0);
    if ( *(_DWORD *)(v8 + 716) != -1 )
      rf_gamesound_resolve_and_load(*(_DWORD *)(v8 + 716));
  }
  return v8;
}

