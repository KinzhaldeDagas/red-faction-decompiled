// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0055EF80 rf_replicator_arm_milliseconds
// UNREALRED VERIFIED [combat-clock-20260930] Arms the stored deadline relative to game clock0x663E90, wrapping by1072800000 ms. Its paired expiry query0x55F040 reads the same clock. Unreal replicated fire/reload absolute deadlines therefore need a common clock for arming and testing; using a receiving clients unrelated world-start epoch is a host-adapter defect, not native weapon cadence.
// UNREALRED VERIFIED [mission-visibility-20261020] For nonnegative duration, equality at period-now preserves deadline1072800000 rather than reducing to0. UnHide uses duration0 at construction and500 on each admitted show/hide pass. Paired expiry comparison55F040 handles the exact-period boundary.
// UNREALRED VERIFIED [trigger-inside-time-20261021] InsideTime arms this source clock after truncating double(seconds)*1000+0.5 to signed milliseconds. Positive sub-half-ms input arms duration0 but504B30 still returns waiting on that first query. Exact period-now equality preserves the period deadline; wrapping occurs only beyond it.
// UNREALRED VERIFIED [combat-emitter-clock-domain-20261112]: The shared source clock663E90 can itself equal1072800000 for a frame because55EE80 wraps only when increment exceeds period-current. A known native Now validator must admit inclusive [0,1072800000]; modulo-normalizing that equality to0 changes55F040 behavior for deadlines0 andPeriod. Native emitter4CDAA0/4CD520 arms+340 by truncating double(binary32 random delay)*1000, while56CFB0 advances source clock by truncating double(binary32 effective frame delta)*1000 EACH frame, without fractional carry (56D1E6..56D1FE). An actor float-age deadline does not model those stores/truncations or cross-owner pooled reuse. This does not establish UE frame-delta/pause input parity; that remains an explicit host adapter.
int *__thiscall rf_replicator_arm_milliseconds(int *this, int a2)
{
  int *result; // eax

  if ( a2 < 0 )
  {
    result = (int *)(a2 + dword_663E90);
    *this = a2 + dword_663E90;
    if ( *this < 0 )
    {
      *this += 1072800000;
      return this;
    }
  }
  else
  {
    result = (int *)(1072800000 - dword_663E90);
    if ( a2 <= 1072800000 - dword_663E90 )
    {
      *this = a2 + dword_663E90;
    }
    else
    {
      *this = a2 - (1072800000 - dword_663E90);
      return this;
    }
  }
  return result;
}

