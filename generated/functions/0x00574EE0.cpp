// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00574EE0 rf_bitmap_load_or_register_metadata_and_slots
// UNREALRED VERIFIED [bitmap-loading-20261028]: Arguments requested name, source context. Returns already-loaded handle by case-insensitive hash lookup, without incrementing references. Context-1 becomes default0x98967F. Copies name into260-byte local buffer unbounded. Global0x704E83==1 bypasses file headers: creates user bitmap format6,32x32, stores name/hash and inserts; no placeholder pixel upload in this branch. Otherwise TGA extension tries equivalent .vbm name, returning cached VBM handle or substituting filename if vfile source resolution succeeds using requested context. Header probe0x575790 itself is called with DEFAULT context0x98967F, not normalized caller context, although caller context is later stored in record+100. Probe result0 or3 delegates named placeholder0x576210. Successful other types call dimension predicate0x5755A0 but ignore result, calculate mip-chain pixels, and
// allocate one slot when framecount==1 or framecount+1 contiguous slots otherwise. No allocation failure check. Initializes parent file type+52, subtype+56=0(single)/1(sequence), format+60, extra byte+68, name/hash, framecount byte+67, ratefloat+76=rate/1000, original/current dimensions+40/+42/+44/+46, mip bytes+64/+65, external mip byte+66,pixelcount+48,nullCPU pointers+72/+80,metadata byte93=0,source context+100,reduction mode+104=0; applies global reduction. Memory-size+96 is stored-size for M2V,else pixels*bytes-per-pixel. If framecount>1, initializes following frame records subtype2 with backoffset byte67=i+1 and shared metadata/null pointers. Framecount0 takes contiguous allocation but no child loop; framecount and offsets truncate to bytes. No CPU image decoding here, source-name length, dimension/rate/mip validation or full-generation checks.
unsigned int __cdecl rf_bitmap_load_or_register_metadata_and_slots(char *String2, char *a2)
{
  unsigned int v3; // eax
  int v4; // eax
  int v5; // eax
  char v6; // [esp+13h] [ebp-3C9h]
  _BYTE *v7; // [esp+18h] [ebp-3C4h]
  char *v8; // [esp+1Ch] [ebp-3C0h]
  char v9; // [esp+23h] [ebp-3B9h]
  char *v10; // [esp+28h] [ebp-3B4h]
  char *v11; // [esp+2Ch] [ebp-3B0h]
  char *v13; // [esp+34h] [ebp-3A8h]
  char v14; // [esp+3Bh] [ebp-3A1h]
  _BYTE *v15; // [esp+40h] [ebp-39Ch]
  char *v16; // [esp+44h] [ebp-398h]
  char v17; // [esp+4Bh] [ebp-391h]
  char *v18; // [esp+50h] [ebp-38Ch]
  char *v19; // [esp+54h] [ebp-388h]
  int v20; // [esp+58h] [ebp-384h]
  int i; // [esp+5Ch] [ebp-380h]
  int self[70]; // [esp+60h] [ebp-37Ch] BYREF
  char *last_char_wrapper; // [esp+178h] [ebp-264h]
  int v24; // [esp+17Ch] [ebp-260h] BYREF
  char v25[256]; // [esp+180h] [ebp-25Ch] BYREF
  unsigned int user_bitmap; // [esp+280h] [ebp-15Ch]
  int v27; // [esp+284h] [ebp-158h]
  int v28; // [esp+288h] [ebp-154h]
  int v29; // [esp+28Ch] [ebp-150h]
  char Src[260]; // [esp+290h] [ebp-14Ch] BYREF
  int v31; // [esp+398h] [ebp-44h]
  int v32; // [esp+39Ch] [ebp-40h] BYREF
  int v33; // [esp+3A0h] [ebp-3Ch] BYREF
  int v34; // [esp+3A4h] [ebp-38h] BYREF
  int v35; // [esp+3A8h] [ebp-34h] BYREF
  _DWORD *single_slot_from_free_list; // [esp+3ACh] [ebp-30h]
  int v37; // [esp+3B0h] [ebp-2Ch] BYREF
  int v38; // [esp+3B4h] [ebp-28h]
  int loaded_handle_by_name; // [esp+3B8h] [ebp-24h]
  int v40; // [esp+3BCh] [ebp-20h] BYREF
  int v41; // [esp+3C0h] [ebp-1Ch] BYREF
  int v42; // [esp+3C4h] [ebp-18h] BYREF
  int v43; // [esp+3C8h] [ebp-14h] BYREF
  int v44; // [esp+3CCh] [ebp-10h]
  int v45; // [esp+3D8h] [ebp-4h]

  loaded_handle_by_name = rf_bitmap_find_loaded_handle_by_name(String2);
  if ( loaded_handle_by_name >= 0 )
    return loaded_handle_by_name;
  if ( a2 == (char *)-1 )
    a2 = byte_98967F;
  v19 = String2;
  v18 = Src;
  do
  {
    v17 = *v19;
    *v18++ = *v19++;
  }
  while ( v17 );
  if ( byte_704E83 == 1 )
  {
    user_bitmap = rf_bitmap_create_user_bitmap(6, 32, 32);
    v27 = rf_bitmap_resolve_current_frame_slot(user_bitmap);
    v28 = dword_1897344 + 108 * v27;
    v16 = Src;
    v15 = (_BYTE *)v28;
    do
    {
      v14 = *v16;
      *v15++ = *v16++;
    }
    while ( v14 );
    *(_DWORD *)(v28 + 32) = rf_bitmap_name_hash_rotate6_lower_abs(Src);
    rf_bitmap_hash_insert_record_pointer(v28);
    return user_bitmap;
  }
  else
  {
    v31 = rf_bitmap_type_from_filename_extension(Src);
    if ( v31 == 2 )
    {
      last_char_wrapper = rf_cstring_find_last_char_wrapper(Src, 46);
      rf_vfile_construct_unopened(self);
      v45 = 0;
      memcpy(v25, Src, last_char_wrapper - Src);
      *(last_char_wrapper - 272) = 0;
      v13 = (char *)&v24 + 3;
      while ( *++v13 )
        ;
      strcpy(v13, ".vbm");
      v24 = rf_bitmap_find_loaded_handle_by_name(v25);
      if ( v24 >= 0 )
      {
        v20 = v24;
        v45 = -1;
        rf_vfile_destruct_close_if_open(self);
        return v20;
      }
      if ( rf_vfile_resolve_open_source((int)self, v25, (int)a2) )
      {
        v11 = v25;
        v10 = Src;
        do
        {
          v9 = *v11;
          *v10++ = *v11++;
        }
        while ( v9 );
      }
      v45 = -1;
      rf_vfile_destruct_close_if_open(self);
    }
    v38 = rf_bitmap_probe_header_by_file_type(
            Src,
            &v43,
            &v41,
            &v37,
            &v34,
            &v42,
            &v35,
            &v32,
            &v40,
            &v33,
            (int)byte_98967F);
    if ( v38 && v38 != 3 )
    {
      rf_bitmap_dimensions_are_powers_4_through_256(v43, v41);
      v44 = rf_bitmap_mip_chain_pixel_count(v43, v41, v34);
      if ( v35 == 1 )
      {
        single_slot_from_free_list = rf_bitmap_allocate_single_slot_from_free_list();
        single_slot_from_free_list[14] = 0;
      }
      else
      {
        single_slot_from_free_list = (_DWORD *)rf_bitmap_allocate_contiguous_slot_run(v35 + 1);
        single_slot_from_free_list[14] = 1;
      }
      single_slot_from_free_list[13] = v38;
      single_slot_from_free_list[15] = v37;
      *((_BYTE *)single_slot_from_free_list + 68) = v33;
      v29 = single_slot_from_free_list[9];
      v8 = Src;
      v7 = single_slot_from_free_list;
      do
      {
        v6 = *v8;
        *v7++ = *v8++;
      }
      while ( v6 );
      v3 = rf_bitmap_name_hash_rotate6_lower_abs(Src);
      single_slot_from_free_list[8] = v3;
      rf_bitmap_hash_insert_record_pointer((int)single_slot_from_free_list);
      *((_BYTE *)single_slot_from_free_list + 67) = v35;
      *((float *)single_slot_from_free_list + 19) = (double)v32 / 1000.0;
      *((_WORD *)single_slot_from_free_list + 22) = v43;
      *((_WORD *)single_slot_from_free_list + 23) = v41;
      *((_WORD *)single_slot_from_free_list + 20) = v43;
      *((_WORD *)single_slot_from_free_list + 21) = v41;
      *((_BYTE *)single_slot_from_free_list + 64) = v34;
      *((_BYTE *)single_slot_from_free_list + 65) = v34;
      *((_BYTE *)single_slot_from_free_list + 66) = v42;
      single_slot_from_free_list[12] = v44;
      single_slot_from_free_list[18] = 0;
      single_slot_from_free_list[20] = 0;
      *((_BYTE *)single_slot_from_free_list + 93) = 0;
      single_slot_from_free_list[25] = a2;
      single_slot_from_free_list[26] = 0;
      rf_bitmap_set_slot_reduction_mode(single_slot_from_free_list[9], dword_1897454);
      if ( single_slot_from_free_list[13] == 6 )
      {
        single_slot_from_free_list[24] = v40;
      }
      else
      {
        v4 = rf_bitmap_format_bytes_per_pixel(v37);
        single_slot_from_free_list[24] = v44 * v4;
      }
      if ( v35 > 1 )
      {
        for ( i = 0; i < v35; ++i )
        {
          single_slot_from_free_list += 27;
          *(_BYTE *)single_slot_from_free_list = 0;
          single_slot_from_free_list[8] = -1;
          single_slot_from_free_list[13] = v38;
          single_slot_from_free_list[14] = 2;
          single_slot_from_free_list[15] = v37;
          *((_WORD *)single_slot_from_free_list + 22) = v43;
          *((_WORD *)single_slot_from_free_list + 23) = v41;
          *((_BYTE *)single_slot_from_free_list + 64) = v34;
          single_slot_from_free_list[12] = v44;
          *((_BYTE *)single_slot_from_free_list + 67) = i + 1;
          single_slot_from_free_list[18] = 0;
          single_slot_from_free_list[20] = 0;
          single_slot_from_free_list[25] = a2;
          if ( single_slot_from_free_list[13] == 6 )
          {
            single_slot_from_free_list[24] = v40;
          }
          else
          {
            v5 = rf_bitmap_format_bytes_per_pixel(v37);
            single_slot_from_free_list[24] = v44 * v5;
          }
        }
      }
      return v29;
    }
    else
    {
      return rf_bitmap_create_named_missing_texture_placeholder(String2);
    }
  }
}

