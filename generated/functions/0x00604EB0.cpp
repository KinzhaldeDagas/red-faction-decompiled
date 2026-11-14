// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00604EB0 rf_jpeg_master_prepare_for_pass
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jcmaster.c:prepare_for_pass matched): Prepares the compression pass. Main (0): select scan and MCU layout; unless raw input, start color/downsampling/prep; start FDCT, entropy with gather=optimize_coding, coefficient controller in SAVE_AND_PASS (3) for multiple passes or PASS_THRU (0), and main controller. Defers header startup when not optimizing. Huffman optimization (1): normally starts entropy gathering and coefficient CRANK_DEST (2). The non-arithmetic DC-refinement special case skips gathering and falls into output after incrementing pass_number. Output (2): starts entropy without gathering and coefficient CRANK_DEST, writes frame header only for scan zero, then scan header. Other pass kinds raise error 48. Sets is_last_pass and progress completed/total counters.
BOOL __cdecl rf_jpeg_master_prepare_for_pass(int a1)
{
  BOOL result; // eax
  int v2; // [esp+0h] [ebp-8h]
  _DWORD *v3; // [esp+4h] [ebp-4h]

  v3 = *(_DWORD **)(a1 + 328);
  v2 = v3[5];
  if ( v2 )
  {
    if ( v2 == 1 )
    {
      rf_jpeg_master_select_scan_parameters((_DWORD *)a1);
      rf_jpeg_master_per_scan_setup((_DWORD *)a1);
      if ( *(_DWORD *)(a1 + 312) || !*(_DWORD *)(a1 + 320) || *(_DWORD *)(a1 + 176) )
      {
        (**(void (__cdecl ***)(int, int))(a1 + 360))(a1, 1);
        (**(void (__cdecl ***)(int, int))(a1 + 340))(a1, 2);
        v3[3] = 0;
        goto LABEL_20;
      }
      v3[5] = 2;
      ++v3[6];
    }
    else if ( v2 != 2 )
    {
      *(_DWORD *)(*(_DWORD *)a1 + 20) = 48;
      (**(void (__cdecl ***)(int))a1)(a1);
      goto LABEL_20;
    }
    if ( !*(_DWORD *)(a1 + 180) )
    {
      rf_jpeg_master_select_scan_parameters((_DWORD *)a1);
      rf_jpeg_master_per_scan_setup((_DWORD *)a1);
    }
    (**(void (__cdecl ***)(int, _DWORD))(a1 + 360))(a1, 0);
    (**(void (__cdecl ***)(int, int))(a1 + 340))(a1, 2);
    if ( !v3[8] )
      (*(void (__cdecl **)(int))(*(_DWORD *)(a1 + 344) + 4))(a1);
    (*(void (__cdecl **)(int))(*(_DWORD *)(a1 + 344) + 8))(a1);
    v3[3] = 0;
  }
  else
  {
    rf_jpeg_master_select_scan_parameters((_DWORD *)a1);
    rf_jpeg_master_per_scan_setup((_DWORD *)a1);
    if ( !*(_DWORD *)(a1 + 172) )
    {
      (**(void (__cdecl ***)(int))(a1 + 348))(a1);
      (**(void (__cdecl ***)(int))(a1 + 352))(a1);
      (**(void (__cdecl ***)(int, _DWORD))(a1 + 336))(a1, 0);
    }
    (**(void (__cdecl ***)(int))(a1 + 356))(a1);
    (**(void (__cdecl ***)(int, _DWORD))(a1 + 360))(a1, *(_DWORD *)(a1 + 180));
    (**(void (__cdecl ***)(int, int))(a1 + 340))(a1, v3[7] <= 1 ? 0 : 3);
    (**(void (__cdecl ***)(int, _DWORD))(a1 + 332))(a1, 0);
    if ( *(_DWORD *)(a1 + 180) )
      v3[3] = 0;
    else
      v3[3] = 1;
  }
LABEL_20:
  result = v3[6] == v3[7] - 1;
  v3[4] = result;
  if ( *(_DWORD *)(a1 + 8) )
  {
    *(_DWORD *)(*(_DWORD *)(a1 + 8) + 12) = v3[6];
    *(_DWORD *)(*(_DWORD *)(a1 + 8) + 16) = v3[7];
    return (BOOL)v3;
  }
  return result;
}

