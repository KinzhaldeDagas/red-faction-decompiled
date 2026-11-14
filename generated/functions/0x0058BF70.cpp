// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0058BF70 rf_font_ensure_atlas_bitmap
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, glyph/string layouts, read/write flow and callers): If font record atlas handle+84<0, creates RF bitmap format4 with dimensions+88/+92. On successful create, locks tile0 mode2 and converts width*height CPU atlas pixels from format4 into actual locked format, then unlocks. Failed lock recycles the bitmap handle and sets+84=-1. Existing nonnegative atlas is left untouched. Return EAX varies by path and is not a uniform success flag; callers inspect record+84. No record/pixel/dimension validation.
int __cdecl rf_font_ensure_atlas_bitmap(int a1)
{
  int result; // eax
  unsigned int v2[8]; // [esp+0h] [ebp-20h] BYREF

  result = a1;
  if ( *(int *)(a1 + 84) < 0 )
  {
    *(_DWORD *)(a1 + 84) = rf_bitmap_create_user_bitmap(4, *(_DWORD *)(a1 + 88), *(_DWORD *)(a1 + 92));
    result = a1;
    if ( *(int *)(a1 + 84) > -1 )
    {
      if ( rf_bitmap_lock_pixels_backend_dispatch(*(_DWORD *)(a1 + 84), 0, v2, 2u) )
      {
        rf_bitmap_convert_pixel_run_selected_formats(
          (void *)v2[3],
          (void *)v2[2],
          *(unsigned __int8 **)(a1 + 104),
          (void *)4,
          *(_DWORD *)(a1 + 92) * *(_DWORD *)(a1 + 88));
        return rf_bitmap_unlock_pixels_backend_dispatch(v2);
      }
      else
      {
        rf_bitmap_handle_recycle_slot_or_animation_entry(*(_DWORD *)(a1 + 84));
        *(_DWORD *)(a1 + 84) = -1;
        return a1;
      }
    }
  }
  return result;
}

