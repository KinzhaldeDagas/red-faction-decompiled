// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005898E0 rf_character_cache_release_without_flag8
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, character-cache callers, resource readers and constructor/destructor paths): For all64 cache slots, releases a record only when flags+68 has loaded bit1 and lacks bit8. Uses full record release588100, which resets headers and all flags. Does not use pinned bit2 as its retention test; that is a separate sweep. EAX incidental.
int rf_character_cache_release_without_flag8()
{
  int result; // eax
  int i; // [esp+0h] [ebp-4h]

  for ( i = 0; i < 64; ++i )
  {
    if ( (dword_18D0A74[1686 * i] & 1) != 0 && (dword_18D0A74[1686 * i] & 8) == 0 )
      rf_character_record_release_resources((int)&byte_18D0A30[6744 * i]);
    result = i + 1;
  }
  return result;
}

