// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0045AD20 rf_multiplayer_chat_cancel_and_clear
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, chat input/console call chains, native500ms throttle, exact key predicates, original key maps/level prefixes,
// RFString ownership and static registration boundaries): Noarg. Assign empty original PE636070 to RFString6F2CDC,then clear initBYTE6F2CC9 and activeBYTE6F2CC8 in that order. Return
// assignment/destination pointer residue. Does not reset stored mode6F2CC4, shared throttle6F2CCC,all-input state,or play sound. Cancel and submit paths both use it; next prompt draw
// may independently initialize string when init byte zero.
_DWORD *rf_multiplayer_chat_cancel_and_clear()
{
  _DWORD *result; // eax

  result = rf_string_assign_from_cstr(unk_6F2CDC, (char *)&byte_636070);
  unk_6F2CC9 = 0;
  unk_6F2CC8 = 0;
  return result;
}

