// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00560090 rf_string_assign_single_char_return_self
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, relative timestamp serialization, RFString extent/buffer ownership, bounded text-log branches and tagged model lookups): ECX RFString plus char, RET4. If stored extent exactly1, writes buffer[0]=char,buffer[1]=NUL WITHOUT checking buffer pointer or reallocating. Thus prior release leaving extent1/bufferNULL can fault here. Other extents release buffer then55F4E0 releases again (second is harmless after nulling), allocates2bytes/extent1. Returns object; charNUL still keeps extent1.
void *__thiscall rf_string_assign_single_char_return_self(void *this, char a2)
{
  if ( *(_DWORD *)this == 1 )
  {
    **((_BYTE **)this + 1) = a2;
    *(_BYTE *)(*((_DWORD *)this + 1) + 1) = 0;
  }
  else
  {
    rf_string_release_buffer_keep_extent(this);
    rf_string_set_single_char_return_buffer(this, a2);
  }
  return this;
}

