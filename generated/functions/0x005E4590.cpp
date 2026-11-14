// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005E4590 rf_d3d8_texture_stage_cache_default_construct
// UNREALRED VERIFIED [texture-conversion-20261028]: Initializes stagecache byte+0=0,cachedbitmapindex+8=-1,cachedtileindex+12=-1,UVscales+16/+20=1. Returns this. StageindexDWORD+4andpaddingremainuninitialized; -1integerfieldsappearNaNincurrentfloatdecompiler.
float *__thiscall rf_d3d8_texture_stage_cache_default_construct(float *this)
{
  *(_BYTE *)this = 0;
  *(this + 2) = NAN;
  *(this + 3) = NAN;
  *(this + 4) = 1.0;
  *(this + 5) = 1.0;
  return this;
}

