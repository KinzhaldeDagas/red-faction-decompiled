// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00507960 rf_vclip_preload_scene_definition
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, VClip initialization/preloads,byte occupancy and physical array sizes,trigger suppression/member cleanup and constructor ABI,original ECX/stack flow and PE bytes): Cdecl index; negative returns, NO upper bound/loaded-count guard. Uses definition+36 RFString actual C-string length via55F720; only positive length obtains CString then calls rf_scene_definition_cache_lookup_adapter(filename,numeric9999999). Ignores return, does not store definition cache/Foley+44, instantiate/start a VFX model, preload VBM+12, require scene success or mark runtime slot active.
void __cdecl rf_vclip_preload_scene_definition(int a1)
{
  char *v1; // eax

  if ( a1 >= 0 && (int)rf_string_length_from_cstr((const char **)&unk_90DC80 + 56 * a1 + 9) > 0 )
  {
    v1 = (char *)rf_string_object_c_str_or_empty((char *)&unk_90DC80 + 224 * a1 + 36);
    rf_scene_definition_cache_lookup_adapter(v1, (int)byte_98967F);
  }
}

