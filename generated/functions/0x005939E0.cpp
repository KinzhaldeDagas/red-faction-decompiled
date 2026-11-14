// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005939E0 rf_vfile_compute_raw_crc32
// UNREALRED VERIFIED [event-registry-crc-20261028]: Optional filename resolves source or returns-4. Already-open VFile requires mode1, saves position and seeks0; otherwise opens mode1 and marks ownership. Reads logical file length in chunks up to1024 and updates zero-initialized raw reflected CRC at caller output. Includes one zero-length update for empty file. On read error breaks before CRC update for that chunk. If opened here returns CLOSE result (can mask prior read error); otherwise seeks saved offset then returns current status helper. Does not return CRC directly; output receives running CRC only after accepted reads. No final complement.
int __thiscall rf_vfile_compute_raw_crc32(int *this, int *a2, char *String2, int a4)
{
  char v6; // [esp+7h] [ebp-421h]
  char v7[1028]; // [esp+8h] [ebp-420h] BYREF
  int v8; // [esp+410h] [ebp-18h]
  int Offset; // [esp+414h] [ebp-14h]
  int v10; // [esp+418h] [ebp-10h]
  size_t Size; // [esp+41Ch] [ebp-Ch]
  int v12; // [esp+420h] [ebp-8h]
  int v13; // [esp+424h] [ebp-4h] BYREF

  v6 = 0;
  Offset = 0;
  rf_crc32_accumulator_construct_zero(&v13);
  if ( String2 && !rf_vfile_resolve_open_source((int)this, String2, a4) )
    return -4;
  if ( *(this + 68) >= 0 )
  {
    if ( !rf_vfile_test_mode_mask(this, 1) )
      return -1;
    Offset = rf_vfile_get_open_slot_offset(this);
    if ( Offset < 0 )
      return Offset;
    v8 = rf_vfile_seek(this, 0, 0);
    if ( v8 )
      return v8;
  }
  else
  {
    v6 = 1;
    v8 = rf_vfile_open_stdio_or_vpp((int)this, 1);
    if ( v8 < 0 )
      return v8;
  }
  v12 = rf_vfile_get_size((int)this, nullptr, (int)byte_98967F);
  v10 = 0;
  do
  {
    if ( v10 + 1024 > v12 )
      Size = v12 - v10;
    else
      Size = 1024;
    rf_vfile_read_buffered_bytes_versioned(this, v7, Size, 0, 0);
    if ( rf_vfile_get_open_slot_status(this) < 0 )
      break;
    v10 += Size;
    *a2 = rf_crc32_update_reflected_raw(&v13, v7, Size);
  }
  while ( v10 < v12 );
  if ( v6 )
    return rf_vfile_close_stdio_or_vpp(this);
  rf_vfile_seek(this, Offset, 0);
  return rf_vfile_get_open_slot_status(this);
}

