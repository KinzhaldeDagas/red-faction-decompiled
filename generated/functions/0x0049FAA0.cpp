// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0049FAA0 rf_multiplayer_notification_text_rows_clear
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, join/browser/roster payload codecs, native admission predicates, item bitmaps, logging clock ABI and peer update arithmetic): 
// No arguments. For8 rows, assigns empty RFStrings to suffix rows at base+20*i and prefix rows at base+20*i. PE-verified NUL sources63A4BE/63A4BF. Does not reset per-row styles/other
// scalar metadata, notification hold timer or allocate player state. Normal EAX ends8 from loop increment, not a general success indicator.
int rf_multiplayer_notification_text_rows_clear()
{
  int result; // eax
  int i; // [esp+0h] [ebp-4h]

  for ( i = 0; i < 8; ++i )
  {
    rf_string_assign_from_cstr((_DWORD *)&rf_multiplayer_notification_suffix_rows + 5 * i, (char *)&byte_63A4BE);
    rf_string_assign_from_cstr(&rf_multiplayer_notification_prefix_rows[20 * i], (char *)&byte_63A4BF);
    result = i + 1;
  }
  return result;
}

