// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0058C420 rf_font_load_register_and_build_atlas
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, glyph/string layouts, read/write flow and callers): Case-sensitive strcmp lookup among records with nonzero+32 returns existing index. Scan tracks first unused slot but never consumes that saved index; after loop uses record at count and appends, incrementing count BEFORE reading. Count==12 raises Too many fonts fatal. Failed read or unsupported pixel encoding returns-1 without count rollback. Supports source tags0xF,0x0F0F0F0F,0xFFFFFFF0. Chooses square atlas64,128,256 from twice estimated source pixels with thresholds4096/16384. Allocates uninitialized 16-bit CPU atlas and two glyph-position arrays. Packs glyphs horizontally, wrapping on x+glyphWidth>=atlasWidth and advancing y by font height; y+height overflow raises Font too big fatal. No independent glyph-width fit check. Coverage0..14 becomes gamma-corrected
// alpha nibble plus white RGB0xFFF; values>14 clamp14. Packed16 copies words directly. Palette mode takes LOW nibble of each palette RGBA byte into A/R/G/B 4-bit positions. Unwritten atlas background is not cleared here. Marks GPU atlas handle-1 and attempts upload via ensure_atlas; returns index even if upload fails. No dimension/count/allocation overflow validation.
int __cdecl rf_font_load_register_and_build_atlas(char *Str)
{
  int v2; // [esp+4h] [ebp-80h]
  int v3; // [esp+8h] [ebp-7Ch]
  int v4; // [esp+2Ch] [ebp-58h]
  int v5; // [esp+40h] [ebp-44h]
  unsigned __int8 *v6; // [esp+44h] [ebp-40h]
  _WORD *v7; // [esp+4Ch] [ebp-38h]
  unsigned int v8; // [esp+50h] [ebp-34h]
  unsigned __int8 *v9; // [esp+54h] [ebp-30h]
  int m; // [esp+58h] [ebp-2Ch]
  int ii; // [esp+58h] [ebp-2Ch]
  int kk; // [esp+58h] [ebp-2Ch]
  int k; // [esp+5Ch] [ebp-28h]
  int n; // [esp+5Ch] [ebp-28h]
  int jj; // [esp+5Ch] [ebp-28h]
  const char *v16; // [esp+60h] [ebp-24h]
  int i; // [esp+64h] [ebp-20h]
  int v18; // [esp+68h] [ebp-1Ch]
  int j; // [esp+6Ch] [ebp-18h]
  int v20; // [esp+70h] [ebp-14h]
  int v21; // [esp+74h] [ebp-10h]
  int v22; // [esp+78h] [ebp-Ch]
  int v23; // [esp+7Ch] [ebp-8h]
  int v24; // [esp+80h] [ebp-4h]

  v16 = (const char *)&unk_193B688;
  v18 = -1;
  for ( i = 0; i < dword_193BB98; ++i )
  {
    if ( *((_DWORD *)v16 + 8) )
    {
      if ( !strcmp(v16, Str) )
        return i;
    }
    else if ( v18 < 0 )
    {
      v18 = i;
    }
    v16 += 108;
  }
  if ( i == 12 )
    rf_fatal_error_show_message_and_exit(
      "D:\\projects\\rf_pc\\vsdk\\gr\\gr_font.cpp",
      641,
      "Too many fonts!\nSee John, or change MAX_FONTS in Graphics\\Font.h\n");
  if ( i == dword_193BB98 )
    ++dword_193BB98;
  if ( !rf_font_read_versioned_file_into_record(Str, (int)v16) )
    return -1;
  v3 = *((_DWORD *)v16 + 9);
  switch ( v3 )
  {
    case 15:
      v23 = *((_DWORD *)v16 + 16);
      break;
    case 252645135:
      v23 = *((_DWORD *)v16 + 16) >> 1;
      break;
    case -16:
      v23 = *((_DWORD *)v16 + 16);
      break;
    default:
      return -1;
  }
  if ( 2 * v23 >= 4096 )
  {
    if ( 2 * v23 >= 0x4000 )
    {
      v22 = 256;
      v24 = 256;
    }
    else
    {
      v22 = 128;
      v24 = 128;
    }
  }
  else
  {
    v22 = 64;
    v24 = 64;
  }
  *((_DWORD *)v16 + 22) = v24;
  *((_DWORD *)v16 + 23) = v22;
  *((_DWORD *)v16 + 26) = operator new(2 * *((_DWORD *)v16 + 23) * *((_DWORD *)v16 + 22));
  *((_DWORD *)v16 + 24) = operator new(4 * *((_DWORD *)v16 + 10));
  *((_DWORD *)v16 + 25) = operator new(4 * *((_DWORD *)v16 + 10));
  v21 = 0;
  v20 = 0;
  for ( j = 0; j < *((_DWORD *)v16 + 10); ++j )
  {
    if ( *(_DWORD *)(*((_DWORD *)v16 + 18) + 16 * j + 4) + v20 >= *((_DWORD *)v16 + 22) )
    {
      v20 = 0;
      v21 += *((_DWORD *)v16 + 13);
      if ( *((_DWORD *)v16 + 13) + v21 > *((_DWORD *)v16 + 23) )
        rf_fatal_error_show_message_and_exit("D:\\projects\\rf_pc\\vsdk\\gr\\gr_font.cpp", 696, "Font too big!\n");
    }
    *(_DWORD *)(*((_DWORD *)v16 + 24) + 4 * j) = v20;
    *(_DWORD *)(*((_DWORD *)v16 + 25) + 4 * j) = v21;
    v2 = *((_DWORD *)v16 + 9);
    switch ( v2 )
    {
      case 15:
        v9 = (unsigned __int8 *)(*(_DWORD *)(*((_DWORD *)v16 + 18) + 16 * j + 8) + *((_DWORD *)v16 + 19));
        for ( k = 0; k < *((_DWORD *)v16 + 13); ++k )
        {
          for ( m = 0; m < *(_DWORD *)(*((_DWORD *)v16 + 18) + 16 * j + 4); ++m )
          {
            v8 = *v9++;
            if ( v8 > 0xE )
              v8 = 14;
            *(_WORD *)(*((_DWORD *)v16 + 26) + 2 * (*((_DWORD *)v16 + 22) * (k + v21) + m + v20)) = ((unsigned __int16)(rf_graphics_gamma_lut_u32[255 * v8 / 0xE] >> 4) << 12) | 0xFFF;
          }
        }
        break;
      case 252645135:
        v7 = (_WORD *)(*(_DWORD *)(*((_DWORD *)v16 + 18) + 16 * j + 8) + *((_DWORD *)v16 + 19));
        for ( n = 0; n < *((_DWORD *)v16 + 13); ++n )
        {
          for ( ii = 0; ii < *(_DWORD *)(*((_DWORD *)v16 + 18) + 16 * j + 4); ++ii )
            *(_WORD *)(*((_DWORD *)v16 + 26) + 2 * (*((_DWORD *)v16 + 22) * (n + v21) + ii + v20)) = *v7++;
        }
        break;
      case -16:
        v5 = *((_DWORD *)v16 + 20);
        v6 = (unsigned __int8 *)(*(_DWORD *)(*((_DWORD *)v16 + 18) + 16 * j + 8) + *((_DWORD *)v16 + 19));
        for ( jj = 0; jj < *((_DWORD *)v16 + 13); ++jj )
        {
          for ( kk = 0; kk < *(_DWORD *)(*((_DWORD *)v16 + 18) + 16 * j + 4); ++kk )
          {
            v4 = *(_DWORD *)(v5 + 4 * *v6++);
            *(_WORD *)(*((_DWORD *)v16 + 26) + 2 * (*((_DWORD *)v16 + 22) * (jj + v21) + kk + v20)) = v4 & 0xF | (16 * (BYTE1(v4) & 0xF)) | ((BYTE2(v4) & 0xF) << 8) | ((HIBYTE(v4) & 0xF) << 12);
          }
        }
        break;
    }
    v20 += *(_DWORD *)(*((_DWORD *)v16 + 18) + 16 * j + 4);
  }
  *((_DWORD *)v16 + 21) = -1;
  rf_font_ensure_atlas_bitmap((int)v16);
  return i;
}

