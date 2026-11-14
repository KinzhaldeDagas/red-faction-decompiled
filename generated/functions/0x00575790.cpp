// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00575790 rf_bitmap_probe_header_by_file_type
// UNREALRED VERIFIED [bitmap-loading-20261028]: Eleven arguments name,width,height,format,mipcount,external-mip-count,framecount,rate,stored-size,extra-field,source context. Initializes mipcount1,external count1,rate0,framecount1,stored-size-1,extra1; width,height,format not universally initialized. Type from0x5756A0. PCX uses0x5E6210 header reader; error fatal bmpman.cpp972,format1. TGA uses0x5DFF80; error returns0; bitdepth8/16/24/32 maps1/5/6/7,unknown0. TGA auto-mips require globals0x663F11 and0x189744C, power-of-two bit tests and dimensions<=256; repeatedly halves with min1 until both1, incrementing mipcount. Does not explicitly reject zero dimensions, which pass power-of-two bit test. With0x663F10 enabled also probes stem-mipN.tga files, accepting only expected halved dimensions and same bitdepth; limits generated name length40, stops first mismatch/missing. USERBMAP type3 returns
// without further output population. VAF loads VANI metadata through temporary player, maps bitdepth16->format3 (different from TGA), returns0 on load failure. VBM delegates0x573F20. M2V reads dimensions/file size0x5E5E40,requires positive size,format5. Unknown type fatal bmpman.cpp1152. Returns file type, not normalized boolean; no pixel decoding or comprehensive header validation.
int __cdecl rf_bitmap_probe_header_by_file_type(
        char *a1,
        int *a2,
        int *a3,
        _DWORD *a4,
        _DWORD *a5,
        _DWORD *a6,
        int *a7,
        int *a8,
        int *a9,
        int *a10,
        void *a11)
{
  const char *v11; // eax
  const char *v12; // eax
  char v14; // [esp+1Bh] [ebp-5FDh]
  char *v15; // [esp+20h] [ebp-5F8h]
  char *v16; // [esp+24h] [ebp-5F4h]
  char v17[256]; // [esp+34h] [ebp-5E4h] BYREF
  char v18[68]; // [esp+134h] [ebp-4E4h] BYREF
  int v19; // [esp+178h] [ebp-4A0h]
  int v20; // [esp+17Ch] [ebp-49Ch]
  int v21; // [esp+180h] [ebp-498h]
  int v22; // [esp+188h] [ebp-490h]
  int v23; // [esp+18Ch] [ebp-48Ch]
  int v24; // [esp+2CCh] [ebp-34Ch] BYREF
  int v25; // [esp+2D0h] [ebp-348h]
  int v26; // [esp+2D4h] [ebp-344h] BYREF
  int v27; // [esp+2D8h] [ebp-340h] BYREF
  int v28; // [esp+2DCh] [ebp-33Ch]
  int v29; // [esp+2E0h] [ebp-338h]
  int v30; // [esp+2E4h] [ebp-334h]
  int v31; // [esp+2E8h] [ebp-330h]
  char Str[256]; // [esp+2ECh] [ebp-32Ch] BYREF
  char v33; // [esp+3ECh] [ebp-22Ch] BYREF
  _BYTE v34[3]; // [esp+3EDh] [ebp-22Bh] BYREF
  int v35; // [esp+4F0h] [ebp-128h]
  char *first_character; // [esp+4F4h] [ebp-124h]
  int v37; // [esp+4F8h] [ebp-120h]
  char Buffer[260]; // [esp+4FCh] [ebp-11Ch] BYREF
  int v39; // [esp+604h] [ebp-14h]
  int v40; // [esp+608h] [ebp-10h] BYREF
  int v41; // [esp+614h] [ebp-4h]

  v39 = rf_bitmap_type_from_filename_extension(a1);
  *a5 = 1;
  *a6 = 1;
  *a8 = 0;
  *a7 = 1;
  *a9 = -1;
  *a10 = 1;
  switch ( v39 )
  {
    case 1:
      v37 = rf_pcx_read_header_dimensions_palette(a1, a2, a3, &v40, nullptr, (int)a11);
      if ( v37 )
      {
        v11 = rf_image_error_message_by_packed_string_index(v37);
        sprintf(Buffer, "Couldn't open %s because of error: %s\n", a1, v11);
        sprintf(Buffer, "Could not open file: %s", a1);
        rf_fatal_error_show_message_and_exit("D:\\projects\\rf_pc\\vsdk\\bmpman\\bmpman.cpp", 972, Buffer);
      }
      *a4 = 1;
      return v39;
    case 2:
      v37 = rf_tga_read_header_dimensions(a1, a2, a3, &v40, 0, 0, a11);
      if ( v37 )
      {
        v12 = rf_image_error_message_by_packed_string_index(v37);
        sprintf(Buffer, "Couldn't open %s because of error: %s\n", a1, v12);
        return 0;
      }
      switch ( v40 )
      {
        case 8:
          *a4 = 1;
          break;
        case 16:
          *a4 = 5;
          break;
        case 24:
          *a4 = 6;
          break;
        case 32:
          *a4 = 7;
          break;
        default:
          *a4 = 0;
          break;
      }
      if ( byte_663F11
        && unk_189744C
        && *a5 == 1
        && (*a2 & (*a2 - 1)) == 0
        && (*a3 & (*a3 - 1)) == 0
        && *a2 <= 256
        && *a3 <= 256 )
      {
        v29 = *a2;
        v30 = *a3;
        do
        {
          v29 = rf_int_max(1, v29 / 2);
          v30 = rf_int_max(1, v30 / 2);
          v28 = rf_int_max(v29, v30);
          ++*a5;
        }
        while ( v28 > 1 );
      }
      if ( !byte_663F10 )
        return v39;
      v16 = a1;
      v15 = Str;
      do
      {
        v14 = *v16;
        *v15++ = *v16++;
      }
      while ( v14 );
      first_character = rf_cstring_find_first_character(Str, 46);
      if ( first_character )
        *first_character = 0;
      v31 = *a2;
      v35 = *a3;
      while ( 2 )
      {
        v31 /= 2;
        v35 /= 2;
        v25 = rf_int_min_signed(v31, v35);
        if ( v25 >= 1 )
        {
          sprintf(&v33, "%s-mip%d.tga", Str, *a6);
          if ( (unsigned int)(&v34[strlen(&v33)] - v34) <= 0x28 )
          {
            v37 = rf_tga_read_header_dimensions(&v33, &v26, &v24, &v27, 0, 1, a11);
            if ( !v37 && v26 == v31 && v24 == v35 && v27 == v40 )
            {
              ++*a6;
              continue;
            }
          }
          else
          {
            sprintf(Buffer, "Mipmap filename exceeds maximum length: '%s'\n", &v33);
          }
        }
        break;
      }
      return v39;
    case 3:
      return v39;
    case 4:
      rf_vani_player_construct(v18);
      v41 = 0;
      if ( rf_vani_player_load_metadata((int)v18, a1, 0) < 0 )
      {
        v41 = -1;
        rf_vani_player_destroy((int *)v18);
        return 0;
      }
      *a2 = v19;
      *a3 = v20;
      *a8 = v23;
      *a7 = v22;
      switch ( v21 )
      {
        case 8:
          *a4 = 1;
          break;
        case 16:
          *a4 = 3;
          break;
        case 24:
          *a4 = 6;
          break;
        case 32:
          *a4 = 7;
          break;
        default:
          *a4 = 0;
          break;
      }
      v41 = -1;
      rf_vani_player_destroy((int *)v18);
      return v39;
    case 5:
      if ( rf_vbm_read_header_metadata(a1, a2, a3, a4, a7, a5, a8, a10, a11) )
        return v39;
      return 0;
    case 6:
      *a9 = rf_m2v_read_dimensions_and_file_size(a1, (unsigned int *)a2, (unsigned int *)a3);
      if ( *a9 <= 0 )
        return 0;
      *a4 = 5;
      *a7 = 1;
      *a5 = 1;
      *a8 = 0;
      return v39;
    default:
      sprintf(v17, "Cannot determine bitmap type in bm_read_header for file %s", a1);
      rf_fatal_error_show_message_and_exit("D:\\projects\\rf_pc\\vsdk\\bmpman\\bmpman.cpp", 1152, v17);
  }
}

