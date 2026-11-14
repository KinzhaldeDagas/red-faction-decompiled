// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005878D0 rf_character_instance_zero_action_weight
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, character bone hierarchy, adapter branches, action/trigger callers and PE-verified affine constants): Finds exact animation index via587210. Missing entry returns immediately with EAX=-1. Found entry writes record float+8=0.0 at instance+4828+12*i and DWORD+7424=0xFFFFFFFF (an index sentinel, NOT a floating NaN). Does not remove/compact action record, release clip or reset time. Successful EAX incidental receiver.
int __thiscall rf_character_instance_zero_action_weight(float *this, int a2)
{
  int result; // eax

  result = rf_character_instance_find_action_record(this, a2);
  if ( result >= 0 )
  {
    *(this + 3 * result + 1207) = 0.0;
    *(this + 1856) = NAN;
    return (int)this;
  }
  return result;
}

