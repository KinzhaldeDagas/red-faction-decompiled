// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0051E980 rf_uv_scroll_descriptor_scalar_deleting_destructor
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, byte arrays,navigation scratch/search/path costs,solid ownership and bounding sphere,vertex reuse,original ECX/stack/x87 flow and PE bytes): Thiscall UV-scroll descriptor,flags low BYTE,RET4. Calls existing UV-scroll descriptor destructor,then scalar-deletes receiver ifflags&1,returns original pointer. No vector-cookie/element loop or owning-container unlink in adapter. Solid destructor uses it for array756.
void **__thiscall rf_uv_scroll_descriptor_scalar_deleting_destructor(void **this, char a2)
{
  rf_uv_scroll_descriptor_destroy(this);
  if ( (a2 & 1) != 0 )
    operator delete(this);
  return this;
}

