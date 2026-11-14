// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004C14A0 rf_bolt_curve_scalar_deleting_destructor
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, four-slot emitter lifecycle, allocation and constructor layouts, native ordered lifetime gates, attachment transforms and paused rendering): 
// Thiscall curve,flags DWORD RET4. Calls shared NOOP destructor4580D0(receiver); if flags&1 invokes operator delete(receiver). Returns original receiver bits in EAX even after free.
// Does not free four embedded curve control points/pointer table individually, clear pointer or validate null. Used for each slot curve by4C0760.
void *__thiscall rf_bolt_curve_scalar_deleting_destructor(void *this, char a2)
{
  rf_shared_noop_destructor_4580d0();
  if ( (a2 & 1) != 0 )
    operator delete(this);
  return this;
}

