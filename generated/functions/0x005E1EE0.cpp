// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005E1EE0 rf_d3d8_create_texture_for_bitmap_format
// UNREALRED VERIFIED [texture-upload-20261028]: Fivearguments internalformat,width,height,miplevels,outputtexturepointer. Devicevtable+80 CreateTexture(width,height,levels,usage0,selectedGPUformat,pool1,out). Internal1/2/4/7 selectglobal0x1DAED84;3/6 select0x1DAE900;5 selects0x1DAE8F4. Unsupportedformat leaveslocalformatuninitialized beforecall. Returns0 ONLYifHRESULT==0 AND*outnonnull,otherwise-1. No outputzeroing,dimension/caps checks orcleanupfornonnullfailureoutput.
int __cdecl rf_d3d8_create_texture_for_bitmap_format(int a1, int a2, int a3, int a4, _DWORD *a5)
{
  int v5; // eax
  int v7; // [esp+0h] [ebp-8h]

  if ( a1 == 2 || a1 == 1 )
    goto LABEL_10;
  if ( a1 == 6 || a1 == 3 )
  {
    v5 = (*(int (__stdcall **)(int, int, int, int, _DWORD, _DWORD, int, _DWORD *))(*(_DWORD *)dword_1DAEDC4 + 80))(
           dword_1DAEDC4,
           a2,
           a3,
           a4,
           0,
           unk_1DAE900,
           1,
           a5);
  }
  else
  {
    switch ( a1 )
    {
      case 5:
        v5 = (*(int (__stdcall **)(int, int, int, int, _DWORD, _DWORD, int, _DWORD *))(*(_DWORD *)dword_1DAEDC4 + 80))(
               dword_1DAEDC4,
               a2,
               a3,
               a4,
               0,
               unk_1DAE8F4,
               1,
               a5);
        goto LABEL_14;
      case 7:
LABEL_10:
        v5 = (*(int (__stdcall **)(int, int, int, int, _DWORD, _DWORD, int, _DWORD *))(*(_DWORD *)dword_1DAEDC4 + 80))(
               dword_1DAEDC4,
               a2,
               a3,
               a4,
               0,
               unk_1DAED84,
               1,
               a5);
        goto LABEL_14;
      case 4:
        v7 = unk_1DAED84;
        break;
    }
    v5 = (*(int (__stdcall **)(int, int, int, int, _DWORD, int, int, _DWORD *))(*(_DWORD *)dword_1DAEDC4 + 80))(
           dword_1DAEDC4,
           a2,
           a3,
           a4,
           0,
           v7,
           1,
           a5);
  }
LABEL_14:
  if ( !v5 && *a5 )
    return 0;
  else
    return -1;
}

