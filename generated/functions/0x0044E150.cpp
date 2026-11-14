// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0044E150 rf_hud_reticle_render
// UNREALRED VERIFIED [hud-viewport-20261027] Ordinary/locked reticle queries current width/height via 0x571C00/0x571C10, queries source bitmap dimensions and centers using (view-source)/2 before an unscaled draw. HUD fitting must preserve the actual owning viewport center; it must not apply a widget transform to already projected world-target screen positions.
void __cdecl rf_hud_reticle_render(int a1)
{
  int v1; // [esp+8h] [ebp-34h]
  int v2; // [esp+Ch] [ebp-30h] BYREF
  float alt_zoom_factor; // [esp+10h] [ebp-2Ch]
  int viewport_width; // [esp+14h] [ebp-28h]
  int viewport_height; // [esp+18h] [ebp-24h]
  int v6; // [esp+1Ch] [ebp-20h]
  int v7; // [esp+20h] [ebp-1Ch]
  int selected_weapon_and_resolve_mesh; // [esp+24h] [ebp-18h]
  char *v9; // [esp+28h] [ebp-14h]
  char target_lock_ready_byte; // [esp+2Fh] [ebp-Dh]
  int v11; // [esp+30h] [ebp-Ch]
  int v12; // [esp+34h] [ebp-8h] BYREF
  int v13; // [esp+38h] [ebp-4h]

  if ( !unk_757658 && unk_6EE698 != 1 )
  {
    v6 = a1 + 228;
    if ( *(_BYTE *)(a1 + 3899) )
    {
      if ( *(_BYTE *)(a1 + 4016) != 1
        && !rf_player_has_no_resolved_entity(a1)
        && !rf_player_resolved_entity_is_dead(a1)
        && !rf_unhide_global_owner_present() )
      {
        v7 = rf_player_resolve_view_entity_with_monitor_fallback(a1);
        if ( !v7 || *(_DWORD *)(v7 + 44) == *(_DWORD *)(a1 + 20) )
        {
          v13 = rf_entity_resolve_handle(*(_DWORD *)(a1 + 20));
          if ( v13 )
          {
            v11 = rf_entity_resolve_handle(*(_DWORD *)(v13 + 512));
            if ( !v11
              || !rf_entity_has_attached_use_vehicle(v13)
              || rf_entity_is_parent_jeep_relation1(v13)
              || rf_entity_class_has_contact_geomod_flag200(v11) )
            {
              selected_weapon_and_resolve_mesh = rf_player_get_selected_weapon_and_resolve_mesh((_DWORD *)a1);
              if ( selected_weapon_and_resolve_mesh >= 0 )
              {
                v9 = (char *)&rf_weapon_records + 1360 * selected_weapon_and_resolve_mesh;
                if ( (!rf_entity_weapon_is_holstered_for_actions(v13) || rf_entity_is_parent_jeep_relation1(v13))
                  && !rf_entity_is_parent_jeep_relation0(v13) )
                {
                  if ( *(_BYTE *)(a1 + 3903) )
                  {
                    alt_zoom_factor = rf_player_query_alt_zoom_factor(a1);
                    if ( alt_zoom_factor <= 0.0 )
                    {
                      target_lock_ready_byte = rf_player_get_target_lock_ready_byte(a1);
                      v1 = unk_187CD38;
                      viewport_width = rf_renderer_get_viewport_width();
                      viewport_height = rf_renderer_get_viewport_height();
                      if ( target_lock_ready_byte == 1 && *((int *)v9 + 148) >= 0 )
                      {
                        rf_bitmap_get_resolved_dimensions(*((_DWORD *)v9 + 148), &v2, &v12);
                        rf_render_color_set_rgba8(255, 255, 255, 255);
                        rf_bitmap_draw_unscaled_clipped(
                          *((_DWORD *)v9 + 148),
                          (viewport_width - v2) / 2,
                          (viewport_height - v12) / 2,
                          v1);
                      }
                      else if ( *((int *)v9 + 146) >= 0 )
                      {
                        rf_bitmap_get_resolved_dimensions(*((_DWORD *)v9 + 146), &v2, &v12);
                        rf_render_color_set_rgba8(255, 255, 255, 255);
                        rf_bitmap_draw_unscaled_clipped(
                          *((_DWORD *)v9 + 146),
                          (viewport_width - v2) / 2,
                          (viewport_height - v12) / 2,
                          v1);
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
}

