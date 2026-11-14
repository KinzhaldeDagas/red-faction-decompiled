// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004CD010 rf_particle_submit_global_lists_for_room
// UNREALRED VERIFIED [vfx-particle-render] Submits matching particles from the primary and detached global live lists to the room renderer.
char __cdecl rf_particle_submit_global_lists_for_room(int a1)
{
  char result; // al
  int i; // [esp+20h] [ebp-4h]
  int j; // [esp+20h] [ebp-4h]

  for ( i = dword_866680; (_DWORD *)i != &dword_866680; i = *(_DWORD *)i )
  {
    if ( *(_DWORD *)(i + 100) == a1 )
      rf_world_submit_render_callback_entry(
        i,
        i + 12,
        i + 12,
        *(float *)(i + 56),
        (int)rf_particle_render_billboard_callback,
        1,
        0,
        0,
        0,
        0,
        1);
  }
  result = dword_867C60;
  for ( j = dword_867C60; (int *)j != &dword_867C60; j = *(_DWORD *)j )
  {
    result = j;
    if ( *(_DWORD *)(j + 100) == a1 )
      result = rf_world_submit_render_callback_entry(
                 j,
                 j + 12,
                 j + 12,
                 *(float *)(j + 56),
                 (int)rf_particle_render_billboard_callback,
                 1,
                 0,
                 0,
                 0,
                 0,
                 1);
  }
  return result;
}

