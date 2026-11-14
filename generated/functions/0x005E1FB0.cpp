// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005E1FB0 rf_d3d8_upload_texture_level_convert_to_u16
// UNREALRED VERIFIED [texture-conversion-20261028]: Tenarguments mipindex,sourcepixels,palette,sourcewidth,sourceheight,sourceformat,tile32-byterectrecord,allocatedW,H,GPUtexture. Locksselectedlevel via vtable+64,anynonzeroHRESULTreturns-1; queriesleveldesc+56withoutcheckingresult. DestinationGPUformats20/21/22 use8-bitRGBshifts16/8/0,alpha16or24;23usesRGB565;24/25usesRGB555/alpha1;26/30usesRGBA4444. UnsupportedGPUformatfataldiagnostic gr_direct3d_texture.cpp559. ALLdestinationstoresare16-bit andadvance2bytes/pixel,evenwhenformatselectorlists24/32-bitformats; widerpackedbitsaretruncated. Sourcecode1paletted8 builds256-entry16-bitlookupfromRGBpalette,opaquealpha;2bytealpha writeswhiteRGB andgamma-LUTalpha;3RGB565,4ARGB4444,5ARGB1555,6BGR24,7BGRA32convert channelsbyintegerdivision/scaling;8copiesraw16-bitpixels. Formats1/3/4/5/6/7/8 startsourceat
// tilex/y+16/+20,copylogicaltileW/H+24/+28withoutresampling,thenzeropadallocatedright/bottom. Fixed16.16increments1pixel; sourceheightunused. Source2insteadloopsfullallocatedW/H,ignoringtileorigin/extentandpadding,using sourcewidthrowstride. Unknownsourceformat performsnowrites butstillunlocksandreturns0. IgnoresunlockHRESULT; no sourcebounds,palette,rect<=allocation,finite ordestinationbytes/pixelguards. Returns0afterconversion,notbyteswritten.
int __cdecl rf_d3d8_upload_texture_level_convert_to_u16(
        int a1,
        int a2,
        int a3,
        int a4,
        int a5,
        int a6,
        _DWORD *a7,
        int a8,
        int a9,
        int a10)
{
  int i21; // [esp+10h] [ebp-3FCh]
  int i24; // [esp+10h] [ebp-3FCh]
  int v13; // [esp+14h] [ebp-3F8h]
  _WORD *v14; // [esp+1Ch] [ebp-3F0h]
  _WORD *v15; // [esp+1Ch] [ebp-3F0h]
  int v16; // [esp+20h] [ebp-3ECh]
  int i22; // [esp+28h] [ebp-3E4h]
  int i23; // [esp+28h] [ebp-3E4h]
  int i25; // [esp+28h] [ebp-3E4h]
  int v20; // [esp+2Ch] [ebp-3E0h]
  int i16; // [esp+3Ch] [ebp-3D0h]
  int i19; // [esp+3Ch] [ebp-3D0h]
  int v23; // [esp+44h] [ebp-3C8h]
  _WORD *v24; // [esp+54h] [ebp-3B8h]
  _WORD *v25; // [esp+54h] [ebp-3B8h]
  int v26; // [esp+58h] [ebp-3B4h]
  int i17; // [esp+60h] [ebp-3ACh]
  int i18; // [esp+60h] [ebp-3ACh]
  int i20; // [esp+60h] [ebp-3ACh]
  int v30; // [esp+68h] [ebp-3A4h]
  int i11; // [esp+78h] [ebp-394h]
  int i14; // [esp+78h] [ebp-394h]
  int v33; // [esp+80h] [ebp-38Ch]
  _WORD *v34; // [esp+90h] [ebp-37Ch]
  _WORD *v35; // [esp+90h] [ebp-37Ch]
  int v36; // [esp+94h] [ebp-378h]
  int i12; // [esp+9Ch] [ebp-370h]
  int i13; // [esp+9Ch] [ebp-370h]
  int i15; // [esp+9Ch] [ebp-370h]
  int v40; // [esp+A4h] [ebp-368h]
  _WORD *v41; // [esp+B0h] [ebp-35Ch]
  int i6; // [esp+B4h] [ebp-358h]
  int i9; // [esp+B4h] [ebp-358h]
  int v44; // [esp+BCh] [ebp-350h]
  _WORD *v45; // [esp+CCh] [ebp-340h]
  _WORD *v46; // [esp+CCh] [ebp-340h]
  int v47; // [esp+D0h] [ebp-33Ch]
  int i7; // [esp+D8h] [ebp-334h]
  int i8; // [esp+D8h] [ebp-334h]
  int i10; // [esp+D8h] [ebp-334h]
  int v51; // [esp+DCh] [ebp-330h]
  int v52; // [esp+E0h] [ebp-32Ch]
  int i1; // [esp+F0h] [ebp-31Ch]
  int i4; // [esp+F0h] [ebp-31Ch]
  int v55; // [esp+F8h] [ebp-314h]
  _WORD *v56; // [esp+108h] [ebp-304h]
  _WORD *v57; // [esp+108h] [ebp-304h]
  int v58; // [esp+10Ch] [ebp-300h]
  int i2; // [esp+114h] [ebp-2F8h]
  int i3; // [esp+114h] [ebp-2F8h]
  int i5; // [esp+114h] [ebp-2F8h]
  int v62; // [esp+11Ch] [ebp-2F0h]
  int ii; // [esp+12Ch] [ebp-2E0h]
  int mm; // [esp+12Ch] [ebp-2E0h]
  int v65; // [esp+134h] [ebp-2D8h]
  _WORD *v66; // [esp+144h] [ebp-2C8h]
  _WORD *v67; // [esp+144h] [ebp-2C8h]
  int v68; // [esp+148h] [ebp-2C4h]
  int jj; // [esp+150h] [ebp-2BCh]
  int kk; // [esp+150h] [ebp-2BCh]
  int nn; // [esp+150h] [ebp-2BCh]
  int v72; // [esp+158h] [ebp-2B4h]
  _WORD *v73; // [esp+15Ch] [ebp-2B0h]
  _WORD *v74; // [esp+16Ch] [ebp-2A0h]
  int m; // [esp+170h] [ebp-29Ch]
  int n; // [esp+170h] [ebp-29Ch]
  _WORD v77[258]; // [esp+174h] [ebp-298h]
  int v78; // [esp+37Ch] [ebp-90h]
  int v79; // [esp+380h] [ebp-8Ch]
  int v80; // [esp+384h] [ebp-88h]
  int v81; // [esp+388h] [ebp-84h]
  int v82; // [esp+38Ch] [ebp-80h]
  int v83; // [esp+390h] [ebp-7Ch]
  int v84; // [esp+394h] [ebp-78h]
  int k; // [esp+398h] [ebp-74h]
  int v86; // [esp+39Ch] [ebp-70h]
  int v87; // [esp+3A0h] [ebp-6Ch]
  _WORD *v88; // [esp+3A4h] [ebp-68h]
  int i; // [esp+3A8h] [ebp-64h]
  int v90; // [esp+3ACh] [ebp-60h]
  int v91; // [esp+3B0h] [ebp-5Ch]
  int v92; // [esp+3B4h] [ebp-58h]
  int j; // [esp+3B8h] [ebp-54h]
  int v94; // [esp+3BCh] [ebp-50h]
  int v95; // [esp+3C0h] [ebp-4Ch]
  int v96; // [esp+3C4h] [ebp-48h]
  int v97; // [esp+3C8h] [ebp-44h]
  int v98; // [esp+3CCh] [ebp-40h]
  int v100[8]; // [esp+3D4h] [ebp-38h] BYREF
  int v101; // [esp+3F4h] [ebp-18h]
  int v102; // [esp+3F8h] [ebp-14h]
  int v103; // [esp+3FCh] [ebp-10h]
  int v104; // [esp+400h] [ebp-Ch]
  int v105; // [esp+404h] [ebp-8h] BYREF
  int v106; // [esp+408h] [ebp-4h]

  if ( (*(int (__thiscall **)(int, int, int, int *, _DWORD, _DWORD))(*(_DWORD *)a10 + 64))(a10, a10, a1, &v105, 0, 0) )
    return -1;
  (*(void (__stdcall **)(int, int, int *))(*(_DWORD *)a10 + 56))(a10, a1, v100);
  v104 = 0;
  v103 = 0;
  v95 = 0;
  v96 = 0;
  v97 = 0;
  v102 = 0;
  v98 = 16;
  v101 = 1;
  switch ( v100[0] )
  {
    case 0x14:
      goto LABEL_5;
    case 0x15:
    case 0x16:
      v98 = 24;
      v101 = 1;
LABEL_5:
      v102 = 1;
      v96 = 1;
      v103 = 1;
      v104 = 16;
      v95 = 8;
      v97 = 0;
      break;
    case 0x17:
      v104 = 11;
      v95 = 5;
      v97 = 0;
      v102 = 8;
      v103 = 8;
      v96 = 4;
      break;
    case 0x18:
    case 0x19:
      v98 = 15;
      v104 = 10;
      v95 = 5;
      v97 = 0;
      v101 = 255;
      v102 = 8;
      v96 = 8;
      v103 = 8;
      break;
    case 0x1A:
    case 0x1E:
      v98 = 12;
      v104 = 8;
      v95 = 4;
      v97 = 0;
      v102 = 17;
      v96 = 17;
      v103 = 17;
      v101 = 17;
      break;
    default:
      rf_fatal_error_show_message_and_exit(
        "D:\\projects\\rf_pc\\vsdk\\gr\\directx\\gr_direct3d_texture.cpp",
        559,
        "Unsupported texture format found.");
  }
  switch ( a6 )
  {
    case 2:
      for ( i = 0; i < a9; ++i )
      {
        v88 = (_WORD *)(v106 + i * v105);
        for ( j = 0; j < a8; ++j )
        {
          v90 = 255 / v103;
          v91 = 255 / v96;
          v92 = 255 / v102;
          v94 = rf_graphics_gamma_lut_u32[*(unsigned __int8 *)(a2 + j + a4 * i)] / v101;
          *v88++ = ((255 / v102) << v97) | ((255 / v96) << v95) | ((255 / v103) << v104) | ((_WORD)v94 << v98);
        }
      }
      break;
    case 1:
      for ( k = 0; k < 256; ++k )
      {
        v78 = *(unsigned __int8 *)(a3 + 3 * k);
        v81 = *(unsigned __int8 *)(a3 + 3 * k + 1);
        v82 = *(unsigned __int8 *)(a3 + 3 * k + 2);
        v78 /= v103;
        v81 /= v96;
        v82 /= v102;
        v86 = 255 / v101;
        v77[k] = ((_WORD)v82 << v97) | ((_WORD)v81 << v95) | ((_WORD)v78 << v104) | ((255 / v101) << v98);
      }
      v83 = a7[4] << 16;
      v87 = a7[5] << 16;
      v80 = 0x10000;
      v84 = 0x10000;
      for ( m = 0; m < a7[7]; ++m )
      {
        v74 = (_WORD *)(v106 + m * v105);
        v79 = v83;
        for ( k = 0; k < a7[6]; ++k )
        {
          *v74++ = v77[*(unsigned __int8 *)(a2 + v79 / 0x10000 + a4 * (v87 / 0x10000))];
          v79 += v80;
        }
        for ( k = a7[6]; k < a8; ++k )
          *v74++ = 0;
        v87 += v84;
      }
      for ( n = a7[7]; n < a9; ++n )
      {
        v73 = (_WORD *)(v106 + n * v105);
        for ( k = 0; k < a8; ++k )
          *v73++ = 0;
      }
      break;
    case 6:
      v68 = a7[4] << 16;
      v72 = a7[5] << 16;
      for ( ii = 0; ii < a7[7]; ++ii )
      {
        v66 = (_WORD *)(v106 + ii * v105);
        v65 = v68;
        for ( jj = 0; jj < a7[6]; ++jj )
        {
          *v66++ = ((*(unsigned __int8 *)(a2 + 3 * (v65 / 0x10000 + a4 * (v72 / 0x10000))) / v102) << v97)
                 | ((*(unsigned __int8 *)(a2 + 3 * (v65 / 0x10000 + a4 * (v72 / 0x10000)) + 1) / v96) << v95)
                 | ((*(unsigned __int8 *)(a2 + 3 * (v65 / 0x10000 + a4 * (v72 / 0x10000)) + 2) / v103) << v104)
                 | ((255 / v101) << v98);
          v65 += 0x10000;
        }
        for ( kk = a7[6]; kk < a8; ++kk )
          *v66++ = 0;
        v72 += 0x10000;
      }
      for ( mm = a7[7]; mm < a9; ++mm )
      {
        v67 = (_WORD *)(v106 + mm * v105);
        for ( nn = 0; nn < a8; ++nn )
          *v67++ = 0;
      }
      break;
    case 4:
      v58 = a7[4] << 16;
      v62 = a7[5] << 16;
      for ( i1 = 0; i1 < a7[7]; ++i1 )
      {
        v56 = (_WORD *)(v106 + i1 * v105);
        v55 = v58;
        for ( i2 = 0; i2 < a7[6]; ++i2 )
        {
          *v56++ = ((255 * (*(_WORD *)(a2 + 2 * (v55 / 0x10000 + a4 * (v62 / 0x10000))) & 0xF) / 15 / v102) << v97)
                 | ((255
                   * (((int)*(unsigned __int16 *)(a2 + 2 * (v55 / 0x10000 + a4 * (v62 / 0x10000))) >> 4) & 0xF)
                   / 15
                   / v96) << v95)
                 | ((255
                   * (((int)*(unsigned __int16 *)(a2 + 2 * (v55 / 0x10000 + a4 * (v62 / 0x10000))) >> 8) & 0xF)
                   / 15
                   / v103) << v104)
                 | ((255
                   * (((int)*(unsigned __int16 *)(a2 + 2 * (v55 / 0x10000 + a4 * (v62 / 0x10000))) >> 12) & 0xF)
                   / 15
                   / v101) << v98);
          v55 += 0x10000;
        }
        for ( i3 = a7[6]; i3 < a8; ++i3 )
          *v56++ = 0;
        v62 += 0x10000;
      }
      for ( i4 = a7[7]; i4 < a9; ++i4 )
      {
        v57 = (_WORD *)(v106 + i4 * v105);
        for ( i5 = 0; i5 < a8; ++i5 )
          *v57++ = 0;
      }
      break;
    case 5:
      v47 = a7[4] << 16;
      v52 = a7[5] << 16;
      for ( i6 = 0; i6 < a7[7]; ++i6 )
      {
        v45 = (_WORD *)(v106 + i6 * v105);
        v44 = v47;
        for ( i7 = 0; i7 < a7[6]; ++i7 )
        {
          if ( (*(_WORD *)(a2 + 2 * (v44 / 0x10000 + a4 * (v52 / 0x10000))) & 0x8000) != 0 )
            v51 = 255;
          else
            v51 = 0;
          v41 = (_WORD *)(a2 + 2 * (v44 / 0x10000 + a4 * (v52 / 0x10000)));
          *v45++ = ((255 * (*v41 & 0x1F) / 31 / v102) << v97)
                 | ((255 * (((int)(unsigned __int16)*v41 >> 5) & 0x1F) / 31 / v96) << v95)
                 | ((255 * (((int)(unsigned __int16)*v41 >> 10) & 0x1F) / 31 / v103) << v104)
                 | ((v51 / v101) << v98);
          v44 += 0x10000;
        }
        for ( i8 = a7[6]; i8 < a8; ++i8 )
          *v45++ = 0;
        v52 += 0x10000;
      }
      for ( i9 = a7[7]; i9 < a9; ++i9 )
      {
        v46 = (_WORD *)(v106 + i9 * v105);
        for ( i10 = 0; i10 < a8; ++i10 )
          *v46++ = 0;
      }
      break;
    case 3:
      v36 = a7[4] << 16;
      v40 = a7[5] << 16;
      for ( i11 = 0; i11 < a7[7]; ++i11 )
      {
        v34 = (_WORD *)(v106 + i11 * v105);
        v33 = v36;
        for ( i12 = 0; i12 < a7[6]; ++i12 )
        {
          *v34++ = ((255 * (*(_WORD *)(a2 + 2 * (v33 / 0x10000 + a4 * (v40 / 0x10000))) & 0x1F) / 31 / v102) << v97)
                 | ((255
                   * (((int)*(unsigned __int16 *)(a2 + 2 * (v33 / 0x10000 + a4 * (v40 / 0x10000))) >> 5) & 0x3F)
                   / 63
                   / v96) << v95)
                 | ((255
                   * (((int)*(unsigned __int16 *)(a2 + 2 * (v33 / 0x10000 + a4 * (v40 / 0x10000))) >> 11) & 0x1F)
                   / 31
                   / v103) << v104)
                 | ((255 / v101) << v98);
          v33 += 0x10000;
        }
        for ( i13 = a7[6]; i13 < a8; ++i13 )
          *v34++ = 0;
        v40 += 0x10000;
      }
      for ( i14 = a7[7]; i14 < a9; ++i14 )
      {
        v35 = (_WORD *)(v106 + i14 * v105);
        for ( i15 = 0; i15 < a8; ++i15 )
          *v35++ = 0;
      }
      break;
    case 7:
      v26 = a7[4] << 16;
      v30 = a7[5] << 16;
      for ( i16 = 0; i16 < a7[7]; ++i16 )
      {
        v24 = (_WORD *)(v106 + i16 * v105);
        v23 = v26;
        for ( i17 = 0; i17 < a7[6]; ++i17 )
        {
          *v24++ = ((*(unsigned __int8 *)(a2 + 4 * (v23 / 0x10000 + a4 * (v30 / 0x10000))) / v102) << v97)
                 | ((*(unsigned __int8 *)(a2 + 4 * (v23 / 0x10000 + a4 * (v30 / 0x10000)) + 1) / v96) << v95)
                 | ((*(unsigned __int8 *)(a2 + 4 * (v23 / 0x10000 + a4 * (v30 / 0x10000)) + 2) / v103) << v104)
                 | ((*(unsigned __int8 *)(a2 + 4 * (v23 / 0x10000 + a4 * (v30 / 0x10000)) + 3) / v101) << v98);
          v23 += 0x10000;
        }
        for ( i18 = a7[6]; i18 < a8; ++i18 )
          *v24++ = 0;
        v30 += 0x10000;
      }
      for ( i19 = a7[7]; i19 < a9; ++i19 )
      {
        v25 = (_WORD *)(v106 + i19 * v105);
        for ( i20 = 0; i20 < a8; ++i20 )
          *v25++ = 0;
      }
      break;
    case 8:
      v16 = a7[4] << 16;
      v20 = a7[5] << 16;
      for ( i21 = 0; i21 < a7[7]; ++i21 )
      {
        v14 = (_WORD *)(v106 + i21 * v105);
        v13 = v16;
        for ( i22 = 0; i22 < a7[6]; ++i22 )
        {
          *v14++ = *(_WORD *)(a2 + 2 * (v13 / 0x10000 + a4 * (v20 / 0x10000)));
          v13 += 0x10000;
        }
        for ( i23 = a7[6]; i23 < a8; ++i23 )
          *v14++ = 0;
        v20 += 0x10000;
      }
      for ( i24 = a7[7]; i24 < a9; ++i24 )
      {
        v15 = (_WORD *)(v106 + i24 * v105);
        for ( i25 = 0; i25 < a8; ++i25 )
          *v15++ = 0;
      }
      break;
  }
  (*(void (__stdcall **)(int, int))(*(_DWORD *)a10 + 68))(a10, a1);
  return 0;
}

