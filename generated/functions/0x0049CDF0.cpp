// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0049CDF0 rf_multiplayer_hud_atexit_clear_notification_strings
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, compiled packet registry, field permutations, x87 transfers, face-list mutation and HUD native stores): Cdecl
// noargs atexit callback registered49CD30. Assign verified empty NUL at63A3E4 to RFString77FE58. For index0..7 assign empty NUL63A3E5 to notification suffix RFString77FE78+20*index.
// Calls assignment, not destructor, and leaves each row's prefix RFString, style DWORD, shared timers, bitmap/font handles and rendered-row count alone. No complete HUD teardown or
// graphics release in this callback.
void __cdecl rf_multiplayer_hud_atexit_clear_notification_strings()
{
  int i; // [esp+0h] [ebp-4h]

  rf_string_assign_from_cstr(dword_77FE58, (char *)&byte_63A3E4);
  for ( i = 0; i < 8; ++i )
    rf_string_assign_from_cstr((_DWORD *)&rf_multiplayer_notification_suffix_rows + 5 * i, (char *)&byte_63A3E5);
}

