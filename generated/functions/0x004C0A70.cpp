// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004C0A70 rf_bolt_emitter_destroy_members
// UNREALRED VERIFIED [level-lifecycle-20261028]: First releases four slot resources through0x4C0760. Then exception-aware vector destructor visits four68-byte slot subobjects starting this+112 through0x4C1550. Does not free emitter allocation itself.
void __thiscall rf_bolt_emitter_destroy_members(int this)
{
  rf_bolt_emitter_release_slot_resources((void **)this);
  `eh vector destructor iterator'(
    (char *)(this + 112),
    0x44u,
    4,
    (void (__thiscall *)(void *))rf_bolt_emitter_slot_destroy_array);
}

