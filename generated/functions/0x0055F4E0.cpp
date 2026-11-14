// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0055F4E0 rf_string_set_single_char_return_buffer
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, relative timestamp serialization, RFString extent/buffer ownership, bounded text-log branches and tagged model lookups): ECX8byte RFString plus char, RET4. Releases existing buffer with extent-preserving helper, sets extent0=1, allocates2bytes through new[], writes supplied byte then NUL terminator, returns BUFFER pointer bits rather than object. Even suppliedNUL still leaves positive stored extent1. No null-allocation guard.
char *__thiscall rf_string_set_single_char_return_buffer(void *this, char a2)
{
  char *result; // eax

  rf_string_release_buffer_keep_extent(this);
  *(_DWORD *)this = 1;
  *((_DWORD *)this + 1) = operator new[](*(_DWORD *)this + 1);
  **((_BYTE **)this + 1) = a2;
  result = *((char **)this + 1);
  result[1] = 0;
  return result;
}

