// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00453A80 rf_endgame_event_or_elapsed_mouse_request_panel13
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, sequence panel and input/binding natives, credits/endgame parsing and Extras-menu X-motion/lifecycle, native
// callback and text-draw argument roles and native signed/x87/stack/callback ABI): Cdecl full32-bit event callback; later callback return ignored by4477F0. Seed local
// requestBYTE=(event==EXACT1). ALWAYS query55F2B0(deadline6F1DA0), even for event1. Only EXACTAL1 elapsed queries held mouse button0; ANYnonzero AL sets request1, otherwise query
// held button1 and ANYnonzero sets request1. Other nonzero elapsed bytes do not admit mouse queries. Event1 bypasses deadline as request admission but does not bypass querying it;
// all other event values, including dispatcher terminating0, can request via held buttons after expiry. Held queries are short-circuit and not press-count consumption.  If local
// request==EXACT1, call446100(panel13,force0) once; no success check, deadline reset or callback loop. Otherwise no panel mutation. Deadline uses wrapped UNPAUSED clock663E94,1000ms
// armed by453450; no own phase/scroll/pause/death gate. Return registers are nonuniform last timer/mouse AL and upper residue, or full request-helper EAX; not normalized
// acknowledgement and not used to stop dispatch.
int __cdecl rf_endgame_event_or_elapsed_mouse_request_panel13(int event)
{
  int result; // eax
  bool v2; // [esp+7h] [ebp-1h]

  v2 = event == 1;
  LOBYTE(result) = rf_clock_deadline_has_elapsed_half_period((int *)&unk_6F1DA0);
  if ( (unsigned __int8)result == 1 )
  {
    LOBYTE(result) = rf_mouse_get_button_held_byte(0);
    if ( (_BYTE)result || (result = (unsigned __int8)rf_mouse_get_button_held_byte(1), (_BYTE)result) )
      v2 = 1;
  }
  if ( v2 )
    return rf_ui_request_panel_immediate(13, 0);
  return result;
}

