// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00571C60 rf_renderer_bind_texture_for_level_warmup
// UNREALRED VERIFIED [level-lifecycle-20261028]: Only when renderer selector0x187CC9C==102 delegates input handle to0x5D2C40. Other backends do nothing. No own handle-range test.
void __cdecl rf_renderer_bind_texture_for_level_warmup(int a1)
{
  if ( dword_187CC9C == 102 )
    rf_renderer_bind_texture_warmup_backend_102(a1);
}

