// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005E4400 rf_d3d8_texture_stage_cache_matches
// UNREALRED VERIFIED [texture-upload-20261028]: Thisstagecache; stackarguments bitmapindex,tileindex,outputUscale,outputVscale. Returns0ifindices+8/+12differ. OtherwiseifUoutnonnull,writesbothcachedscales+16/+20,assumingVoutnonnull; returns1. IfUoutnull,Voutuntouched. Doesnotcheckentrydirtyflag,GPUbinding,validstage ortexturelifetime.
char __thiscall rf_d3d8_texture_stage_cache_matches(int this, int a2, int a3, float *a4, float *a5)
{
  if ( *(_DWORD *)(this + 8) != a2 || *(_DWORD *)(this + 12) != a3 )
    return 0;
  if ( a4 )
  {
    *a4 = *(float *)(this + 16);
    *a5 = *(float *)(this + 20);
  }
  return 1;
}

