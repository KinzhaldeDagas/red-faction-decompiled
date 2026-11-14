// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004C37B0 rf_firing_effect_ring_process_selected_pair
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, firing effect ring paired ownership, original GeoMod chunk initialization/motion, x87 threshold branches and native five-argument call ABI): 
// Cdecl no args. For16 stride40 slots, BYTE multiplayer0 selects pointers0/4, any nonzero selects8/12; requires BOTH selected pointers. Copies shared slot position16 once, then
// set_world_frame(emitter,position,direction28)+process for first, repeats same stored position/direction for second. Thus initial too-variant position+0.2*direction from creator is
// replaced on first successful process with common slot position. Does not process inactive mode pair, explicitly gate enabled state, reclaim lone pointer, normalize direction,
// pause-check or expire slots. Normal EAX16 loop artifact.
void *rf_firing_effect_ring_process_selected_pair()
{
  void *result; // eax
  float v1[3]; // [esp+0h] [ebp-28h] BYREF
  float copy_result[3]; // [esp+Ch] [ebp-1Ch] BYREF
  int i; // [esp+18h] [ebp-10h]
  float destination[3]; // [esp+1Ch] [ebp-Ch] BYREF

  result = rf_vector3_default_construct_noop(destination);
  for ( i = 0; i < 16; ++i )
  {
    if ( rf_multiplayer_runtime_mode )
    {
      if ( unk_814D00[10 * i] && unk_814D04[10 * i] )
      {
        rf_vector_copy(destination, v1, (const float *)&unk_814D08 + 10 * i);
        rf_particle_emitter_set_world_frame(unk_814D00[10 * i], destination, &unk_814D14[10 * i]);
        rf_particle_emitter_process(unk_814D00[10 * i]);
        rf_particle_emitter_set_world_frame(unk_814D04[10 * i], destination, &unk_814D14[10 * i]);
        rf_particle_emitter_process(unk_814D04[10 * i]);
      }
    }
    else if ( unk_814CF8[10 * i] )
    {
      if ( unk_814CFC[10 * i] )
      {
        rf_vector_copy(destination, copy_result, (const float *)&unk_814D08 + 10 * i);
        rf_particle_emitter_set_world_frame(unk_814CF8[10 * i], destination, &unk_814D14[10 * i]);
        rf_particle_emitter_process(unk_814CF8[10 * i]);
        rf_particle_emitter_set_world_frame(unk_814CFC[10 * i], destination, &unk_814D14[10 * i]);
        rf_particle_emitter_process(unk_814CFC[10 * i]);
      }
    }
    result = (void *)(i + 1);
  }
  return result;
}

