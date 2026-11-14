// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005E6030 rf_m2v_read_whole_file_allocated
// UNREALRED VERIFIED [bitmap-decoders-20261028]: Arguments filename,output allocation pointer. Opens given name or fallback .m2v through default source0x98967F, obtains file size, allocates that many bytes and reads whole file. Success closes/destroys vfile and returns size. Read-status error closes, deletes allocation and returns0 WITHOUT nulling caller output, leaving dangling pointer. Open failure leaves output unchanged; allocation failure leaves null. No MPEG signature check, size cap or decoding; existing output allocation not freed first.
size_t __cdecl rf_m2v_read_whole_file_allocated(char *Str, char **a2)
{
  size_t v3; // [esp+4h] [ebp-244h]
  char v4[256]; // [esp+1Ch] [ebp-22Ch] BYREF
  int self[70]; // [esp+11Ch] [ebp-12Ch] BYREF
  size_t Size; // [esp+238h] [ebp-10h]
  int v7; // [esp+244h] [ebp-4h]

  rf_vfile_construct_unopened(self);
  v7 = 0;
  if ( (rf_vfile_open_with_extension_cache_control_paths(self, Str, 1, byte_98967F) >= 0
     || (rf_path_replace_last_dot_suffix_unbounded(v4, Str, ".m2v"),
         rf_vfile_open_with_extension_cache_control_paths(self, v4, 1, byte_98967F) >= 0))
    && (Size = rf_vfile_get_size((int)self, nullptr, (int)byte_98967F), (*a2 = (char *)operator new(Size)) != nullptr) )
  {
    rf_vfile_read_buffered_bytes_versioned(self, *a2, Size, 0, 0);
    if ( rf_vfile_get_open_slot_status(self) )
    {
      rf_vfile_close_stdio_or_vpp(self);
      operator delete(*a2);
      v7 = -1;
      rf_vfile_destruct_close_if_open(self);
      return 0;
    }
    else
    {
      rf_vfile_close_stdio_or_vpp(self);
      v3 = Size;
      v7 = -1;
      rf_vfile_destruct_close_if_open(self);
      return v3;
    }
  }
  else
  {
    v7 = -1;
    rf_vfile_destruct_close_if_open(self);
    return 0;
  }
}

