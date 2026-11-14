// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00600670 rf_jpeg_jinit_c_coef_controller
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jccoefct.c:jinit_c_coef_controller matched): Allocates104-byteimagepool1coefcontroller,cinfo.coef340=it,start_pass0=600790. Ifneed_full_bufferTRUE,foreachcomponent requestsvirtualblockarraypreZeroFALSE,widthblocksroundedtoh_samp,heightblocksroundedtov_samp,maxaccess=v_samp;storeswhole_imageptr64+4*i. Elseallocates1280bytesfor10contiguous128-byteJBLOCKs,setsMCU_bufferptr24+4*j,setswhole_image[0]64=NULLsentinel. Othercounter/processfieldsinitializedstartpass. No immediateDCTorvirtualrealizehere;dimensionvalidityassumedfrommaster.
int __cdecl rf_jpeg_jinit_c_coef_controller(int a1, int a2)
{
  int result; // eax
  int v3; // eax
  int v4; // [esp-8h] [ebp-1Ch]
  int v5; // [esp-4h] [ebp-18h]
  int v6; // [esp+0h] [ebp-14h]
  int j; // [esp+4h] [ebp-10h]
  int v8; // [esp+8h] [ebp-Ch]
  int *i; // [esp+Ch] [ebp-8h]
  _DWORD *v10; // [esp+10h] [ebp-4h]

  v10 = (_DWORD *)(**(int (__cdecl ***)(int, int, int))(a1 + 4))(a1, 1, 104);
  *(_DWORD *)(a1 + 340) = v10;
  *v10 = rf_jpeg_coef_start_pass;
  if ( a2 )
  {
    v8 = 0;
    for ( i = *(int **)(a1 + 64); ; i += 21 )
    {
      result = v8;
      if ( v8 >= *(_DWORD *)(a1 + 56) )
        break;
      v5 = i[3];
      v4 = rf_jpeg_jround_up(i[8], v5);
      v3 = rf_jpeg_jround_up(i[7], i[2]);
      v10[v8++ + 16] = (*(int (__cdecl **)(int, int, _DWORD, int, int, int))(*(_DWORD *)(a1 + 4) + 20))(
                         a1,
                         1,
                         0,
                         v3,
                         v4,
                         v5);
    }
  }
  else
  {
    result = (*(int (__cdecl **)(int, int, int))(*(_DWORD *)(a1 + 4) + 4))(a1, 1, 1280);
    v6 = result;
    for ( j = 0; j < 10; ++j )
    {
      result = j;
      v10[j + 6] = v6 + (j << 7);
    }
    v10[16] = 0;
  }
  return result;
}

