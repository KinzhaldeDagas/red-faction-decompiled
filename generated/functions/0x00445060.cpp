// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00445060 rf_game_frame_update_and_render_single_local_view
// [UnrealRed combat room owner 2026-11-12; verified original-byte ASM] Normal frame invokes444D30(AI/physics/effects) at445191 BEFORE442950(clear352+auxiliaryview passes)44519E and final playerRenderView4451AB. AI410170 reads retained previous render-group room352. Branch byte704E83==1 only runs444D30 and skips clear/render, retaining prior visibility data; source must not recompute fresh same-AI-tick camera visibility.
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity fire actions, shared definitions and burn/debug records, Foley input, local-player controls and
// auxiliary view/render state and native signed/x87/stack/callback ABI): Cdecl(raw LOWBYTE skip-update argument), void. MP BYTE704E81 EXACT1 AND authority BYTE704E82 EXACT0 AND
// DWORD704E90 ANY nonzero AND446190() full EAX EXACT11 force local skip argument to1. Independently BYTE704E83 EXACT1 calls444D30 world update ONLY, regardless skip argument, then
// common clear BYTE6E6ABC=0; this branch does not dereference local player, poll UI, update listener, clear rooms or render. Other byte values follow normal path: read RDTSC (save
// LOW32 only), copy position from local-player196 wrapper.entity COMMON+60 and retained orientation+2016 into local pose, initialize separate velocity vector(0,0,0). These snapshots
// precede UI polling and world/player updates. If46F8A0 modal AL==0 call4477F0(callback441490,raw extra DWORD0), ignoring result. ANY nonzero skip argument suppresses listener,4E0DF0
// and444D30 but still allows these initial pose reads/UI polling and later rendering. With skipBYTE0: pause-query448C10 ANY nonzero skips ONLY listener update; otherwise monitor
// predicate4E0700(localPlayer) AL EXACT1 replaces local pose with primary entity global681E38 retained position2004/orientation2016, without primary NULL guard.
// Then568D20(position,zeroVelocity,matrix), ignored result. Regardless pause query, call4E0DF0(re-read localPlayer), then444D30 (which has its own wider gates). Normal path then
// reads RDTSC LOW32 to another local, calls442950 auxiliary-view/room352 union, calls442BC0(re-read localPlayer,0) main view, reads RDTSC LOW32 into final unused local. All normal
// paths end clearing BYTE6E6ABC=0; no computed timing delta/global timing write, pointer guard, result test or rollback. Position/matrix can be stale relative to UI callbacks or
// updated local-player state unless monitor override replaces them. Preserve existing room352 ordering: world/AI update precedes this frame's clear/auxiliary/main render group;
// EXACT1 special branch retains previous room352 state.
void __cdecl rf_game_frame_update_and_render_single_local_view(char a1)
{
  float copy_result[3]; // [esp+Ch] [ebp-54h] BYREF
  float destination[3]; // [esp+18h] [ebp-48h] BYREF
  float v3[6]; // [esp+24h] [ebp-3Ch] BYREF
  float v4[9]; // [esp+3Ch] [ebp-24h] BYREF

  if ( rf_multiplayer_runtime_mode == 1
    && !rf_multiplayer_server_authority
    && unk_704E90
    && rf_ui_panel_stack_current_id() == 11 )
  {
    a1 = 1;
  }
  if ( byte_704E83 == 1 )
  {
    sub_444D30();
  }
  else
  {
    LODWORD(v3[3]) = rf_clock_read_timestamp_counter();
    rf_entity_view_copy_referenced_position(destination, *(_DWORD *)(rf_local_fpgun_player + 196));
    rf_vector3_set_components_return_destination(v3, 0.0, 0.0, 0.0);
    rf_entity_view_copy_referenced_matrix_2016((int)v4, *(_DWORD **)(rf_local_fpgun_player + 196));
    if ( !rf_ui_modal_active_byte_get() )
      rf_ui_poll_and_dispatch_event((int (__cdecl *)(int))rf_gameplay_pause_then_route_chat_key);
    if ( !a1 )
    {
      if ( !rf_game_pause_gate_query() )
      {
        if ( rf_player_view_target_is_monitor(rf_local_fpgun_player) )
        {
          rf_vector_copy(destination, copy_result, (const float *)(dword_681E38 + 2004));
          rf_matrix3_copy(v4, (const float *)(dword_681E38 + 2016));
        }
        rf_sound_update_listener_and_instances(destination, (int)v3, v4);
      }
      sub_4E0DF0(rf_local_fpgun_player);
      sub_444D30();
    }
    LODWORD(v3[5]) = rf_clock_read_timestamp_counter();
    rf_render_local_player_auxiliary_views_and_visibility_union();
    rf_player_render_view(rf_local_fpgun_player, 0);
    LODWORD(v3[4]) = rf_clock_read_timestamp_counter();
  }
  unk_6E6ABC = 0;
}

