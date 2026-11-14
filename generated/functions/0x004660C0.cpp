// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004660C0 rf_browser_apply_server_info_to_rows
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, browser reply and host/options/intro UI call chains, original switch/literal data, native float predicates and
// callback ownership/ABI): Cdecl NINE stack words:IPv4,endpointDWORD4,serverName,mapName,mod/archive,playersLOWBYTE,maxLOWBYTE,modeLOWBYTE,wireFlagsLOWBYTE. Packet1 handler4A3D70
// verified callers pass36 bytes,including incompatible-version placeholder path. Capture millisecond clock BEFORE cancel6F51A1 test;cancel nonzero returns without dirty/row work.
// Otherwise set dirty6F52D9 BEFORE endpoint lookup. Existing endpoint:bounded31 name/map with finalNUL,players/max bytes,zero-extend mode toDWORD80;full strlen mod,nonempty
// strncpy15/NUL79 else mod[0]=0. If awaiting20000000:clear it,pingWORD94=LOW16(now-DWORD96) (native subtract reads FULLDWORD timestamp,despite pseudocode WORD),increment
// completed6F5190 only if signed<liveCount,increment succeeded6F52C4;nonnegative nextcursor validates mapped raw row then ORs queued40000000,advances cursor/end-1 WITHOUT resetting
// retry;singleQuery6F52D8=0. Replies without awaiting still update metadata/low flags but no success accounting. Map wireFlag4->recordFlag2 and wireFlag1->recordFlag1,clearing absent
// bits,preserving favorite/otherflags;selected matching row sets follow6F52DA=1. Missing endpoint:ONLY LAN checkbox nonzero AND wireFlag2 CLEAR ->zero100-byte local,copy
// endpointDWORDs,names/mod,byte counts,mode,pingLOW16(now-DWORD6F51A4),mapped lowflags;import favorite0,ignore failure,increment completed regardless. No
// allocation,active/runtime/protocol validation here,capacity growth,immediate send,follow mark for inserted row or retry reset. Existing int return incidental mixed EAX/AL residues.
char __cdecl rf_browser_apply_server_info_to_rows(
        unsigned int a1,
        int a2,
        char *Source,
        char *a4,
        char *a5,
        char a6,
        char a7,
        char a8,
        char a9)
{
  char result; // al
  _DWORD v10[27]; // [esp+20h] [ebp-78h] BYREF
  int v11; // [esp+90h] [ebp-8h]
  int v12; // [esp+94h] [ebp-4h] BYREF

  v11 = rf_performance_clock_elapsed_scaled(1000);
  result = unk_6F51A1;
  if ( !unk_6F51A1 )
  {
    unk_6F52D9 = 1;
    result = rf_browser_find_endpoint_or_insertion_index(a1, a2, &v12);
    if ( result )
    {
      *((_BYTE *)dword_6F52CC + 108 * v12 + 31) = 0;
      strncpy((char *)dword_6F52CC + 108 * v12, Source, 0x1Fu);
      *((_BYTE *)dword_6F52CC + 108 * v12 + 63) = 0;
      strncpy((char *)dword_6F52CC + 108 * v12 + 32, a4, 0x1Fu);
      *((_BYTE *)dword_6F52CC + 108 * v12 + 92) = a6;
      *((_BYTE *)dword_6F52CC + 108 * v12 + 93) = a7;
      *((_DWORD *)dword_6F52CC + 27 * v12 + 20) = (unsigned __int8)a8;
      if ( strlen(a5) )
      {
        strncpy((char *)dword_6F52CC + 108 * v12 + 64, a5, 0xFu);
        *((_BYTE *)dword_6F52CC + 108 * v12 + 79) = 0;
      }
      else
      {
        *((_BYTE *)dword_6F52CC + 108 * v12 + 64) = 0;
      }
      if ( (*((_DWORD *)dword_6F52CC + 27 * v12 + 26) & 0x20000000) != 0 )
      {
        *((_DWORD *)dword_6F52CC + 27 * v12 + 26) &= ~0x20000000u;
        *((_WORD *)dword_6F52CC + 54 * v12 + 47) = v11 - *((_WORD *)dword_6F52CC + 54 * v12 + 48);
        if ( dword_6F5190 < dword_6F51A8 )
          ++dword_6F5190;
        ++unk_6F52C4;
        if ( dword_6F51B0 >= 0 )
        {
          if ( *(int *)(unk_6F52D0 + 4 * dword_6F51B0) >= 0 && *(_DWORD *)(unk_6F52D0 + 4 * dword_6F51B0) < dword_6F51A8 )
            *((_DWORD *)dword_6F52CC + 27 * *(_DWORD *)(unk_6F52D0 + 4 * dword_6F51B0) + 26) |= 0x40000000u;
          if ( ++dword_6F51B0 >= dword_6F51A8 )
            dword_6F51B0 = -1;
        }
        unk_6F52D8 = 0;
      }
      if ( (a9 & 4) != 0 )
        *((_DWORD *)dword_6F52CC + 27 * v12 + 26) |= 2u;
      else
        *((_DWORD *)dword_6F52CC + 27 * v12 + 26) &= ~2u;
      if ( (a9 & 1) != 0 )
        *((_DWORD *)dword_6F52CC + 27 * v12 + 26) |= 1u;
      else
        *((_DWORD *)dword_6F52CC + 27 * v12 + 26) &= ~1u;
      result = v12;
      if ( v12 == dword_661F9C )
        unk_6F52DA = 1;
    }
    else if ( byte_6F5DB8[0] && (a9 & 2) == 0 )
    {
      memset(v10, 0, 0x64u);
      v10[0] = a1;
      v10[1] = a2;
      strncpy((char *)&v10[2], Source, 0x1Fu);
      HIBYTE(v10[9]) = 0;
      strncpy((char *)&v10[10], a4, 0x1Fu);
      HIBYTE(v10[17]) = 0;
      LOBYTE(v10[23]) = a6;
      BYTE1(v10[23]) = a7;
      v10[22] = (unsigned __int8)a8;
      if ( strlen(a5) )
      {
        strncpy((char *)&v10[18], a5, 0xFu);
        HIBYTE(v10[21]) = 0;
      }
      else
      {
        LOBYTE(v10[18]) = 0;
      }
      HIWORD(v10[23]) = v11 - word_6F51A4;
      v10[24] = 0;
      if ( (a9 & 4) != 0 )
        v10[24] |= 2u;
      if ( (a9 & 1) != 0 )
        v10[24] |= 1u;
      rf_browser_import_cache100((int)v10, 0);
      return ++dword_6F5190;
    }
  }
  return result;
}

