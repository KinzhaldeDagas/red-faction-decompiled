// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00501F30 rf_mission_event_render_debug_icon
// UNREALRED VERIFIED [event-state-registry-continuation-20261027] Only global byte0x90B054==1 proceeds. Get view position from current context0x87C640+0xC4, reject geometry obstruction(view,event+0x40,3,0). Set opaque white, lazily load icon_event.tga into global0x90B0D8 if-1, bind(handle,-1), and invoke0x57E990(event position,0.0,1.0,renderer state). No event activation, icon release or explicit bitmap-load-failure return gate.
char __cdecl rf_mission_event_render_debug_icon(int a1)
{
  char result; // al
  float v2[3]; // [esp+Ch] [ebp-Ch] BYREF

  result = unk_90B054;
  if ( unk_90B054 == 1 )
  {
    rf_entity_view_copy_referenced_position(v2, *(_DWORD *)(unk_87C640 + 196));
    result = rf_geometry_segment_is_obstructed(v2, (float *)(a1 + 64), 3, nullptr);
    if ( !result )
    {
      rf_render_color_set_rgba8(255, 255, 255, 255);
      if ( dword_90B0D8 == -1 )
        dword_90B0D8 = rf_bitmap_load_with_optional_mipmap_generation("icon_event.tga", (void *)0xFFFFFFFF, 1);
      rf_renderer_set_pending_texture_handles(dword_90B0D8, -1);
      return rf_renderer_world_billboard_aspect_backend_dispatch(a1 + 64, 0.0, 1.0, unk_182ABAC);
    }
  }
  return result;
}

