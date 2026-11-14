// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00536810 rf_lightmap_descriptor_destroy_record_storage
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, lightmap clusters, tile mapping, atlas placement, seam blend snapshots, recovered halfplanes and original PE bytes): Destroys only member record-array backing at descriptor+32 via47A3F0. Does not free atlas page,bitmap,descriptor itself,or remove world array registration. Member count/capacity/backing remain unchanged after destructor-style free;no reusable reset.
void __thiscall rf_lightmap_descriptor_destroy_record_storage(void **this)
{
  rf_pointer_array_destroy_backing_storage(this + 8);
}

