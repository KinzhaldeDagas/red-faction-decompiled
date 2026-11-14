// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005D2DD0 rf_renderer_clear_depth_clip_rectangle
// UNREALRED VERIFIED [renderer-polygons-20261028]: If depth mode0x187CD1C==2,does nothing. Otherwise applies packed state(0,0,0,0,4,0),builds rectangle using viewport origin plus clip bounds WITHOUT+1 on right/bottom. Device vtable+144 call count1,flags2,color0,depth0 if mode0 else1,stencil0. No explicit immediate flush or state restoration in this body. Existing depth-mode comment retained.
void rf_renderer_clear_depth_clip_rectangle()
{
  int *v0; // eax
  float v1; // [esp+8h] [ebp-18h]
  int v2; // [esp+Ch] [ebp-14h] BYREF
  _DWORD v3[4]; // [esp+10h] [ebp-10h] BYREF

  if ( dword_187CD1C != 2 )
  {
    v0 = rf_render_state_pack(&v2, 0, 0, 0, 0, 4, 0);
    rf_renderer_apply_packed_render_state(*v0);
    v3[0] = unk_187CCBC + dword_187CCD4;
    v3[1] = unk_187CCC0 + dword_187CCDC;
    v3[2] = unk_187CCBC + dword_187CCD8;
    v3[3] = unk_187CCC0 + dword_187CCE0;
    if ( dword_187CD1C )
      v1 = 1.0;
    else
      v1 = 0.0;
    (*(void (__stdcall **)(int, int, _DWORD *, int, _DWORD, float, _DWORD))(*(_DWORD *)dword_1DAEDC4 + 144))(
      dword_1DAEDC4,
      1,
      v3,
      2,
      0,
      COERCE_FLOAT(LODWORD(v1)),
      0);
  }
}

