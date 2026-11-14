// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004BA710 rf_object_render_one_type_dispatch
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, object lifetime/free-slot/attachment/render chains, original dispatch tables and field widths and native
// signed/x87/stack/callback ABI): One required object pointer. Common flags+124 bit2 returns before color/render work. Otherwise sets current RGBA to255 each. Only when model+128 is
// nonnull: inactive predicate AL==EXACT1 returns before dispatch/rendered flag; descriptor kind==3 invokes VFX update with six stack arguments (model, frameDelta
// float32,0,object+60,object+72,1). Model-null objects still reach type dispatch even if inactive. Unsigned type DWORD+36 must be0..10:
// entity42BD40,item,projectile,debris,clutter,trigger debug,event debug(object-4 with local null conversion),corpse,mover debug,moving solid,glare respectively. Out-of-range enters
// repeated fatal-report path object.cpp:1761. After normal dispatch ORs common bit0x10, regardless whether type renderer actually submitted geometry. Early returns do not set it.
// Native EAX/AL return depends on path; not a uniform render-success boolean.
char __cdecl rf_object_render_one_type_dispatch(int a1)
{
  int v1; // eax

  LOBYTE(v1) = a1;
  if ( (*(_DWORD *)(a1 + 124) & 2) == 0 )
  {
    rf_render_color_set_rgba8(255, 255, 255, 255);
    if ( *(_DWORD *)(a1 + 128) )
    {
      LOBYTE(v1) = rf_object_has_respawn_inactive_flag(a1);
      if ( (unsigned __int8)v1 == 1 )
        return v1;
      if ( rf_model_descriptor_get_kind(*(_DWORD *)(a1 + 128)) == 3 )
        rf_vfx_update_instance(*(int **)(a1 + 128), rf_frame_delta_seconds, 0, a1 + 60, a1 + 72, 1);
    }
    switch ( *(_DWORD *)(a1 + 36) )
    {
      case 0:
        rf_entity_render_body_and_attachments_with_view_gates(a1);
        break;
      case 1:
        rf_item_render_model(a1);
        break;
      case 2:
        rf_projectile_render_model_bitmap_or_tracer(a1);
        break;
      case 3:
        rf_physical_debris_render_with_lifetime_alpha(a1);
        break;
      case 4:
        rf_clutter_render_model_with_shield_view_gate((_DWORD *)a1);
        break;
      case 5:
        rf_trigger_debug_draw_one(a1);
        break;
      case 6:
        if ( a1 )
          rf_mission_event_render_debug_icon(a1 - 4);
        else
          rf_mission_event_render_debug_icon(0);
        break;
      case 7:
        rf_corpse_render_alpha(a1);
        break;
      case 8:
        rf_mover_debug_draw_keys((_DWORD *)a1);
        break;
      case 9:
        rf_moving_solid_submit_faces_unless_suppressed(a1);
        break;
      case 0xA:
        rf_glare_render_runtime_volumetric_beam(a1);
        break;
      default:
        rf_fatal_error_show_message_and_exit(
          "D:\\projects\\rf_pc\\gamesrc\\object\\object.cpp",
          1761,
          "Unhandled obj type in obj_render");
    }
    v1 = *(_DWORD *)(a1 + 124) | 0x10;
    *(_DWORD *)(a1 + 124) = v1;
  }
  return v1;
}

