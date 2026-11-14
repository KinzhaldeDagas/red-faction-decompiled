// IDA pseudocode evidence; not yet portable or build-ready.
// 0x006031E0 rf_jpeg_prep_create_context_buffer
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jcprepct.c:create_context_buffer matched): Allocates 5*max_v row pointers per component and 3*max_v actual sample rows. Middle pointer groups address the actual rows; the leading group aliases the last actual group and the trailing group aliases the first. Stores a pointer shifted past the leading margin, permitting negative context row indices. Sample width is max_h*8*width_in_blocks/h_samp. Pixels are initialized later by preprocessing.
int __cdecl rf_jpeg_prep_create_context_buffer(int a1)
{
  int result; // eax
  int v2; // [esp+4h] [ebp-1Ch]
  int v3; // [esp+8h] [ebp-18h]
  int v4; // [esp+Ch] [ebp-14h]
  int v5; // [esp+10h] [ebp-10h]
  int i; // [esp+14h] [ebp-Ch]
  int j; // [esp+18h] [ebp-8h]
  void *Src; // [esp+1Ch] [ebp-4h]

  v2 = *(_DWORD *)(a1 + 336);
  v3 = *(_DWORD *)(a1 + 232);
  v4 = (**(int (__cdecl ***)(int, int, int))(a1 + 4))(a1, 1, 4 * v3 * 5 * *(_DWORD *)(a1 + 56));
  v5 = 0;
  for ( i = *(_DWORD *)(a1 + 64); ; i += 84 )
  {
    result = v5;
    if ( v5 >= *(_DWORD *)(a1 + 56) )
      break;
    Src = (void *)(*(int (__cdecl **)(int, int, int, int))(*(_DWORD *)(a1 + 4) + 8))(
                    a1,
                    1,
                    *(_DWORD *)(a1 + 228) * 8 * *(_DWORD *)(i + 28) / *(_DWORD *)(i + 8),
                    3 * v3);
    memcpy((void *)(v4 + 4 * v3), Src, 12 * v3);
    for ( j = 0; j < v3; ++j )
    {
      *(_DWORD *)(v4 + 4 * j) = *((_DWORD *)Src + 2 * v3 + j);
      *(_DWORD *)(v4 + 4 * (j + 4 * v3)) = *((_DWORD *)Src + j);
    }
    *(_DWORD *)(v2 + 4 * v5 + 8) = v4 + 4 * v3;
    v4 += 20 * v3;
    ++v5;
  }
  return result;
}

