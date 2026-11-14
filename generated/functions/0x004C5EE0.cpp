// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004C5EE0 rf_glass_shard_system_update
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, persistent shard pool and keyed buckets, launch-delay/damage cadence, first-hit face traversal, native ordered branches and settling ownership): 
// Cdecl no args. Returns early ONLY if bucketCount==0, not activeCount; retained empty buckets still permit audio housekeeping. Local damage cadence counter starts0 EACH call.
// Iterates signed k<mutable bucketCount; circular head per key, caches next (orNULL when next==CURRENT bucket head) BEFORE delegates. Deadline108 armed==1: if not elapsed skip ALL
// motion/damage for node; elapsed resets108,arms112 for500ms, then proceeds same call. Deadline112 not tested here and is not a fixed shard lifetime.
// Only signed budget96>0 at entry integrates collision6370. If still>0 afterward, velocityY68-=gravity*dt and matrix20 updated by spin axis76/angularRate88*dt (F32angle). A shard
// that becomes resting this call skips gravity/rotation but STILL participates in following damage cadence. Single-player only (multiplayer BYTE==0), increment cadence for each
// budget-positive-at-entry nondelayed node; exactly every32nd resets counter and, if flags196&4 clear, scans local players. Requires resolved entity and native field56<DOUBLE5 OR
// UNORDERED (TEST AH1); no same-room check. Strict sphere overlap(entity common60/radius120,shard.position8/radius92)
// ->flags196|4,damage=F32(length(velocity64)*(double(radius92)*DOUBLE0.30000001192092896)); invokes43E0F0(position,room104,0,damage), copies unchecked normalized velocity, dispatches
// damage(handle44,damage,-1,911CBC,1,0,-1,0),ORs player direction nibble. Flag checked only BEFORE player loop: multiple overlapping players can be hit same call; later calls
// suppress. Cadence restarts each update, not rotating sample across frames.
// No visited-node set: bucket transition may append/create a later bucket; mutable loop bound allows same shard processed again if encountered later this pass. After lists, clears
// ten nonzero saved voice handles whose playback ended. If shared822764 elapsed==1 resets. When unarmed AND signed accumulated impactCount>5: averages position/speed by F32reciprocal
// count, selects Glass Drop event, positional play gainF32(avgSpeed/10*.5+.5),listener17F10B0,flags0. Returned voice kept LOCAL, not saved into channel array. DensityF32=count/192,
// clamp only ordered>1 to1; arm deadline trunc(randomUnit*200*(1-density)); clear count/position/speed even if playback failed. Otherwise sums persist ACROSS calls. No pause gate,
// automatic settled-shard release/fixed lifetime or room refresh apart from collision transition delegates.
void rf_glass_shard_system_update()
{
  float *v0; // eax
  const float *v1; // eax
  char v2; // al
  double v3; // st7
  float v4; // [esp+1Ch] [ebp-ACh]
  double v5; // [esp+20h] [ebp-A8h]
  float v6; // [esp+28h] [ebp-A0h]
  int v7; // [esp+2Ch] [ebp-9Ch]
  float copy_result[3]; // [esp+30h] [ebp-98h] BYREF
  char v9[12]; // [esp+3Ch] [ebp-8Ch] BYREF
  float v10[9]; // [esp+48h] [ebp-80h] BYREF
  float v11; // [esp+6Ch] [ebp-5Ch]
  float v12; // [esp+70h] [ebp-58h]
  int v13; // [esp+74h] [ebp-54h]
  int v14; // [esp+78h] [ebp-50h]
  float destination[3]; // [esp+7Ch] [ebp-4Ch] BYREF
  int v16; // [esp+88h] [ebp-40h]
  int j; // [esp+8Ch] [ebp-3Ch]
  float v18[9]; // [esp+90h] [ebp-38h] BYREF
  float v19; // [esp+B4h] [ebp-14h]
  int v20; // [esp+B8h] [ebp-10h]
  int v21; // [esp+BCh] [ebp-Ch]
  int i; // [esp+C0h] [ebp-8h]
  int k; // [esp+C4h] [ebp-4h]

  if ( !rf_glass_shard_bucket_count )
    return;
  v20 = 0;
  k = 0;
LABEL_3:
  if ( k < rf_glass_shard_bucket_count )
  {
    for ( i = rf_glass_shard_bucket_heads[2 * k]; ; i = v21 )
    {
      while ( 1 )
      {
        if ( !i )
        {
          ++k;
          goto LABEL_3;
        }
        v7 = *(_DWORD *)i == rf_glass_shard_bucket_heads[2 * k] ? 0 : *(_DWORD *)i;
        v21 = v7;
        if ( rf_replicator_is_armed((_DWORD *)(i + 108)) )
          break;
LABEL_13:
        if ( *(int *)(i + 96) > 0 )
        {
          rf_glass_shard_integrate_collision(i);
          if ( *(int *)(i + 96) > 0 )
          {
            *(float *)(i + 68) = *(float *)(i + 68) - rf_physics_gravity_acceleration * rf_frame_delta_seconds;
            rf_matrix3_construct((char *)v18);
            v6 = *(float *)(i + 88) * rf_frame_delta_seconds;
            rf_matrix3_set_axis_angle_unchecked_axis(v18, (float *)(i + 76), v6);
            v0 = rf_matrix3_argument_times_receiver_to_output((const float *)(i + 20), v10, v18);
            rf_matrix3_copy((float *)(i + 20), v0);
          }
          if ( !rf_multiplayer_runtime_mode && ++v20 == 32 )
          {
            v20 = 0;
            if ( (*(_DWORD *)(i + 196) & 4) == 0 )
            {
              for ( j = 0; j < rf_local_player_entry_count; ++j )
              {
                v16 = rf_entity_resolve_handle(*(_DWORD *)(rf_local_player_entries[j] + 20));
                if ( v16 && *(float *)(v16 + 56) < 5.0 )
                {
                  if ( rf_spheres_overlap_strict(
                         (const float *)(v16 + 60),
                         (const float *)(i + 8),
                         *(float *)(v16 + 120),
                         *(float *)(i + 92)) )
                  {
                    *(_DWORD *)(i + 196) |= 4u;
                    v5 = *(float *)(i + 92) * 0.300000011920929;
                    v19 = rf_vector3_length((float *)(i + 64)) * v5;
                    rf_spawn_gray_particle_and_vclip((float *)(i + 8), *(_DWORD *)(i + 104), 0, v19);
                    rf_vector3_default_construct_noop(destination);
                    v1 = (const float *)rf_vector3_normalized_copy_unchecked((float *)(i + 64), (int)v9);
                    rf_vector_copy(destination, copy_result, v1);
                    rf_damage_dispatch(*(_DWORD *)(v16 + 44), v19, -1, dword_911CBC, 1, 0, -1, 0);
                    v2 = rf_player_direction_to_local_quadrant_mask(*(_DWORD *)(v16 + 5168), destination);
                    rf_player_or_direction_nibble_into_flags(*(_DWORD *)(v16 + 5168), v2);
                  }
                }
              }
            }
          }
        }
        i = v21;
      }
      if ( rf_replicator_has_elapsed((int *)(i + 108)) )
      {
        rf_replicator_reset((_DWORD *)(i + 108));
        rf_replicator_arm_milliseconds((int *)(i + 112), 500);
        goto LABEL_13;
      }
    }
  }
  for ( k = 0; k < 10; ++k )
  {
    if ( rf_glass_drop_sound_channels[k] && !rf_gamesound_voice_is_playing(rf_glass_drop_sound_channels[k]) )
      rf_glass_drop_sound_channels[k] = 0;
  }
  if ( rf_replicator_has_elapsed(&unk_822764) )
    rf_replicator_reset(&unk_822764);
  if ( !rf_replicator_is_armed(&unk_822764) && rf_glass_frame_impact_count > 5 )
  {
    v12 = 1.0 / (double)rf_glass_frame_impact_count;
    rf_vector3_scale_in_place_return_self(rf_glass_frame_impact_position_sum, v12);
    rf_glass_frame_impact_speed_sum = rf_glass_frame_impact_speed_sum * v12;
    v14 = rf_foley_choose_random_sound(rf_glass_drop_foley_id);
    v4 = rf_glass_frame_impact_speed_sum / 10.0 * 0.5 + 0.5;
    v13 = rf_gamesound_play_positional_event(v14, rf_glass_frame_impact_position_sum, v4, (int)flt_17F10B0, 0);
    v11 = (double)rf_glass_frame_impact_count / 192.0;
    if ( v11 > 1.0 )
      v11 = 1.0;
    v3 = sub_567730() * 200.0 * (1.0 - v11);
    rf_replicator_arm_milliseconds(&unk_822764, (int)v3);
    rf_glass_frame_impact_count = 0;
    rf_vector3_zero_return_destination(rf_glass_frame_impact_position_sum);
    rf_glass_frame_impact_speed_sum = 0.0;
  }
}

