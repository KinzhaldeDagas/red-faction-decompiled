// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00417460 rf_clutter_class_destroy_members
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, monitor lifetime, debris lifecycle/contact audio, native render ABI and mixed spawn descriptor): Destroys glare pointer-array backing at +212, all cookie-capacity skin records via the destructor at +200, invokes the no-op member hook at +132, destroys emitter-ID array backing at +40, then RFStrings at +32,+24,+16,+8,+0. Does not free the containing 232-byte class, reset array headers, unregister the class or decrement the registry count.
void __thiscall rf_clutter_class_destroy_members(char *this)
{
  rf_pointer_array_destroy_backing_storage((void **)this + 53);
  rf_clutter_skin_array_destroy_members((char **)this + 50);
  rf_shared_noop_destructor_4580d0();
  rf_pointer_array_destroy_backing_storage((void **)this + 10);
  rf_string_destroy_buffer(this + 32);
  rf_string_destroy_buffer(this + 24);
  rf_string_destroy_buffer(this + 16);
  rf_string_destroy_buffer(this + 8);
  rf_string_destroy_buffer(this);
}

