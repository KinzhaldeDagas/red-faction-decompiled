// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00576210 rf_bitmap_create_named_missing_texture_placeholder
// UNREALRED VERIFIED [bitmap-loading-20261028]: Sets global missing marker0x189744E=1 if not already. Creates user bitmap format6,size32x32. If GPU pixel lock succeeds, converts1024 pixels from built-in placeholder buffer0x1897450 format6 to lock descriptor format and unlocks; lock failure still continues. Resolves new handle, copies requested name into record without length bound, computes hash and inserts record pointer. Returns user bitmap handle even if GPU fill failed. Does not validate creation/resolution success or image ownership; record name capacity32 bytes before hash+32.
unsigned int __cdecl rf_bitmap_create_named_missing_texture_placeholder(char *a1)
{
  unsigned int v1; // eax
  char v3; // [esp+3h] [ebp-39h]
  _BYTE *v4; // [esp+8h] [ebp-34h]
  char *v5; // [esp+Ch] [ebp-30h]
  unsigned int user_bitmap; // [esp+10h] [ebp-2Ch]
  unsigned int v7[8]; // [esp+14h] [ebp-28h] BYREF
  int v8; // [esp+34h] [ebp-8h]
  int v9; // [esp+38h] [ebp-4h]

  if ( !byte_189744E )
    byte_189744E = 1;
  user_bitmap = rf_bitmap_create_user_bitmap(6, 32, 32);
  if ( rf_bitmap_lock_pixels_backend_dispatch(user_bitmap, 0, v7, 1u) )
  {
    rf_bitmap_convert_pixel_run_selected_formats(
      (void *)v7[3],
      (void *)v7[2],
      *(unsigned __int8 **)&byte_189744F[1],
      (void *)6,
      1024);
    rf_bitmap_unlock_pixels_backend_dispatch(v7);
  }
  v8 = rf_bitmap_resolve_current_frame_slot(user_bitmap);
  v9 = dword_1897344 + 108 * v8;
  v5 = a1;
  v4 = (_BYTE *)v9;
  do
  {
    v3 = *v5;
    *v4++ = *v5++;
  }
  while ( v3 );
  v1 = rf_bitmap_name_hash_rotate6_lower_abs(a1);
  *(_DWORD *)(v9 + 32) = v1;
  rf_bitmap_hash_insert_record_pointer(v9);
  return user_bitmap;
}

