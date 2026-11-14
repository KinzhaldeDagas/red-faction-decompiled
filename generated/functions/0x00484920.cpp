// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00484920 rf_geomod_operation_step
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, geometry-operation phases, terrain/debris ownership, saved replay, native x87 gates and localized level-text lifecycle): 
// Cdecl noargs, AL0/1 active status. Entry phase<0 returns0 immediately without UV-cache work. One switch phase per call: phase0 optionally submits blastmark decal if normal6FF4FC
// not exactly zero and decal byte662830==1. Descriptor position=cut center,room resolved(center,center),solid=world,flags512,all three
// dimensions=F32(scale*double2*cutter.radius96+double0.5),orientation from raw normal. Then initializes Boolean: flags6FCCE8 bit2 ->mode1 with zero ancillary args; otherwise mode3
// with global selector6FCCE0,option2,scale,scalar accumulator6FCCEC and two constraint vectors. Ignores init result and increments phase regardless. Phase1 calls Boolean advance;
// only returned AL0 increments to2, nonzero stays1.
// Phase2 classifies terrain components, then for every label0..count-1 extracts from WORLD and recenters before EVERY bounds/debris capacity check. If detached-bounds count<32,
// stores world AABB (local min72+delta -0.5, local max84+delta +0.5) at0x6FF508+24*i and increments. This cap limits interaction metadata, not terrain extraction. If physical-debris
// byte EXACT1, takes free work record (solid+8,position+12=delta,measure,append active tail); no free record destroys only extracted solid. Other byte values also destroy extracted
// copy. If classified count>0, nonzero physical-debris byte invokes subdivider, then always rewinds scratch arena; zero count skips both. Increments phase3.
// Phase3 computes FLOAT cut radius=cutter.radius96*scale; calls postcut world-object update(center,radius,bounds,count,1), clears detached count0, calls fragment update and
// glass-shard invalidation(center,radius), invokes case-insensitive current-level RFString vs uso_bridge.rfl comparison but discards result, sets phase-1. No conditional bridge
// behavior is present after that comparison.
// After EVERY nonnegative-entry step, including final phase3 and unknown phase>=4 default, rebuilds every UV-scroll descriptor cache from world pointer vector+756. Returns1 iff
// resulting phase>=0. Unknown nonnegative phases do no phase progress and continue returning1/rebuilding caches indefinitely; phase3 returns0 after cache rebuild. No rollback when
// Boolean init fails or debris capacity is exhausted; no same-call fallthrough between phases.
bool rf_geomod_operation_step()
{
  float *v1; // eax
  float *v2; // eax
  float *v3; // eax
  float *v4; // eax
  float v5[4]; // [esp+28h] [ebp-F0h] BYREF
  char *v6; // [esp+38h] [ebp-E0h]
  float v7[3]; // [esp+3Ch] [ebp-DCh] BYREF
  int v8[3]; // [esp+48h] [ebp-D0h] BYREF
  float v9[3]; // [esp+54h] [ebp-C4h] BYREF
  float v10[3]; // [esp+60h] [ebp-B8h] BYREF
  int v11[3]; // [esp+6Ch] [ebp-ACh] BYREF
  float sum_result[3]; // [esp+78h] [ebp-A0h] BYREF
  float copy_result[3]; // [esp+84h] [ebp-94h] BYREF
  _DWORD *v14; // [esp+90h] [ebp-88h]
  float v15; // [esp+94h] [ebp-84h]
  float *v16; // [esp+98h] [ebp-80h]
  float *v17; // [esp+9Ch] [ebp-7Ch]
  int v18; // [esp+A0h] [ebp-78h]
  int i; // [esp+A4h] [ebp-74h]
  float source[3]; // [esp+A8h] [ebp-70h] BYREF
  float v21; // [esp+B4h] [ebp-64h]
  float destination[3]; // [esp+B8h] [ebp-60h] BYREF
  float v23[9]; // [esp+C4h] [ebp-54h] BYREF
  float v24[10]; // [esp+E8h] [ebp-30h] BYREF
  int j; // [esp+110h] [ebp-8h]
  int first_dword; // [esp+114h] [ebp-4h]

  if ( rf_geomod_operation_phase < 0 )
    return 0;
  switch ( rf_geomod_operation_phase )
  {
    case 0:
      if ( !rf_vector3_is_exact_zero(&flt_6FF4FC) && byte_662830 == 1 )
      {
        rf_decal_parameter_record_construct((int)destination);
        v21 = unk_6FCCDC * 2.0 * *(float *)(unk_6FCCF0 + 96) + 0.5;
        LODWORD(v24[3]) = unk_6FCCE4;
        LODWORD(v24[6]) = 512;
        rf_vector_copy(destination, copy_result, &flt_6FDD0C);
        LODWORD(v24[4]) = rf_world_resolve_cached_room((void *)rf_world_solid, nullptr, &flt_6FDD0C, &flt_6FDD0C, 0);
        LODWORD(v24[8]) = rf_world_solid;
        rf_vector3_set_components_thiscall(v24, v21, v21, v21);
        rf_orientation_matrix_from_direction(v23, (int)&flt_6FF4FC);
        rf_impact_decal_world_submit((int)destination);
      }
      if ( (unk_6FCCE8 & 2) != 0 )
        rf_geomod_boolean_init(
          rf_world_solid,
          unk_6FCCF0,
          1,
          0,
          (int)&flt_6FDD0C,
          (int)&flt_6FF808,
          0,
          0,
          0.0,
          0,
          0,
          0,
          0);
      else
        rf_geomod_boolean_init(
          rf_world_solid,
          unk_6FCCF0,
          3,
          0,
          (int)&flt_6FDD0C,
          (int)&flt_6FF808,
          unk_6FCCE0,
          2,
          unk_6FCCDC,
          (int)&unk_6FCCEC,
          0,
          (int)&flt_6FDD00,
          (int)&flt_6FDD44);
      ++rf_geomod_operation_phase;
      break;
    case 1:
      if ( !rf_geomod_boolean_advance() )
        ++rf_geomod_operation_phase;
      break;
    case 2:
      v18 = rf_geomod_terrain_components_classify(rf_world_solid);
      rf_vector3_default_construct_noop(source);
      for ( i = 0; i < v18; ++i )
      {
        v17 = (float *)rf_geomod_component_extract((char *)rf_world_solid, i);
        rf_geomod_component_recenter(v17, (int)source);
        if ( rf_geomod_detached_bounds_count < 32 )
        {
          v1 = rf_vector_add(v17 + 18, sum_result, source);
          v2 = rf_vector3_subtract_scalar_from_components(v1, (float *)v11, 0.5);
          rf_vector_copy((float *)&unk_6FF508 + 6 * rf_geomod_detached_bounds_count, v10, v2);
          v3 = rf_vector_add(v17 + 21, v9, source);
          v4 = rf_vector3_add_scalar_to_components(v3, (float *)v8, 0.5);
          rf_vector_copy(&flt_6FF514[6 * rf_geomod_detached_bounds_count], v7, v4);
          ++rf_geomod_detached_bounds_count;
        }
        if ( rf_geomod_create_physical_debris == 1 )
        {
          if ( rf_geomod_debris_work_free_head == &rf_geomod_debris_work_free_head )
          {
            LODWORD(v5[3]) = v17;
            v6 = (char *)v17;
            if ( v17 )
              rf_solid_destroy(v6, 1);
          }
          else
          {
            v16 = (float *)rf_geomod_debris_work_free_head;
            *(_DWORD *)rf_geomod_debris_work_free_head[1] = *rf_geomod_debris_work_free_head;
            *(float *)(*(_DWORD *)v16 + 4) = v16[1];
            *v16 = 0.0;
            v16[1] = 0.0;
            *((_DWORD *)v16 + 2) = v17;
            rf_vector_copy(v16 + 3, v5, source);
            rf_geomod_debris_work_measure((int)v16);
            *((_DWORD *)v16 + 1) = rf_geomod_debris_work_active_tail;
            *(_DWORD *)v16 = &rf_geomod_debris_work_active_head;
            *rf_geomod_debris_work_active_tail = v16;
            rf_geomod_debris_work_active_tail = v16;
          }
        }
        else if ( v17 )
        {
          rf_solid_destroy((char *)v17, 1);
        }
      }
      if ( v18 > 0 )
      {
        if ( rf_geomod_create_physical_debris )
          rf_geomod_debris_subdivide();
        rf_scratch_arena_rewind_and_clear_owners();
      }
      ++rf_geomod_operation_phase;
      break;
    case 3:
      v15 = *(float *)(unk_6FCCF0 + 96) * unk_6FCCDC;
      rf_geomod_postcut_world_object_update((int)&flt_6FDD0C, v15, (int)&unk_6FF508, rf_geomod_detached_bounds_count, 1);
      rf_geomod_detached_bounds_count = 0;
      rf_geomod_postcut_fragment_update((int)&flt_6FDD0C, v15);
      rf_geomod_postcut_glass_shard_invalidate(v15, &flt_6FDD0C, v15);
      rf_string_equals_case_insensitive((int)unk_6FC31C, "uso_bridge.rfl");
      rf_geomod_operation_phase = -1;
      break;
    default:
      break;
  }
  first_dword = rf_receiver_get_first_dword((void *)(rf_world_solid + 756));
  for ( j = 0; j < first_dword; ++j )
  {
    v14 = *(_DWORD **)sub_552200((_DWORD *)(rf_world_solid + 756), j);
    rf_uv_scroll_descriptor_rebuild_face_cache(v14, rf_world_solid);
  }
  return rf_geomod_operation_phase >= 0;
}

