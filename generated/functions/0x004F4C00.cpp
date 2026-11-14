// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004F4C00 rf_savegame_callback_call_46F8B0
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, UI panel switches,startup/frame/shutdown state,shared position codec boundaries and native return/argument ABI,original ECX/stack flow and PE bytes): No-argument void wrapper: calls46F8B0 then returns. Referenced as callback at savegame writer4F3C22. No own file read/write, state restoration, UI request, argument forwarding or error/status handling; semantic purpose of delegate beyond this call is not assigned here.
void rf_savegame_callback_call_46F8B0()
{
  rf_ui_modal_cancel();
}

