// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005FE710 rf_jpeg_realize_virt_arrays
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jmemmgr.c:realize_virt_arrays matched): Forpending sample/block descriptors(buffer0NULL),sumsminimum=rowBytes*maxAccess andmaximum=rowBytes*totalRows (rowBytes=items8,oritems8*128forblocks). Ifminimum<=0 returnswithoutrealizing. Callsjpeg_mem_available(cinfo,min,max,manager.total76),FOUR cdeclarguments verified0x5FE7D8..7EA despitepreviousSTLlabel/three-argprototype. Ifavailable<max,minheights=max(available/min,1),else1000000000. Perdescriptor,ifceil(totalRows/maxAccess)>minheights,rowsInMemory=maxAccess*minheights andrequestsbackingstore,setsopen40=1;elsefullrows. Allocatesrowarrayviaalloc_sarray/barray,setsrowsPerChunk20=manager80,start24=0,firstUndefined28=0,dirty36=0. ThisRFplatformjpeg_mem_availablealwaysreturnsmax,sonormalvalidrequestsusefullRAM;open_backing_storefatals49. No overflow/synchronization
// guard.
_DWORD *__cdecl rf_jpeg_realize_virt_arrays(_DWORD *cinfo)
{
  _DWORD *result; // eax
  _DWORD *v2; // [esp+0h] [ebp-20h]
  _DWORD *j; // [esp+4h] [ebp-1Ch]
  int *m; // [esp+4h] [ebp-1Ch]
  int v5; // [esp+8h] [ebp-18h]
  _DWORD *i; // [esp+Ch] [ebp-14h]
  int *k; // [esp+Ch] [ebp-14h]
  _DWORD *max_bytes; // [esp+10h] [ebp-10h]
  int min_bytes; // [esp+14h] [ebp-Ch]
  int v10; // [esp+1Ch] [ebp-4h]

  v2 = (_DWORD *)cinfo[1];
  min_bytes = 0;
  max_bytes = nullptr;
  result = (_DWORD *)v2[17];
  for ( i = result; i; i = (_DWORD *)i[11] )
  {
    result = i;
    if ( !*i )
    {
      min_bytes += i[2] * i[3];
      result = (_DWORD *)((char *)max_bytes + i[2] * i[1]);
      max_bytes = result;
    }
  }
  for ( j = (_DWORD *)v2[18]; j; j = (_DWORD *)j[11] )
  {
    if ( !*j )
    {
      min_bytes += (j[2] * j[3]) << 7;
      max_bytes += 32 * j[2] * j[1];
    }
    result = j;
  }
  if ( min_bytes > 0 )
  {
    v5 = rf_jpeg_mem_available(cinfo, min_bytes, (int)max_bytes, v2[19]);
    if ( v5 < (int)max_bytes )
    {
      v10 = v5 / min_bytes;
      if ( v5 / min_bytes <= 0 )
        v10 = 1;
    }
    else
    {
      v10 = 1000000000;
    }
    for ( k = (int *)v2[17]; k; k = (int *)k[11] )
    {
      if ( !*k )
      {
        if ( (int)((k[1] - 1) / (unsigned int)k[3] + 1) > v10 )
        {
          k[4] = k[3] * v10;
          rf_jpeg_open_backing_store(cinfo, k + 12, k[2] * k[1]);
          k[10] = 1;
        }
        else
        {
          k[4] = k[1];
        }
        *k = rf_jpeg_alloc_sarray(cinfo, 1u, k[2], k[4]);
        k[5] = v2[20];
        k[6] = 0;
        k[7] = 0;
        k[9] = 0;
      }
    }
    result = v2;
    for ( m = (int *)v2[18]; m; m = result )
    {
      if ( !*m )
      {
        if ( (int)((m[1] - 1) / (unsigned int)m[3] + 1) > v10 )
        {
          m[4] = m[3] * v10;
          rf_jpeg_open_backing_store(cinfo, m + 12, (m[2] * m[1]) << 7);
          m[10] = 1;
        }
        else
        {
          m[4] = m[1];
        }
        *m = rf_jpeg_alloc_barray(cinfo, 1u, m[2], m[4]);
        m[5] = v2[20];
        m[6] = 0;
        m[7] = 0;
        m[9] = 0;
      }
      result = (_DWORD *)m[11];
    }
  }
  return result;
}

