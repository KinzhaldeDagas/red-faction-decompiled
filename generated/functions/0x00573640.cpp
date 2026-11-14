// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00573640 rf_bitmap_lock_pixels_backend_dispatch
// UNREALRED VERIFIED [lightmap-pixels-20261028]: Arguments bitmaphandle,tileindex,32-byte lockdescriptor,modeDWORD. Stores mode atdescriptor+28 BEFORE checking backendselector. Backend102 delegates0x5E3DC0,otherbackends return0 leaving otherdescriptorfields uninitialized. Does not reset descriptoronfailure.
char __cdecl rf_bitmap_lock_pixels_backend_dispatch(
        unsigned int a1,
        unsigned int a2,
        unsigned int *a3,
        unsigned int a4)
{
  a3[7] = a4;
  if ( dword_187CC9C == 102 )
    return rf_d3d8_bitmap_lock_tile_pixels(a1, a2, a3);
  else
    return 0;
}

