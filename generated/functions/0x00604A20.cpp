// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00604A20 rf_jpeg_jinit_c_master_control
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jcmaster.c:jinit_c_master_control matched): void cdecl(cinfo, transcodeOnly). Allocates a 36-byte pool-1 master at cinfo+328, installs prepare/startup/finish callbacks and runs initial_setup. Assembly pushes all THREE allocator arguments and stores returned EAX at [ebp-4] (0x604A39); pseudocode showing an uninitialized master or one-argument stdcall allocator is incorrect. scan_info != NULL raises error 48 because custom scans are not compiled in. Otherwise progressive_mode=FALSE and num_scans=1. Normal pass starts at main (0); transcode starts at Huffman optimization (1) if optimize_coding, else output (2). Pass and scan counters start at zero; total passes is num_scans times one or two.
void __cdecl rf_jpeg_jinit_c_master_control(void *cinfo, int transcode_only)
{
  BOOL (__cdecl **v2)(int); // eax
  _DWORD *v3; // [esp+0h] [ebp-4h]

  v2 = (BOOL (__cdecl **)(int))(**((int (__stdcall ***)(void *))cinfo + 1))(cinfo);
  *((_DWORD *)cinfo + 82) = v2;
  *v2 = rf_jpeg_master_prepare_for_pass;
  v2[1] = rf_jpeg_master_pass_startup;
  v2[2] = (BOOL (__cdecl *)(int))rf_jpeg_master_finish_pass;
  v2[4] = nullptr;
  rf_jpeg_master_initial_setup(cinfo);
  if ( *((_DWORD *)cinfo + 42) )
  {
    *(_DWORD *)(*(_DWORD *)cinfo + 20) = 48;
    (**(void (__cdecl ***)(void *))cinfo)(cinfo);
  }
  else
  {
    *((_DWORD *)cinfo + 56) = 0;
    *((_DWORD *)cinfo + 41) = 1;
  }
  if ( *((_DWORD *)cinfo + 56) )
    *((_DWORD *)cinfo + 45) = 1;
  if ( transcode_only )
  {
    if ( *((_DWORD *)cinfo + 45) )
      v3[5] = 1;
    else
      v3[5] = 2;
  }
  else
  {
    v3[5] = 0;
  }
  v3[8] = 0;
  v3[6] = 0;
  if ( *((_DWORD *)cinfo + 45) )
    v3[7] = 2 * *((_DWORD *)cinfo + 41);
  else
    v3[7] = *((_DWORD *)cinfo + 41);
}

