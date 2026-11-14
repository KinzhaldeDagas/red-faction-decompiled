// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004EBD20 sub_4EBD20
// UNREALRED VERIFIED [fpgun-action-dispatch]: Writes a fpgun timestamp gate with raw values 20000 and 40000. Units and stronger gameplay semantics remain unresolved.
int __cdecl sub_4EBD20(int a1)
{
  return rf_timestamp_arm_random_inclusive_milliseconds((int *)(a1 + 60), 20000, 40000);
}

