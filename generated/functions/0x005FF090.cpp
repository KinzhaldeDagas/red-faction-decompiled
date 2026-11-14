// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005FF090 rf_jpeg_free_pool
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jmemmgr.c:free_pool matched): Cdecl(cinfo,poolID),requiresunsignedpoolID<2 elseerror14. Forimagepool1:walksvirtualsample/blocklists68/72,clearsbackingopen40 BEFOREcallingclose callbackdescriptor56(cinfo,&backing48),thenNULLseachlist. Detaches/freeslargechunks60/64 first viajpeg_free_large(cinfo,chunk,size),then small52/56viafree_small;size=header.used4+left8+12,subtractsfromtotal76. Retainsmemorymanager84bytesandotherpool. No individualobjectdestructors,FILEdestinationcloseorstate20resethere;voidAPI.
_DWORD *__cdecl rf_jpeg_free_pool(_DWORD *cinfo, unsigned int a2)
{
  _DWORD *result; // eax
  _DWORD *v3; // [esp+0h] [ebp-20h]
  _DWORD *v4; // [esp+4h] [ebp-1Ch]
  int j; // [esp+8h] [ebp-18h]
  int i; // [esp+Ch] [ebp-14h]
  _DWORD *v7; // [esp+10h] [ebp-10h]
  _DWORD *Block; // [esp+14h] [ebp-Ch]
  _DWORD *object; // [esp+18h] [ebp-8h]
  int bytes; // [esp+1Ch] [ebp-4h]
  int bytesa; // [esp+1Ch] [ebp-4h]

  v7 = (_DWORD *)cinfo[1];
  if ( a2 >= 2 )
  {
    *(_DWORD *)(*cinfo + 20) = 14;
    *(_DWORD *)(*cinfo + 24) = a2;
    (*(void (__cdecl **)(_DWORD *))*cinfo)(cinfo);
  }
  if ( a2 == 1 )
  {
    for ( i = v7[17]; i; i = *(_DWORD *)(i + 44) )
    {
      if ( *(_DWORD *)(i + 40) )
      {
        *(_DWORD *)(i + 40) = 0;
        (*(void (__cdecl **)(_DWORD *, int))(i + 56))(cinfo, i + 48);
      }
    }
    v7[17] = 0;
    for ( j = v7[18]; j; j = *(_DWORD *)(j + 44) )
    {
      if ( *(_DWORD *)(j + 40) )
      {
        *(_DWORD *)(j + 40) = 0;
        (*(void (__cdecl **)(_DWORD *, int))(j + 56))(cinfo, j + 48);
      }
    }
    v7[18] = 0;
  }
  object = (_DWORD *)v7[a2 + 15];
  v7[a2 + 15] = 0;
  while ( object )
  {
    v4 = (_DWORD *)*object;
    bytes = object[1] + object[2] + 12;
    rf_jpeg_free_large(cinfo, object, bytes);
    v7[19] -= bytes;
    object = v4;
  }
  result = (_DWORD *)v7[a2 + 13];
  Block = result;
  v7[a2 + 13] = 0;
  while ( Block )
  {
    v3 = (_DWORD *)*Block;
    bytesa = Block[1] + Block[2] + 12;
    rf_jpeg_free_small(cinfo, Block, bytesa);
    result = v7;
    v7[19] -= bytesa;
    Block = v3;
  }
  return result;
}

