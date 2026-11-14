// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00591820 rf_command_line_clear_arguments_preserve_option_registry
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, tokenizer ownership/quote rules, native hook contracts, observer registration, startup signaling and thread-exit/calling-convention paths): Cdecl cleanup/atexit. Walks initialized circular option list1BA1EE0, deletes each owned argument via592080 and clears matched byte+20, preserving registration/name/aux/requires fields. For each i<global token count1BA1EDC, deletes nonnull owned token pointer1BA1D48+8*i and sets pointerNULL, then count=0. Does not clear consumed byte flags, unlink/free option objects or bound count to50. Assumes list sentinel initialized; no prior-state reconstruction.
void __cdecl rf_command_line_clear_arguments_preserve_option_registry()
{
  void **i; // [esp+4h] [ebp-8h]
  int j; // [esp+8h] [ebp-4h]

  for ( i = (void **)dword_1BA1EE0; i != (void **)&dword_1BA1EE0; i = (void **)*i )
  {
    rf_command_line_option_delete_argument(i);
    *((_BYTE *)i + 20) = 0;
  }
  for ( j = 0; j < dword_1BA1EDC; ++j )
  {
    if ( dword_1BA1D48[2 * j] )
    {
      operator delete((void *)dword_1BA1D48[2 * j]);
      dword_1BA1D48[2 * j] = 0;
    }
  }
  dword_1BA1EDC = 0;
}

