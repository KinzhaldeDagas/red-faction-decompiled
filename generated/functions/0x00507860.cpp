// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00507860 rf_vclip_preload_bitmap_and_vfx_stub
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, VClip initialization/preloads,byte occupancy and physical array sizes,trigger suppression/member cleanup and constructor ABI,original ECX/stack flow and PE bytes): Cdecl definition index; negative skips everything, but NO upper bound or loaded-count check. Uses55F720 actual strlen(buffer) helper, not RFString stored extent. If definition RFString+12 has positive C-string length, calls5078C0(index), which lazy-loads VBM cache+20 and warms frames. Independently if RFString+36 length positive, supplies index to507950; that body is a no-op and does NOT load a VFX scene. Does not call scene preload507960, modify strings, require either resource to load successfully, spawn effects or aggregate status. Both paths can run for one record.
void __cdecl rf_vclip_preload_bitmap_and_vfx_stub(int definition_index)
{
  if ( definition_index >= 0 )
  {
    if ( (int)rf_string_length_from_cstr((const char **)&unk_90DC8C + 56 * definition_index) > 0 )
      sub_5078C0(definition_index);
    if ( (int)rf_string_length_from_cstr((const char **)&unk_90DCA4 + 56 * definition_index) > 0 )
      rf_vclip_vfx_preload_noop(definition_index);
  }
}

