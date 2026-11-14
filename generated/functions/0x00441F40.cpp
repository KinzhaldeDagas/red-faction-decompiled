// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00441F40 rf_input_action_any_bound_key_or_mouse_held
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity fire actions, shared definitions and burn/debug records, Foley input, local-player controls and
// auxiliary view/render state and native signed/x87/stack/callback ABI): Cdecl(input-state pointer,signed action index), canonical AL0/1 only; upper EAX incidental. Sole action bound
// is signed action<DWORD[input+3596]; action>=count returnsAL0, but there is NO action>=0 check. Accepted negative action uses native32-bit input+12+28*action address. For i=0 then1,
// read signed16 keycode at actionRecord+20+2*i. Nonnegative key calls console5701E0; only console AL0 calls58BC90(keycode), and ANYnonzero key AL immediately returns1. Independently
// after each failed/skipped key, read signed16 mousebutton at actionRecord+24; nonnegative calls58AC50(button), ANYnonzero AL immediately returns1. Consequently identical mousebutton
// is queried TWICE when first iteration fails; console visibility suppresses only keyboard, never mouse. Both iterations exhausted returnAL0. No key/button upper bound,
// action-mode/enable byte, chat/pause/death gate, NULL guard, edge/press-count consumption or own state writes; delegated held-query behavior remains native.
char __cdecl rf_input_action_any_bound_key_or_mouse_held(int a1, int a2)
{
  int v3; // [esp+4h] [ebp-8h]
  int i; // [esp+8h] [ebp-4h]

  if ( a2 >= *(_DWORD *)(a1 + 3596) )
    return 0;
  v3 = a1 + 28 * a2 + 12;
  for ( i = 0; i < 2; ++i )
  {
    if ( *(__int16 *)(v3 + 2 * i + 20) >= 0
      && !rf_console_get_visible_byte()
      && rf_input_get_scan_code_state_byte(*(__int16 *)(v3 + 2 * i + 20)) )
    {
      return 1;
    }
    if ( *(__int16 *)(a1 + 28 * a2 + 36) >= 0 && rf_mouse_get_button_held_byte(*(__int16 *)(a1 + 28 * a2 + 36)) )
      return 1;
  }
  return 0;
}

