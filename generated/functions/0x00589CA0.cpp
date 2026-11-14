// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00589CA0 rf_character_cache_mark_all_retained
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, character-cache callers, resource readers and constructor/destructor paths): For each loaded cache record sets retention bit0x10 in flags+68. Does not load resources or clear that bit from inactive entries. EAX is loop count, not number marked.
int rf_character_cache_mark_all_retained()
{
  int result; // eax
  int i; // [esp+0h] [ebp-4h]

  for ( i = 0; i < 64; ++i )
  {
    if ( (dword_18D0A74[1686 * i] & 1) != 0 )
      dword_18D0A74[1686 * i] |= 0x10u;
    result = i + 1;
  }
  return result;
}

