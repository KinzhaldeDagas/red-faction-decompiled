// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004CF1A0 rf_underwater_particles_update_and_render
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, emitter extent ownership, underwater motion/pause state, projectile geometry continuation and native output writes): 
// Cdecl noargs, called from player view render at 0x444010. Static guard bits1/2/4/8 at 0x872A60 construct up=(0,1,0) at 0x872A54 and no-op vector objects at scratch 0x872A48 and box
// min/max 0x872A3C/0x872A30. If enable BYTE 0x662E00 is zero, exits after those guards. Otherwise reads view reference from global 0x87C640+196, copies referenced position and full
// 36-byte visual matrix2016 (the local at EBP-18 is its forward row), resolves referenced room, and exits unless the view point is in its liquid. No owner/room NULL guard here beyond
// delegated behavior. Selects glowball texture 0x662E04, secondary -1. Elapsed shared deadline samples a full-sphere direction about up (cone min-dot -1), scales it by
// random[0.2,0.5], stores global ambient acceleration 0x872A78, and rearms random inclusive100..200ms. This deadline/RNG work occurs even while paused.
// Builds camera-centered box with component half-extent 0x872A6C. Static original initializer 0x62CDE0 sets it to F32(0x662E0C * double1.100000023841858); 0x62CDC0 sets squared far
// cutoff 0x872A70=F32(0x662E0C^2). Original initialized radius0x662E0C=6, max alpha0x662E08=128, active count0x662DFC=1024. Iterates signed i<count over 32-byte records at 0x872A88,
// with no local 1024 clamp.
// When unpaused, finds first containing enabled push region at current particle position. Region direction+48 is copied or randomized by clamped quadratic nibble attenuation when
// flags+8 mask0xF0000 is set. Let q=length_squared(particle_position-region_position+12),R2=region+60,strength=region+100. Region bit4 takes priority and scales direction by
// F32((1-q/R2)*strength); else bit8 scales by F32(q/R2*strength); otherwise strength alone. No attenuation clamp or R2-zero guard. Adds this acceleration*global frame delta to
// velocity, or uses global ambient acceleration when no region; then adds updated velocity*delta to position. No collision sweep, emitter ownership, lifetime, or per-record age.
// Point inside strict ordered camera box: scratch0x872A48 becomes particle_position-view_position. Outside: if ordered velocity_length_squared>1 divides velocity by its SQUARED
// length, not its length. Selects rand()%6 cube face (+X,-X,+Y,-Y,+Z,-Z), fixes that offset component at +/-radius0x662E0C, samples other two uniformly within that range, stores
// offset in scratch0x872A48 and respawns position=view_position+offset. No liquid recheck before this relocation; liquid admission occurs below.
// Rendering requires ordered dot(scratch,view_forward)>0 and particle point in the SAME view room's liquid. Set d2=F32(length_squared(scratch)); native d2>=1 OR unordered passes its
// threshold. For ordered1<=d2<5 alpha factor is F32(d2/5); at d2>=5 OR unordered factor=F32(1-d2/max(d2,global squared cutoff0x872A70)). Note thresholds1/5 are squared distances, not
// radii; no smoothing at5. Writes per-record alpha byte=low8(trunc(signed_max_alpha*factor)), then requires unsigned stored alpha>5. Scales factor by exact double0.009999999776482582
// and, only when unpaused, jitters each position component independently within +/-that value. Does not recalculate scratch/dot/liquid/alpha after jitter. Sets packed record RGBA and
// draws aspect billboard at angle0, record radius+24, global glow state.
// PAUSE semantics are stateful: skips the entire per-record motion/respawn/scratch update but still performs dot/liquid/distance/alpha/render for each record. The shared scratch
// vector is therefore retained from prior work and reused for all paused records, not freshly recomputed from each position. Jitter is separately pause-gated. Texture/color pending
// state is left modified. Unwind entries only clear static guard bits; no per-call particle allocation or cleanup.
void __cdecl rf_underwater_particles_update_and_render()
{
  float *v0; // eax
  float *v1; // eax
  float *v2; // eax
  double v3; // st7
  float *v4; // eax
  double v5; // st7
  float *v6; // eax
  float *v7; // eax
  float *v8; // eax
  float *v9; // eax
  float *v10; // eax
  double v11; // st7
  int v12; // esi
  double v13; // st7
  int v14; // esi
  double v15; // st7
  int v16; // esi
  double v17; // st7
  float v18; // [esp-4h] [ebp-12Ch] BYREF
  float v19; // [esp+0h] [ebp-128h]
  float v20; // [esp+4h] [ebp-124h]
  float scalar; // [esp+8h] [ebp-120h]
  float v22; // [esp+14h] [ebp-114h]
  float v23; // [esp+18h] [ebp-110h]
  float v24[3]; // [esp+1Ch] [ebp-10Ch] BYREF
  float v25[3]; // [esp+28h] [ebp-100h] BYREF
  float v26[3]; // [esp+34h] [ebp-F4h] BYREF
  float sum_result[3]; // [esp+40h] [ebp-E8h] BYREF
  float v28[3]; // [esp+4Ch] [ebp-DCh] BYREF
  float v29[3]; // [esp+58h] [ebp-D0h] BYREF
  float scaled_result[3]; // [esp+64h] [ebp-C4h] BYREF
  float v31[3]; // [esp+70h] [ebp-B8h] BYREF
  float out_vector[3]; // [esp+7Ch] [ebp-ACh] BYREF
  float v33[4]; // [esp+88h] [ebp-A0h] BYREF
  float v34[3]; // [esp+98h] [ebp-90h] BYREF
  int v35[3]; // [esp+A4h] [ebp-84h] BYREF
  float copy_result[3]; // [esp+B0h] [ebp-78h] BYREF
  int v37[4]; // [esp+BCh] [ebp-6Ch] BYREF
  float v38; // [esp+CCh] [ebp-5Ch]
  int v39; // [esp+D0h] [ebp-58h]
  float v40; // [esp+D4h] [ebp-54h]
  float v41; // [esp+D8h] [ebp-50h] BYREF
  int containing_point; // [esp+DCh] [ebp-4Ch]
  int i; // [esp+E0h] [ebp-48h]
  float rhs[3]; // [esp+E4h] [ebp-44h] BYREF
  float v45; // [esp+F0h] [ebp-38h]
  int room; // [esp+F4h] [ebp-34h]
  _BYTE v47[24]; // [esp+F8h] [ebp-30h] BYREF
  float v48[3]; // [esp+110h] [ebp-18h] BYREF
  int v49; // [esp+124h] [ebp-4h]

  if ( (dword_872A60[0] & 1) == 0 )
  {
    dword_872A60[0] |= 1u;
    rf_vector3_set_components_return_destination(flt_872A54, 0.0, 1.0, 0.0);
    v49 = -1;
  }
  if ( (dword_872A60[0] & 2) == 0 )
  {
    dword_872A60[0] |= 2u;
    rf_vector3_default_construct_noop(&flt_872A48);
    v49 = -1;
  }
  if ( (dword_872A60[0] & 4) == 0 )
  {
    dword_872A60[0] |= 4u;
    rf_vector3_default_construct_noop(&flt_872A3C);
    v49 = -1;
  }
  if ( (dword_872A60[0] & 8) == 0 )
  {
    dword_872A60[0] |= 8u;
    rf_vector3_default_construct_noop(&flt_872A30);
    v49 = -1;
  }
  if ( byte_662E00 )
  {
    rf_entity_view_copy_referenced_position(rhs, *(_DWORD *)(unk_87C640 + 196));
    rf_entity_view_copy_referenced_matrix_2016((int)v47, *(_DWORD **)(unk_87C640 + 196));
    room = rf_camera_slot_get_room(*(void ***)(unk_87C640 + 196));
    if ( rf_liquid_room_contains_point(room, (int)rhs) )
    {
      rf_renderer_set_pending_texture_handles(flt_662E04, -1);
      if ( rf_replicator_has_elapsed(&unk_872A74) )
      {
        scalar = -1.0;
        v37[3] = (int)&v18;
        rf_vector3_copy_return_destination(&v18, flt_872A54);
        rf_random_unit_vector_in_cone(&flt_872A78, v18, v19, v20, scalar);
        scalar = rf_random_float_range(0.2, 0.5);
        rf_vector3_scale_in_place_return_self(&flt_872A78, scalar);
        rf_timestamp_arm_random_inclusive_milliseconds(&unk_872A74, 100, 200);
      }
      v0 = rf_vector3_subtract_scalar_from_components(rhs, (float *)v37, unk_872A6C);
      rf_vector_copy(&flt_872A3C, copy_result, v0);
      v1 = rf_vector3_add_scalar_to_components(rhs, (float *)v35, unk_872A6C);
      rf_vector_copy(&flt_872A30, v34, v1);
      for ( i = 0; i < dword_662DFC; ++i )
      {
        if ( !rf_game_pause_gate_query() )
        {
          containing_point = rf_push_region_find_containing_point((const float *)&unk_872A88 + 8 * i);
          if ( containing_point )
          {
            if ( (*(_DWORD *)(containing_point + 8) & 0xF0000) != 0 )
            {
              v41 = rf_flag_nibble_quadratic_attenuation(containing_point);
              rf_float_clamp_in_place(&v41, -1.0, 1.0);
              scalar = v41;
              LODWORD(v33[3]) = &v18;
              rf_vector3_copy_return_destination(&v18, (float *)(containing_point + 48));
              rf_random_unit_vector_in_cone(&flt_872A48, v18, v19, v20, scalar);
            }
            else
            {
              rf_vector_copy(&flt_872A48, v33, (const float *)(containing_point + 48));
            }
            if ( (*(_DWORD *)(containing_point + 8) & 4) != 0 )
            {
              v2 = rf_vector_subtract(
                     (const float *)&unk_872A88 + 8 * i,
                     out_vector,
                     (const float *)(containing_point + 12));
              v3 = rf_vector_length_squared(v2);
              v23 = (1.0 - v3 / *(float *)(containing_point + 60)) * *(float *)(containing_point + 100);
              rf_vector3_scale_in_place_return_self(&flt_872A48, v23);
            }
            else if ( (*(_DWORD *)(containing_point + 8) & 8) != 0 )
            {
              v4 = rf_vector_subtract((const float *)&unk_872A88 + 8 * i, v31, (const float *)(containing_point + 12));
              v5 = rf_vector_length_squared(v4);
              v22 = v5 / *(float *)(containing_point + 60) * *(float *)(containing_point + 100);
              rf_vector3_scale_in_place_return_self(&flt_872A48, v22);
            }
            else
            {
              scalar = 0.0;
              rf_vector3_scale_in_place_return_self(&flt_872A48, *(float *)(containing_point + 100));
            }
            v6 = rf_vector_multiply_scalar(&flt_872A48, scaled_result, rf_frame_delta_seconds);
            rf_vector_accumulate((float *)&unk_872A94 + 8 * i, v6);
          }
          else
          {
            v7 = rf_vector_multiply_scalar(&flt_872A78, v29, rf_frame_delta_seconds);
            rf_vector_accumulate((float *)&unk_872A94 + 8 * i, v7);
          }
          v8 = rf_vector_multiply_scalar((const float *)&unk_872A94 + 8 * i, v28, rf_frame_delta_seconds);
          rf_vector_accumulate((float *)&unk_872A88 + 8 * i, v8);
          if ( rf_aabb_overlap_strict_ordered(
                 &flt_872A3C,
                 &flt_872A30,
                 (float *)&unk_872A88 + 8 * i,
                 (float *)&unk_872A88 + 8 * i) )
          {
            v10 = rf_vector_subtract((const float *)&unk_872A88 + 8 * i, v25, rhs);
            rf_vector_copy(&flt_872A48, v24, v10);
          }
          else
          {
            v40 = rf_vector_length_squared((float *)&unk_872A94 + 8 * i);
            if ( v40 > 1.0 )
              rf_vector3_divide_in_place_reciprocal((float *)&unk_872A94 + 8 * i, v40);
            v39 = rand() % 6;
            if ( v39 )
            {
              if ( v39 == 1 )
              {
                flt_872A48 = -flt_662E0C;
              }
              else
              {
                v20 = -flt_662E0C;
                flt_872A48 = rf_random_float_range(v20, flt_662E0C);
              }
            }
            else
            {
              flt_872A48 = flt_662E0C;
            }
            if ( v39 == 2 )
            {
              unk_872A4C = flt_662E0C;
            }
            else if ( v39 == 3 )
            {
              unk_872A4C = -flt_662E0C;
            }
            else
            {
              v20 = -flt_662E0C;
              unk_872A4C = rf_random_float_range(v20, flt_662E0C);
            }
            if ( v39 == 4 )
            {
              unk_872A50 = flt_662E0C;
            }
            else if ( v39 == 5 )
            {
              unk_872A50 = -flt_662E0C;
            }
            else
            {
              v20 = -flt_662E0C;
              unk_872A50 = rf_random_float_range(v20, flt_662E0C);
            }
            v9 = rf_vector_add(rhs, sum_result, &flt_872A48);
            rf_vector_copy((float *)&unk_872A88 + 8 * i, v26, v9);
          }
        }
        if ( rf_vector_dot(&flt_872A48, v48) > 0.0 && rf_liquid_room_contains_point(room, (int)&unk_872A88 + 32 * i) )
        {
          v45 = rf_vector_length_squared(&flt_872A48);
          if ( v45 >= 1.0 )
          {
            if ( v45 >= 5.0 )
            {
              v11 = rf_float_maximum_two_values(v45, unk_872A70);
              v38 = 1.0 - v45 / v11;
            }
            else
            {
              v38 = v45 / 5.0;
            }
            unk_872AA7[32 * i] = (int)((double)dword_662E08 * v38);
            if ( (unsigned __int8)unk_872AA7[32 * i] > 5u )
            {
              v38 = v38 * 0.009999999776482582;
              if ( !rf_game_pause_gate_query() )
              {
                v12 = 32 * i;
                v20 = -v38;
                v13 = rf_random_float_range(v20, v38);
                *((float *)&unk_872A88 + 8 * i) = v13 + *(float *)(v12 + 8858248);
                v14 = 32 * i;
                v20 = -v38;
                v15 = rf_random_float_range(v20, v38);
                *((float *)&unk_872A8C + 8 * i) = v15 + *(float *)(v14 + 8858252);
                v16 = 32 * i;
                v20 = -v38;
                v17 = rf_random_float_range(v20, v38);
                *((float *)&unk_872A90 + 8 * i) = v17 + *(float *)(v16 + 8858256);
              }
              rf_render_color_set_packed_rgba8((unsigned __int8 *)&unk_872AA4[32 * i]);
              scalar = rf_particle_glow_billboard_render_state;
              LODWORD(v20) = 32 * i;
              rf_renderer_world_billboard_aspect_backend_dispatch(
                (int)&unk_872A88 + 32 * i,
                0.0,
                *((float *)&unk_872AA0 + 8 * i),
                SLODWORD(rf_particle_glow_billboard_render_state));
            }
          }
        }
      }
    }
  }
}

