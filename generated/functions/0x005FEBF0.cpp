// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005FEBF0 rf_jpeg_do_sarray_io
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jmemmgr.c:do_sarray_io matched): rowBytes=samplesPerRow8. Localcdecl(cinfo,descriptor,writing). Startsfileoffset=rowBytes*currentStart24;iteratesbufferinchunksofrowsPerChunk20,clipsrowcountbyrowsInMemory16,firstUndefined28-currentRow,totalRows4-currentRow;stopswhennovalidrows. Calls backingwrite callbackdescriptor52 orread48 with(cinfo,&backingState48,rowpointer,byteOffset,byteCount),advancesoffset. Doesnotupdatewindow/dirtyflagoropenstore;callerguaranteesvalidrealizeddescriptor. NativeRFplatformdoesnotimplementbackingstore,butgenericvirtualarrayIOcodeiscompiledin.
int __cdecl rf_jpeg_do_sarray_io(int a1, int a2, int a3)
{
  int result; // eax
  int v4; // [esp+0h] [ebp-24h]
  int v5; // [esp+4h] [ebp-20h]
  int v6; // [esp+8h] [ebp-1Ch]
  int v7; // [esp+Ch] [ebp-18h]
  int v8; // [esp+10h] [ebp-14h]
  int v9; // [esp+14h] [ebp-10h]
  int i; // [esp+1Ch] [ebp-8h]
  int v11; // [esp+20h] [ebp-4h]

  v11 = *(_DWORD *)(a2 + 8);
  v7 = v11 * *(_DWORD *)(a2 + 24);
  for ( i = 0; ; i += *(_DWORD *)(a2 + 20) )
  {
    result = a2;
    if ( i >= *(_DWORD *)(a2 + 16) )
      break;
    v6 = *(_DWORD *)(a2 + 20) >= *(_DWORD *)(a2 + 16) - i ? *(_DWORD *)(a2 + 16) - i : *(_DWORD *)(a2 + 20);
    v9 = i + *(_DWORD *)(a2 + 24);
    v5 = v6 >= *(_DWORD *)(a2 + 28) - v9 ? *(_DWORD *)(a2 + 28) - v9 : v6;
    result = a2;
    if ( v5 >= *(_DWORD *)(a2 + 4) - v9 )
    {
      result = a2;
      v4 = *(_DWORD *)(a2 + 4) - v9;
    }
    else
    {
      v4 = v5;
    }
    if ( v4 <= 0 )
      break;
    v8 = v11 * v4;
    if ( a3 )
      (*(void (__cdecl **)(int, int, _DWORD, int, int))(a2 + 52))(
        a1,
        a2 + 48,
        *(_DWORD *)(*(_DWORD *)a2 + 4 * i),
        v7,
        v8);
    else
      (*(void (__cdecl **)(int, int, _DWORD, int, int))(a2 + 48))(
        a1,
        a2 + 48,
        *(_DWORD *)(*(_DWORD *)a2 + 4 * i),
        v7,
        v8);
    v7 += v8;
  }
  return result;
}

