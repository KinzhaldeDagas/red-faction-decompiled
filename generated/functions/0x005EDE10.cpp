// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005EDE10 rf_wave_mmio_close_handle_pointer
// UNREALRED VERIFIED [wave-codec-20261028]: If *caller HMMIO nonnull,calls mmioClose(handle,0) and nulls it regardless result. Returns pointer to caller handle. Does not free format buffers or ACM handle; no caller-pointer validation.
HMMIO *__cdecl rf_wave_mmio_close_handle_pointer(HMMIO *a1)
{
  HMMIO *result; // eax

  result = a1;
  if ( *a1 )
  {
    mmioClose(*a1, 0);
    *a1 = nullptr;
    return a1;
  }
  return result;
}

