// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00589D00 rf_character_cache_release_unretained
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, character-cache callers, resource readers and constructor/destructor paths): Walks64 loaded records; bit0x10 entries are kept, others fully released/reset through588100. Local kept/freed counters are not returned; EAX is final loop count. Retention bit is not cleared on kept entries, and pin bit2/legacy bit8 are not separate guards in this pass.
int rf_character_cache_release_unretained()
{
  int result; // eax
  int v1; // [esp+0h] [ebp-Ch]
  int i; // [esp+4h] [ebp-8h]
  int v3; // [esp+8h] [ebp-4h]

  v3 = 0;
  v1 = 0;
  for ( i = 0; i < 64; ++i )
  {
    if ( (dword_18D0A74[1686 * i] & 1) != 0 )
    {
      if ( (dword_18D0A74[1686 * i] & 0x10) != 0 )
      {
        ++v1;
      }
      else
      {
        rf_character_record_release_resources((int)&byte_18D0A30[6744 * i]);
        ++v3;
      }
    }
    result = i + 1;
  }
  return result;
}

