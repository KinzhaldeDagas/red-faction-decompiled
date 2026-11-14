// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0045B4B0 rf_multiplayer_chat_active_byte_get
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, chat input/console call chains, native500ms throttle, exact key predicates, original key maps/level prefixes,
// RFString ownership and static registration boundaries): Noarg,return AL. RuntimeBYTE EXACT1 ->return raw activeBYTE6F2CC8,without normalization. Every other runtime value
// returnsAL0;does not clear stored active state. No game-mode,authority,pause or initialized-byte query. Callers441490 and gameplay routing may compare AL EXACT1,so arbitrary nonzero
// active byte is not universally admitted. Full EAX upper bits not a promised bool/int ABI.
char rf_multiplayer_chat_active_byte_get()
{
  if ( rf_multiplayer_runtime_mode == 1 )
    return unk_6F2CC8;
  else
    return 0;
}

