// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0041E310 rf_corpse_schedule_eviction
// UNREALRED VERIFIED [mission-mover-occupancy-20261020] Endpoint mover occupancy0x488E20 calls this for each contained corpse only after no entity holds the volume. Eligibility rejects corpse+0x29C bits0x2/0x40, common+0x7C bit0x4000 and already-retiring bit1. Accepted request sets retiring bit1 and one-second duration; repeated occupancy does not restart an existing fade. Occupancy itself does not depend on acceptance.
char __cdecl rf_corpse_schedule_eviction(int a1)
{
  char result; // al

  result = rf_corpse_is_eviction_protected(a1);
  if ( !result )
  {
    result = rf_corpse_is_retiring(a1);
    if ( !result )
    {
      *(_DWORD *)(a1 + 668) |= 1u;
      *(float *)(a1 + 664) = 1.0;
      return a1;
    }
  }
  return result;
}

