// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00552D90 rf_lightmap_atlas_page_destroy_resources
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, atlas ownership, lightmap seam lifecycle, selected-face topology, SDK misidentification, x87 return ABI and PE bytes): Thiscall page24. If signed bitmap handle16>=0,recycles handle. Always operator-deletes nonNULL RGB pointer12 and occupancy pointer0,including RGB pointer supplied externally to constructor552CA0. No ownership flag or borrowed-buffer exemption. Does not zero handles/pointers/dimensions,unregister global page slot,or free page receiver. Repeated destruction unsafe unless caller resets fields.
void __thiscall rf_lightmap_atlas_page_destroy_resources(int this)
{
  if ( *(int *)(this + 16) > -1 )
    rf_bitmap_handle_recycle_slot_or_animation_entry(*(_DWORD *)(this + 16));
  if ( *(_DWORD *)(this + 12) )
    operator delete(*(void **)(this + 12));
  if ( *(_DWORD *)this )
    operator delete(*(void **)this);
}

