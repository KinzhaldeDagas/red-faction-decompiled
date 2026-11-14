// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0040D380 sub_40D380
// UNREALRED VERIFIED [combat-reaction-20261111]: Returns1 only for a nonnull owner whose class+50 MaxVel is exactly0.0; ordered floating equality, not mass, humanoid, or current speed. Nonzero-MaxVel bodies do not reach40B6D0 attached-child recursion when both selected slots are-1.
bool __cdecl sub_40D380(int a1)
{
  return a1 && *(float *)(*(_DWORD *)(a1 + 660) + 80) == 0.0;
}

