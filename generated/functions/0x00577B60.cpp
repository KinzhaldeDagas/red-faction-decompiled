// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00577B60 rf_bitmap_load_vaf_frames_cpu_by_slot
// UNREALRED VERIFIED [bitmap-decoders-20261028]: Argument bitmap slot INDEX. Any nonzero subtype+56 backs up108*byte67 to assumed parent. If parent pixels null, constructs temporary VANI player and reads metadata; failure returns0 after destruction. Allocates all frames in one contiguous pixel block, plus768*framecount palette block when format1; assigns child slice pointers, decodes each frame index0..count-1 via0x5E52D0. Negative decode result returns0 but does not release parent/child pixel allocations or clear pointers; later calls can see nonnull partially initialized parent and skip reload. On full success sets parent reference byte92=framecount. Subtype0 uses its own allocation/palette and decodes frame index equal to record byte67, not forced0. Temporary player destroyed on all paths. Returns1 on success/already-loaded sequence. No allocation, count, index or size validation;
// helper assumes resolved child for sequence path.
char __cdecl rf_bitmap_load_vaf_frames_cpu_by_slot(int a1)
{
  int i; // [esp+20h] [ebp-358h]
  char v3[408]; // [esp+24h] [ebp-354h] BYREF
  char *v4; // [esp+1BCh] [ebp-1BCh]
  char *v5; // [esp+1C0h] [ebp-1B8h]
  char v6[412]; // [esp+1C4h] [ebp-1B4h] BYREF
  char *v7; // [esp+364h] [ebp-14h]
  int v8; // [esp+368h] [ebp-10h]
  int v9; // [esp+374h] [ebp-4h]

  v7 = (char *)(dword_1897344 + 108 * a1);
  v8 = rf_bitmap_format_bytes_per_pixel(*((_DWORD *)v7 + 15));
  if ( *((_DWORD *)v7 + 14) )
  {
    v5 = &v7[-108 * (unsigned __int8)v7[67]];
    if ( !*((_DWORD *)v5 + 18) )
    {
      rf_vani_player_construct(v3);
      v9 = 1;
      if ( rf_vani_player_load_metadata((int)v3, v5, 0) < 0 )
      {
LABEL_10:
        v9 = -1;
        rf_vani_player_destroy((int *)v3);
        return 0;
      }
      *((_DWORD *)v5 + 18) = operator new((unsigned __int8)v5[67] * v8 * *((_DWORD *)v5 + 12));
      if ( *((_DWORD *)v5 + 15) == 1 )
        *((_DWORD *)v5 + 20) = operator new(768 * (unsigned __int8)v5[67]);
      else
        *((_DWORD *)v5 + 20) = 0;
      v4 = v5;
      for ( i = 0; i < (unsigned __int8)v5[67]; ++i )
      {
        v4 += 108;
        *((_DWORD *)v4 + 18) = *((_DWORD *)v5 + 18) + i * v8 * *((_DWORD *)v4 + 12);
        if ( *((_DWORD *)v5 + 15) == 1 )
          *((_DWORD *)v4 + 20) = *((_DWORD *)v5 + 20) + 768 * ((unsigned __int8)v4[67] - 1);
        else
          *((_DWORD *)v4 + 20) = 0;
        if ( (rf_vani_player_read_frame_pixels((int)v3, i, *((void **)v4 + 18), *((void **)v4 + 20)) & 0x80000000) != 0 )
          goto LABEL_10;
      }
      v5[92] = v5[67];
      v9 = -1;
      rf_vani_player_destroy((int *)v3);
    }
  }
  else
  {
    rf_vani_player_construct(v6);
    v9 = 0;
    if ( rf_vani_player_load_metadata((int)v6, v7, 0) < 0 )
      goto LABEL_3;
    *((_DWORD *)v7 + 18) = operator new(v8 * *((_DWORD *)v7 + 12));
    if ( *((_DWORD *)v7 + 15) == 1 )
      *((_DWORD *)v7 + 20) = operator new(0x300u);
    if ( (rf_vani_player_read_frame_pixels((int)v6, (unsigned __int8)v7[67], *((void **)v7 + 18), *((void **)v7 + 20))
        & 0x80000000) != 0 )
    {
LABEL_3:
      v9 = -1;
      rf_vani_player_destroy((int *)v6);
      return 0;
    }
    v9 = -1;
    rf_vani_player_destroy((int *)v6);
  }
  return 1;
}

