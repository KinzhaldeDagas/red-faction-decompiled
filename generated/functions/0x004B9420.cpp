// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004B9420 rf_object_move_one_type_dispatch
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, object lifetime/free-slot/attachment/render chains, original dispatch tables and field widths and native
// signed/x87/stack/callback ABI): One stack common-object pointer. Clears common flags+124 bit0x200000, processes emitter chain starting at+616 using ECX=emitter and reading next+336
// AFTER each callback. Then switches unsigned type DWORD+36,0..10: entity426890/item fade/projectile prephysics/debris expiry/clutter lifetime for0..4, each followed unconditionally
// by4B7710(object), including if preceding callback marked deletion. Types5/6 have no further callback;7 corpse animation;8 mover motion;9 noop helper receives pushed object;10 glare
// owner check. Out-of-range enters repeated fatal-report path (object.cpp:1476). No return-status construction or independent deletion here. Decompiler-inferred ST0 argument comes
// from callee propagation and is not evidenced by this body; native calls push one object and clean four bytes.
void __cdecl rf_object_move_one_type_dispatch(_DWORD *a1)
{
  int i; // [esp+4h] [ebp-4h]

  a1[31] &= ~0x200000u;
  for ( i = a1[154]; i; i = *(_DWORD *)(i + 336) )
    rf_particle_emitter_process(i);
  switch ( a1[9] )
  {
    case 0:
      rf_entity_update_shield_ai_vfx_and_runtime_markers((int)a1);
      rf_object_apply_containing_push_region((int)a1);
      break;
    case 1:
      rf_item_advance_fade_lifetime((int)a1);
      rf_object_apply_containing_push_region((int)a1);
      break;
    case 2:
      rf_projectile_prephysics_update((int)a1);
      rf_object_apply_containing_push_region((int)a1);
      break;
    case 3:
      rf_physical_debris_expiry_health_update((int)a1);
      rf_object_apply_containing_push_region((int)a1);
      break;
    case 4:
      rf_clutter_update_lifetime_and_death((int)a1);
      rf_object_apply_containing_push_region((int)a1);
      break;
    case 5:
    case 6:
      return;
    case 7:
      rf_corpse_update_animation((int)a1);
      break;
    case 8:
      rf_mover_update_motion((int)a1);
      break;
    case 9:
      rf_object_move_dispatch_noop();
      break;
    case 0xA:
      rf_glare_mark_delete_if_owner_missing((int)a1);
      break;
    default:
      rf_fatal_error_show_message_and_exit(
        "D:\\projects\\rf_pc\\gamesrc\\object\\object.cpp",
        1476,
        "Unhandled object type in obj_move_one\n");
  }
}

