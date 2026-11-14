// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005CDFC0 rf_scene_instance_set_draining_low_bit
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, scene instance dispatch, allocation/deletion callers, pool strides and key constructors): Replaces runtime flags bit0 with input byte AND1,preserving other bits. Does NOT propagate change to emitter states: clearing scene draining bit does not clear their emission-disable flags set by stop/drain5CDF20. No time/count/reset operation. Returns receiver.
unsigned int *__thiscall rf_scene_instance_set_draining_low_bit(unsigned int *this, char a2)
{
  *this = a2 & 1 | *this & 0xFFFFFFFE;
  return this;
}

