// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00592470 rf_binary_stream_version_at_least
// VERIFIED: Returns whether the active binary stream version is greater than or equal to its integer argument.
// UNREALRED VERIFIED [general-gap-20260830]: Returns whether the active binary stream version is greater than or equal to the requested minimum.
BOOL __thiscall rf_binary_stream_version_at_least(_DWORD *this, int a2)
{
  return unk_189CEB8[8208 * *(this + 68)] >= a2;
}

