// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00412580 rf_common_object_destroy_embedded_members
// UNREALRED VERIFIED [event-lifecycle-20261028]: Destroys embedded member at common object C+136 through0x412640, then RF string at C+24 through0x55F6D0. Does not itself unregister common object or free C storage. Event base destructor supplies C=E+4.
void __thiscall rf_common_object_destroy_embedded_members(int this)
{
  rf_common_embedded_destroy_pointer_array(this + 136);
  rf_string_destroy_buffer((void *)(this + 24));
}

