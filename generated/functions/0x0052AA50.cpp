// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0052AA50 _atan2f
// UNREALRED VERIFIED [reflection-uv-20260903]: Corrected CRT wrapper identity: forwards two floats through 0x0052AA70 to the atan2 intrinsic dispatch descriptor at 0x00665D60. The former _hypotf label was inconsistent with both the dispatcher descriptor and every angular caller.
float __cdecl atan2f(float X, float Y)
{
  return sub_52AA70(X);
}

