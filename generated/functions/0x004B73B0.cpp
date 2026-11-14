// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004B73B0 rf_object_delete_dispatch
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, object lifetime/free-slot/attachment/render chains, original dispatch tables and field widths and native
// signed/x87/stack/callback ABI): One cdecl common-object pointer, required nonnull. First removes collision pairs, then dispatches DWORD+36 types 0..10 respectively to431260, item
// unlink/name cleanup, projectile destruction, physical-debris destruction, clutter cleanup/unlink, trigger cleanup/unlink, mission-event unregister(object-4), corpse cleanup/unlink,
// mover resources/unlink,48A540, and glare unlink. Out-of-range unsigned type enters repeated fatal-report path (object.cpp:1097). The event-case null conversion does not make the
// overall function null-safe. After the type callback: releases physics sphere storage at object+136, invokes4BBFC0 for model ownership cleanup, drains emitter head+616 while saving
// emitter+336 BEFORE destruction, assigns empty string to object+24, then releases object-table slot LOW16(object DWORD+44) through4B7570. No object access after slot release; EAX is
// the free-node address returned by that helper, not an independent success status.
int *__cdecl rf_object_delete_dispatch(_DWORD *a1)
{
  int v2; // [esp+8h] [ebp-8h]

  rf_collision_remove_pairs_for_object((int)a1);
  switch ( a1[9] )
  {
    case 0:
      rf_entity_release_runtime_resources_and_unlink((int)a1);
      break;
    case 1:
      rf_item_unlink_and_clear_instance_name(a1);
      break;
    case 2:
      rf_projectile_destroy_runtime(a1);
      break;
    case 3:
      rf_geomod_debris_object_destroy(a1);
      break;
    case 4:
      rf_clutter_cleanup_resources_and_unlink((int)a1);
      break;
    case 5:
      rf_trigger_unlink_and_clear_members((int)a1);
      break;
    case 6:
      if ( a1 )
        rf_mission_event_unregister_and_track_removal((int)(a1 - 1));
      else
        rf_mission_event_unregister_and_track_removal(0);
      break;
    case 7:
      rf_corpse_cleanup_resources_and_unlink(a1);
      break;
    case 8:
      rf_mover_release_keys_arrays_and_unlink((int)a1);
      break;
    case 9:
      sub_48A540(a1);
      break;
    case 0xA:
      rf_glare_unlink_runtime_record((int)a1);
      break;
    default:
      rf_fatal_error_show_message_and_exit(
        "D:\\projects\\rf_pc\\gamesrc\\object\\object.cpp",
        1097,
        "Unhandled object type in obj_delete");
  }
  rf_physics_state_release_sphere_array_storage((int)(a1 + 34));
  rf_object_release_owned_model_handle((int)a1);
  while ( a1[154] )
  {
    v2 = *(_DWORD *)(a1[154] + 336);
    rf_particle_emitter_destroy(a1[154]);
    a1[154] = v2;
  }
  rf_string_assign_from_cstr(a1 + 6, (char *)&byte_63B86D);
  return rf_object_release_slot_and_storage((unsigned __int16)a1[11]);
}

