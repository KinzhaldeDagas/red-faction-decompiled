// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00412640 rf_common_embedded_destroy_pointer_array
// UNREALRED VERIFIED [event-lifecycle-20261028]: Calls backing-storage destructor0x47A3F0 at this+252. No clearing of array metadata or freeing pointees. Common-object destructor supplies this=C+136, so this array is at C+388.
void __thiscall rf_common_embedded_destroy_pointer_array(void **this)
{
  rf_pointer_array_destroy_backing_storage(this + 63);
}

