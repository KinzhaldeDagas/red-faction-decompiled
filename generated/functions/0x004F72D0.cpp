// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004F72D0 rf_blood_mark_snapshot_record_construct
// UNREALRED VERIFIED [level-state-file-cache-flow-20261028] Construct four raw short quaternion components at record+6 via0x5823A0, then no-op color constructor0x571990 at+14. No quantized position initialization or color clear. Constructor writes raw quaternion(0,0,0,1), not(0,0,0,16383).
char *__thiscall rf_blood_mark_snapshot_record_construct(char *this)
{
  rf_short_quaternion_construct_0001((_WORD *)this + 3);
  rf_rgba8_default_construct_noop(this + 14);
  return this;
}

