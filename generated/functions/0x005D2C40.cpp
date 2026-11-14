// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005D2C40 rf_renderer_bind_texture_warmup_backend_102
// UNREALRED VERIFIED [level-lifecycle-20261028]: Nonnegative bitmap handle calls rf_renderer_bind_texture_handle(0,handle,0,&global0x1E014DC,&global0x1E014D0,0). Negative handle does nothing. This is stage0 texture binding, not texture destruction.
void __cdecl rf_renderer_bind_texture_warmup_backend_102(int a1)
{
  if ( a1 > -1 )
    rf_renderer_bind_texture_handle(0, a1, 0, (int)&unk_1E014DC, (int)&unk_1E014D0, 0);
}

