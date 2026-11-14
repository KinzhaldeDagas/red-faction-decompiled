// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005765C0 rf_bitmap_get_resolved_cpu_pixel_and_aux_pointers
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, bitmap records/animation rates, decoded-handle tag test, tile descriptor offsets and text-parser ownership): cdecl(handle,outPixels,outAuxiliary),nonnull output pointers. Resolves current frame,then copies record DWORD+72 and+80 to outputs,returns format DWORD+60. Field+80 is auxiliary/palette pointer,NOT allocation byte count. Unlike576610 lock/load helper,this does not load/decode pixels,increment CPU refs or test file type before returning cached pointers. No failed-index,handle generation or pointer validation.
int __cdecl rf_bitmap_get_resolved_cpu_pixel_and_aux_pointers(unsigned int handle, void **pixels, void **auxiliary)
{
  int v4; // [esp+4h] [ebp-4h]

  v4 = dword_1897344 + 108 * rf_bitmap_resolve_current_frame_slot(handle);
  *pixels = *(void **)(v4 + 72);
  *auxiliary = *(void **)(v4 + 80);
  return *(_DWORD *)(v4 + 60);
}

