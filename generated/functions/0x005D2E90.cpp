// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005D2E90 rf_renderer_apply_viewport_rectangle
// UNREALRED VERIFIED [renderer-polygons-20261028]: If immediateactive0x1E014E5,flushes immediate buffers first. Builds six-DWORD viewport: X=0x187CCBC+0x187CCD4,Y=0x187CCC0+0x187CCDC,width0x187CCC4,height0x187CCC8,minZ0,maxZ1. Calls device vtable+160 with viewport pointer and returns result. Width/height are globals,not computed from clip right/bottom. No negative/range validation.
int rf_renderer_apply_viewport_rectangle()
{
  _DWORD v1[6]; // [esp+4h] [ebp-18h] BYREF

  if ( unk_1E014E5 )
    rf_renderer_flush_immediate_buffers();
  v1[0] = unk_187CCBC + dword_187CCD4;
  v1[1] = unk_187CCC0 + dword_187CCDC;
  v1[2] = dword_187CCC4;
  v1[3] = dword_187CCC8;
  *(float *)&v1[4] = 0.0;
  *(float *)&v1[5] = 1.0;
  return (*(int (__stdcall **)(int, _DWORD *))(*(_DWORD *)dword_1DAEDC4 + 160))(dword_1DAEDC4, v1);
}

