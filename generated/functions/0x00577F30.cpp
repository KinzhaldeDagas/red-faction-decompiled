// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00577F30 rf_bitmap_unlock_cpu_handle_wrapper
// UNREALRED VERIFIED [texture-upload-20261028]: Calls0x5741B0(bitmaphandle,0),nootherwork. Voidwrapper; doesnotdirectlyunlockGPUtexture. Calleeownsbitmapref/bookkeepingbehavior.
void __cdecl rf_bitmap_unlock_cpu_handle_wrapper(unsigned int a1)
{
  rf_bitmap_release_cpu_pixels_force_or_reference(a1, 0);
}

