// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00412980 rf_object_setup152_destroy_array_backing
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, debris/solid ownership, glare definitions and runtime factories, native render admission and x87 unordered gates): Thiscall setup receiver. Only calls pointer-array backing destructor on header+136; if base+144 nonnull, operator-delete backing allocation. Does not free pointed elements or outer setup, reset count/capacity/base, destroy model/solid, or interpret the other setup bytes. No defined application return value.
void __thiscall rf_object_setup152_destroy_array_backing(void **this)
{
  rf_pointer_array_destroy_backing_storage(this + 34);
}

