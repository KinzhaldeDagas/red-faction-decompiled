// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00603330 rf_jpeg_jinit_downsampler
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jcsample.c:jinit_downsampler matched): Initializes the 52-byte downsampler at cinfo+352. Method pointers begin at +12; +8 is need_context_rows. CCIR601_sampling raises error 25. Chooses full-size, h2v1, h2v2, or generic integer-ratio methods; fractional ratios raise error 38. Smoothing selects the full-size or h2v2 smooth method and requests context rows. Unsupported smoothing for other ratios retains the ordinary method and emits trace 99 at level 0; supported components may still be smoothed.
int __cdecl rf_jpeg_jinit_downsampler(_DWORD *a1)
{
  int result; // eax
  void (__cdecl **v2)(void *); // [esp+0h] [ebp-10h]
  int v3; // [esp+4h] [ebp-Ch]
  int v4; // [esp+8h] [ebp-8h]
  int i; // [esp+Ch] [ebp-4h]

  v3 = 1;
  v2 = (void (__cdecl **)(void *))(*(int (__cdecl **)(_DWORD *, int, int))a1[1])(a1, 1, 52);
  a1[88] = v2;
  *v2 = rf_jpeg_downsample_start_pass;
  v2[1] = (void (__cdecl *)(void *))rf_jpeg_downsample_dispatch_components;
  v2[2] = nullptr;
  if ( a1[46] )
  {
    *(_DWORD *)(*a1 + 20) = 25;
    (*(void (__cdecl **)(_DWORD *))*a1)(a1);
  }
  v4 = 0;
  for ( i = a1[16]; ; i += 84 )
  {
    result = v4;
    if ( v4 >= a1[14] )
      break;
    if ( *(_DWORD *)(i + 8) == a1[57] && *(_DWORD *)(i + 12) == a1[58] )
    {
      if ( a1[47] )
      {
        v2[v4 + 3] = (void (__cdecl *)(void *))rf_jpeg_downsample_fullsize_smooth;
        v2[2] = (void (__cdecl *)(void *))1;
      }
      else
      {
        v2[v4 + 3] = (void (__cdecl *)(void *))rf_jpeg_downsample_fullsize;
      }
    }
    else if ( 2 * *(_DWORD *)(i + 8) == a1[57] && *(_DWORD *)(i + 12) == a1[58] )
    {
      v3 = 0;
      v2[v4 + 3] = (void (__cdecl *)(void *))rf_jpeg_downsample_h2v1;
    }
    else if ( 2 * *(_DWORD *)(i + 8) == a1[57] && 2 * *(_DWORD *)(i + 12) == a1[58] )
    {
      if ( a1[47] )
      {
        v2[v4 + 3] = (void (__cdecl *)(void *))rf_jpeg_downsample_h2v2_smooth;
        v2[2] = (void (__cdecl *)(void *))1;
      }
      else
      {
        v2[v4 + 3] = (void (__cdecl *)(void *))rf_jpeg_downsample_h2v2;
      }
    }
    else if ( a1[57] % *(_DWORD *)(i + 8) || a1[58] % *(_DWORD *)(i + 12) )
    {
      *(_DWORD *)(*a1 + 20) = 38;
      (*(void (__cdecl **)(_DWORD *))*a1)(a1);
    }
    else
    {
      v3 = 0;
      v2[v4 + 3] = (void (__cdecl *)(void *))rf_jpeg_downsample_integer_box;
    }
    ++v4;
  }
  if ( a1[47] && !v3 )
  {
    *(_DWORD *)(*a1 + 20) = 99;
    return (*(int (__cdecl **)(_DWORD *, _DWORD))(*a1 + 4))(a1, 0);
  }
  return result;
}

