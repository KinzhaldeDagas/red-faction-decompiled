// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004CEC00 rf_particle_submit_emitters_for_room
// UNREALRED VERIFIED [vfx-particle-render] Walks live emitters in one room and submits each emitter bounds record with the owned-particle render callback.
char __cdecl rf_particle_submit_emitters_for_room(int a1)
{
  char result; // al
  int i; // [esp+20h] [ebp-1Ch]
  int v3[3]; // [esp+24h] [ebp-18h] BYREF
  float v4[3]; // [esp+30h] [ebp-Ch] BYREF

  rf_vector3_default_construct_noop(v3);
  rf_vector3_default_construct_noop(v4);
  result = dword_867A50;
  for ( i = dword_867A50; (int *)i != dword_867908; i = *(_DWORD *)(i + 328) )
  {
    result = i;
    if ( *(_DWORD *)(i + 76) == a1 )
    {
      sub_4CD460(i, (float *)v3, v4);
      result = rf_world_submit_render_callback_entry(
                 i,
                 (int)v3,
                 (int)v3,
                 *(float *)(i + 156),
                 (int)rf_particle_emitter_render_live_particles,
                 1,
                 0,
                 0,
                 0,
                 0,
                 1);
    }
  }
  return result;
}

