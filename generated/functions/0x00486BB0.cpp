// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00486BB0 rf_material_prefix_entry_scalar_delete
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, material/foley parse and ownership, RFString input ABI, bitmap cache, property fallback and directional sound numbering): 
// Thiscall scalar deleting destructor, one stack flags argument (RET4). Destroys receiver's first RFString via shared body4873C0 (whose glare-specific name does not imply a52-byte
// prefix object). If flags bit0 set calls raw operator delete(receiver), otherwise retains allocation. Always returns original receiver EAX even after freeing it. Prefix entries
// allocate12 bytes in loader. Does not release bitmap handles, alter registry/count or clear material byte+8.
void *__thiscall rf_material_prefix_entry_scalar_delete(void *this, char a2)
{
  rf_glare_definition52_destroy_name_member(this);
  if ( (a2 & 1) != 0 )
    operator delete(this);
  return this;
}

