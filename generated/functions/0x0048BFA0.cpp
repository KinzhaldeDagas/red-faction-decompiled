// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0048BFA0 rf_mover_destroy_member_storage
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, mover UID and handle queries, detachment and member ownership, original console packet serialization, native team-byte sentinel and authority comparisons): 
// Thiscall mover member destructor. Destroys ONLY backing storage of arrays716,704,692,680,668 in reverse construction order, then common embedded members; unwind handles remaining
// members. No receiver free, per-key raw-delete, list unlink, voice stop or child detachment here. Distinct from487DC0 ownership cleanup that frees key pointees and unlinks live
// mover. Static exit wrapper62F0A0 passes sentinel704610; no runtime list traversal in destructor.
void __thiscall rf_mover_destroy_member_storage(void **this)
{
  rf_pointer_array_destroy_backing_storage(this + 179);
  rf_pointer_array_destroy_backing_storage(this + 176);
  rf_pointer_array_destroy_backing_storage(this + 173);
  rf_pointer_array_destroy_backing_storage(this + 170);
  rf_pointer_array_destroy_backing_storage(this + 167);
  rf_common_object_destroy_embedded_members((int)this);
}

