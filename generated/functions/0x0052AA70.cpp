// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0052AA70 sub_52AA70
// UNREALRED VERIFIED [reflection-uv-20260903]: Loads both float arguments onto the x87 stack, invokes the atan2 intrinsic dispatcher at 0x0060ACBA, and returns its floating result.
double __cdecl sub_52AA70(float a1)
{
  void *v1; // ecx

  sub_60ACBA(v1);
  return a1;
}

