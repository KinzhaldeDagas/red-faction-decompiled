// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005E4280 rf_d3d8_bitmap_texture_add_reference
// UNREALRED VERIFIED [texture-upload-20261028]: Calls rf_renderer_bind_texture_for_level_warmup,thenresolveshandle,indexes16-bytecacheentry,INCREMENTSbyte+10withwrap,returnsentrypointer. No error/overflowguard; doesnotincrementlockcount+8.
int __cdecl rf_d3d8_bitmap_texture_add_reference(unsigned int a1)
{
  int result; // eax

  rf_renderer_bind_texture_for_level_warmup(a1);
  result = (int)dword_1E01548 + 16 * rf_bitmap_resolve_current_frame_slot(a1);
  ++*(_BYTE *)(result + 10);
  return result;
}

