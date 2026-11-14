// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005FFBF0 rf_jpeg_marker_write_scan_header
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jcmarker.c:write_scan_header matched): Ifarith176 nonzero,callscompiledno-opemit_dac5FFE60;elseforeachcurrent_scancomponent244+4*i:sequentialemitsDCandACDHT;progressiveACscan(Ss312!=0)emitsAC only,DCfirstscan(Ss0,Ah320==0)emitsDC,DCrefinementemitsneither. Ifrestart_interval196 differsfrommarker.last_restart_interval28,emitsDRIincludingzero-to-disableandupdatescachedvalue. FinallyemitSOS. No entropybitstreamorstatevalidation;fullencoderrejectsunsupportedarith/progressiveininitializer.
int __cdecl rf_jpeg_marker_write_scan_header(_DWORD *cinfo)
{
  int v2; // [esp+0h] [ebp-Ch]
  int i; // [esp+4h] [ebp-8h]
  int v4; // [esp+8h] [ebp-4h]

  v4 = cinfo[86];
  if ( cinfo[44] )
  {
    rf_jpeg_marker_emit_dac_disabled(cinfo);
  }
  else
  {
    for ( i = 0; i < cinfo[60]; ++i )
    {
      v2 = cinfo[i + 61];
      if ( cinfo[56] )
      {
        if ( cinfo[78] )
        {
          rf_jpeg_marker_emit_dht(cinfo, *(_DWORD *)(v2 + 24), 1);
        }
        else if ( !cinfo[80] )
        {
          rf_jpeg_marker_emit_dht(cinfo, *(_DWORD *)(v2 + 20), 0);
        }
      }
      else
      {
        rf_jpeg_marker_emit_dht(cinfo, *(_DWORD *)(v2 + 20), 0);
        rf_jpeg_marker_emit_dht(cinfo, *(_DWORD *)(v2 + 24), 1);
      }
    }
  }
  if ( cinfo[49] != *(_DWORD *)(v4 + 28) )
  {
    rf_jpeg_marker_emit_dri(cinfo);
    *(_DWORD *)(v4 + 28) = cinfo[49];
  }
  return rf_jpeg_marker_emit_sos((int)cinfo);
}

