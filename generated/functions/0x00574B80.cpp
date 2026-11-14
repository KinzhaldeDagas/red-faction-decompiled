// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00574B80 rf_bitmap_resolve_current_frame_slot
// UNREALRED VERIFIED [bitmap-lifecycle-20261028]: Stores decoded slot in global 0x663F24. Animated handles use 36-byte entry: source index+0, rate+16, loop mode+20, initial frame byte+24, status+28, start clock+32. If status!=2, status0 initializes status1 and start=clock-int(initialFrame/rate), then calls 0x574C90; result-1 sets status2. If status already2, returns DECODED ANIMATION SLOT unchanged, rather than -1 or source frame. Ordinary bitmap subtype+56==1 resolves via 0x574C90(base,0,record rate+76,mode1); other ordinary records return decoded slot. Mutates animation state and global last-resolved index. No full-handle generation or rate/count validation.
int __cdecl rf_bitmap_resolve_current_frame_slot(unsigned int a1)
{
  int *v2; // [esp+Ch] [ebp-8h]

  dword_663F24 = rf_bitmap_handle_to_slot_index(a1);
  if ( (a1 & 0x40000000) != 0 )
  {
    v2 = &unk_187CD40[9 * dword_663F24];
    if ( v2[7] != 2 )
    {
      if ( !v2[7] )
      {
        v2[7] = 1;
        v2[8] = unk_18092E4 - (int)(1.0 / *((float *)v2 + 4) * (double)*((unsigned __int8 *)v2 + 24));
      }
      dword_663F24 = rf_bitmap_animation_frame_index_from_clock(*v2, v2[8], *((float *)v2 + 4), v2[5]);
      if ( dword_663F24 == -1 )
        v2[7] = 2;
    }
  }
  else if ( *(_DWORD *)(dword_1897344 + 108 * dword_663F24 + 56) == 1 )
  {
    dword_663F24 = rf_bitmap_animation_frame_index_from_clock(
                     dword_663F24,
                     0,
                     *(float *)(dword_1897344 + 108 * dword_663F24 + 76),
                     1);
  }
  return dword_663F24;
}

