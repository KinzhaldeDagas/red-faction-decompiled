// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0044D160 rf_hud_persona_update_and_render
// UNREALRED VERIFIED [hud-persona-presentation-20261027] Presentation owns fade retirement separately from the activation timer: advance opacity first (snap upward, subtract frame_delta/0.75 downward, clamp); retire active index only at nonpositive opacity. With an active record and entity context, timer +0x124 elapsed AND selected record voice +0x1C not playing requests target zero, then current opacity still renders this frame. Expiring the source timer must not discard text/portrait before this admitted renderer can fade. Player persona flag/zoom/master admission outside this function can postpone fade processing.
void __cdecl rf_hud_persona_update_and_render(int a1)
{
  unsigned __int8 *v1; // eax
  int v2; // [esp-4h] [ebp-198h]
  int opacity_255; // [esp+0h] [ebp-194h]
  int height_select_current; // [esp+18h] [ebp-17Ch]
  char Destination[260]; // [esp+1Ch] [ebp-178h] BYREF
  int v6; // [esp+124h] [ebp-70h]
  size_t Count[8]; // [esp+128h] [ebp-6Ch] BYREF
  int line_offsets[8]; // [esp+148h] [ebp-4Ch] BYREF
  int i; // [esp+168h] [ebp-2Ch]
  int v10; // [esp+16Ch] [ebp-28h]
  int v11; // [esp+170h] [ebp-24h]
  int v12; // [esp+174h] [ebp-20h]
  std::exception *v13; // [esp+178h] [ebp-1Ch]
  int v14; // [esp+17Ch] [ebp-18h]
  int v15; // [esp+180h] [ebp-14h]
  int v16; // [esp+184h] [ebp-10h]
  int viewport_width; // [esp+188h] [ebp-Ch]
  int v18; // [esp+18Ch] [ebp-8h]
  int viewport_height; // [esp+190h] [ebp-4h]

  if ( rf_hud_persona_target_opacity >= (double)rf_hud_persona_opacity )
  {
    if ( rf_hud_persona_target_opacity > (double)rf_hud_persona_opacity )
      rf_hud_persona_opacity = rf_hud_persona_target_opacity;
  }
  else
  {
    rf_hud_persona_opacity = rf_hud_persona_opacity - rf_frame_delta_seconds / 0.75;
    if ( rf_hud_persona_target_opacity > (double)rf_hud_persona_opacity )
      rf_hud_persona_opacity = rf_hud_persona_target_opacity;
  }
  if ( rf_hud_persona_opacity <= 0.0 || rf_hud_persona_active_index == -1 )
  {
    rf_hud_persona_active_index = -1;
  }
  else if ( rf_ui_top_panel_is11_or18() )
  {
    v12 = 0;
    v18 = rf_entity_resolve_handle(*(_DWORD *)(a1 + 20));
    if ( v18 )
    {
      v16 = rf_entity_resolve_handle(*(_DWORD *)(v18 + 512));
      if ( v16
        && (rf_entity_class_has_contact_geomod_flag400(v16)
         || rf_entity_class_flag1000(v16)
         || rf_entity_has_jeep_flag(v16)
         || rf_entity_class_flags724_has_mask800(v16)) )
      {
        v12 = unk_6EE034;
      }
      v13 = (std::exception *)&rf_hud_persona_records[296 * rf_hud_persona_active_index];
      if ( rf_replicator_has_elapsed((int *)v13 + 73) && !rf_gamesound_voice_is_playing(*((_DWORD *)v13 + 7)) )
      {
        rf_hud_store_scalar66188C_divided_by255(255.0);
        rf_hud_persona_set_target_opacity255(0.0);
      }
      rf_render_color_set_packed_rgba8(byte_6EE6BC);
      rf_render_color_set_alpha8((int)((double)unk_6EE6BF * rf_hud_persona_opacity));
      v11 = unk_6EE000;
      v15 = v12 + unk_6EE004;
      viewport_width = rf_renderer_get_viewport_width();
      viewport_height = rf_renderer_get_viewport_height();
      v14 = viewport_width - 317;
      rf_renderer_fill_rectangle_clipped(158, v12 + 11, 70, (int)(rf_hud_persona_opacity * 85.0), dword_182ABB8);
      rf_render_color_set_rgba8(255, 255, 255, (int)(rf_hud_persona_opacity * 77.0));
      rf_renderer_fill_rectangle_clipped(157, v15, 2, 106, dword_182ABB8);
      rf_renderer_fill_rectangle_clipped(viewport_width - 158, v15, 2, 106, dword_182ABB8);
      rf_renderer_fill_rectangle_clipped(159, v15, viewport_width - 317, 2, dword_182ABB8);
      rf_renderer_fill_rectangle_clipped(159, v12 + 114, viewport_width - 317, 2, dword_182ABB8);
      rf_render_color_set_rgba8(0, 0, 0, (int)(rf_hud_persona_opacity * 128.0));
      rf_renderer_fill_rectangle_clipped(159, v15 + 2, viewport_width - 317, 102, dword_182ABB8);
      rf_render_color_set_packed_rgba8(byte_6EE6A4);
      rf_render_color_set_alpha8((int)((double)unk_6EE6A7 * rf_hud_persona_opacity));
      if ( rf_string_is_empty((int *)v13 + 4) )
      {
        opacity_255 = dword_182ABBC;
        v2 = dword_663048;
        v1 = (unsigned __int8 *)rf_string_object_c_str_or_empty(v13);
      }
      else
      {
        opacity_255 = dword_182ABBC;
        v2 = dword_663048;
        v1 = (unsigned __int8 *)rf_string_object_c_str_or_empty((char *)v13 + 16);
      }
      rf_font_draw_text_aligned(1, 193, v12 + 82, v1, v2, opacity_255);
      if ( v13 != (std::exception *)-36 )
      {
        Destination[255] = 0;
        v10 = v15 + 6;
        height_select_current = rf_font_get_height_select_current(dword_663050);
        v6 = rf_text_wrap_into_offset_length_arrays(
               (int *)Count,
               line_offsets,
               (const char *)v13 + 36,
               dword_6EE018,
               8,
               0,
               dword_663050);
        rf_render_color_set_packed_rgba8(byte_6EE6A8);
        rf_render_color_set_alpha8((int)((double)unk_6EE6AB * rf_hud_persona_opacity));
        for ( i = 0; i < v6; ++i )
        {
          strncpy(Destination, (const char *)v13 + line_offsets[i] + 36, Count[i]);
          Destination[Count[i]] = 0;
          rf_font_draw_text_screen(235, v10, (unsigned __int8 *)Destination, dword_663050, dword_182ABBC);
          v10 += height_select_current;
        }
      }
      rf_render_color_set_packed_rgba8(byte_6EE6A8);
      rf_render_color_set_alpha8((int)((double)unk_6EE6AB * rf_hud_persona_opacity));
      rf_bitmap_draw_unscaled_clipped(*((_DWORD *)v13 + 6), 161, v15 + 4, unk_187CC7C);
    }
  }
}

