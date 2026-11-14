// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005A0230 rf_vfile_read_buffered_bytes_versioned
// UNREALRED VERIFIED [string-pool-stream-20261028]: Thiscall vfile,destination,requested bytes,minimum version,unused last argument. Slot index from object+272 selects global0x189CEB0 stride32832(0x8040). Increments operation count+20 even on early return; if signed slot version+8<minimum or status+12 nonzero returns0. Consumes cache bytes valid+40 minus cursor+36,data+44,then remaining request<32768 refills cache (up to min(total+28-current position+16-already copied,32768)); larger remainder reads direct FILE+32812 or VPP member object+264. IMPORTANT stdio refill stores fread actual count,may set status-99999 on short read when0x593540 returns0,then UNCONDITIONALLY overwrites cache valid count with requested refill length. Copy count is based on expected remaining bytes,not actual refill length,so short reads can expose stale cache and report copied bytes. VPP refill also chooses copy
// count from expected remaining rather than returned actual count. Optional feedback flag slot+4 mask1 transforms output bytes via state+32820. Advances position+16 and cumulative bytes+24 by copied count; requested!=copied sets status-1 (can overwrite previous error). Returns copied byte count. No slot/destination/capacity/request sign validation,locking or general rollback.
int __thiscall rf_vfile_read_buffered_bytes_versioned(int *this, char *a2, size_t Size, int a4, int a5)
{
  int ElementCount; // [esp+4h] [ebp-1Ch]
  int v8; // [esp+8h] [ebp-18h]
  char *Buffer; // [esp+Ch] [ebp-14h]
  int v10; // [esp+10h] [ebp-10h]
  int *v12; // [esp+18h] [ebp-8h]
  int Sizea; // [esp+2Ch] [ebp+Ch]
  int Sizeb; // [esp+2Ch] [ebp+Ch]

  v12 = &unk_189CEB0[8208 * *(this + 68)];
  ++v12[5];
  if ( v12[2] < a4 || v12[3] )
    return 0;
  v10 = rf_int_min_signed(v12[10] - v12[9], Size);
  memcpy(a2, (char *)v12 + v12[9] + 44, v10 < 0 ? 0 : v10);
  v12[9] += v10;
  Sizea = Size - v10;
  if ( Sizea > 0 )
  {
    Buffer = &a2[v10];
    if ( Sizea < 0x8000 )
    {
      v8 = v12[7] - (v10 + v12[4]);
      ElementCount = rf_int_min_signed(v8, 0x8000);
      if ( v12[8203] )
      {
        v12[10] = fread(v12 + 11, 1u, ElementCount, (FILE *)v12[8203]);
        if ( v12[10] < ElementCount && !rf_vfile_is_position_at_or_past_end_signed(this) )
          unk_189CEBC[8208 * *(this + 68)] = -99999;
        v12[10] = ElementCount;
      }
      else
      {
        v12[10] = rf_vpackfile_entry_read(v12 + 11, 1u, ElementCount, *(this + 66));
      }
      v12[8] = v10 + v12[4];
      Sizeb = rf_int_min_signed(v8, Sizea);
      if ( Sizeb < 0 )
        Sizeb = 0;
      memcpy(Buffer, v12 + 11, Sizeb);
      v12[9] = Sizeb;
      v10 += Sizeb;
    }
    else
    {
      v12[9] = 0;
      v12[10] = 0;
      v12[8] = -1;
      if ( v12[8203] )
        v10 += fread(Buffer, 1u, Sizea, (FILE *)v12[8203]);
      else
        v10 += rf_vpackfile_entry_read(Buffer, 1u, Sizea, *(this + 66));
    }
  }
  if ( (v12[1] & 1) != 0 )
    rf_feedback_xor_transform_bytes_in_place(v12 + 8205, a2, v10);
  v12[4] += v10;
  v12[6] += v10;
  if ( Size != v10 )
    v12[3] = -1;
  return v10;
}

