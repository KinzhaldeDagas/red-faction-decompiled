// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0055F3B0 rf_clock_deadline_elapsed_signed_half_period
// UNREALRED VERIFIED [list-selection-20261029]: Thiscall deadline pointer. Returns NEGATION of0x55F320 remaining result. Thus clock after deadline yields positive elapsed within half-period,while unarmed negative deadline yields-1072800000. Does not advance/rearm timer or independently test ready. Text-list type-ahead resets after returned value>1500.
int __thiscall rf_clock_deadline_elapsed_signed_half_period(int *this)
{
  return -rf_clock_deadline_remaining_signed_half_period(this);
}

