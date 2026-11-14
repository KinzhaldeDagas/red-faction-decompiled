// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00417640 rf_monitor_destroy_all_records
// UNREALRED VERIFIED [level-lifecycle-20261028]: Traverses monitor doubly-linked list from sentinel0x6807E4, saves next pointer before calling rf_monitor_unlink_and_destroy_record on each. Stops at sentinel. No array iteration or extra record allocations.
void __cdecl rf_monitor_destroy_all_records()
{
  void **v0; // [esp+0h] [ebp-8h]
  void **i; // [esp+4h] [ebp-4h]

  for ( i = (void **)dword_6807E4; i != &dword_6807E4; i = v0 )
  {
    v0 = (void **)*i;
    rf_monitor_unlink_and_destroy_record((int)i);
  }
}

