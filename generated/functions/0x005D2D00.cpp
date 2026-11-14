// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005D2D00 rf_renderer_clear_color_clip_rectangle
// UNREALRED VERIFIED [renderer-polygons-20261028]: Packs/applies render state(0,0,0,0,0,0). Builds rectangle left=viewportX0x187CCBC+clipLeft0x187CCD4,top=viewportY0x187CCC0+clipTop0x187CCDC,right=viewportX+clipRight0x187CCD8+1,bottom=viewportY+clipBottom0x187CCE0+1. Device vtable+144 call count1,rectangle,flags1,color opaqueARGB from current RGB,depth0,stencil0. Ignores current alpha and color-filter globals; no explicit immediate flush in this body. Returns device result.
int rf_renderer_clear_color_clip_rectangle()
{
  int *v0; // eax
  int v2[2]; // [esp+8h] [ebp-1Ch] BYREF
  _DWORD v3[4]; // [esp+10h] [ebp-14h] BYREF
  unsigned int v4; // [esp+20h] [ebp-4h]

  v0 = rf_render_state_pack(v2, 0, 0, 0, 0, 0, 0);
  rf_renderer_apply_packed_render_state(*v0);
  v3[0] = unk_187CCBC + dword_187CCD4;
  v3[1] = unk_187CCC0 + dword_187CCDC;
  v3[2] = dword_187CCD8 + unk_187CCBC + 1;
  v3[3] = dword_187CCE0 + unk_187CCC0 + 1;
  v2[1] = (int)&rf_render_current_red;
  v4 = rf_render_current_blue | (rf_render_current_green << 8) | (rf_render_current_red << 16) | 0xFF000000;
  return (*(int (__stdcall **)(int, int, _DWORD *, int, unsigned int, _DWORD, _DWORD))(*(_DWORD *)dword_1DAEDC4 + 144))(
           dword_1DAEDC4,
           1,
           v3,
           1,
           v4,
           0.0,
           0);
}

