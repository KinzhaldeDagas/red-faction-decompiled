// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00589A40 rf_character_cache_allocate_and_load
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, character-cache callers, resource readers and constructor/destructor paths): Finds first of64 slots with loaded bit1 clear, else fatal character.cpp:444 MAX_BASE_CHARACTERS message. Resets its header, copies requested name unbounded to record start and calls589340. Failed model load returnsNULL without clearing copied name or rolling back other partial allocations. Success ORs loaded bit1 and returns record. No name-length or duplicate-name check inside this allocator.
char *__cdecl rf_character_cache_allocate_and_load(const char *a1)
{
  char v2; // [esp+3h] [ebp-15h]
  char *v3; // [esp+8h] [ebp-10h]
  const char *v4; // [esp+Ch] [ebp-Ch]
  char *v5; // [esp+10h] [ebp-8h]
  int i; // [esp+14h] [ebp-4h]

  for ( i = 0; i < 64 && (dword_18D0A74[1686 * i] & 1) != 0; ++i )
    ;
  if ( i == 64 )
  {
    sprintf(
      &unk_18CD828,
      "Error loading character %s.  No more base character room.\nPlease up the constance MAX_BASE_CHARACTERS.",
      a1);
    rf_fatal_error_show_message_and_exit("D:\\projects\\rf_pc\\vsdk\\ca\\character.cpp", 444, &unk_18CD828);
  }
  v5 = &byte_18D0A30[6744 * i];
  rf_character_record_reset_header((int)v5);
  v4 = a1;
  v3 = v5;
  do
  {
    v2 = *v4;
    *v3++ = *v4++;
  }
  while ( v2 );
  if ( !rf_character_load_vcm_and_build_aux_bindings((int)v5) )
    return nullptr;
  *((_DWORD *)v5 + 17) |= 1u;
  return &byte_18D0A30[6744 * i];
}

