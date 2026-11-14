// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004B8FB0 rf_object_physics_frame_update
// UNREALRED VERIFIED [mission-mover-world-20261013] Mover update order verified: first common-list pass calls0x487EB0 for type8; second pass dispatches each object movement and builds physics work. Calls mover child composition0x48B500(initial=false) BEFORE0x4273E0 and rf_physics_work_batch_execute. Postphysics type-list effects and published transforms occur afterward. A renderer/postphysics-only mover integration is too late for current-frame collision/base movement.
// [UnrealRed combat room owner 2026-11-12; verified original-byte ASM] Room-refresh loop4B9362..4B93EB is GLOBAL AFTER move/type dispatch, mover composition,4273E0,batchphysics4B8C20,type-listupdate, and whole-object attachment recursion4B9AB0. It tests common7C dirty04000000&&!10000000 before4BC240. NOT per-object AI-then-room refresh; all earlier AI sees pre-late-refresh room data. Dirty position producer4BC330 is invoked by completed/forced physics work before this loop.
// UNREALRED VERIFIED [combat-original-facing-20261112]: Native worklist preparation is distinct from4B8C20 execution. In the second COMMON-list loop, retain next link, call per-type move, then common124 bit2 causes delete/skip. Otherwise4D7C90 resets physics even for a body that will not simulate. Only a nonzero should-simulate byte admits to the work array; for admitted type0 with physics424 bit2000,4D9410 spring preparation runs before OR40000000 and append. A separate player-flag OR player-associated predicate marks40000000 even outside that append branch. After the loop, mover child composition(initial0) then4273E0 precede4B8C20(workArray,fullDWORD1). Neither the full entity ring nor every type0 body is this already-reset active work array; an adapter must preserve admission/order and must not reset contact history twice.
void rf_object_physics_frame_update()
{
  float copy_result[3]; // [esp+4h] [ebp-1058h] BYREF
  int v1; // [esp+10h] [ebp-104Ch]
  int v2; // [esp+14h] [ebp-1048h]
  int timestamp_counter; // [esp+18h] [ebp-1044h]
  void *j; // [esp+1Ch] [ebp-1040h]
  void *v5; // [esp+20h] [ebp-103Ch]
  int v6; // [esp+24h] [ebp-1038h]
  int v7; // [esp+28h] [ebp-1034h]
  int v8; // [esp+2Ch] [ebp-1030h]
  int v9; // [esp+30h] [ebp-102Ch]
  int v10; // [esp+34h] [ebp-1028h]
  int v11; // [esp+38h] [ebp-1024h]
  int v12; // [esp+3Ch] [ebp-1020h]
  _DWORD v13[1027]; // [esp+40h] [ebp-101Ch] BYREF
  int i; // [esp+104Ch] [ebp-10h]
  int v15; // [esp+1058h] [ebp-4h]

  dword_6663C8 = 0;
  timestamp_counter = rf_clock_read_timestamp_counter();
  rf_embedded_array_construct_count_only_51ebe0(v13);
  v15 = 0;
  for ( i = 0; i < 2; ++i )
  {
    if ( rf_camera_slot_has_player_unchecked(i) && rf_view_wrapper_get_dword8((int)&unk_666AA0[3 * i]) == 2 )
    {
      v1 = unk_666AA0[3 * i];
      if ( ((unsigned int)&unk_800000 & *(_DWORD *)(v1 + 424)) != 0 )
      {
        *(_DWORD *)(v1 + 424) &= ~0x800000u;
      }
      else
      {
        rf_physics_state_frame_reset(v1 + 136);
        *(_DWORD *)(v1 + 424) |= 0x40000000u;
        rf_physics_work_batch_append(v13, v1);
      }
    }
  }
  v10 = rf_clock_read_timestamp_counter();
  for ( j = (void *)unk_7D0C90; j != &unk_7D0C80; j = *((void **)j + 4) )
  {
    rf_vector_copy((float *)j + 27, copy_result, (const float *)j + 15);
    *((_DWORD *)j + 31) &= ~0x1000000u;
    if ( *((_DWORD *)j + 9) == 8 )
      rf_mover_clear_linked_object_physics_flag((int)j);
  }
  j = (void *)unk_7D0C90;
  while ( j != &unk_7D0C80 )
  {
    v5 = *((void **)j + 4);
    rf_object_move_one_type_dispatch(j);
    if ( (*((_DWORD *)j + 31) & 2) != 0 )
    {
      rf_object_delete_dispatch(j);
      j = v5;
    }
    else
    {
      rf_physics_state_frame_reset((int)j + 136);
      if ( rf_object_physics_should_simulate((int)j) )
      {
        if ( (*((_DWORD *)j + 106) & 0x2000) != 0 && !*((_DWORD *)j + 9) )
          sub_4D9410((int)j);
        *((_DWORD *)j + 106) |= 0x40000000u;
        rf_physics_work_batch_append(v13, (int)j);
      }
      if ( rf_object_has_player_flag((int)j) || rf_object_is_player_associated((int)j) )
        *((_DWORD *)j + 106) |= 0x40000000u;
      j = v5;
    }
  }
  v9 = rf_clock_read_timestamp_counter();
  rf_mover_compose_child_transforms(0);
  rf_entities_copy_resolved_motion_vector();
  v2 = rf_clock_read_timestamp_counter();
  rf_physics_work_batch_execute(v13, 1);
  v6 = rf_clock_read_timestamp_counter();
  rf_pointer_array_clear_count_keep_storage(v13);
  v7 = rf_clock_read_timestamp_counter();
  rf_glass_commit_queued_geometry_when_boolean_idle();
  v11 = rf_clock_read_timestamp_counter();
  rf_object_type_lists_update();
  v8 = rf_clock_read_timestamp_counter();
  for ( j = (void *)unk_7D0C90; j != &unk_7D0C80; j = *((void **)j + 4) )
    rf_object_update_attachment_ancestors_once(j, 0);
  for ( j = (void *)unk_7D0C90; j != &unk_7D0C80; j = *((void **)j + 4) )
  {
    if ( (*((_DWORD *)j + 31) & 0x4000000) != 0 && (*((_DWORD *)j + 31) & 0x10000000) == 0 )
    {
      rf_object_refresh_room_cache_and_audio(j);
      if ( rf_object_is_entity((int)j) )
        rf_entity_update_liquid_flags_motion_and_shared_sound((int)j);
      else
        rf_object_liquid_state_update(j);
    }
  }
  v12 = rf_clock_read_timestamp_counter();
  v15 = -1;
  rf_shared_noop_destructor_4580d0();
}

