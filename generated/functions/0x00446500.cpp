// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00446500 rf_ui_panel_stack_contains11
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, panel-stack transition and modal-frame flow, sound tables, message/binding expansion and native partial-state
// ownership and native signed/x87/stack/callback ABI): No arguments, canonicalAL0/1. Signed index starts0, while index<=LIVE signed depth6615F8, returnAL1 at first stack6E6DE8[index]
// EXACT11; otherwise increment and re-read depth until greater, thenAL0. Negative depth skips all slot reads. No fixed capacity/depth overflow/ID/NULL validation, current-only
// restriction or state change. Other panel IDs including18 do not match; upperEAX incidental.
char rf_ui_panel_stack_contains11()
{
  int i; // [esp+0h] [ebp-4h]

  for ( i = 0; i <= dword_6615F8; ++i )
  {
    if ( unk_6E6DE8[i] == 11 )
      return 1;
  }
  return 0;
}

