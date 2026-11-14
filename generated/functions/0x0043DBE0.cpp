// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0043DBE0 rf_blood_surface_marks_render_for_region
// UNREALRED VERIFIED [runtime-snapshots-blood-glass-20261028] Visit active blood-mark ring, selecting node region/context+0x44 equal input. Submit0x51EFD0 with node,position+0x14 twice,current size+4 and draw callback0x43D940 plus observed flags. Does not advance age, free expired marks or load texture in this wrapper.
char __cdecl rf_blood_surface_marks_render_for_region(int a1)
{
  char result; // al
  int v2; // [esp+20h] [ebp-8h]
  int i; // [esp+24h] [ebp-4h]

  result = dword_6E6254;
  for ( i = dword_6E6254; i; i = v2 )
  {
    result = i;
    if ( *(_DWORD *)(i + 68) == a1 )
      result = rf_world_submit_render_callback_entry(
                 i,
                 i + 20,
                 i + 20,
                 *(float *)(i + 4),
                 (int)rf_blood_surface_mark_draw_quad,
                 1,
                 0,
                 0,
                 0,
                 0,
                 1);
    if ( *(_DWORD *)(i + 76) == dword_6E6254 )
    {
      v2 = 0;
    }
    else
    {
      result = i;
      v2 = *(_DWORD *)(i + 76);
    }
  }
  return result;
}

