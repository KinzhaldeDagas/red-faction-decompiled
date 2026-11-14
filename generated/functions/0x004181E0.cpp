// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004181E0 rf_monitor_record_destroy_array_member
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, monitor lifetime, debris lifecycle/contact audio, native render ABI and mixed spawn descriptor): Only destroys pointer-array backing at receiver+24 via 0x47A3F0. Leaves header words stale. No pointee/bitmap destruction, list unlink, entity deletion or containing allocation free.
void __thiscall rf_monitor_record_destroy_array_member(void **this)
{
  rf_pointer_array_destroy_backing_storage(this + 6);
}

