// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0047A420 rf_level_runtime_state_destroy
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, liquid transition lifecycle, native x87 unordered comparisons, stable pointer erase, static runtime ownership and level-browser flow): 
// Thiscall global runtime state at6FC310 (static exit wrapper62EF40). Destroys managed particle-effect list240 first: delegate drains and deletes child nodes, releases their
// emitters/voices and sentinel own emitter/voice, without freeing sentinel allocation. Then destroys vector backing storage at228,216,204,192,180,168, followed by
// RFStrings156,28,20,12,4. Unwind cleanup covers remaining members. No receiver free, per-element ownership traversal for six vectors, world-solid unload or explicit scalar reset
// here.
void __thiscall rf_level_runtime_state_destroy(int this)
{
  rf_managed_particle_effect_list_destroy((int *)(this + 240));
  rf_pointer_array_destroy_backing_storage((void **)(this + 228));
  rf_pointer_array_destroy_backing_storage((void **)(this + 216));
  rf_pointer_array_destroy_backing_storage((void **)(this + 204));
  rf_pointer_array_destroy_backing_storage((void **)(this + 192));
  rf_pointer_array_destroy_backing_storage((void **)(this + 180));
  rf_pointer_array_destroy_backing_storage((void **)(this + 168));
  rf_string_destroy_buffer((void *)(this + 156));
  rf_string_destroy_buffer((void *)(this + 28));
  rf_string_destroy_buffer((void *)(this + 20));
  rf_string_destroy_buffer((void *)(this + 12));
  rf_string_destroy_buffer((void *)(this + 4));
}

