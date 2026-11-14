// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00556270 rf_solid_has_faces_and_lightmap_storage
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, solid boundary topology, generated UV modes, selection transforms and independently recovered routine boundaries): Returns byte boolean requiring nonempty face list112, nonzero global atlas-page array15A7148 count, and nonzero solid lightmap descriptor array192 count. Does not verify per-face descriptor IDs, resources, tile validity, or ownership consistency. It is a shallow availability predicate.
unsigned __int8 __thiscall rf_solid_has_faces_and_lightmap_storage(const void *this)
{
  if ( !rf_shared_second_dword_getter_518050((_DWORD *)this + 28) )
    return 0;
  return rf_receiver_get_first_dword(unk_15A7148) && rf_receiver_get_first_dword((char *)this + 192);
}

