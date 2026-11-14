// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00483AE0 rf_rfl_moving_group_destroy
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, RFL region-version layouts, cutscene stream ABI and count bounds, constructor/destructor ownership and debris descriptor bits): 
// Thiscall moving-group temporary destructor. Destroys four RFStrings starting56,stride8, then backing arrays in REVERSE constructor order: vector28,16,4. Shared unwind entries also
// destroy backing storage. Does not free receiver allocation, destroy objects whose pointer ids may be stored in vectors, clear registry membership or reset scalar fields.
// Pointer-array destructor frees storage only; this differs from a per-element owning destructor.
void __thiscall rf_rfl_moving_group_destroy(int this)
{
  `eh vector destructor iterator'((char *)(this + 56), 8u, 4, rf_string_destroy_buffer);
  rf_pointer_array_destroy_backing_storage((void **)(this + 28));
  rf_pointer_array_destroy_backing_storage((void **)(this + 16));
  rf_pointer_array_destroy_backing_storage((void **)(this + 4));
}

