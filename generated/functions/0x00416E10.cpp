// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00416E10 rf_clutter_skin108_copy_construct
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, clutter registry grammar/default retention,108-byte skin ownership, allocator cookies, native stack aliases and original flag-table strings): Thiscall destination plus source pointer,RET4. Copy-constructs name RFString0,copies raw DWORDcount8,EH copy-constructs ALL12 RFStrings at12 stride8 regardless sourcecount. String constructor allocates own text via C-string assignment;does not share ownership or preserve source reserve extent. Returns destinationEAX. Intended fresh storage;no existing-destination release/full-record staging/self-copy guard. Exact source==destination is NOT a safe copy-construction path because RFString constructor clears its buffer before reading aliased source.
char *__thiscall rf_clutter_skin108_copy_construct(char *this, char *a2)
{
  rf_string_copy_construct_from_object(this, (char **)a2);
  *((_DWORD *)this + 2) = *((_DWORD *)a2 + 2);
  `eh vector copy constructor iterator'(
    this + 12,
    a2 + 12,
    8u,
    12,
    (void (__thiscall *)(void *, void *))rf_string_copy_construct_from_object,
    rf_string_destroy_buffer);
  return this;
}

