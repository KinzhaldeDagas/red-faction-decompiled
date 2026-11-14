// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00417FA0 rf_monitor_render_selected_entity_view
// UNREALRED VERIFIED [alarm-monitor-slay-continuation-20261027] Proceed only when flags+0x38 bit4 clear, selected entity+0x10 resolves, and monitor clutter+0xC resolves. Establish viewport from dimensions+0x30/+0x34 and entity view data(+0x7E0/+0x7D4), clear and render world rooms with authored sky, then admitted bolt emitters. Scoped global0x6807E0 is1 during room render and reset0 afterward. Copy resulting rectangle to bitmap+0x14 through0x573920, run0x51E620 and set flag4. Missing entity/clutter leaves flag4 clear. This body alone does not establish full renderer-state restoration.
// [UnrealRed retained room-view state 2026-11-12; full original-byte main/monitor closure] Actual mode0 monitor world-room view contributes toROOM352. It has its own camera5C4D10 setup but no own farsetter, therefore inherits shared renderer far/other state left by prior ordered passes. Thermal/scanner captures do not write352 yet may alter projection/pool state between world passes. Do not default far anew for each monitor or drop this pass from previous-render union.
int *__cdecl rf_monitor_render_selected_entity_view(int *a1)
{
  int *result; // eax
  int v2; // eax
  int first_dword; // eax
  _DWORD **v4; // eax
  float **v5; // eax
  int i; // [esp+Ch] [ebp-Ch]
  int *v7; // [esp+10h] [ebp-8h]

  result = a1;
  if ( (a1[14] & 4) == 0 )
  {
    result = (int *)rf_entity_resolve_handle(a1[4]);
    v7 = result;
    if ( result )
    {
      result = (int *)rf_clutter_find_by_uid(a1[3]);
      if ( result )
      {
        rf_renderer_set_viewport_and_relative_clip(0, 0, a1[12], a1[13]);
        rf_render_color_set_rgba8(0, 0, 0, 255);
        rf_renderer_clear_color_backend_dispatch();
        rf_renderer_set_camera_projection_dispatch((int)(v7 + 504), (int)(v7 + 501), 50.0, 1, 1);
        rf_renderer_reserved_noop_5260d0();
        rf_world_decal_advance_fade_and_expiry();
        rf_volume_prepare_visible_for_view();
        rf_object_clear_rendered_and_physics_skip_flags();
        unk_6807E0 = 1;
        if ( rf_skybox_rotation_degrees_per_second <= 0.0 )
        {
          first_dword = rf_receiver_get_first_dword(v7);
          rf_world_render_rooms_with_authored_sky(rf_world_solid, first_dword, 0, 0);
        }
        else
        {
          v2 = rf_receiver_get_first_dword(v7);
          rf_world_render_rooms_with_authored_sky(rf_world_solid, v2, 0, (int)&rf_skybox_rotation_matrix);
        }
        unk_6807E0 = 0;
        for ( i = 0; i < rf_receiver_get_first_dword(rf_bolt_emitter_registry); ++i )
        {
          v4 = (_DWORD **)sub_552200(rf_bolt_emitter_registry, i);
          if ( rf_bolt_emitter_get_room_byte352(*v4) == 1 )
          {
            v5 = (float **)sub_552200(rf_bolt_emitter_registry, i);
            rf_bolt_emitter_regenerate_points_and_render(*v5, (int)(v7 + 501));
          }
        }
        rf_renderer_reserved_noop_5738C0();
        rf_bitmap_capture_backbuffer_into_bitmap(0, 0, a1[12], a1[13], a1[5]);
        rf_solid_reset_array168_cache_indices(rf_world_solid);
        a1[14] |= 4u;
        return a1;
      }
    }
  }
  return result;
}

