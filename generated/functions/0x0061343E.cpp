// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0061343E crt_store_dword665A84_return_address
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Genuine runtime scalar setter, KEEP library flag. One cdecl DWORD argument. Calls613426 getter which returns ADDRESS665A84, stores raw argument DWORD through
// that pointer, returns same pointer in fullEAX. Does not return stored value or canonical bool, validate argument, allocate, take a lock or change neighboring globals. MOV EDI,EDI
// prologue is inert. Fresh getter native is MOV EAX,665A84/RET; caller is runtime timezone setup, but no broader timezone-field label is inferred.
int *__cdecl crt_store_dword665A84_return_address(int a1)
{
  int *result; // eax

  result = crt_address_of_00665a84();
  *result = a1;
  return result;
}

