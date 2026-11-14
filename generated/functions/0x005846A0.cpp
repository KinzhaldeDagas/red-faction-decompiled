// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005846A0 rf_snapshot_pack_quaternion_s16_times16383
// UNREALRED VERIFIED [object-entity-snapshot-continuation-20261027] Destination inECX, source four floats on stack. Each component multiplied by double16383.0, truncated via floating-to-int helper and stored low16 bits. No quaternion normalization, range clamp, sign canonicalization or omitted-component reconstruction in this body.
int __thiscall rf_snapshot_pack_quaternion_s16_times16383(_WORD *this, float *a2)
{
  int result; // eax

  *this = (int)(*a2 * 16383.0);
  *(this + 1) = (int)(a2[1] * 16383.0);
  *(this + 2) = (int)(a2[2] * 16383.0);
  result = (int)(a2[3] * 16383.0);
  *(this + 3) = result;
  return result;
}

