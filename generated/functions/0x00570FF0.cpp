// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00570FF0 rf_renderer_capture_viewport_pixels_to_image
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, renderer/window context, capture ownership across calls, gamma precision and ramp bytes): cdecl(basePath,jpegFlag,optionalVfileContext). Reads effective viewport dimensions187CCC4/CCC8,allocates4*width*height bytes via operatornew using unchecked32bit arithmetic. NULL allocation skips all work. Backend102 first flushes immediate buffers. Calls5732A0 readback with origin fields187CCD4/CCDC (relative clip left/top),dimensions and private buffer,plus an extra sixth stack word0 ignored by5732A0;does NOT itself add stored viewport origin187CCBC/CCC0. Passes returned RF pixel format straight to5710A0 along with dimensions,path,jpeg flag/context,WITHOUT checking format/readback success. Unconditionally operator-deletes private buffer after imagewriter returns. TGA writer packet-allocation failure5711DA already
// operator-deletes supplied source buffer;this caller then deletes it again at571091,so that failure path has double deletion. Other imagewriter/source-conversion ownership behavior inherited. No dimension/overflow,capacity/format or file-write result validation;void result.
void __cdecl rf_renderer_capture_viewport_pixels_to_image(char *a1, int a2, int a3)
{
  int backbuffer_rectangle_dispatch; // [esp+8h] [ebp-10h]
  _BYTE *v4; // [esp+Ch] [ebp-Ch]
  int v5; // [esp+10h] [ebp-8h]
  int v6; // [esp+14h] [ebp-4h]

  v6 = unk_187CCC4;
  v5 = unk_187CCC8;
  v4 = operator new(4 * unk_187CCC8 * unk_187CCC4);
  if ( v4 )
  {
    if ( dword_187CC9C == 102 )
      rf_renderer_flush_immediate_buffers();
    backbuffer_rectangle_dispatch = rf_renderer_read_backbuffer_rectangle_dispatch(
                                      unk_187CCD4,
                                      unk_187CCDC,
                                      v6,
                                      v5,
                                      (int)v4);
    rf_image_write_tga_or_jpeg(v4, backbuffer_rectangle_dispatch, v6, v5, a1, a2, a3);
    operator delete(v4);
  }
}

