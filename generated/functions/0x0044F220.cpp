// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0044F220 rf_hud_weapon_ammo_dispatch
// UNREALRED VERIFIED [hud-admission-20261027] The valid selected-weapon branch moves current 0x661888 toward persistent target 0x66188C by frame delta / 0.3, clamping at target. This dispatcher has no selected-weapon-name comparison or reset-to-zero. The sole direct target setter 0x44F200 stores argument/255; the traced direct persona-end caller requests 255.0. Preserve persistent visibility across weapon changes rather than fabricating a weapon-switch fade.
void __cdecl rf_hud_weapon_ammo_dispatch(_DWORD *a1)
{
  int v1; // [esp+0h] [ebp-10h]
  int v2; // [esp+4h] [ebp-Ch]
  int selected_weapon_and_resolve_mesh; // [esp+8h] [ebp-8h]
  int v4; // [esp+Ch] [ebp-4h]

  selected_weapon_and_resolve_mesh = rf_player_get_selected_weapon_and_resolve_mesh(a1);
  if ( selected_weapon_and_resolve_mesh >= 0 )
  {
    if ( flt_66188C <= (double)flt_661888 )
    {
      if ( flt_66188C < (double)flt_661888 )
      {
        flt_661888 = flt_661888 - rf_frame_delta_seconds / 0.300000011920929;
        if ( flt_66188C > (double)flt_661888 )
          flt_661888 = flt_66188C;
      }
    }
    else
    {
      flt_661888 = rf_frame_delta_seconds / 0.300000011920929 + flt_661888;
      if ( flt_66188C < (double)flt_661888 )
        flt_661888 = flt_66188C;
    }
    v4 = rf_entity_resolve_handle(a1[5]);
    if ( v4
      && (!rf_entity_has_attached_use_vehicle(v4) || rf_entity_is_parent_jeep_relation1(v4))
      && (!rf_splitscreen_runtime_active || !rf_splitscreen_get_match_ended_byte())
      && selected_weapon_and_resolve_mesh != unk_911C80 )
    {
      v2 = v4;
      if ( rf_entity_has_attached_use_turret(v4) || rf_entity_is_parent_jeep_relation1(v4) )
      {
        v1 = rf_entity_resolve_handle(*(_DWORD *)(v4 + 512));
        if ( v1 )
        {
          v2 = v1;
          selected_weapon_and_resolve_mesh = *(_DWORD *)(v1 + 676);
        }
      }
      if ( rf_ui_top_panel_is11_or18() )
      {
        if ( rf_weapon_has_positive_clip_size(selected_weapon_and_resolve_mesh) )
        {
          if ( selected_weapon_and_resolve_mesh == unk_911C98 || selected_weapon_and_resolve_mesh == dword_911CC4 )
          {
            rf_hud_ammo_clip_render(v4, dword_911CC4, 0, selected_weapon_and_resolve_mesh != dword_911CC4);
            if ( !rf_multiplayer_runtime_mode )
              rf_hud_ammo_clip_render(v4, unk_911C98, 45, selected_weapon_and_resolve_mesh != unk_911C98);
          }
          else if ( selected_weapon_and_resolve_mesh == rf_weapon_id_riot_stick
                 || selected_weapon_and_resolve_mesh == rf_weapon_id_flamethrower )
          {
            rf_hud_ammo_special_power_render(v4, selected_weapon_and_resolve_mesh, 0, 0);
          }
          else
          {
            rf_hud_ammo_clip_render(v4, selected_weapon_and_resolve_mesh, 0, 0);
          }
        }
        else
        {
          rf_hud_ammo_noclip_render(v2, selected_weapon_and_resolve_mesh);
        }
      }
    }
  }
}

