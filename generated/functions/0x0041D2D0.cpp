// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0041D2D0 rf_corpse_create_from_entity
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, corpse factory/support/drop lifecycle, fixed-stride snapshot boundaries and existing-object restoration, record24 ownership and native decal ABI): Cdecl(entity,stateName,position,matrix,lowByteProtect,lowByteHeld), six DWORD slots. Null entity returns0. Empty class model-name RFString+24 first ORs source common flags0x400; samples humanoid and class-secondary20 predicates, then marks source for deferred deletion BEFORE setup allocation/object creation, with no rollback on failure. Constructs then MEMSETs152-byte setup0, copies mass entity152,scalar140, supplied pose,radius384,flags0x33 plus0x40 for class flags+1828 mask0x80000, and copies every source sphere record24 by-value into setup array. Creates distinct type7 with NEW runtime handle and source handle+44 as parent. Success preserves source stable ID+32, source
// field620, derives shadow packet unless source flags2068 mask2 (then corpse736=0), initializes corpse flags668 from humanoid0x80/class-secondary20 0x400; copies source2276 to692 except native ADD8E4 zero branch writes-1, initializes death action696=-1 and copies color source5236 to728. Nonempty class model name loads mode1 descriptor; empty reuses source model+128 without clearing source field here. Speech/body-action admission and state lookup select action2644+16*ordinal unless class flags0x200000; exact held BYTE==1 sets mask8 and refreshes sphere geometry only on selected action. Class0x200000 instead uses source2628 cyclic index when!=-1, ORmask4. Sets radius120=384,material508,creation time660 from global6FC428,health52=class68,class index672=source664,secondary effect720=0,voice724=-1,zero velocities324/336; assigns RFString676 only if stateName nonnull, invalidates timer684,
// optionally creates class particle emitter and links it at616. Emitter index>0 arms timer from float(class44*1000+0.5) through integer conversion; index0 can create emitter but leaves timer unarmed. Source2068 mask8 sets corpse flag2; protect BYTE EXACT1 sets0x40. Tail-links652/656, increments count, then schedules oldest unprotected/nonretiring corpses until eligible count is at most5; global list count is not immediately reduced. Copies class-indexed float5396-stride into688, looks up corpse_drop/corpse_carry IDs700/704, assigns pose708 by CASE-SENSITIVE substring forward/front->0,back->1,else2. These final strstr calls are UNCONDITIONAL, so earlier stateName null guard does not make null input safe. Initializes712=0 then conditionally moves source5136 there and clears source slot for source2064 mask0x200000. Conditional helper4BFCF0, then source blood-surface-mark helper43D450, local
// setup destructor, returns corpse. No model/emitter/ID bounds validation, whole-object zeroing or explicit associated-item716 initialization here.
// UNREALRED VERIFIED [original-target-corpse-list-membership-20261112]: Marks source common for deferred deletion, creates a DISTINCT type7 object, and appends new corpse to sentinel681AF8 via tail681D88 /next652/prev656 at41D8AE..41D8EA. This is NOT the type0 entity ring sentinel681E90/head68211C used by402160. Source entity remains in entity ring until actual431260 teardown unlink; death/presentation alone is not entity unlink. Dedicated native type7 is therefore excluded from target entity enumeration, while ambiguous host logical multiplayer-corpse presentation cannot establish that separate native list membership.
int __cdecl rf_corpse_create_from_entity(int a1, char *Str, float *source, float *a4, char a5, char a6)
{
  int first_dword; // eax
  float *element_address_unchecked; // eax
  char *v9; // eax
  int v3m_mode1; // eax
  int v11; // eax
  float v12[4]; // [esp-14h] [ebp-10Ch] BYREF
  int v13; // [esp-4h] [ebp-FCh]
  int v14; // [esp+0h] [ebp-F8h]
  int v15; // [esp+8h] [ebp-F0h]
  int v16; // [esp+Ch] [ebp-ECh]
  float *v17; // [esp+10h] [ebp-E8h]
  float copy_result[3]; // [esp+14h] [ebp-E4h] BYREF
  int oldest_evictable; // [esp+20h] [ebp-D8h]
  int j; // [esp+24h] [ebp-D4h]
  int v21; // [esp+28h] [ebp-D0h]
  int v22; // [esp+2Ch] [ebp-CCh]
  int v23; // [esp+30h] [ebp-C8h]
  char v24; // [esp+37h] [ebp-C1h]
  int body_action_slot_by_name; // [esp+38h] [ebp-C0h]
  int v26; // [esp+3Ch] [ebp-BCh]
  char v27; // [esp+43h] [ebp-B5h]
  void *v28[39]; // [esp+44h] [ebp-B4h] BYREF
  int i; // [esp+E0h] [ebp-18h]
  int v30; // [esp+E4h] [ebp-14h]
  int v31; // [esp+E8h] [ebp-10h]
  int v32; // [esp+F4h] [ebp-4h]

  v27 = 0;
  v24 = 0;
  if ( !a1 )
    return 0;
  if ( rf_string_equals_case_insensitive(*(_DWORD *)(a1 + 660) + 24, (char *)&byte_631928) )
    *(_DWORD *)(a1 + 124) |= 0x400u;
  if ( rf_entity_has_humanoid_flag(a1) )
    v27 = 1;
  if ( rf_entity_class_has_secondary_flag20(a1) )
    v24 = 1;
  rf_object_mark_for_deferred_delete(a1);
  rf_object_setup152_construct_members((char *)v28);
  v32 = 0;
  memset(v28, 0, 0x98u);
  v28[5] = *(void **)(a1 + 152);
  v28[3] = *(void **)(a1 + 140);
  rf_vector_copy((float *)&v28[15], copy_result, source);
  rf_matrix3_copy((float *)&v28[18], a4);
  v28[33] = *(void **)(a1 + 384);
  v28[37] = (void *)51;
  if ( (*(_DWORD *)(*(_DWORD *)(a1 + 660) + 1828) & 0x80000) != 0 )
    v28[37] = (void *)((int)v28[37] | 0x40);
  for ( i = 0; ; ++i )
  {
    first_dword = rf_receiver_get_first_dword((void *)(a1 + 388));
    if ( i >= first_dword )
      break;
    element_address_unchecked = (float *)rf_array24_get_element_address_unchecked((_DWORD *)(a1 + 388), i);
    v17 = v12;
    rf_record24_copy_construct_six_floats(v12, element_address_unchecked);
    rf_array24_append_record_by_value(
      (int *)&v28[34],
      v12[0],
      SLODWORD(v12[1]),
      SLODWORD(v12[2]),
      SLODWORD(v12[3]),
      v13,
      v14);
  }
  v30 = rf_object_create(7, -1, *(_DWORD *)(a1 + 44), (int)v28, 0, 0);
  if ( v30 )
  {
    *(_DWORD *)(v30 + 620) = *(_DWORD *)(a1 + 620);
    if ( (*(_DWORD *)(a1 + 2068) & 2) != 0 )
      *(_DWORD *)(v30 + 736) = 0;
    else
      rf_projected_shadow_build_entity_packet(a1, v30 + 732);
    *(_DWORD *)(v30 + 668) = 0;
    if ( v27 )
      *(_DWORD *)(v30 + 668) |= 0x80u;
    if ( v24 )
      *(_DWORD *)(v30 + 668) |= 0x400u;
    *(_DWORD *)(v30 + 32) = *(_DWORD *)(a1 + 32);
    if ( a1 == -2276 )
      *(_DWORD *)(v30 + 692) = -1;
    else
      *(_DWORD *)(v30 + 692) = *(_DWORD *)(a1 + 2276);
    *(_DWORD *)(v30 + 696) = -1;
    *(_DWORD *)(v30 + 728) = *(_DWORD *)(a1 + 5236);
    if ( rf_rf_string_not_equals_cstring_case_insensitive(*(_DWORD *)(a1 + 660) + 24, (char *)&byte_631929) )
    {
      v14 = -1;
      v13 = 1;
      v9 = (char *)rf_string_object_c_str_or_empty((const void *)(*(_DWORD *)(a1 + 660) + 24));
      v3m_mode1 = rf_model_handle_load_v3m_mode1(v9, v13, (void *)v14);
      *(_DWORD *)(v30 + 128) = v3m_mode1;
    }
    else
    {
      *(_DWORD *)(v30 + 128) = *(_DWORD *)(a1 + 128);
    }
    body_action_slot_by_name = -1;
    if ( rf_entity_admits_speech_body_actions(a1) )
      body_action_slot_by_name = rf_entity_find_body_action_slot_by_name(a1, Str);
    if ( body_action_slot_by_name != -1 && (*(_DWORD *)(*(_DWORD *)(a1 + 660) + 1828) & 0x200000) == 0 )
    {
      *(_DWORD *)(v30 + 696) = *(_DWORD *)(a1 + 16 * body_action_slot_by_name + 2644);
      if ( a6 == 1 )
        *(_DWORD *)(v30 + 668) |= 8u;
      rf_corpse_refresh_vmesh_geometry(v30);
    }
    if ( (*(_DWORD *)(*(_DWORD *)(a1 + 660) + 1828) & 0x200000) != 0 )
    {
      v22 = *(_DWORD *)(a1 + 2628);
      if ( v22 != -1 )
      {
        rf_model_handle_set_cyclic_mix_adapter(*(int **)(v30 + 128), v22, 1.0);
        *(_DWORD *)(v30 + 668) |= 4u;
      }
    }
    *(float *)(v30 + 120) = *(float *)(v30 + 384);
    *(_DWORD *)(v30 + 508) = *(_DWORD *)(a1 + 508);
    *(float *)(v30 + 660) = *(float *)&dword_6FC428;
    *(float *)(v30 + 52) = *(float *)(*(_DWORD *)(a1 + 660) + 68);
    *(_DWORD *)(v30 + 672) = *(_DWORD *)(a1 + 664);
    *(_DWORD *)(v30 + 720) = 0;
    *(_DWORD *)(v30 + 724) = -1;
    rf_vector3_zero_return_destination((float *)(v30 + 324));
    rf_vector3_zero_return_destination((float *)(v30 + 336));
    if ( Str )
      rf_string_assign_from_cstr((_DWORD *)(v30 + 676), Str);
    rf_timestamp4_invalidate((_DWORD *)(v30 + 684));
    if ( *(int *)(*(_DWORD *)(a1 + 660) + 40) > -1 )
    {
      v14 = 1;
      v13 = v30 + 60;
      v11 = rf_receiver_get_first_dword((void *)v30);
      v21 = rf_particle_emitter_create(
              *(_DWORD *)(v30 + 44),
              (float *)dword_867800[*(_DWORD *)(*(_DWORD *)(a1 + 660) + 40)],
              v11,
              v13,
              v14);
      if ( v21 )
      {
        *(_DWORD *)(v21 + 336) = *(_DWORD *)(v30 + 616);
        *(_DWORD *)(v30 + 616) = v21;
      }
      if ( *(int *)(*(_DWORD *)(a1 + 660) + 40) > 0 )
        rf_replicator_arm_milliseconds((int *)(v30 + 684), (int)(*(float *)(*(_DWORD *)(a1 + 660) + 44) * 1000.0 + 0.5));
    }
    if ( (*(_DWORD *)(a1 + 2068) & 8) != 0 )
      *(_DWORD *)(v30 + 668) |= 2u;
    if ( a5 == 1 )
      *(_DWORD *)(v30 + 668) |= 0x40u;
    *(_DWORD *)(v30 + 656) = unk_681D88;
    *(_DWORD *)(v30 + 652) = &unk_681AF8;
    *(_DWORD *)(unk_681D88 + 652) = v30;
    unk_681D88 = v30;
    ++unk_681AF0;
    v31 = rf_corpse_count_evictable();
    v23 = v31 - 5;
    if ( v31 - 5 > 0 )
    {
      for ( j = 0; j < v23; ++j )
      {
        oldest_evictable = rf_corpse_find_oldest_evictable();
        if ( oldest_evictable )
          rf_corpse_schedule_eviction(oldest_evictable);
      }
    }
    *(float *)(v30 + 688) = flt_68492C[1349 * *(_DWORD *)(v30 + 672)];
    v26 = rf_entity_find_body_action_slot_by_name(a1, "corpse_drop");
    if ( v26 == -1 )
      *(_DWORD *)(v30 + 700) = -1;
    else
      *(_DWORD *)(v30 + 700) = *(_DWORD *)(a1 + 16 * v26 + 2644);
    v26 = rf_entity_find_body_action_slot_by_name(a1, "corpse_carry");
    if ( v26 == -1 )
      *(_DWORD *)(v30 + 704) = -1;
    else
      *(_DWORD *)(v30 + 704) = *(_DWORD *)(a1 + 16 * v26 + 2644);
    if ( strstr(Str, "forward") || strstr(Str, "front") )
    {
      *(_DWORD *)(v30 + 708) = 0;
    }
    else if ( strstr(Str, "back") )
    {
      *(_DWORD *)(v30 + 708) = 1;
    }
    else
    {
      *(_DWORD *)(v30 + 708) = 2;
    }
    *(_DWORD *)(v30 + 712) = 0;
    if ( (*(_DWORD *)(a1 + 2064) & 0x200000) != 0 && *(_DWORD *)(a1 + 5136) )
    {
      *(_DWORD *)(v30 + 712) = *(_DWORD *)(a1 + 5136);
      *(_DWORD *)(a1 + 5136) = 0;
    }
    if ( (*(_DWORD *)(v30 + 424) & 0x20) != 0 && (*(_DWORD *)(v30 + 124) & 0x8000) == 0 )
      rf_collision_register_object_against_active_list(v30);
    rf_entity_spawn_flagged_blood_marks(a1);
    v15 = v30;
    v32 = -1;
    rf_object_setup152_destroy_array_backing(v28);
    return v15;
  }
  else
  {
    v16 = 0;
    v32 = -1;
    rf_object_setup152_destroy_array_backing(v28);
    return v16;
  }
}

