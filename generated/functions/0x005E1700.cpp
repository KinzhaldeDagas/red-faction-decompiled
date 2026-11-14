// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005E1700 rf_d3d8_texture_cache_initialize_array
// UNREALRED VERIFIED [image-headers-20261028]: Allocates16*bitmap slot count0x663F14 bytes at0x1E01548. Each entry handle-1,tilecount+4=0,array+12=null,ageWORD+6=0,referenceBYTE+10=0,lockcountWORD+8=0. Leaves dirty byte+11 uninitialized. Constructs two24-byte stage caches for stages0/1 through0x5E4390; that constructor leaves UV scales uninitialized. No allocation failure or prior array cleanup check; returns second constructor result.
_DWORD *rf_d3d8_texture_cache_initialize_array()
{
  int i; // [esp+4h] [ebp-4h]

  unk_1E01548 = operator new(16 * dword_663F14);
  for ( i = 0; i < dword_663F14; ++i )
  {
    *(_DWORD *)(unk_1E01548 + 16 * i) = -1;
    *(_WORD *)(unk_1E01548 + 16 * i + 4) = 0;
    *(_DWORD *)(unk_1E01548 + 16 * i + 12) = 0;
    *(_WORD *)(unk_1E01548 + 16 * i + 6) = 0;
    *(_BYTE *)(unk_1E01548 + 16 * i + 10) = 0;
    *(_WORD *)(unk_1E01548 + 16 * i + 8) = 0;
  }
  rf_d3d8_texture_stage_cache_construct(unk_1E01550, 0);
  return rf_d3d8_texture_stage_cache_construct(dword_1E01568, 1);
}

