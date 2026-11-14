// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005FFAB0 rf_jpeg_marker_emit_sof
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jcmarker.c:emit_sof matched): Args cinfo,SOFcode;emitsmarker,length=3*num_components56+8. Thenchecks signedimage_height32/image_width28 >65535 ->error41,param65535;negativedimensionsnotrejectedhere(earliervalidationassumed). Emitsprecision52,height/widthbig-endian16,numcomponentsBYTE. Per84-bytecomponent:ID0,samplingbyte=(h_samp_factor8<<4)+v_samp_factor12,quanttableindex16. No orientation,colorspaceconversionorDCTdata;voidAPI.
int __cdecl rf_jpeg_marker_emit_sof(int a1, char a2)
{
  int result; // eax
  int v3; // [esp+0h] [ebp-8h]
  int v4; // [esp+4h] [ebp-4h]

  rf_jpeg_marker_emit_marker((_DWORD *)a1, a2);
  rf_jpeg_marker_emit_2bytes((_DWORD *)a1, 3 * *(_WORD *)(a1 + 56) + 8);
  if ( *(int *)(a1 + 32) > 0xFFFF || *(int *)(a1 + 28) > 0xFFFF )
  {
    *(_DWORD *)(*(_DWORD *)a1 + 20) = 41;
    *(_DWORD *)(*(_DWORD *)a1 + 24) = 0xFFFF;
    (**(void (__cdecl ***)(int))a1)(a1);
  }
  rf_jpeg_marker_emit_byte((_DWORD *)a1, *(_DWORD *)(a1 + 52));
  rf_jpeg_marker_emit_2bytes((_DWORD *)a1, *(_DWORD *)(a1 + 32));
  rf_jpeg_marker_emit_2bytes((_DWORD *)a1, *(_DWORD *)(a1 + 28));
  rf_jpeg_marker_emit_byte((_DWORD *)a1, *(_DWORD *)(a1 + 56));
  v3 = 0;
  result = a1;
  v4 = *(_DWORD *)(a1 + 64);
  while ( v3 < *(_DWORD *)(a1 + 56) )
  {
    rf_jpeg_marker_emit_byte((_DWORD *)a1, *(_DWORD *)v4);
    rf_jpeg_marker_emit_byte((_DWORD *)a1, *(_BYTE *)(v4 + 12) + 16 * *(_BYTE *)(v4 + 8));
    rf_jpeg_marker_emit_byte((_DWORD *)a1, *(_DWORD *)(v4 + 16));
    ++v3;
    result = v4 + 84;
    v4 += 84;
  }
  return result;
}

