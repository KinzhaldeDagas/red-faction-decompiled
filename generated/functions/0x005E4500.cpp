// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005E4500 rf_d3d8_texture_stage_unbind_if_bitmap_index
// UNREALRED VERIFIED [texture-upload-20261028]: Ifstagecachedbitmapindex+8matchescallerindex,callsdevicevtable+244(stage+4,nulltexture)then sets cachedbitmapindex=-1. Leavescachedtileindex/UVscalesunchanged,ignoresHRESULTforcacheupdate. ReturnsdeviceHRESULTonmatch,else thispointer. No generalcacheentryreleasehere.
_DWORD *__thiscall rf_d3d8_texture_stage_unbind_if_bitmap_index(_DWORD *this, int a2)
{
  _DWORD *result; // eax

  result = this;
  if ( *(this + 2) == a2 )
  {
    result = (_DWORD *)(*(int (__stdcall **)(int, _DWORD, _DWORD))(*(_DWORD *)dword_1DAEDC4 + 244))(
                         dword_1DAEDC4,
                         *(this + 1),
                         0);
    *(this + 2) = -1;
  }
  return result;
}

