// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00576790 rf_bitmap_load_tga_cpu_pixels_and_mips_by_slot
// UNREALRED VERIFIED [bitmap-decoders-20261028]: Argument bitmap slot INDEX. Applies global reduction mode; maps stored mode0/1/2 to source mip skip0/1/2, other modes retain-1. Auto generation requires globals0x663F11 and0x189744C; otherwise caps skipped level by external-mip byte66-1. Allocates temporary original-size buffer only when desired skip>=external mip count, then pixel block bytes/pixel*current mip-chain pixelcount and optional768-byte palette. Only temporary allocation checked. Name stem strips last dot. If current mipcount byte64<=1, calls0x5E03F0 and returns0 on decode error without freeing allocated record buffers/temp. Multi-mip loop uses original mipcount byte65, external count byte66 and auto-generation flag. Loads base or stem-mipN.tga through0x5E0B50 until external levels exhausted; ignores these decoder return values. Skips unneeded higher levels, reads last needed
// source into temporary when generating reduced base. Generated formats3/5 use integer channel averages from previous level; format6 averages four source BGR pixels; format7 averages BGRA and forces perimeter alpha to previous level first pixel alpha. Other formats fill generated level bytes255. IMPORTANT observed16-bit inconsistencies: format3 loops 2*destination dimensions in steps2 but advances source pointer only one source row per outer iteration; no extra row skip. Format5 loops destination dimensions themselves in steps2, producing fewer pixels, and shifts averaged source red field to bit11 rather than bit10. Do not interpret as correct generic downsampling. Dimensions halve and clamp>=1; non-square final1x1 copies one previous pixel instead of generated value. Frees temporary only normal success, returns1. No record bounds, mip-chain capacity, first previous-level initialization or
// broad allocation/failure guards.
char __cdecl rf_bitmap_load_tga_cpu_pixels_and_mips_by_slot(int a1)
{
  char v2; // [esp+7h] [ebp-92Dh]
  char *v3; // [esp+Ch] [ebp-928h]
  char *v4; // [esp+10h] [ebp-924h]
  char v5; // [esp+17h] [ebp-91Dh]
  char *v6; // [esp+1Ch] [ebp-918h]
  char *v7; // [esp+20h] [ebp-914h]
  int v8; // [esp+24h] [ebp-910h]
  bool v9; // [esp+28h] [ebp-90Ch]
  unsigned __int16 *v10; // [esp+3Ch] [ebp-8F8h]
  int i2; // [esp+40h] [ebp-8F4h]
  int v12; // [esp+44h] [ebp-8F0h]
  _BYTE *v13; // [esp+48h] [ebp-8ECh]
  int v14; // [esp+50h] [ebp-8E4h]
  int v15; // [esp+54h] [ebp-8E0h]
  int v16; // [esp+58h] [ebp-8DCh]
  char *v17; // [esp+60h] [ebp-8D4h]
  char *v18; // [esp+64h] [ebp-8D0h]
  _BYTE *v19; // [esp+68h] [ebp-8CCh]
  int mm; // [esp+6Ch] [ebp-8C8h]
  int nn; // [esp+6Ch] [ebp-8C8h]
  int kk; // [esp+70h] [ebp-8C4h]
  int i1; // [esp+70h] [ebp-8C4h]
  _BYTE *v24; // [esp+74h] [ebp-8C0h]
  char *v25; // [esp+78h] [ebp-8BCh]
  char v26; // [esp+7Fh] [ebp-8B5h]
  int v27; // [esp+88h] [ebp-8ACh]
  int v28; // [esp+8Ch] [ebp-8A8h]
  int jj; // [esp+90h] [ebp-8A4h]
  int ii; // [esp+94h] [ebp-8A0h]
  _BYTE *v31; // [esp+98h] [ebp-89Ch]
  unsigned __int16 *v32; // [esp+A8h] [ebp-88Ch]
  int n; // [esp+ACh] [ebp-888h]
  int m; // [esp+B0h] [ebp-884h]
  _WORD *v35; // [esp+B4h] [ebp-880h]
  unsigned __int16 *v36; // [esp+C4h] [ebp-870h]
  int k; // [esp+C8h] [ebp-86Ch]
  int j; // [esp+CCh] [ebp-868h]
  _WORD *v39; // [esp+D0h] [ebp-864h]
  int v40; // [esp+D4h] [ebp-860h]
  int v41; // [esp+D8h] [ebp-85Ch]
  int v42; // [esp+E0h] [ebp-854h] BYREF
  int v43; // [esp+E4h] [ebp-850h] BYREF
  int v44; // [esp+E8h] [ebp-84Ch] BYREF
  int v45; // [esp+ECh] [ebp-848h]
  bool v46; // [esp+F3h] [ebp-841h]
  char Buffer[1028]; // [esp+F4h] [ebp-840h] BYREF
  int v48; // [esp+4F8h] [ebp-43Ch]
  int v49; // [esp+4FCh] [ebp-438h]
  int v50; // [esp+500h] [ebp-434h]
  unsigned __int8 v51; // [esp+507h] [ebp-42Dh]
  int v52; // [esp+508h] [ebp-42Ch]
  void *v53; // [esp+50Ch] [ebp-428h]
  int v54; // [esp+510h] [ebp-424h]
  char Str[1024]; // [esp+514h] [ebp-420h] BYREF
  unsigned __int16 *v56; // [esp+918h] [ebp-1Ch]
  char *v57; // [esp+91Ch] [ebp-18h]
  bool v58; // [esp+923h] [ebp-11h]
  void *v59; // [esp+924h] [ebp-10h]
  int i; // [esp+928h] [ebp-Ch]
  int v61; // [esp+92Ch] [ebp-8h]
  char *first_character; // [esp+930h] [ebp-4h]

  v57 = (char *)(dword_1897344 + 108 * a1);
  v59 = nullptr;
  v9 = byte_663F11 && unk_189744C;
  v58 = v9;
  v52 = -1;
  rf_bitmap_set_slot_reduction_mode(*((_DWORD *)v57 + 9), dword_1897454);
  v8 = *((_DWORD *)v57 + 26);
  if ( v8 )
  {
    if ( v8 == 1 )
    {
      v52 = 1;
    }
    else if ( v8 == 2 )
    {
      v52 = 2;
    }
  }
  else
  {
    v52 = 0;
  }
  if ( !v58 )
    v52 = rf_int_min_signed(v52, (unsigned __int8)v57[66] - 1);
  v61 = rf_bitmap_format_bytes_per_pixel(*((_DWORD *)v57 + 15));
  if ( v52 >= (unsigned __int8)v57[66] )
  {
    v59 = operator new(v61 * *((unsigned __int16 *)v57 + 21) * *((unsigned __int16 *)v57 + 20));
    if ( !v59 )
      return 0;
  }
  *((_DWORD *)v57 + 18) = operator new(v61 * *((_DWORD *)v57 + 12));
  if ( *((_DWORD *)v57 + 15) == 1 )
    *((_DWORD *)v57 + 20) = operator new(0x300u);
  v53 = nullptr;
  v56 = nullptr;
  v54 = *((_DWORD *)v57 + 20);
  v51 = 0;
  v7 = v57;
  v6 = Str;
  do
  {
    v5 = *v7;
    *v6++ = *v7++;
  }
  while ( v5 );
  first_character = rf_cstring_find_first_character(Str, 46);
  if ( first_character )
    *first_character = 0;
  if ( (unsigned __int8)v57[64] > 1u )
  {
    v48 = 0;
    v50 = rf_bitmap_format_bytes_per_pixel(*((_DWORD *)v57 + 15));
    v45 = *((unsigned __int16 *)v57 + 20);
    v49 = *((unsigned __int16 *)v57 + 21);
    v46 = *((unsigned __int16 *)v57 + 20) != *((unsigned __int16 *)v57 + 21);
    for ( i = 0; ; ++i )
    {
      if ( i >= (unsigned __int8)v57[65] || i >= (unsigned __int8)v57[66] && !v58 )
        goto LABEL_87;
      if ( i >= v52 )
      {
        if ( i == v52 )
          v53 = *((void **)v57 + 18);
      }
      else
      {
        if ( i + 1 < (unsigned __int8)v57[66] )
        {
          v45 /= 2;
          v49 /= 2;
          v45 = rf_int_max(1, v45);
          v49 = rf_int_max(1, v49);
          continue;
        }
        v53 = v59;
      }
      if ( i >= (unsigned __int8)v57[66] )
      {
        v41 = 2 * v45;
        v40 = 2 * v49;
        switch ( *((_DWORD *)v57 + 15) )
        {
          case 3:
            v36 = v56;
            v39 = v53;
            for ( j = 0; j < v40; j += 2 )
            {
              for ( k = 0; k < v41; k += 2 )
              {
                *v39++ = (((v36[v41 + 1] & 0x1F) + (v36[v41] & 0x1F) + (v36[1] & 0x1F) + (*v36 & 0x1F)) / 4)
                       | (32
                        * (((((int)v36[v41 + 1] >> 5) & 0x3F)
                          + (((int)v36[v41] >> 5) & 0x3F)
                          + (((int)v36[1] >> 5) & 0x3F)
                          + (((int)*v36 >> 5) & 0x3F))
                         / 4))
                       | ((unsigned __int16)(((((int)v36[v41 + 1] >> 11) & 0x1F)
                                            + (((int)v36[v41] >> 11) & 0x1F)
                                            + (((int)v36[1] >> 11) & 0x1F)
                                            + (((int)*v36 >> 11) & 0x1F))
                                           / 4) << 11);
                v36 += 2;
              }
            }
            break;
          case 5:
            v32 = v56;
            v35 = v53;
            for ( m = 0; m < v49; m += 2 )
            {
              for ( n = 0; n < v45; n += 2 )
              {
                *v35++ = (((v32[v41 + 1] & 0x1F) + (v32[v41] & 0x1F) + (v32[1] & 0x1F) + (*v32 & 0x1F)) / 4)
                       | (32
                        * (((((int)v32[v41 + 1] >> 5) & 0x1F)
                          + (((int)v32[v41] >> 5) & 0x1F)
                          + (((int)v32[1] >> 5) & 0x1F)
                          + (((int)*v32 >> 5) & 0x1F))
                         / 4))
                       | ((unsigned __int16)(((((int)v32[v41 + 1] >> 10) & 0x1F)
                                            + (((int)v32[v41] >> 10) & 0x1F)
                                            + (((int)v32[1] >> 10) & 0x1F)
                                            + (((int)*v32 >> 10) & 0x1F))
                                           / 4) << 11);
                v32 += 2;
              }
            }
            break;
          case 6:
            v31 = v53;
            for ( ii = 0; ii < v49; ++ii )
            {
              for ( jj = 0; jj < v45; ++jj )
              {
                v27 = (*((unsigned __int8 *)&v56[3 * jj + 2 + 3 * v41 / 2u] + 2 * ii * 3 * v41)
                     + *((unsigned __int8 *)&v56[3 * jj + 3 * v41 / 2u] + 2 * ii * 3 * v41 + 1)
                     + *((unsigned __int8 *)&v56[3 * jj + 2] + 2 * ii * 3 * v41)
                     + *((unsigned __int8 *)&v56[3 * jj] + 2 * ii * 3 * v41 + 1))
                    / 4;
                v28 = (*((unsigned __int8 *)&v56[3 * jj + 2 + 3 * v41 / 2u] + 2 * ii * 3 * v41 + 1)
                     + *((unsigned __int8 *)&v56[3 * jj + 1 + 3 * v41 / 2u] + 2 * ii * 3 * v41)
                     + *((unsigned __int8 *)&v56[3 * jj + 2] + 2 * ii * 3 * v41 + 1)
                     + *((unsigned __int8 *)&v56[3 * jj + 1] + 2 * ii * 3 * v41))
                    / 4;
                *v31 = (*((unsigned __int8 *)&v56[3 * jj + 1 + 3 * v41 / 2u] + 2 * ii * 3 * v41 + 1)
                      + *((unsigned __int8 *)&v56[3 * jj + 3 * v41 / 2u] + 2 * ii * 3 * v41)
                      + *((unsigned __int8 *)&v56[3 * jj + 1] + 2 * ii * 3 * v41 + 1)
                      + *((unsigned __int8 *)&v56[3 * jj] + 2 * ii * 3 * v41))
                     / 4;
                v31[1] = v27;
                v31[2] = v28;
                v31 += 3;
              }
            }
            break;
          case 7:
            v24 = v53;
            for ( kk = 0; kk < v49; ++kk )
            {
              for ( mm = 0; mm < v45; ++mm )
              {
                v14 = (*((unsigned __int8 *)&v56[4 * mm + 3 + 2 * v41] + 2 * kk * 4 * v41)
                     + *((unsigned __int8 *)&v56[4 * mm + 1 + 2 * v41] + 2 * kk * 4 * v41)
                     + *((unsigned __int8 *)&v56[4 * mm + 3] + 2 * kk * 4 * v41)
                     + *((unsigned __int8 *)&v56[4 * mm + 1] + 2 * kk * 4 * v41))
                    / 4;
                v15 = (*((unsigned __int8 *)&v56[4 * mm + 2 + 2 * v41] + 2 * kk * 4 * v41 + 1)
                     + *((unsigned __int8 *)&v56[4 * mm + 2 * v41] + 2 * kk * 4 * v41 + 1)
                     + *((unsigned __int8 *)&v56[4 * mm + 2] + 2 * kk * 4 * v41 + 1)
                     + *((unsigned __int8 *)&v56[4 * mm] + 2 * kk * 4 * v41 + 1))
                    / 4;
                v16 = (*((unsigned __int8 *)&v56[4 * mm + 2 + 2 * v41] + 2 * kk * 4 * v41)
                     + *((unsigned __int8 *)&v56[4 * mm + 2 * v41] + 2 * kk * 4 * v41)
                     + *((unsigned __int8 *)&v56[4 * mm + 2] + 2 * kk * 4 * v41)
                     + *((unsigned __int8 *)&v56[4 * mm] + 2 * kk * 4 * v41))
                    / 4;
                v24[3] = (*((unsigned __int8 *)&v56[4 * mm + 3 + 2 * v41] + 2 * kk * 4 * v41 + 1)
                        + *((unsigned __int8 *)&v56[4 * mm + 1 + 2 * v41] + 2 * kk * 4 * v41 + 1)
                        + *((unsigned __int8 *)&v56[4 * mm + 3] + 2 * kk * 4 * v41 + 1)
                        + *((unsigned __int8 *)&v56[4 * mm + 1] + 2 * kk * 4 * v41 + 1))
                       / 4;
                v24[2] = v14;
                v24[1] = v15;
                *v24 = v16;
                v24 += 4;
              }
            }
            v26 = *((_BYTE *)v56 + 3);
            v17 = (char *)v53;
            v25 = (char *)v53 + 4 * v45 * (v49 - 1);
            for ( nn = 0; nn < v45; ++nn )
            {
              v17[3] = v26;
              v25[3] = v26;
              v17 += 4;
              v25 += 4;
            }
            v19 = v53;
            v18 = (char *)v53 + 4 * v45 - 4;
            for ( i1 = 0; i1 < v49; ++i1 )
            {
              v19[3] = v26;
              v18[3] = v26;
              v19 += 4 * v45;
              v18 += 4 * v45;
            }
            break;
          default:
            memset(v53, 255, v50 * v49 * v45);
            break;
        }
      }
      else
      {
        if ( i )
        {
          sprintf(Buffer, "%s-mip%d.tga", Str, i);
        }
        else
        {
          v4 = v57;
          v3 = Buffer;
          do
          {
            v2 = *v4;
            *v3++ = *v4++;
          }
          while ( v2 );
        }
        rf_tga_read_pixels_palette_report_dimensions(Buffer, (int)v53, &v43, &v42, &v44, v54, v51, *((void **)v57 + 25));
        v51 = 1;
        ++v48;
      }
      if ( v45 == 1 && v49 == 1 && v46 )
      {
        v12 = rf_bitmap_format_bytes_per_pixel(*((_DWORD *)v57 + 15));
        v10 = v56;
        v13 = v53;
        for ( i2 = 0; i2 < v12; ++i2 )
        {
          *v13++ = *(_BYTE *)v10;
          v10 = (unsigned __int16 *)((char *)v10 + 1);
        }
      }
      v56 = (unsigned __int16 *)v53;
      v53 = (char *)v53 + v50 * v49 * v45;
      v45 /= 2;
      v49 /= 2;
      v45 = rf_int_max(1, v45);
      v49 = rf_int_max(1, v49);
    }
  }
  v53 = *((void **)v57 + 18);
  v54 = *((_DWORD *)v57 + 20);
  if ( rf_tga_read_pixels_palette(v57, (int)v53, v54, 0, *((void **)v57 + 25)) )
    return 0;
LABEL_87:
  if ( v59 )
    operator delete(v59);
  return 1;
}

