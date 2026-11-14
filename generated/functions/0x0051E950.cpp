// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0051E950 rf_lightmap_descriptor_scalar_deleting_destructor
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, atlas ownership, lightmap seam lifecycle, selected-face topology, SDK misidentification, x87 return ABI and PE bytes): Calls536810 to destroy descriptor member record-array storage+32;flags01 optionally operator-deletes receiver,returns original address(possibly freed). Does not remove world array registration,free atlas pages or clear member header;no array cookie/flag02 vector destruction.
void **__thiscall rf_lightmap_descriptor_scalar_deleting_destructor(void **this, char a2)
{
  rf_lightmap_descriptor_destroy_record_storage(this);
  if ( (a2 & 1) != 0 )
    operator delete(this);
  return this;
}

