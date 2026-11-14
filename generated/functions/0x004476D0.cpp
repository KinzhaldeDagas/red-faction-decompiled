// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004476D0 rf_console_command_request_panel17
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, panel-stack transition and modal-frame flow, sound tables, message/binding expansion and native partial-state
// ownership and native signed/x87/stack/callback ABI): No arguments. If console DWORD1809818 is nonzero, calls446100(panel17,force0), forwarding its incidental EAX; otherwise
// performs no calls or writes and leaves incoming EAX unchanged. No argument parsing, help handling or explicit success result.
int rf_console_command_request_panel17()
{
  int result; // eax

  if ( dword_1809818 )
    return rf_ui_request_panel_immediate(17, 0);
  return result;
}

