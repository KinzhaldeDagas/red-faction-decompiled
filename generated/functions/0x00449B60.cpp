// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00449B60 rf_geomod_history_atexit_clear_adapter
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, panel-stack transition and modal-frame flow, sound tables, message/binding expansion and native partial-state
// ownership and native signed/x87/stack/callback ABI): No arguments, void wrapper. Calls449B70 history clear exactly once, no own state/gate/loop. Helper saves each next link before
// unlink/delete while walking history ring to sentinel and adjusts count per node. Wrapper does not clear Geomod execution queue, free payload resources itself or reinterpret
// incidental delegate EAX as success.
void __cdecl rf_geomod_history_atexit_clear_adapter()
{
  rf_geomod_network_history_clear();
}

