// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00504140 rf_trigger_registry_atexit_cleanup
// UNREALRED VERIFIED [event-lifecycle-20261028]: Operator-deletes four auxiliary12-byte objects pointed to at0x90B4F4[0..3] and clears pointers, then sets trigger count0x90B504=0. Does not traverse or delete linked trigger records.
void __cdecl rf_trigger_registry_atexit_cleanup()
{
  int i; // [esp+4h] [ebp-4h]

  for ( i = 0; i < 4; ++i )
  {
    operator delete((void *)dword_90B4F4[i]);
    dword_90B4F4[i] = 0;
  }
  unk_90B504 = 0;
}

