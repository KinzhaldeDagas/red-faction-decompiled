// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005E4450 rf_d3d8_texture_stage_bind_cached_tile
// UNREALRED VERIFIED [texture-upload-20261028]: Thisstagecache; arguments cacheentry,tileindex,outputUscale,outputVscale. Operatesifstageindex+4==0 ORrf_d3d8_multitexture_available; otherstageswithoutmultitexturereturnthisunchanged. Clearsentrydirtybyte+11,bindstileGPUtexturevia devicevtable+244(stage,texture),IGNORESHRESULT. WritesBOTHUVoutpointersunconditionally,updatesstagecachedbitmapindex=(entry-0x1E01548)>>4,tileindexandUVscales. ReturnsVoutpointer. No tilebounds,nulloutputs orbindingerrorrollback.
float *__thiscall rf_d3d8_texture_stage_bind_cached_tile(int this, int a2, int a3, float *a4, float *a5)
{
  float *result; // eax
  int v7; // [esp+4h] [ebp-4h]

  result = (float *)this;
  if ( !*(_DWORD *)(this + 4) || rf_d3d8_multitexture_available )
  {
    v7 = *(_DWORD *)(a2 + 12) + 32 * a3;
    *(_BYTE *)(a2 + 11) = 0;
    (*(void (__stdcall **)(int, _DWORD, _DWORD))(*(_DWORD *)dword_1DAEDC4 + 244))(
      dword_1DAEDC4,
      *(_DWORD *)(this + 4),
      *(_DWORD *)v7);
    *a4 = *(float *)(v7 + 8);
    *a5 = *(float *)(v7 + 12);
    *(_DWORD *)(this + 8) = (a2 - (int)dword_1E01548) >> 4;
    *(_DWORD *)(this + 12) = a3;
    *(float *)(this + 16) = *a4;
    *(float *)(this + 20) = *a5;
    return a5;
  }
  return result;
}

