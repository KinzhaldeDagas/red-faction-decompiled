// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004FA860 rf_event_create_switch_record
// UNREALRED VERIFIED [mission-update-creation-continuation-20261027] Create event32 Switch. Store raw dwords+0x2B8/+0x2BC/+0x2D4, copy sound source C string+0x2C0, store raw byte+0x2C8 and initialize dword+0x2CC=0. Load sound at resource distance5.0,gain1,scale1 into+0x2D0 and resolve/load it only when handle!=-1. Failed sound load leaves event allocated; no initial target activation in this routine.
int __cdecl rf_event_create_switch_record(float *a1, int a2, int a3, int a4, char *Source, char a6)
{
  int v7; // [esp+Ch] [ebp-4h]

  v7 = rf_mission_event_create_at_position(a1, 0x20u);
  if ( v7 )
  {
    *(_DWORD *)(v7 + 696) = a2;
    *(_DWORD *)(v7 + 700) = a3;
    rf_string_assign_from_cstr((_DWORD *)(v7 + 704), Source);
    *(_BYTE *)(v7 + 712) = a6;
    *(_DWORD *)(v7 + 724) = a4;
    *(_DWORD *)(v7 + 716) = 0;
    *(_DWORD *)(v7 + 720) = rf_sound_resource_load(Source, 5.0, 1.0, 1.0);
    if ( *(_DWORD *)(v7 + 720) != -1 )
      rf_gamesound_resolve_and_load(*(_DWORD *)(v7 + 720));
  }
  return v7;
}

