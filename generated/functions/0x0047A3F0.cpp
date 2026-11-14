// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0047A3F0 rf_pointer_array_destroy_backing_storage
// UNREALRED VERIFIED [event-lifecycle-20261028]: If backing pointer at this+8 is nonnull, operator delete it. Leaves pointer/count/capacity words unchanged; unlike release helper0x517F40 this is destructor-style cleanup, not a reusable container reset. Does not free pointed elements.
void __thiscall rf_pointer_array_destroy_backing_storage(void **this)
{
  if ( *(this + 2) )
    operator delete(*(this + 2));
}

