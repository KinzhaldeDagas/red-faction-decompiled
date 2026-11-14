// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004C3BB0 rf_geomod_impact_chunks_update_motion_damage_audio
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, firing effect ring paired ownership, original GeoMod chunk initialization/motion, x87 threshold branches and native five-argument call ABI): 
// Cdecl no args. Once-only8220BC bit1 invokes NOOP matrix ctor822098; not identity initialization. If active head equals sentinel, returns immediately: no voice/timer/audio
// housekeeping. With any active node, builds ONE shared face cache from FIRST chunk old position8 to predicted end=position+(velocity72*dt)*(F32.2 only when roomBYTE388==1 AND
// liquid_contains_point returns1, else1), bounds expanded by2 each axis. Cache reused for ALL chunks; not rebuilt from each trajectory. Cache-build result stored but not used as a
// success gate.
// Walk active next0, caching next BEFORE delegate. Only signed remaining-bounces100>0 calls4C40D0. If still>0 afterward: velocityY76-=gravity*dt; F32angle=spin96*dt; build
// unchecked-axis rotation from84 and multiply into matrix20. If flags120&2 clear at this point, loops all local player entries: resolve entity handle20, require entity cached
// room0==chunk.room108 and strict sphere overlap(entity common60/radius120,chunk.position8/radius56). Sets flag2, damage=F32(length(velocity72)*(double(radius56)*.5)), dispatches
// damage(entity.handle44,damage,-1,global911CBC,1,0,-1,0), calls43E0F0 with position/room/0/damage, derives player direction nibble from normalized velocity and ORs player flags. No
// break or flag recheck inside player loop: multiple overlapping local players can be hit this call, flag suppresses later calls. Floor collision delegate can set bit2 before this
// gate, suppressing damage even while still bouncing.
// Clears face cache after walk, then ten nonzero saved voices that are not playing ->slot0. If elapsed sound deadline814FAC returns1 resets it. If unarmed AND signed
// hitCount814FA8>5: scales accumulated position/speed by F32(1/count), chooses Foley event662DD0, plays at averaged position with F32volume=(averageSpeed/10)*.5+.5,
// listener17F10B0,flags0. Playback return is local only, NOT inserted into ten-voice array. Density=F32(count/40), clamp only ordered>1 to1; arms deadline
// trunc(randomUnit*200*(1-density)). Then count0,positionSum0,speedSum0 even if audio failed. Counts<=5 or armed timer retain sums. No independent per-chunk age
// increment/recycle/pause/room refresh; lifetime aging is elsewhere. Return AL incidental, not simulation success.
unsigned __int8 rf_geomod_impact_chunks_update_motion_damage_audio()
{
  unsigned __int8 result; // al
  float *v1; // eax
  float *v2; // eax
  int first_dword; // eax
  const float *v4; // eax
  char v5; // al
  double v6; // st7
  float radius_b; // [esp+18h] [ebp-E4h]
  float v8; // [esp+20h] [ebp-DCh]
  double v9; // [esp+24h] [ebp-D8h]
  float v10; // [esp+2Ch] [ebp-D0h]
  float copy_result[3]; // [esp+30h] [ebp-CCh] BYREF
  _BYTE v12[12]; // [esp+3Ch] [ebp-C0h] BYREF
  float v13[9]; // [esp+48h] [ebp-B4h] BYREF
  float scaled_result[3]; // [esp+6Ch] [ebp-90h] BYREF
  float v15; // [esp+78h] [ebp-84h]
  float v16; // [esp+7Ch] [ebp-80h]
  int v17; // [esp+80h] [ebp-7Ch]
  int v18; // [esp+84h] [ebp-78h]
  float destination[3]; // [esp+88h] [ebp-74h] BYREF
  int v20; // [esp+94h] [ebp-68h]
  int i; // [esp+98h] [ebp-64h]
  int v22; // [esp+9Ch] [ebp-60h]
  float rhs[3]; // [esp+A0h] [ebp-5Ch] BYREF
  float v24[3]; // [esp+ACh] [ebp-50h] BYREF
  float v25; // [esp+B8h] [ebp-44h]
  float v26[3]; // [esp+BCh] [ebp-40h] BYREF
  float sum_result[3]; // [esp+C8h] [ebp-34h] BYREF
  float v28[3]; // [esp+D4h] [ebp-28h] BYREF
  float v29; // [esp+E0h] [ebp-1Ch]
  int v30; // [esp+E4h] [ebp-18h]
  int v31; // [esp+E8h] [ebp-14h]
  int j; // [esp+ECh] [ebp-10h]
  int v33; // [esp+F8h] [ebp-4h]

  result = dword_8220BC & 1;
  if ( (dword_8220BC & 1) == 0 )
  {
    dword_8220BC |= 1u;
    result = (unsigned __int8)rf_matrix3_construct((char *)flt_822098);
    v33 = -1;
  }
  if ( (_DWORD *)rf_geomod_impact_chunk_active_head != &rf_geomod_impact_chunk_active_head )
  {
    v30 = rf_geomod_impact_chunk_active_head;
    v25 = 1.0;
    if ( *(_BYTE *)(*(_DWORD *)(rf_geomod_impact_chunk_active_head + 108) + 388) == 1
      && rf_liquid_room_contains_point(*(_DWORD *)(v30 + 108), v30 + 8) )
    {
      v25 = 0.2;
    }
    radius_b = v25;
    v1 = rf_vector_multiply_scalar((const float *)(v30 + 72), scaled_result, rf_frame_delta_seconds);
    rf_vector_multiply_scalar(v1, rhs, radius_b);
    rf_vector_add((const float *)(v30 + 8), sum_result, rhs);
    rf_vector3_default_construct_noop(v28);
    rf_vector3_default_construct_noop(v26);
    rf_segment_bounds_build(v28, v26, (float *)(v30 + 8), sum_result);
    rf_vector3_set_components_return_destination(v24, 2.0, 2.0, 2.0);
    rf_vector_subtract_in_place(v28, v24);
    rf_vector_accumulate(v26, v24);
    v22 = rf_collision_face_cache_build((_DWORD *)rf_world_solid, v28, v26, 0);
    while ( (_DWORD *)v30 != &rf_geomod_impact_chunk_active_head )
    {
      v31 = *(_DWORD *)v30;
      if ( *(int *)(v30 + 100) > 0 )
      {
        rf_geomod_impact_chunk_move_and_bounce(v30);
        if ( *(int *)(v30 + 100) > 0 )
        {
          *(float *)(v30 + 76) = *(float *)(v30 + 76) - rf_physics_gravity_acceleration * rf_frame_delta_seconds;
          v10 = *(float *)(v30 + 96) * rf_frame_delta_seconds;
          rf_matrix3_set_axis_angle_unchecked_axis(flt_822098, (float *)(v30 + 84), v10);
          v2 = rf_matrix3_argument_times_receiver_to_output((const float *)(v30 + 20), v13, flt_822098);
          rf_matrix3_copy((float *)(v30 + 20), v2);
          if ( (*(_DWORD *)(v30 + 120) & 2) == 0 )
          {
            for ( i = 0; i < rf_local_player_entry_count; ++i )
            {
              v20 = rf_entity_resolve_handle(*(_DWORD *)(rf_local_player_entries[i] + 20));
              if ( v20 )
              {
                first_dword = rf_receiver_get_first_dword((void *)v20);
                if ( first_dword == *(_DWORD *)(v30 + 108) )
                {
                  if ( rf_spheres_overlap_strict(
                         (const float *)(v20 + 60),
                         (const float *)(v30 + 8),
                         *(float *)(v20 + 120),
                         *(float *)(v30 + 56)) )
                  {
                    *(_DWORD *)(v30 + 120) |= 2u;
                    v9 = *(float *)(v30 + 56) * 0.5;
                    v29 = rf_vector3_length((float *)(v30 + 72)) * v9;
                    rf_damage_dispatch(*(_DWORD *)(v20 + 44), v29, -1, dword_911CBC, 1, 0, -1, 0);
                    rf_spawn_gray_particle_and_vclip((float *)(v30 + 8), *(_DWORD *)(v30 + 108), 0, v29);
                    rf_vector3_default_construct_noop(destination);
                    v4 = (const float *)rf_vector3_normalized_copy_unchecked((float *)(v30 + 72), (int)v12);
                    rf_vector_copy(destination, copy_result, v4);
                    v5 = rf_player_direction_to_local_quadrant_mask(*(_DWORD *)(v20 + 5168), destination);
                    rf_player_or_direction_nibble_into_flags(*(_DWORD *)(v20 + 5168), v5);
                  }
                }
              }
            }
          }
        }
      }
      v30 = v31;
    }
    rf_collision_face_cache_clear();
    for ( j = 0; j < 10; ++j )
    {
      if ( unk_814F78[j] && !rf_gamesound_voice_is_playing(unk_814F78[j]) )
        unk_814F78[j] = 0;
    }
    if ( rf_replicator_has_elapsed(&unk_814FAC) )
      rf_replicator_reset(&unk_814FAC);
    result = rf_replicator_is_armed(&unk_814FAC);
    if ( !result && dword_814FA8 > 5 )
    {
      v16 = 1.0 / (double)dword_814FA8;
      rf_vector3_scale_in_place_return_self(flt_81523C, v16);
      unk_814FA0 = unk_814FA0 * v16;
      v18 = rf_foley_choose_random_sound(dword_662DD0);
      v8 = unk_814FA0 / 10.0 * 0.5 + 0.5;
      v17 = rf_gamesound_play_positional_event(v18, flt_81523C, v8, (int)flt_17F10B0, 0);
      v15 = (double)dword_814FA8 / 40.0;
      if ( v15 > 1.0 )
        v15 = 1.0;
      v6 = sub_567730() * 200.0 * (1.0 - v15);
      rf_replicator_arm_milliseconds(&unk_814FAC, (int)v6);
      dword_814FA8 = 0;
      result = (unsigned __int8)rf_vector3_zero_return_destination(flt_81523C);
      unk_814FA0 = 0.0;
    }
  }
  return result;
}

