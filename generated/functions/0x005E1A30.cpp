// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005E1A30 rf_d3d8_texture_cache_release_tiles
// UNREALRED VERIFIED [texture-upload-20261028]: Arguments16-bytecacheentry. If tilecountWORD+4nonzero,walksSIGNEDtilecount and32-bytetilearray+12; nonnullGPUtexture releasedviaIUnknown vtable+8,cleared,and globalmemoryestimate0x1E0154C reducedbytileDWORD+4 thenzeroed. Deletesarray,resets handle-1,count0,arraynull,lockcountWORD+8=0. Zerocountbranch resetsfieldswithoutdeletingnonnullarray. Leaves cacheWORD+6,byte+10refcount,byte+11dirtyunchanged. Doesnotcheckoutstandinglocks,unbindstagecaches orvalidatecount; returns0.
int __cdecl rf_d3d8_texture_cache_release_tiles(int a1)
{
  int i; // [esp+4h] [ebp-4h]

  if ( *(_WORD *)(a1 + 4) )
  {
    for ( i = 0; i < *(__int16 *)(a1 + 4); ++i )
    {
      if ( *(_DWORD *)(32 * i + *(_DWORD *)(a1 + 12)) )
      {
        (*(void (__stdcall **)(_DWORD))(**(_DWORD **)(32 * i + *(_DWORD *)(a1 + 12)) + 8))(*(_DWORD *)(32 * i + *(_DWORD *)(a1 + 12)));
        *(_DWORD *)(32 * i + *(_DWORD *)(a1 + 12)) = 0;
        unk_1E0154C -= *(_DWORD *)(*(_DWORD *)(a1 + 12) + 32 * i + 4);
        *(_DWORD *)(*(_DWORD *)(a1 + 12) + 32 * i + 4) = 0;
      }
    }
    *(_DWORD *)a1 = -1;
    *(_WORD *)(a1 + 4) = 0;
    operator delete(*(void **)(a1 + 12));
    *(_DWORD *)(a1 + 12) = 0;
    *(_WORD *)(a1 + 8) = 0;
    return 0;
  }
  else
  {
    *(_DWORD *)a1 = -1;
    *(_WORD *)(a1 + 4) = 0;
    *(_DWORD *)(a1 + 12) = 0;
    *(_WORD *)(a1 + 8) = 0;
    return 0;
  }
}

