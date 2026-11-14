// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00605570 rf_jpeg_master_finish_pass
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jcmaster.c:finish_pass_master matched): Finishes the entropy pass, then advances master state. Main (0) becomes output (2), incrementing scan_number only when not optimizing. Huffman optimization (1) becomes output without advancing the scan. Output (2) becomes optimization (1) when optimizing, then always increments scan_number. Every path increments pass_number. Header trailer and memory cleanup occur elsewhere.
_DWORD *__cdecl rf_jpeg_master_finish_pass(_DWORD *a1)
{
  int v2; // [esp+0h] [ebp-8h]
  _DWORD *v3; // [esp+4h] [ebp-4h]

  v3 = (_DWORD *)a1[82];
  (*(void (__cdecl **)(_DWORD *))(a1[90] + 8))(a1);
  v2 = v3[5];
  if ( v2 )
  {
    if ( v2 == 1 )
    {
      v3[5] = 2;
    }
    else if ( v2 == 2 )
    {
      if ( a1[45] )
        v3[5] = 1;
      ++v3[8];
    }
  }
  else
  {
    v3[5] = 2;
    if ( !a1[45] )
      ++v3[8];
  }
  ++v3[6];
  return v3;
}

