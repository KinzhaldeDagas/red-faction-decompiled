// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0044A9C0 rf_hud_update_messages_persona_audio_and_directional_damage
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, panel-stack transition and modal-frame flow, sound tables, message/binding expansion and native partial-state
// ownership and native signed/x87/stack/callback ABI): One cdecl raw argument forwarded only to final directional-damage update. Strict unconditional order:44B290 message-queue
// deadline update,44D0C0 persona audio update,44DFD0(argument) directional damage update. No parent NULL/runtime/pause/visibility gate, no result short-circuit, no render/draw call
// or aggregation. Full EAX from final delegate is forwarded incidentally; not normalized success. Earlier queue/audio mutations survive later failures.
unsigned int __cdecl rf_hud_update_messages_persona_audio_and_directional_damage(int a1)
{
  rf_hud_message_queue_expire_one_and_activate_head();
  rf_hud_persona_update_audio();
  return rf_hud_directional_damage_update(a1);
}

