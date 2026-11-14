// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004E72C0 rf_fpgun_request_draw_action
// UNREALRED VERIFIED [fpgun-action-dispatch]: Requests draw from the frame path and arms its duration gate.
int __cdecl rf_fpgun_request_draw_action(_DWORD *a1)
{
  int result; // eax
  float v2; // [esp+0h] [ebp-10h]
  unsigned int selected_weapon_and_resolve_mesh; // [esp+4h] [ebp-Ch]
  int v4; // [esp+8h] [ebp-8h]
  float action_animation_duration; // [esp+Ch] [ebp-4h]

  result = (int)a1;
  if ( a1 == (_DWORD *)rf_local_fpgun_player )
  {
    result = rf_entity_resolve_handle(a1[5]);
    v4 = result;
    if ( result )
    {
      selected_weapon_and_resolve_mesh = rf_player_get_selected_weapon_and_resolve_mesh(a1);
      if ( rf_weapon_has_alt_zoom_flag(selected_weapon_and_resolve_mesh) )
      {
        if ( selected_weapon_and_resolve_mesh == unk_911CB4 )
          rf_renderer_bind_texture_for_level_warmup(dword_662FB8);
        else
          rf_renderer_bind_texture_for_level_warmup(dword_662FB4);
      }
      rf_fpgun_dispatch_semantic_action((int)a1, 6u);
      action_animation_duration = rf_fpgun_get_action_animation_duration((int)a1, 6u);
      rf_replicator_arm_milliseconds(a1 + 1055, (int)(action_animation_duration * 1000.0) + 200);
      result = rf_weapon_is_riot_stick(selected_weapon_and_resolve_mesh);
      if ( (unsigned __int8)result == 1 )
      {
        v2 = rf_fpgun_get_action_animation_duration((int)a1, 6u);
        if ( sub_436310(v4) > 0 )
          return rf_replicator_arm_milliseconds(a1 + 994, (int)(v2 * 1000.0));
        else
          return (int)rf_replicator_reset(a1 + 994);
      }
    }
  }
  return result;
}

