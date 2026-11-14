// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00503D20 rf_mission_event_destroy_base_members
// UNREALRED VERIFIED [event-lifecycle-20261028]: Destroys pointer-array backing at E+668 via0x47A3F0, then common-object members at E+4 via0x412580. Does not unregister E or operator-delete E in this body. Distinguish member destruction from registry removal and scalar deleting wrapper.
void __thiscall rf_mission_event_destroy_base_members(void **this)
{
  rf_pointer_array_destroy_backing_storage(this + 167);
  rf_common_object_destroy_embedded_members((int)(this + 1));
}

