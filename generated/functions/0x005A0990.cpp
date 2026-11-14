// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005A0990 rf_vfile_write_bytes_with_optional_feedback
// UNREALRED VERIFIED [string-pool-stream-20261028]: Thiscall vfile,MUTABLE source buffer,byte count. Slot index from object DWORD at+272 selects0x189CEB0 stride32832;increments operation count+20. Existing nonzero status+12 or zero count skips write. Feedback flag DWORD+4 mask1 saves state+32820,transforms caller buffer IN PLACE,then fwrite(buffer,count,1,FILE slot+32812). Reseeds through0x5EDE40 and transforms buffer again; with nonzero saved seeds this recovers original buffer and leaves state advanced once for count bytes,even if fwrite failed. The reseed helper REPLACES zero seeds with constants,so zero-valued saved seeds do not restore exactly and may leave caller buffer changed. Successful one-element fwrite adds count to position+16 and cumulative bytes+24; zero result sets status-2 without advancing those counters,even if underlying partial bytes written. No VPP write branch,source
// capacity check,slot validation or lock. Return varies among operation count,slot address,transform helper and cumulative-byte value; caller must inspect status,not treat it as byte count.
int *__thiscall rf_vfile_write_bytes_with_optional_feedback(_DWORD *this, _BYTE *Buffer, size_t ElementSize)
{
  int *result; // eax
  size_t v4; // [esp+4h] [ebp-18h]
  _DWORD v5[3]; // [esp+8h] [ebp-14h] BYREF
  int *v6; // [esp+18h] [ebp-4h]

  v6 = &unk_189CEB0[8208 * *(this + 68)];
  result = (int *)(v6[5] + 1);
  v6[5] = (int)result;
  if ( !v6[3] && ElementSize )
  {
    if ( (v6[1] & 1) != 0 )
    {
      rf_feedback_xor_state_copy_out(v6 + 8205, v5);
      rf_feedback_xor_transform_bytes_in_place(v6 + 8205, Buffer, ElementSize);
    }
    v4 = fwrite(Buffer, ElementSize, 1u, (FILE *)v6[8203]);
    result = v6;
    if ( (v6[1] & 1) != 0 )
    {
      rf_feedback_xor_state_set_nonzero_seeds(v6 + 8205, v5);
      result = (int *)rf_feedback_xor_transform_bytes_in_place(v6 + 8205, Buffer, ElementSize);
    }
    if ( v4 )
    {
      v6[4] += ElementSize;
      result = (int *)(ElementSize + v6[6]);
      v6[6] = (int)result;
    }
    else
    {
      v6[3] = -2;
    }
  }
  return result;
}

