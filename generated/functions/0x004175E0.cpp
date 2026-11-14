// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004175E0 rf_clutter_runtime_destroy_members
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, monitor lifetime, debris lifecycle/contact audio, native render ABI and mixed spawn descriptor): Destroys pointer-array backing at runtime+704, then common embedded members via 0x412580 (pointer-array member +136 and RFString +24). Does not perform the separate runtime cleanup callback 0x415A50: no voice stops, secondary model release, monitor/list unlink, bitset release or count decrement here; no containing allocation free.
void __thiscall rf_clutter_runtime_destroy_members(void **this)
{
  rf_pointer_array_destroy_backing_storage(this + 176);
  rf_common_object_destroy_embedded_members((int)this);
}

