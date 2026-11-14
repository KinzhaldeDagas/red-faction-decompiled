// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00602C90 rf_jpeg_prep_start_pass
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jcprepct.c:start_pass_prep matched): Accepts only JBUF_PASS_THRU (0); other modes raise error 4. Initializes rows_to_go to image_height, next_buf_row and this_row_group to zero, and next_buf_stop to 2*max_v. Shared by ordinary and context preprocessing.
_DWORD *__cdecl rf_jpeg_prep_start_pass(_DWORD *a1, int a2)
{
  _DWORD *v3; // [esp+0h] [ebp-4h]

  v3 = (_DWORD *)a1[84];
  if ( a2 )
  {
    *(_DWORD *)(*a1 + 20) = 4;
    (*(void (__cdecl **)(_DWORD *))*a1)(a1);
  }
  v3[12] = a1[8];
  v3[13] = 0;
  v3[14] = 0;
  v3[15] = 2 * a1[58];
  return v3;
}

