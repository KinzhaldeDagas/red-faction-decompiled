// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005E4750 rf_vani_player_release_pixel_palette_buffers
// UNREALRED VERIFIED [texture-conversion-20261028]: Deletesnonnullpixelbuffer+112andpalettebuffer+116withoperatordelete,andnullseach. Doesnotreleasebitmap,closevfile orresetmetadata.
void __thiscall rf_vani_player_release_pixel_palette_buffers(void **this)
{
  if ( *(this + 28) )
  {
    operator delete(*(this + 28));
    *(this + 28) = nullptr;
  }
  if ( *(this + 29) )
  {
    operator delete(*(this + 29));
    *(this + 29) = nullptr;
  }
}

