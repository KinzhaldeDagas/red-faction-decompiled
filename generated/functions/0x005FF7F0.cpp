// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005FF7F0 rf_jpeg_marker_write_frame_header
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jcmarker.c:write_frame_header matched): Forallcomponents84-byte stride,emitsneededquanttable referencedbycomponent.quant_tbl_no16;accumulateswhetherANYtablehas16-bitcoefficients,evenifsent_tablealreadysuppressesemission. Baselineeligibleonlyarith176=0,progressive224=0,data_precision52=8,andallDC20/AC24tableindices<=1. If16-bitquantwhileotherwisebaseline,disablesbaselineandemitstrace75(level0),notfatal. SOFchoicepriority:arithmetic->C9,elseprogressive->C2,elsebaseline->C0,otherwiseC1. Fullcompressorinitializerrejectsarithmetic/progressiveearlier,butgenericmarkerbranchesremaincompiled. No scandata orstatechange.
int __cdecl rf_jpeg_marker_write_frame_header(_DWORD *a1)
{
  int v2; // [esp+0h] [ebp-10h]
  int v3; // [esp+4h] [ebp-Ch]
  int v4; // [esp+4h] [ebp-Ch]
  int v5; // [esp+8h] [ebp-8h]
  int v6; // [esp+8h] [ebp-8h]
  int v7; // [esp+Ch] [ebp-4h]

  v7 = 0;
  v3 = 0;
  v5 = a1[16];
  while ( v3 < a1[14] )
  {
    v7 += rf_jpeg_marker_emit_dqt((int)a1, *(_DWORD *)(v5 + 16));
    ++v3;
    v5 += 84;
  }
  if ( a1[44] || a1[56] || a1[13] != 8 )
  {
    v2 = 0;
  }
  else
  {
    v2 = 1;
    v4 = 0;
    v6 = a1[16];
    while ( v4 < a1[14] )
    {
      if ( *(int *)(v6 + 20) > 1 || *(int *)(v6 + 24) > 1 )
        v2 = 0;
      ++v4;
      v6 += 84;
    }
    if ( v7 && v2 )
    {
      v2 = 0;
      *(_DWORD *)(*a1 + 20) = 75;
      (*(void (__cdecl **)(_DWORD *, _DWORD))(*a1 + 4))(a1, 0);
    }
  }
  if ( a1[44] )
    return rf_jpeg_marker_emit_sof((int)a1, 201);
  if ( a1[56] )
    return rf_jpeg_marker_emit_sof((int)a1, 194);
  if ( v2 )
    return rf_jpeg_marker_emit_sof((int)a1, 192);
  return rf_jpeg_marker_emit_sof((int)a1, 193);
}

