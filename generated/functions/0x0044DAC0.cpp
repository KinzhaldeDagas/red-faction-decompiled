// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0044DAC0 rf_hud_player_status_render
// UNREALRED VERIFIED [hud-status-font-20261027] On-foot health and suit numeric values are measured (0x58C130) and drawn (0x58CFC0) with SMALL font handle 0x661694. X is authored value origin plus signed integer (authored region width - measured text width)/2; it is not clamped at the origin. Health uses coordinate pairs 1/2, suit 4/5. Replacing this font with bigfont causes overlapping 100/100 values; applying proportional host scale cannot repair that source-font ownership error.
int __cdecl rf_hud_player_status_render(int a1)
{
  int result; // eax
  int v2; // eax
  int v3; // eax
  int v4; // eax
  int v5; // [esp+4h] [ebp-C8h] BYREF
  int v6; // [esp+8h] [ebp-C4h] BYREF
  int v7; // [esp+Ch] [ebp-C0h] BYREF
  char v8[32]; // [esp+10h] [ebp-BCh] BYREF
  int v9; // [esp+30h] [ebp-9Ch]
  char v10[64]; // [esp+34h] [ebp-98h] BYREF
  char Buffer[68]; // [esp+74h] [ebp-58h] BYREF
  int v12; // [esp+BCh] [ebp-10h]
  int v13; // [esp+C0h] [ebp-Ch] BYREF
  int v14; // [esp+C4h] [ebp-8h] BYREF
  int v15; // [esp+C8h] [ebp-4h]

  result = rf_entity_resolve_handle(*(_DWORD *)(a1 + 20));
  v15 = result;
  if ( result )
  {
    if ( rf_entity_has_attached_use_vehicle(v15) )
    {
      rf_hud_directional_damage_render(a1);
      v12 = rf_entity_resolve_handle(*(_DWORD *)(v15 + 512));
      if ( rf_entity_is_parent_jeep_relation0(v15) || rf_entity_is_parent_jeep_relation1(v15) )
      {
        rf_render_color_set_rgba8(255, 255, 255, 120);
        rf_bitmap_draw_unscaled_clipped(dword_66187C, unk_6EE060, unk_6EE064, unk_187CD34);
        rf_bitmap_draw_unscaled_clipped(dword_661884, unk_6EE068, unk_6EE06C, unk_187CD34);
        v2 = rf_int_max((int)*(float *)(v12 + 52), 1);
        sprintf(Buffer, "%d", v2);
        rf_render_color_set_packed_rgba8((unsigned __int8 *)&rf_hud_color_full_rgba);
        return rf_font_draw_text_screen(unk_6EE070, unk_6EE074, (unsigned __int8 *)Buffer, dword_661694, dword_182ABBC);
      }
      else
      {
        result = rf_entity_class_flag1000(v12);
        if ( (_BYTE)result )
        {
          rf_render_color_set_rgba8(255, 255, 255, 120);
          rf_bitmap_draw_unscaled_clipped(dword_661880, unk_6EE078, unk_6EE07C, unk_187CD34);
          rf_bitmap_draw_unscaled_clipped(dword_661884, unk_6EE080, unk_6EE084, unk_187CD34);
          v3 = rf_int_max((int)*(float *)(v12 + 52), 1);
          sprintf(v10, "%d", v3);
          rf_render_color_set_packed_rgba8((unsigned __int8 *)&rf_hud_color_full_rgba);
          return rf_font_draw_text_screen(unk_6EE088, unk_6EE08C, (unsigned __int8 *)v10, dword_661694, dword_182ABBC);
        }
      }
    }
    else
    {
      if ( rf_ui_top_panel_is11_or18() )
      {
        rf_render_color_set_rgba8(255, 255, 255, 120);
        v6 = (int)(*(float *)(v15 + 52) / 10.0);
        rf_integer_clamp_in_place(&v6, 0, 10);
        rf_bitmap_draw_unscaled_clipped(unk_6EFD5C[v6], rf_hud_active_layout_coordinates, unk_6EDF14, unk_187CD34);
        v7 = (int)(*(float *)(v15 + 56) / *(float *)(*(_DWORD *)(v15 + 660) + 72) * 10.0);
        rf_integer_clamp_in_place(&v7, 0, 10);
        rf_bitmap_draw_unscaled_clipped(unk_6EFD30[v7], unk_6EDF28, unk_6EDF2C, unk_187CD34);
        rf_render_color_set_packed_rgba8((unsigned __int8 *)&rf_hud_color_full_rgba);
        v4 = rf_int_max((int)*(float *)(v15 + 52), 1);
        sprintf(v8, "%d", v4);
        rf_font_measure_text_extent(&v13, &v14, (unsigned __int8 *)v8, -1, dword_661694);
        v9 = unk_6EDF18 + (unk_6EDF20 - v13) / 2;
        rf_font_draw_text_screen(v9, unk_6EDF1C, (unsigned __int8 *)v8, dword_661694, dword_182ABBC);
        rf_render_color_set_packed_rgba8((unsigned __int8 *)&rf_hud_color_mid_rgba);
        sprintf(v8, "%d", (int)*(float *)(v15 + 56));
        rf_font_measure_text_extent(&v13, &v14, (unsigned __int8 *)v8, -1, dword_661694);
        v9 = unk_6EDF30 + (unk_6EDF38 - v13) / 2;
        rf_font_draw_text_screen(v9, unk_6EDF34, (unsigned __int8 *)v8, dword_661694, dword_182ABBC);
      }
      rf_hud_directional_damage_render(a1);
      result = rf_entity_is_carrying_body(v15);
      if ( (_BYTE)result )
      {
        rf_render_color_set_rgba8(255, 255, 255, 255);
        rf_render_state_pack(&v5, 1, 2, 3, 1, 0, 3);
        rf_bitmap_draw_unscaled_clipped(dword_661878, unk_6EE050, unk_6EE054, v5);
        rf_render_color_set_packed_rgba8(byte_6EE6B8);
        return rf_font_draw_text_screen(unk_6EE058, unk_6EE05C, unk_88D44C, dword_663050, dword_182ABBC);
      }
    }
  }
  return result;
}

