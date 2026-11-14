// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004867F0 rf_bitmap_material_to_index
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, material/foley parse and ownership, RFString input ABI, bitmap cache, property fallback and directional sound numbering): 
// Cdecl raw bitmap/material handle. Exact -1 returns Default0 immediately; other negative handles pass to bitmap metadata helpers. Reads source metadata byte93; any nonzero returned
// value is accepted verbatim as cached material id without local0..9 validation. Zero triggers source-name retrieval, first-underscore prefix lookup, writes low8 resolved id back to
// metadata byte93, returns resolved value. Default0 is ALSO unresolved sentinel, so a Default/unknown result remains0 and future calls repeat name lookup and cache write. No
// registry-version invalidation, failure status or independent object material override here.
int __cdecl rf_bitmap_material_to_index(int bitmap_material_id)
{
  const char *source_record_name_pointer; // eax
  int source_metadata_byte93; // [esp+0h] [ebp-4h]

  if ( bitmap_material_id == -1 )
    return 0;
  source_metadata_byte93 = rf_bitmap_get_source_metadata_byte93(bitmap_material_id);
  if ( !source_metadata_byte93 )
  {
    source_record_name_pointer = (const char *)rf_bitmap_get_source_record_name_pointer(bitmap_material_id);
    source_metadata_byte93 = rf_bitmap_prefix_to_material_index(source_record_name_pointer);
    rf_bitmap_set_source_metadata_byte93(bitmap_material_id, source_metadata_byte93);
  }
  return source_metadata_byte93;
}

