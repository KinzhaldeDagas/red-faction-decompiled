// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005FDE80 rf_jpeg_jinit_memory_mgr
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jmemmgr.c:jinit_memory_mgr matched): Clearscinfo.mem4;calls platformjpeg_mem_init0x6002F0,allocates84-bytemanager viajpeg_get_small0x600230. Allocationfailurecallsplatformmem_term0x600300 thenfatal54,param0. Installs11callbacks small/large/samplearray/blockarray,virtualrequests/realize/access,poolfree,selfdestruct atoffset0..40;max_alloc_chunk48=1000000000,max_memory_to_use44=platformlimit. Clears2smallpoolheads52/56,2largepoolheads60/64,virtual lists68/72;total_space_allocated76=84. Storesmanagerincinfo.mem. OptionalJPEGMEM env parsed%ld%c;defaultunitk,Mc ormc multiplies1000 extra,thenalways*1000bytes(decimal). No explicitpositive/overflowcheckonenv. Binaryv6bdoublealignment8verifiedbystructureoffsets;noapplicationbufferallocationhere.
char *__cdecl rf_jpeg_jinit_memory_mgr(_DWORD *cinfo)
{
  char *result; // eax
  char v2; // [esp+3h] [ebp-15h] BYREF
  char *Buffer; // [esp+4h] [ebp-14h]
  int i; // [esp+8h] [ebp-10h]
  char *small; // [esp+Ch] [ebp-Ch]
  int v6; // [esp+10h] [ebp-8h]
  int v7; // [esp+14h] [ebp-4h] BYREF

  cinfo[1] = 0;
  v6 = 1000000000;
  v7 = rf_jpeg_mem_init(cinfo);
  small = (char *)rf_jpeg_get_small(cinfo, 0x54u);
  if ( !small )
  {
    rf_jpeg_mem_term(cinfo);
    *(_DWORD *)(*cinfo + 20) = 54;
    *(_DWORD *)(*cinfo + 24) = 0;
    (*(void (__cdecl **)(_DWORD *))*cinfo)(cinfo);
  }
  *(_DWORD *)small = rf_jpeg_alloc_small;
  *((_DWORD *)small + 1) = rf_jpeg_alloc_large;
  *((_DWORD *)small + 2) = rf_jpeg_alloc_sarray;
  *((_DWORD *)small + 3) = rf_jpeg_alloc_barray;
  *((_DWORD *)small + 4) = rf_jpeg_request_virt_sarray;
  *((_DWORD *)small + 5) = rf_jpeg_request_virt_barray;
  *((_DWORD *)small + 6) = rf_jpeg_realize_virt_arrays;
  *((_DWORD *)small + 7) = rf_jpeg_access_virt_sarray;
  *((_DWORD *)small + 8) = rf_jpeg_access_virt_barray;
  *((_DWORD *)small + 9) = rf_jpeg_free_pool;
  *((_DWORD *)small + 10) = rf_jpeg_memory_self_destruct;
  *((_DWORD *)small + 12) = 1000000000;
  *((_DWORD *)small + 11) = v7;
  for ( i = 1; i >= 0; --i )
  {
    *(_DWORD *)&small[4 * i + 52] = 0;
    *(_DWORD *)&small[4 * i + 60] = 0;
  }
  *((_DWORD *)small + 17) = 0;
  *((_DWORD *)small + 18) = 0;
  *((_DWORD *)small + 19) = 84;
  cinfo[1] = small;
  result = getenv("JPEGMEM");
  Buffer = result;
  if ( result )
  {
    v2 = 120;
    result = (char *)sscanf(Buffer, "%ld%c", &v7, &v2);
    if ( (int)result > 0 )
    {
      if ( v2 == 109 || v2 == 77 )
        v7 *= 1000;
      result = small;
      *((_DWORD *)small + 11) = 1000 * v7;
    }
  }
  return result;
}

