// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00504270 rf_trigger_registry_initialize
// UNREALRED VERIFIED [event-lifecycle-20261028]: Clears trigger count0x90B504 and global0x90B4F0. Sets both runtime list links to sentinel0x90B510 (named runtime head and global0x90B7A0). Allocates four12-byte objects, calls no-op default constructor0x4F2700 for each (allocated bytes remain uninitialized), stores pointers at0x90B4F4; allocation failures store null. Registers0x504140 with atexit and returns registration result.
int rf_trigger_registry_initialize()
{
  void *v1; // [esp+4h] [ebp-1Ch]
  void *v2; // [esp+8h] [ebp-18h]
  int i; // [esp+10h] [ebp-10h]

  unk_90B504 = 0;
  unk_90B4F0 = 0;
  rf_trigger_runtime_list_head = &unk_90B510;
  unk_90B7A0 = &unk_90B510;
  for ( i = 0; i < 4; ++i )
  {
    v2 = operator new(0xCu);
    if ( v2 )
      v1 = rf_vector3_default_construct_noop(v2);
    else
      v1 = nullptr;
    dword_90B4F4[i] = (int)v1;
  }
  return atexit(rf_trigger_registry_atexit_cleanup);
}

