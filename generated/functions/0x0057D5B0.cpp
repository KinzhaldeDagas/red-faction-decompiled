// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0057D5B0 rf_stream_adapter_read_bytes
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, character bone hierarchy, adapter branches, action/trigger callers and PE-verified affine constants): Mode0 delegates to versioned virtual-file bulk reader with minimumversion0/default0. Nonzero mode copies requested bytes from memory+cursor only if signed(cursor+size)<length, then advances and returns size. EXACT-END reads fail, unlike typed scalar readers which allow <=. Failure sets error+84=-1, returns0 and leaves destination/cursor unchanged. Size arithmetic is unchecked; no NULL/negative-size validation.
int __thiscall rf_stream_adapter_read_bytes(int **this, char *a2, size_t Size)
{
  if ( !*this )
    return rf_vfile_read_buffered_bytes_versioned(*(this + 1), a2, Size, 0, 0);
  if ( (int)((int)*(this + 3) + Size) < (int)*(this + 4) )
  {
    memcpy(a2, (char *)*(this + 2) + (_DWORD)*(this + 3), Size);
    *(this + 3) = (int *)((char *)*(this + 3) + Size);
    return Size;
  }
  else
  {
    *(this + 21) = (int *)-1;
    return 0;
  }
}

