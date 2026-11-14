// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005FFD10 rf_jpeg_marker_emit_dht
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jcmarker.c:emit_dht matched): Args cinfo,index,isAC. SelectstableDC84+4*index orAC100+4*index;ACencodedtableID=index+16. Missingtablefatal50,paramencodedID;no localindexboundcheck. Ifsent_table276==0,emitsDHT FF C4,count=sumunsignedbits[1..16],length=count+19,tableID,16lengthcounts,thenexactcounthuffvalbytesat17;sent_table=1. Doesnotvalidatecount<=256/canonicaltreehere(assumesconfiguredvalidtable),so sourcefieldsdriveemission. No outputwhenalready-sent;voidAPI.
int __cdecl rf_jpeg_marker_emit_dht(_DWORD *a1, int a2, int a3)
{
  int result; // eax
  int v4; // [esp+0h] [ebp-Ch]
  int i; // [esp+4h] [ebp-8h]
  int j; // [esp+4h] [ebp-8h]
  int k; // [esp+4h] [ebp-8h]
  int v8; // [esp+8h] [ebp-4h]

  if ( a3 )
  {
    v4 = a1[a2 + 25];
    result = a2 + 16;
    a2 += 16;
  }
  else
  {
    result = a1[a2 + 21];
    v4 = result;
  }
  if ( !v4 )
  {
    *(_DWORD *)(*a1 + 20) = 50;
    *(_DWORD *)(*a1 + 24) = a2;
    result = (*(int (__cdecl **)(_DWORD *))*a1)(a1);
  }
  if ( !*(_DWORD *)(v4 + 276) )
  {
    rf_jpeg_marker_emit_marker(a1, 196);
    v8 = 0;
    for ( i = 1; i <= 16; ++i )
      v8 += *(unsigned __int8 *)(i + v4);
    rf_jpeg_marker_emit_2bytes(a1, v8 + 19);
    rf_jpeg_marker_emit_byte(a1, a2);
    for ( j = 1; j <= 16; ++j )
      rf_jpeg_marker_emit_byte(a1, *(_BYTE *)(j + v4));
    for ( k = 0; ; ++k )
    {
      result = k;
      if ( k >= v8 )
        break;
      rf_jpeg_marker_emit_byte(a1, *(_BYTE *)(k + v4 + 17));
    }
    *(_DWORD *)(v4 + 276) = 1;
  }
  return result;
}

