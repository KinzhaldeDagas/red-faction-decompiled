// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004DC860 rf_weapon_selector_draw
// UNREALRED VERIFIED [weapon-cycle] Draws the four-category weapon selector from the local Player+0x1154 preference order and the 32 fixed cycle slots; empty owned weapons are colored unavailable.
// UNREALRED VERIFIED [weapon-selector] Draws the timed right-edge selector with rfpc-medium.vf, four category boxes, owned-ammo markers, WeaponInfo+0x524 128x34 icons, and WeaponInfo+0x0 display names; timeout plays Off and closes it.
void rf_weapon_selector_draw()
{
  char *v0; // eax
  unsigned __int8 *v1; // eax
  int v2; // [esp+4h] [ebp-54h]
  int j; // [esp+20h] [ebp-38h]
  int v4; // [esp+24h] [ebp-34h]
  _DWORD v5[4]; // [esp+2Ch] [ebp-2Ch] BYREF
  int v6; // [esp+3Ch] [ebp-1Ch]
  int v7; // [esp+40h] [ebp-18h]
  int i; // [esp+44h] [ebp-14h]
  int viewport_width; // [esp+48h] [ebp-10h]
  int v10; // [esp+4Ch] [ebp-Ch]
  int viewport_height; // [esp+50h] [ebp-8h]
  int v12; // [esp+54h] [ebp-4h]

  if ( rf_local_fpgun_player )
  {
    if ( !rf_replicator_has_elapsed(&rf_weapon_selector_deadline_event)
      && rf_replicator_is_armed(&rf_weapon_selector_deadline_event) )
    {
      viewport_width = rf_renderer_get_viewport_width();
      viewport_height = rf_renderer_get_viewport_height();
      v10 = 0;
      rf_render_color_set_rgba8(15, 242, 2, 255);
      rf_font_set_default_by_name("rfpc-medium.vf");
      switch ( rf_weapon_cycle_slots_category[4 * rf_weapon_selector_current_cycle_slot] )
      {
        case 0:
          rf_font_draw_text_aligned(1, viewport_width - 74, 113, unk_88E064, -1, dword_182ABBC);
          v10 = viewport_width - 120;
          break;
        case 1:
          rf_font_draw_text_aligned(1, viewport_width - 74, 113, unk_88E068, -1, dword_182ABBC);
          v10 = viewport_width - 97;
          break;
        case 2:
          rf_font_draw_text_aligned(1, viewport_width - 74, 113, unk_88E06C, -1, dword_182ABBC);
          v10 = viewport_width - 74;
          break;
        case 3:
          rf_font_draw_text_aligned(1, viewport_width - 74, 113, unk_88E070, -1, dword_182ABBC);
          v10 = viewport_width - 51;
          break;
        default:
          break;
      }
      rf_render_color_set_rgba8(0, 0, 0, 128);
      rf_renderer_fill_rectangle_clipped(viewport_width - 119, 129, 20, 20, dword_182ABB8);
      rf_renderer_fill_rectangle_clipped(viewport_width - 96, 129, 20, 20, dword_182ABB8);
      rf_renderer_fill_rectangle_clipped(viewport_width - 73, 129, 20, 20, dword_182ABB8);
      rf_renderer_fill_rectangle_clipped(viewport_width - 50, 129, 20, 20, dword_182ABB8);
      rf_render_color_set_rgba8(15, 242, 2, 255);
      rf_font_draw_text_screen(viewport_width - 114, 132, "1", -1, dword_182ABBC);
      rf_font_draw_text_screen(viewport_width - 91, 132, "2", -1, dword_182ABBC);
      rf_font_draw_text_screen(viewport_width - 68, 132, "3", -1, dword_182ABBC);
      rf_font_draw_text_screen(viewport_width - 45, 132, "4", -1, dword_182ABBC);
      rf_render_color_set_rgba8(239, 213, 52, 255);
      rf_renderer_fill_rectangle_clipped(v10, 127, 22, 1, dword_182ABB8);
      rf_renderer_fill_rectangle_clipped(v10 + 22, 127, 1, 22, dword_182ABB8);
      rf_renderer_fill_rectangle_clipped(v10, 127, 1, 22, dword_182ABB8);
      rf_renderer_fill_rectangle_clipped(v10 + 1, 149, 22, 1, dword_182ABB8);
      memset(v5, 0, sizeof(v5));
      v12 = rf_entity_resolve_handle(*(_DWORD *)(rf_local_fpgun_player + 20));
      v7 = rf_player_resolve_entity_inventory(rf_local_fpgun_player);
      for ( i = 0; i < 32; ++i )
      {
        for ( j = 0;
              j < 32 && rf_weapon_cycle_slots_weapon_index[4 * j] != *(_DWORD *)(rf_local_fpgun_player + 4 * i + 4436);
              ++j )
        {
          ;
        }
        v6 = rf_weapon_cycle_slots_category[4 * j];
        v4 = rf_weapon_cycle_slots_weapon_index[4 * j];
        if ( v4 != -1 && v6 != -1 && j != 32 && sub_403D00(v7, v4) )
        {
          if ( rf_player_weapon_available_ammo(rf_local_fpgun_player, v4) <= 0 )
            rf_render_color_set_rgba8(254, 55, 55, 255);
          else
            rf_render_color_set_rgba8(60, 126, 5, 255);
          rf_renderer_fill_rectangle_clipped(viewport_width + 23 * v6 - 114, 5 * v5[v6] + 150, 10, 3, dword_182ABB8);
          if ( v6 == rf_weapon_cycle_slots_category[4 * rf_weapon_selector_current_cycle_slot] )
          {
            if ( rf_weapon_selector_icon_cache[v4] == -1 )
            {
              v0 = (char *)rf_string_object_c_str_or_empty((char *)&rf_weapon_records_selector_icon + 1360 * v4);
              rf_weapon_selector_icon_cache[v4] = rf_bitmap_load_with_optional_mipmap_generation(
                                                    v0,
                                                    (void *)0xFFFFFFFF,
                                                    1);
            }
            rf_bitmap_draw_unscaled_clipped(
              rf_weapon_selector_icon_cache[v4],
              viewport_width - 139,
              35 * v5[v6] + 176,
              unk_187CD38);
            if ( v4 == rf_weapon_cycle_slots_weapon_index[4 * rf_weapon_selector_current_cycle_slot] )
            {
              rf_render_color_set_rgba8(239, 213, 52, 255);
              rf_renderer_fill_rectangle_clipped(viewport_width - 139, 35 * v5[v6] + 176, 128, 1, dword_182ABB8);
              rf_renderer_fill_rectangle_clipped(viewport_width - 12, 35 * v5[v6] + 177, 1, 34, dword_182ABB8);
              rf_renderer_fill_rectangle_clipped(viewport_width - 139, 35 * v5[v6] + 177, 1, 33, dword_182ABB8);
              rf_renderer_fill_rectangle_clipped(viewport_width - 138, 35 * v5[v6] + 209, 126, 1, dword_182ABB8);
            }
          }
          ++v5[v6];
        }
      }
      rf_render_color_set_rgba8(15, 242, 2, 255);
      v2 = dword_182ABBC;
      v1 = (unsigned __int8 *)rf_string_object_c_str_or_empty(
                                (char *)&rf_weapon_records_display_name
                              + 1360 * rf_weapon_cycle_slots_weapon_index[4 * rf_weapon_selector_current_cycle_slot]);
      rf_font_draw_text_aligned(
        1,
        viewport_width - 74,
        35 * (v5[rf_weapon_cycle_slots_category[4 * rf_weapon_selector_current_cycle_slot]] + 1) + 176,
        v1,
        -1,
        v2);
    }
    else
    {
      rf_gamesound_play_event(rf_weapon_selector_off_sound_event, 0, 0.0, 1.0);
      rf_weapon_selector_is_open = 0;
    }
  }
}

