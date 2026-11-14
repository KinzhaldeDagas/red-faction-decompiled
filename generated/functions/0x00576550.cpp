// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00576550 rf_bitmap_get_resolved_format_code
// UNREALRED VERIFIED [lightmap-shadows-20261028]: Resolves bitmap/frame via0x574B80,returns DWORD+60 from108-byte record at0x1897344+108*index. No failedindex/bounds guard. Resolver can mutateanimationstate; query isnot necessarily side-effect-free. Internalnumericformat semantics not invented here.
int __cdecl rf_bitmap_get_resolved_format_code(unsigned int a1)
{
  return *(_DWORD *)(dword_1897344 + 108 * rf_bitmap_resolve_current_frame_slot(a1) + 60);
}

