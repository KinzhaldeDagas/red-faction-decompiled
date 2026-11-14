// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00602B90 rf_jpeg_jinit_c_prep_controller
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jcprepct.c:jinit_c_prep_controller matched): Initializes the compression preprocessing controller. need_full_buffer != 0 raises error 4. Allocates a 64-byte pool-1 object at cinfo+336, with start_pass at +0 and process_data at +4. Selects context processing when downsample+8 requests context rows; otherwise allocates per-component color buffers of width max_h*8*width_in_blocks/h_samp and height max_v. State: +48 rows_to_go, +52 next_buf_row, +56 this_row_group, +60 next_buf_stop.
int __cdecl rf_jpeg_jinit_c_prep_controller(int a1, int a2)
{
  int result; // eax
  _DWORD *v3; // [esp+0h] [ebp-Ch]
  int v4; // [esp+4h] [ebp-8h]
  int v5; // [esp+8h] [ebp-4h]

  if ( a2 )
  {
    *(_DWORD *)(*(_DWORD *)a1 + 20) = 4;
    (**(void (__cdecl ***)(int))a1)(a1);
  }
  v3 = (_DWORD *)(**(int (__cdecl ***)(int, int, int))(a1 + 4))(a1, 1, 64);
  *(_DWORD *)(a1 + 336) = v3;
  *v3 = rf_jpeg_prep_start_pass;
  if ( *(_DWORD *)(*(_DWORD *)(a1 + 352) + 8) )
  {
    v3[1] = rf_jpeg_prep_pre_process_context;
    return rf_jpeg_prep_create_context_buffer(a1);
  }
  else
  {
    v3[1] = rf_jpeg_prep_pre_process_data;
    v4 = 0;
    result = a1;
    v5 = *(_DWORD *)(a1 + 64);
    while ( v4 < *(_DWORD *)(a1 + 56) )
    {
      v3[v4++ + 2] = (*(int (__cdecl **)(int, int, int, _DWORD))(*(_DWORD *)(a1 + 4) + 8))(
                       a1,
                       1,
                       *(_DWORD *)(a1 + 228) * 8 * *(_DWORD *)(v5 + 28) / *(_DWORD *)(v5 + 8),
                       *(_DWORD *)(a1 + 232));
      result = v5 + 84;
      v5 += 84;
    }
  }
  return result;
}

