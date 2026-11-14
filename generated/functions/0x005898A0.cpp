// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005898A0 rf_character_cache_reset_all_headers
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, character-cache callers, resource readers and constructor/destructor paths): Calls record-header reset588070 for all64 static slots at18D0A30,stride6744. No resource release before resetting; this is header initialization, not destructor traversal. EAX incidental loop count.
int rf_character_cache_reset_all_headers()
{
  int result; // eax
  int i; // [esp+0h] [ebp-4h]

  for ( i = 0; i < 64; ++i )
  {
    rf_character_record_reset_header((int)&byte_18D0A30[6744 * i]);
    result = i + 1;
  }
  return result;
}

