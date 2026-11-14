// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00600410 rf_jpeg_jinit_c_main_controller
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jcmainct.c:jinit_c_main_controller matched): Allocates64-byteimagepool1maincontroller,cinfo.main332=it,start_pass0=6004E0. Ifraw_data_in172!=0,returnswithoutstripbuffers(rawinputbypassesmain). Else need_full_bufferTRUE fatal4 BadBufferMode (full-imagepreprocessedbuffersnotcompiled);FALSEallocatesone samplearraypercomponent:width=8*width_in_blocks28,height=8*v_samp_factor12,storesptrsatmain24+4*i. Doesnotinitializepasscountersuntilstartpassorconsumeinput.
_DWORD *__cdecl rf_jpeg_jinit_c_main_controller(_DWORD *a1, int a2)
{
  _DWORD *result; // eax
  _DWORD *v3; // [esp+0h] [ebp-Ch]
  int v4; // [esp+4h] [ebp-8h]
  int i; // [esp+8h] [ebp-4h]

  result = (_DWORD *)(*(int (__cdecl **)(_DWORD *, int, int))a1[1])(a1, 1, 64);
  v3 = result;
  a1[83] = result;
  *result = rf_jpeg_main_start_pass;
  if ( !a1[43] )
  {
    if ( a2 )
    {
      *(_DWORD *)(*a1 + 20) = 4;
      return (*(_DWORD *(__cdecl **)(_DWORD *))*a1)(a1);
    }
    else
    {
      v4 = 0;
      for ( i = a1[16]; ; i += 84 )
      {
        result = a1;
        if ( v4 >= a1[14] )
          break;
        v3[v4++ + 6] = (*(int (__cdecl **)(_DWORD *, int, int, int))(a1[1] + 8))(
                         a1,
                         1,
                         8 * *(_DWORD *)(i + 28),
                         8 * *(_DWORD *)(i + 12));
      }
    }
  }
  return result;
}

