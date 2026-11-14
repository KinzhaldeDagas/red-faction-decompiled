// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004FA1B0 rf_play_animation_file_event_create
// UNREALRED VERIFIED [mission-play-animation-file-20261013] Creates internal type12 filename animation event: RF string+0x2B8=filename; byte+0x2C0=arg4 action selector; int+0x2C4=-1 unresolved registry index; byte+0x2C8=arg3 hold. Distinct from canonical type11 field layout.
int __cdecl rf_play_animation_file_event_create(float *a1, int a2, char a3, char a4)
{
  int v5; // [esp+0h] [ebp-4h]

  v5 = rf_mission_event_create_at_position(a1, 0xCu);
  if ( v5 )
  {
    rf_string_assign_from_object((_DWORD *)(v5 + 696), a2);
    *(_BYTE *)(v5 + 704) = a4;
    *(_DWORD *)(v5 + 708) = -1;
    *(_BYTE *)(v5 + 712) = a3;
  }
  return v5;
}

