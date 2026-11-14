// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005E5E40 rf_m2v_read_dimensions_and_file_size
// UNREALRED VERIFIED [bitmap-lifecycle-20261028]: Arguments filename,width output,height output. Opens given name or fallback name with .m2v extension via0x57C380. Gets file size, reads first8 bytes; read error closes/destroys vfile and returns0 without writing dimensions. Otherwise byte-swaps second DWORD, width=(word>>20)&0xFFF,height=(word>>8)&0xFFF, closes/destroys and returns file size. Does NOT verify first DWORD is an MPEG sequence header or scan for one later. Open failure0; outputs unchanged. Fallback name buffer256 bytes, no length validation in this body.
int __cdecl rf_m2v_read_dimensions_and_file_size(char *Str, unsigned int *a2, unsigned int *a3)
{
  int v4; // [esp+4h] [ebp-248h]
  __int16 v5; // [esp+14h] [ebp-238h]
  char v6[256]; // [esp+18h] [ebp-234h] BYREF
  int self[70]; // [esp+118h] [ebp-134h] BYREF
  char v8[4]; // [esp+234h] [ebp-18h] BYREF
  int v9; // [esp+238h] [ebp-14h]
  int size; // [esp+23Ch] [ebp-10h]
  int v11; // [esp+248h] [ebp-4h]

  rf_vfile_construct_unopened(self);
  v11 = 0;
  size = 0;
  if ( rf_vfile_open_with_extension_cache_control_paths(self, Str, 1, byte_98967F) >= 0
    || (rf_path_replace_last_dot_suffix_unbounded(v6, Str, ".m2v"),
        rf_vfile_open_with_extension_cache_control_paths(self, v6, 1, byte_98967F) >= 0) )
  {
    size = rf_vfile_get_size((int)self, nullptr, (int)byte_98967F);
    rf_vfile_read_buffered_bytes_versioned(self, v8, 8u, 0, 0);
    if ( rf_vfile_get_open_slot_status(self) )
    {
      rf_vfile_close_stdio_or_vpp(self);
      v11 = -1;
      rf_vfile_destruct_close_if_open(self);
      return 0;
    }
    else
    {
      v5 = v9;
      LOBYTE(v9) = HIBYTE(v9);
      BYTE1(v9) = BYTE2(v9);
      BYTE2(v9) = HIBYTE(v5);
      HIBYTE(v9) = v5;
      *a2 = (v9 & 0xFFF00000) >> 20;
      *a3 = (v9 & 0xFFF00u) >> 8;
      rf_vfile_close_stdio_or_vpp(self);
      v4 = size;
      v11 = -1;
      rf_vfile_destruct_close_if_open(self);
      return v4;
    }
  }
  else
  {
    v11 = -1;
    rf_vfile_destruct_close_if_open(self);
    return 0;
  }
}

