// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004E2C90 rf_player_render_attached_vehicle_cockpit
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, cockpit material/animation, vehicle camera nodes and integer gauge ABI): Assumes player and camera pointer+196 valid. Any nonzero camera state(camera+8 via4118B0) exits. Resolve own entity then linked UID+512, either missing exits. If cockpit handle2C40!=0, update private cockpit material table2E90, construct render options, render at saved player position4244/matrix4256 when linked class flags+1828 mask0x1000, otherwise own entity position2004/matrix72. Regardless cockpit handle, linked selected weapon676==-1 exits; otherwise derive1360-byte weapon record. Unelapsed linked timer4972 and weapon effect index60!=-1 set flash byte1. For nonfighter(class mask0x800 clear), compose linked model128 at class prop244 with position60/matrix72 then call41A790(effect,position,matrix,1). Fighter invokes46B0(player,linked,flash),
// then all selected-weapon paths render reticle. No own weapon/index/NULL camera validation. Flash condition uses timer result==0, not a firing predicate.
void __cdecl rf_player_render_attached_vehicle_cockpit(int a1)
{
  float v1[3]; // [esp+0h] [ebp-98h] BYREF
  char v2[36]; // [esp+Ch] [ebp-8Ch] BYREF
  char v3[84]; // [esp+30h] [ebp-68h] BYREF
  int attached_cockpit_model_handle; // [esp+84h] [ebp-14h]
  int v5; // [esp+88h] [ebp-10h]
  char *v6; // [esp+8Ch] [ebp-Ch]
  char v7; // [esp+93h] [ebp-5h]
  int v8; // [esp+94h] [ebp-4h]

  if ( !rf_view_wrapper_get_dword8(*(_DWORD *)(a1 + 196)) )
  {
    v8 = rf_entity_resolve_handle(*(_DWORD *)(a1 + 20));
    if ( v8 )
    {
      v5 = rf_entity_resolve_handle(*(_DWORD *)(v8 + 512));
      if ( v5 )
      {
        attached_cockpit_model_handle = rf_player_get_attached_cockpit_model_handle(a1);
        if ( attached_cockpit_model_handle )
        {
          rf_player_update_attached_cockpit_private_materials(a1, attached_cockpit_model_handle);
          rf_model_render_options_construct(v3);
          if ( rf_entity_class_flag1000(v5) )
            rf_model_handle_render_all_adapter(attached_cockpit_model_handle, a1 + 4244, a1 + 4256, (int)v3);
          else
            rf_model_handle_render_all_adapter(attached_cockpit_model_handle, v8 + 2004, v8 + 72, (int)v3);
        }
        if ( *(_DWORD *)(v5 + 676) != -1 )
        {
          v7 = 0;
          v6 = (char *)&rf_weapon_records + 1360 * *(_DWORD *)(v5 + 676);
          if ( !rf_replicator_has_elapsed((int *)(v5 + 4972)) && *((_DWORD *)v6 + 15) != -1 )
          {
            v7 = 1;
            if ( !rf_entity_class_flags724_has_mask800(v5) )
            {
              rf_vector3_default_construct_noop(v1);
              rf_matrix3_construct(v2);
              rf_vmesh_compose_prop_world_transform(
                *(_DWORD *)(v5 + 128),
                *(_DWORD *)(*(_DWORD *)(v5 + 660) + 244),
                (float *)(v5 + 72),
                v5 + 60,
                (int)v2,
                v1);
              rf_glare_render_definition_beam_and_corona(*((_DWORD *)v6 + 15), v1, (int)v2, 1);
            }
          }
          if ( rf_entity_class_flags724_has_mask800(v5) )
            rf_player_render_fighter_chaingun_and_muzzle_flash(a1, v5, v7);
          rf_hud_reticle_render(a1);
        }
      }
    }
  }
}

