// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005E4390 rf_d3d8_texture_stage_cache_construct
// UNREALRED VERIFIED [texture-upload-20261028]: Initializes24-bytestagecache: byte+0=1,stageDWORD+4=callerindex,cachedbitmapindex+8=-1,cachedtileindex+12=-1. Returns this. Doesnotinitializepaddingbytes1..3orUVscalefloats+16/+20orissueGPUcalls.
_DWORD *__thiscall rf_d3d8_texture_stage_cache_construct(_DWORD *this, int a2)
{
  *(_BYTE *)this = 1;
  *(this + 1) = a2;
  *(this + 2) = -1;
  *(this + 3) = -1;
  return this;
}

