// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005732A0 rf_renderer_read_backbuffer_rectangle_dispatch
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, clipping arithmetic, stack ABI and callers): For backend102 forwards x,y,width,height,destination to D3D readback and returns RF pixel-format code. Other backends return0. NULL destination behavior is inherited from backend (format3); no added validation.
int __cdecl rf_renderer_read_backbuffer_rectangle_dispatch(int a1, int a2, int a3, int a4, void *a5)
{
  if ( dword_187CC9C == 102 )
    return rf_d3d8_read_backbuffer_rectangle(a1, a2, a3, a4, a5);
  else
    return 0;
}

