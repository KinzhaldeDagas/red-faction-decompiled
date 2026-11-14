// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004C1550 rf_bolt_emitter_slot_destroy_array
// UNREALRED VERIFIED [level-lifecycle-20261028]: Invokes pointer-array backing destructor0x47A3F0 at slot+8. Does not free pointed elements, clear metadata or free slot storage. Full emitter member cleanup first releases elements/resources through0x4C0760.
void __thiscall rf_bolt_emitter_slot_destroy_array(void **this)
{
  rf_pointer_array_destroy_backing_storage(this + 2);
}

