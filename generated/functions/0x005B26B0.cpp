// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005B26B0 rf_scene_model_state152_destroy_arrays
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, scene instance dispatch, allocation/deletion callers, pool strides and key constructors): For152-byte model state,operator deletes nonNULL owned pointers+128 and+132. Does not NULL pointers,delete containing state or release shared definition/geometry. No allocation/ownership/count validation;repeat calls can double free.
void __thiscall rf_scene_model_state152_destroy_arrays(void **this)
{
  if ( *(this + 32) )
    operator delete(*(this + 32));
  if ( *(this + 33) )
    operator delete(*(this + 33));
}

