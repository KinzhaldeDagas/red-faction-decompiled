// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00604020 rf_jpeg_jinit_color_converter
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jccolor.c:jinit_color_converter matched): Initializes the 12-byte color converter at cinfo+348. Validates input component count (error 9) and output count (error 10). Gray output accepts gray/YCbCr by copying the first channel or RGB through luminance tables. RGB and CMYK output require matching input. YCbCr accepts RGB conversion or matching YCbCr; YCCK accepts CMYK conversion or matching YCCK. Other enums require exact input/output enum and count agreement. Unsupported conversions raise error 27. Matching formats use deinterleaving, not a no-op.
void (__cdecl **__cdecl rf_jpeg_jinit_color_converter(int a1))(void *cinfo)
{
  void (__cdecl **result)(void *); // eax
  void (__cdecl **v2)(void *); // [esp+8h] [ebp-4h]

  v2 = (void (__cdecl **)(void *))(**(int (__cdecl ***)(int, int, int))(a1 + 4))(a1, 1, 12);
  *(_DWORD *)(a1 + 348) = v2;
  *v2 = rf_jpeg_color_null_start_pass;
  switch ( *(_DWORD *)(a1 + 40) )
  {
    case 1:
      if ( *(_DWORD *)(a1 + 36) != 1 )
      {
        *(_DWORD *)(*(_DWORD *)a1 + 20) = 9;
        (**(void (__cdecl ***)(int))a1)(a1);
      }
      break;
    case 2:
    case 3:
      if ( *(_DWORD *)(a1 + 36) != 3 )
      {
        *(_DWORD *)(*(_DWORD *)a1 + 20) = 9;
        (**(void (__cdecl ***)(int))a1)(a1);
      }
      break;
    case 4:
    case 5:
      if ( *(_DWORD *)(a1 + 36) != 4 )
      {
        *(_DWORD *)(*(_DWORD *)a1 + 20) = 9;
        (**(void (__cdecl ***)(int))a1)(a1);
      }
      break;
    default:
      if ( *(int *)(a1 + 36) < 1 )
      {
        *(_DWORD *)(*(_DWORD *)a1 + 20) = 9;
        (**(void (__cdecl ***)(int))a1)(a1);
      }
      break;
  }
  result = (void (__cdecl **)(void *))(*(_DWORD *)(a1 + 60) - 1);
  switch ( *(_DWORD *)(a1 + 60) )
  {
    case 1:
      if ( *(_DWORD *)(a1 + 56) != 1 )
      {
        *(_DWORD *)(*(_DWORD *)a1 + 20) = 10;
        result = (void (__cdecl **)(void *))(**(int (__cdecl ***)(int))a1)(a1);
      }
      switch ( *(_DWORD *)(a1 + 40) )
      {
        case 1:
          v2[1] = (void (__cdecl *)(void *))rf_jpeg_color_grayscale_convert;
          result = v2;
          break;
        case 2:
          *v2 = (void (__cdecl *)(void *))rf_jpeg_color_rgb_ycc_start;
          v2[1] = (void (__cdecl *)(void *))rf_jpeg_color_rgb_gray_convert;
          result = v2;
          break;
        case 3:
          v2[1] = (void (__cdecl *)(void *))rf_jpeg_color_grayscale_convert;
          break;
        default:
          goto LABEL_46;
      }
      break;
    case 2:
      if ( *(_DWORD *)(a1 + 56) != 3 )
      {
        *(_DWORD *)(*(_DWORD *)a1 + 20) = 10;
        (**(void (__cdecl ***)(int))a1)(a1);
      }
      if ( *(_DWORD *)(a1 + 40) != 2 )
        goto LABEL_46;
      v2[1] = (void (__cdecl *)(void *))rf_jpeg_color_null_convert;
      result = v2;
      break;
    case 3:
      if ( *(_DWORD *)(a1 + 56) != 3 )
      {
        *(_DWORD *)(*(_DWORD *)a1 + 20) = 10;
        (**(void (__cdecl ***)(int))a1)(a1);
      }
      if ( *(_DWORD *)(a1 + 40) == 2 )
      {
        *v2 = (void (__cdecl *)(void *))rf_jpeg_color_rgb_ycc_start;
        v2[1] = (void (__cdecl *)(void *))rf_jpeg_color_rgb_ycc_convert;
        result = v2;
      }
      else
      {
        if ( *(_DWORD *)(a1 + 40) != 3 )
          goto LABEL_46;
        v2[1] = (void (__cdecl *)(void *))rf_jpeg_color_null_convert;
        result = v2;
      }
      break;
    case 4:
      if ( *(_DWORD *)(a1 + 56) != 4 )
      {
        *(_DWORD *)(*(_DWORD *)a1 + 20) = 10;
        (**(void (__cdecl ***)(int))a1)(a1);
      }
      if ( *(_DWORD *)(a1 + 40) != 4 )
        goto LABEL_46;
      v2[1] = (void (__cdecl *)(void *))rf_jpeg_color_null_convert;
      result = v2;
      break;
    case 5:
      if ( *(_DWORD *)(a1 + 56) != 4 )
      {
        *(_DWORD *)(*(_DWORD *)a1 + 20) = 10;
        (**(void (__cdecl ***)(int))a1)(a1);
      }
      if ( *(_DWORD *)(a1 + 40) == 4 )
      {
        *v2 = (void (__cdecl *)(void *))rf_jpeg_color_rgb_ycc_start;
        v2[1] = (void (__cdecl *)(void *))rf_jpeg_color_cmyk_ycck_convert;
        result = v2;
      }
      else if ( *(_DWORD *)(a1 + 40) == 5 )
      {
        v2[1] = (void (__cdecl *)(void *))rf_jpeg_color_null_convert;
        result = v2;
      }
      else
      {
LABEL_46:
        *(_DWORD *)(*(_DWORD *)a1 + 20) = 27;
        result = (void (__cdecl **)(void *))(**(int (__cdecl ***)(int))a1)(a1);
      }
      break;
    default:
      if ( *(_DWORD *)(a1 + 60) != *(_DWORD *)(a1 + 40)
        || (result = *(void (__cdecl ***)(void *))(a1 + 56), result != *(void (__cdecl ***)(void *))(a1 + 36)) )
      {
        *(_DWORD *)(*(_DWORD *)a1 + 20) = 27;
        result = (void (__cdecl **)(void *))(**(int (__cdecl ***)(int))a1)(a1);
      }
      v2[1] = (void (__cdecl *)(void *))rf_jpeg_color_null_convert;
      break;
  }
  return result;
}

