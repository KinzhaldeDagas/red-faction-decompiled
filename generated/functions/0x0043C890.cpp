// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0043C890 rf_record_construct_first_string_empty
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, material/foley parse and ownership, RFString input ABI, bitmap cache, property fallback and directional sound numbering): 
// Shared thiscall constructor body: calls rf_string_construct_empty on the receiver at offset0, then explicitly MOV EAX,saved_receiver at0x43C89F and returns without stack arguments.
// Initializes only the first 8-byte RFString (extent/buffer), not the whole enclosing record. Used by material loader for newly allocated12-byte prefix entries, whose material byte+8
// is assigned separately. Prior void return prototype hid the constructor's returned allocation pointer in decompiled loader; corrected to return DWORD pointer. No allocation,
// scalar/padding initialization or validation here.
_DWORD *__thiscall rf_record_construct_first_string_empty(_DWORD *this)
{
  rf_string_construct_empty(this);
  return this;
}

