// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005E4350 rf_d3d8_bitmap_get_first_gpu_texture
// UNREALRED VERIFIED [texture-upload-20261028]: ResolvescacheentryBEFOREwarmuphelper,thenreturnsDWORD0offirsttilearrayentry. Warmupmaycreatecache; no nullarray,refcount,tilecount orfailurechecks. ReturnsborrowedGPUtexturepointerwithoutAddRef.
int __cdecl rf_d3d8_bitmap_get_first_gpu_texture(unsigned int a1)
{
  char *v2; // [esp+0h] [ebp-8h]

  v2 = (char *)dword_1E01548 + 16 * rf_bitmap_resolve_current_frame_slot(a1);
  rf_renderer_bind_texture_for_level_warmup(a1);
  return **((_DWORD **)v2 + 3);
}

