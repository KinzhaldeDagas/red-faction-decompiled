// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004E6FB0 rf_fpgun_request_fire_fail_action
// UNREALRED VERIFIED [fpgun-action-dispatch]: Dispatches fire_fail and arms the decoded idle timestamp gate.
int __cdecl rf_fpgun_request_fire_fail_action(int a1)
{
  int result; // eax

  result = a1;
  if ( a1 == rf_local_fpgun_player )
  {
    rf_fpgun_dispatch_semantic_action(a1, 2u);
    return sub_4EBD20(a1);
  }
  return result;
}

