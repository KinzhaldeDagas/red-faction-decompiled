// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0045AF60 rf_multiplayer_chat_clear_input_buffer_only
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, chat input/console call chains, native500ms throttle, exact key predicates, original key maps/level prefixes,
// RFString ownership and static registration boundaries): Noarg. Assign empty original PE636071 to RFString6F2CDC and return delegate/destination pointer. Does NOT alter
// initBYTE6F2CC9,activeBYTE6F2CC8,modeDWORD6F2CC4 or throttle. Prompt45AE50 invokes it when init byte zero and sets init1 only after return; distinct from cancel45AD20 which clears
// both flags as well.
_DWORD *rf_multiplayer_chat_clear_input_buffer_only()
{
  return rf_string_assign_from_cstr(unk_6F2CDC, (char *)&byte_636071);
}

