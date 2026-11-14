// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00442210 rf_gated_singleplayer_grant_all_weapons
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity fire actions, shared definitions and burn/debug records, Foley input, local-player controls and
// auxiliary view/render state and native signed/x87/stack/callback ABI): No arguments, void. Require DWORD1809818 ANY nonzero and multiplayer BYTE704E81 EXACT0. XOR ECX,ECX followed
// by JZ makes the literal "You feel better armed" branch unreachable: selected message is always the pointer loaded from DWORD88E384. Calls HUD message queue44B4B0(message,0,0,NULL),
// then50FC20(0), ignoring both results. Queue helper ignores second argument; duration0 selects4000ms, NULL color selects current message color, and NULL/empty message or
// exactlyfull8-entry queue can reject without suppressing the subsequent grant. Grant helper selects current split entity when split is active, otherwise primary entity, through its
// own rules; this wrapper has no split/local-player/entity guard, permission result, ownership loop or rollback. No message/grant call on either rejected global gate.
void rf_gated_singleplayer_grant_all_weapons()
{
  if ( dword_1809818 )
  {
    if ( !rf_multiplayer_runtime_mode )
    {
      rf_hud_message_enqueue_expand_tokens_and_rearm_head(unk_88E384, 0, 0, nullptr);
      rf_entity_grant_all_player_weapons_and_refill_ammo(0);
    }
  }
}

