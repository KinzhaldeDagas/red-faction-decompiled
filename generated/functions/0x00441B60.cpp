// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00441B60 rf_player_apply_input_stance_dispatch_and_fire_release
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity fire actions, shared definitions and burn/debug records, Foley input, local-player controls and
// auxiliary view/render state and native signed/x87/stack/callback ABI): Cdecl(required player pointer,control-output pointer), void/incidental EAX. First resolve player DWORD20 as
// full ENTITY handle433EE0 and CAPTURE pointer E; take input ADDRESS=player+228. No player NULL guard. Only if captured E nonnull AND DWORD[E+5168]==player perform initial
// vector/movement/stance phase; control pointer is otherwise not dereferenced in this body. There is no control NULL/finite guard on admitted phase. LengthSquared(control+12)
// ORDERED>0 copies FLOAT seconds clock6FC428 to E1972; then lengthSquared(control+0) ORDERED>0 OR controlFLOAT28 ORDERED>0 OR controlFLOAT32 ORDERED>0 copies current clock toE1968.
// These are short-circuit strictly-positive tests: NaN rejects each test, and a negative28/32 alone does not refresh1968.  Query477CA0(E COMMONposition60) first-containing OBB region
// R. If R nonnull: query movement-is-index1-or2 ANYnonzero; if true OR R!=E DWORD5100, then query descriptor-kind2 and, only AL0, call435750(E,R), ignoring its non-bool result. ANY
// present R skips all later no-region/stance handling, even if no installation or installation fails. If R NULL: descriptor-kind2 ANYnonzero calls4355A0(E) and then skips stance
// regardless return. Otherwise stance is admitted by short-circuit437EC0(E) ANYnonzero OR437E80(E) ANYnonzero OR437F00(E) ANYnonzero, then player BYTE3896 must0 and chat45B4B0 AL
// must0. Query441F40(input,4) raw held bindings: if ANYnonzero and player BYTE177==0 and4E08B0(player) ANYnonzero, call436100(E), then setplayer BYTE177=1,
// request4344D0(this=E,speed0), then438650(E,state9,FLOAT0.25), all returns ignored. Crouch shape/support/timestamp side effects precede player byte and speed/body-state requests. If
// raw held query0 and player BYTE177 ANYnonzero, call4361B0(E); only ANYnonzero AL then clearsplayer BYTE177 and calls4344D0(this=E,speed1). Failed clearance leaves this caller's
// byte/speed suffix untouched; helper's already-completed query effects remain. No own pause gate covers this whole initial phase.  Next query448C10 once. AL0 runs signed increasing
// i=0..60 inclusive: call451F70(input,i,&localEdgeByte), and ANYnonzero AL calls4E1060(player,i,zero-extended localEdgeByte). Action queries initialize edge byte only on their
// in-range paths; out-of-range false never dispatches. Calls occur even when initial entity was NULL/unassociated. Loop does not revalidate entity/association after each dispatch and
// does not requery pause; delegates can consume input or alter state. Nonzero pause skips ONLY this61-action loop.  After loop/skip, reuse original captured E (do NOT resolve
// player's handle again), require E stillnonnull and CURRENT DWORD[E+5168]==player once. Then call451F70(input,0,NULL) afresh, even if action0 was queried/dispatched in loop. If AL0,
// resolve CURRENT E DWORD512 parent HANDLE. For nonnull parent P, require4BCE50(P)==EXACTAL1 and422270(P fullhandle44,P primaryindex676)==EXACTAL1; then422A40(P handle44,P index676),
// rereading both fields for call and ignoring result. Next independently50FDB0(CURRENT E primary676,selectorLOWBYTE0)==EXACTAL1 AND DWORD[CURRENT *(E+5168)+16] mask0x20 CLEAR
// causes422A40(CURRENT E fullhandle44,CURRENT E primary676). No own firing-byte check precedes this owner stop. Then, regardless first query outcome, call451F70(input,1,NULL) afresh.
// AL0 plus50FDB0(CURRENT primary676,selector1)==EXACTAL1 and current associated-player flags16 mask0x20 SET causes same owner stop. These cleanup queries/calls run while paused too,
// and repeated press queries are potentially consuming; do not reuse loop results or snapshot selector/flags/weapon fields. Association is not rechecked between cleanup delegates,
// and later nested-player dereferences have no NULL guard. No dead/authority/additional gameplay admission, normalized return or rollback.
void __cdecl rf_player_apply_input_stance_dispatch_and_fire_release(int a1, float *a2)
{
  int v2; // [esp+4h] [ebp-18h]
  char v3; // [esp+Bh] [ebp-11h] BYREF
  int i; // [esp+Ch] [ebp-10h]
  _DWORD *containing_point; // [esp+10h] [ebp-Ch]
  int v6; // [esp+14h] [ebp-8h]
  int v7; // [esp+18h] [ebp-4h]

  v6 = rf_entity_resolve_handle(*(_DWORD *)(a1 + 20));
  v7 = a1 + 228;
  if ( v6 && *(_DWORD *)(v6 + 5168) == a1 )
  {
    if ( rf_vector_length_squared(a2 + 3) > 0.0 )
      *(float *)(v6 + 1972) = *(float *)&dword_6FC428;
    if ( rf_vector_length_squared(a2) > 0.0 || a2[7] > 0.0 || a2[8] > 0.0 )
      *(float *)(v6 + 1968) = *(float *)&dword_6FC428;
    containing_point = (_DWORD *)rf_world_obb_region_find_containing_point(v6 + 60);
    if ( containing_point )
    {
      if ( (rf_entity_movement_is_index1_or2(v6) || containing_point != *(_DWORD **)(v6 + 5100))
        && !rf_entity_movement_descriptor_kind_is2(v6) )
      {
        rf_entity_install_custom_movement2(v6, containing_point);
      }
    }
    else if ( rf_entity_movement_descriptor_kind_is2(v6) )
    {
      sub_4355A0(v6);
    }
    else if ( (rf_entity_descriptor_mode1_and_speedmode1(v6)
            || sub_437E80(v6)
            || rf_entity_uses_fall_or_airborne_vehicle_motion((_DWORD *)v6))
           && !*(_BYTE *)(a1 + 3896)
           && !rf_multiplayer_chat_active_byte_get() )
    {
      if ( rf_input_action_any_bound_key_or_mouse_held(v7, 4) )
      {
        if ( !*(_BYTE *)(a1 + 177) && rf_player_entity_mode1_or3_without_use_attachments(a1) )
        {
          rf_entity_apply_crouch_shape_centers(v6);
          *(_BYTE *)(a1 + 177) = 1;
          sub_4344D0(v6, 0);
          rf_entity_request_body_state(v6, 9u, 0.25);
        }
      }
      else if ( *(_BYTE *)(a1 + 177) && rf_entity_try_apply_standing_shape_centers(v6) )
      {
        *(_BYTE *)(a1 + 177) = 0;
        sub_4344D0(v6, 1);
      }
    }
  }
  if ( !rf_game_pause_gate_query() )
  {
    for ( i = 0; i < 61; ++i )
    {
      if ( rf_input_binding_poll_pressed_or_held(v7, i, &v3) )
        rf_player_dispatch_action_input(a1, i, v3);
    }
  }
  if ( v6 && *(_DWORD *)(v6 + 5168) == a1 )
  {
    if ( !rf_input_binding_poll_pressed_or_held(v7, 0, nullptr) )
    {
      v2 = rf_entity_resolve_handle(*(_DWORD *)(v6 + 512));
      if ( v2
        && rf_entity_matches_local_player_or_related_handle(v2) == 1
        && rf_entity_weapon_firing_byte_is_set(*(_DWORD *)(v2 + 44), *(_DWORD *)(v2 + 676)) )
      {
        rf_entity_stop_weapon_firing(*(_DWORD *)(v2 + 44), *(_DWORD *)(v2 + 676));
      }
      if ( rf_weapon_selected_mode_is_continuous_exact_selector(*(_DWORD *)(v6 + 676), 0)
        && (*(_DWORD *)(*(_DWORD *)(v6 + 5168) + 16) & 0x20) == 0 )
      {
        rf_entity_stop_weapon_firing(*(_DWORD *)(v6 + 44), *(_DWORD *)(v6 + 676));
      }
    }
    if ( !rf_input_binding_poll_pressed_or_held(v7, 1, nullptr)
      && rf_weapon_selected_mode_is_continuous_exact_selector(*(_DWORD *)(v6 + 676), 1)
      && (*(_DWORD *)(*(_DWORD *)(v6 + 5168) + 16) & 0x20) != 0 )
    {
      rf_entity_stop_weapon_firing(*(_DWORD *)(v6 + 44), *(_DWORD *)(v6 + 676));
    }
  }
}

