// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004AE1F0 rf_console_request_split_match_start
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, packet14/27 registry bindings, rate-width/clamp policy, native string ABI and pregame17/18 wire layout): Noarg
// game console callback, incorrectly matched SDK __concrt_static_cleanup/FUNC_LIB. If argument-present DWORD1809818 nonzero call4AE4F0, else no action. Does not parse argument text,
// check runtime/server mode, perform cleanup or schedule a CRT destructor. Delegate sets split pending byte7B25D1 and requests panel5 unforced. Native19-byte body entirely
// application logic; false library classification removed. EAX delegate/incidental on noarg.
int rf_console_request_split_match_start()
{
  int result; // eax

  if ( dword_1809818 )
    return rf_splitscreen_set_pending_and_request_panel5();
  return result;
}

