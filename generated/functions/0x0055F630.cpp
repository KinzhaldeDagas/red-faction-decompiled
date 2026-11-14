// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0055F630 rf_string_construct_single_char
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, relative timestamp serialization, RFString extent/buffer ownership, bounded text-log branches and tagged model lookups): ECX8byte RFString plus char, RET4. First sets buffer4=NULL (extent initially untouched), then55F4E0 allocates2bytes and sets extent1/content byte plus NUL. Returns object, unlike setter buffer return. Intended fresh-object constructor; overwriting a live object buffer pointer first would lose that allocation.
void *__thiscall rf_string_construct_single_char(void *this, char a2)
{
  *((_DWORD *)this + 1) = 0;
  rf_string_set_single_char_return_buffer(this, a2);
  return this;
}

