// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00574400 rf_bitmap_set_slot_reduction_mode
// UNREALRED VERIFIED [bitmap-lifecycle-20261028]: Arguments handle, reduction mode. Uses decoded ordinary record directly; no animation source indirection. Operates only when type+52!=3, subtype+56==0, stored mode+104 differs, original width/height+40/+42 BOTH>16, and original mip count byte+65!=1. Stores requested mode+104. Mode0 restores dimensions/mips; mode1 halves dimensions and subtracts1 mip; mode2 quarters and subtracts2. Other modes still stored but leave dimensions/mip count unchanged. Recalculates pixel count+48 via0x573E80 and marks renderer dirty using stored handle+36 via0x571F50. No CPU pixel release/reload here, no mip underflow or arbitrary-mode rejection.
unsigned int __cdecl rf_bitmap_set_slot_reduction_mode(unsigned int a1, int a2)
{
  unsigned int result; // eax
  int v3; // [esp+4h] [ebp-4h]

  result = dword_1897344 + 108 * rf_bitmap_handle_to_slot_index(a1);
  v3 = result;
  if ( *(_DWORD *)(result + 52) != 3 && !*(_DWORD *)(result + 56) && *(_DWORD *)(result + 104) != a2 )
  {
    result = *(unsigned __int16 *)(result + 40);
    if ( *(unsigned __int16 *)(v3 + 40) > 0x10u && *(unsigned __int16 *)(v3 + 42) > 0x10u )
    {
      result = v3;
      if ( *(_BYTE *)(v3 + 65) != 1 )
      {
        *(_DWORD *)(v3 + 104) = a2;
        if ( a2 )
        {
          if ( a2 == 1 )
          {
            *(_WORD *)(v3 + 44) = (int)*(unsigned __int16 *)(v3 + 40) >> 1;
            *(_WORD *)(v3 + 46) = (int)*(unsigned __int16 *)(v3 + 42) >> 1;
            *(_BYTE *)(v3 + 64) = *(_BYTE *)(v3 + 65) - 1;
          }
          else if ( a2 == 2 )
          {
            *(_WORD *)(v3 + 44) = (int)*(unsigned __int16 *)(v3 + 40) >> 2;
            *(_WORD *)(v3 + 46) = (int)*(unsigned __int16 *)(v3 + 42) >> 2;
            *(_BYTE *)(v3 + 64) = *(_BYTE *)(v3 + 65) - 2;
          }
        }
        else
        {
          *(_WORD *)(v3 + 44) = *(_WORD *)(v3 + 40);
          *(_WORD *)(v3 + 46) = *(_WORD *)(v3 + 42);
          *(_BYTE *)(v3 + 64) = *(_BYTE *)(v3 + 65);
        }
        *(_DWORD *)(v3 + 48) = rf_bitmap_mip_chain_pixel_count(
                                 *(unsigned __int16 *)(v3 + 44),
                                 *(unsigned __int16 *)(v3 + 46),
                                 *(unsigned __int8 *)(v3 + 64));
        return rf_bitmap_mark_renderer_dirty_backend_dispatch(*(_DWORD *)(dword_1897344
                                                                        + 108 * ((v3 - dword_1897344) / 108)
                                                                        + 36));
      }
    }
  }
  return result;
}

