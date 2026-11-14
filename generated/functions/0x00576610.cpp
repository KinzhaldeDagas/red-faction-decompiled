// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00576610 rf_bitmap_lock_cpu_pixels_resolved
// UNREALRED VERIFIED [texture-upload-20261028]: Resolvesbitmap/frame into108-byterecord. TypeDWORD+52==3returns pixelpointer+72,aux/palettepointer+80 throughoutputs,andformatcode+60 directly. Other types call0x5709C0,dispatchtype1->0x577AC0,2->0x576790,4->0x577B60,5->0x577700,6->0x577EF0; onloadsuccess calls0x5709D0 thenreturns samefields. Loaderfailurereturns0 after0x5709D0; type5assumessuccess. Unsupportedtypefataldiagnostic bmpman.cpp2839. No resolvedindexguard,outputinitializationonfailure ortype-specificloadercontractinferred. Lock bookkeeping/realallocationhandledbycallees.
int __cdecl rf_bitmap_lock_cpu_pixels_resolved(unsigned int a1, _DWORD *a2, _DWORD *a3)
{
  int result; // eax
  int v4; // [esp+4h] [ebp-8h]
  _DWORD *v5; // [esp+8h] [ebp-4h]

  v4 = rf_bitmap_resolve_current_frame_slot(a1);
  v5 = (_DWORD *)(dword_1897344 + 108 * v4);
  if ( v5[13] == 3 )
  {
LABEL_29:
    *a2 = v5[18];
    *a3 = v5[20];
    return v5[15];
  }
  else
  {
    if ( v5 )
      rf_renderer_reserved_noop_5709C0();
    switch ( v5[13] )
    {
      case 1:
        if ( rf_bitmap_load_pcx_cpu_pixels_by_slot(v4) )
          goto LABEL_27;
        if ( v5 )
          rf_renderer_reserved_noop_5709D0();
        return 0;
      case 2:
        if ( rf_bitmap_load_tga_cpu_pixels_and_mips_by_slot(v4) )
          goto LABEL_27;
        if ( v5 )
          rf_renderer_reserved_noop_5709D0();
        return 0;
      case 4:
        if ( rf_bitmap_load_vaf_frames_cpu_by_slot(v4) )
          goto LABEL_27;
        if ( v5 )
          rf_renderer_reserved_noop_5709D0();
        return 0;
      case 5:
        rf_bitmap_load_vbm_cpu_payload_by_slot(v4);
        goto LABEL_27;
      case 6:
        if ( rf_bitmap_load_m2v_bytes_by_slot(v4) )
        {
LABEL_27:
          if ( v5 )
            rf_renderer_reserved_noop_5709D0();
          goto LABEL_29;
        }
        if ( v5 )
          rf_renderer_reserved_noop_5709D0();
        result = 0;
        break;
      default:
        rf_fatal_error_show_message_and_exit(
          "D:\\projects\\rf_pc\\vsdk\\bmpman\\bmpman.cpp",
          2839,
          "Unsupported type in bm_lock");
    }
  }
  return result;
}

