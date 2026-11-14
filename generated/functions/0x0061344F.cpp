// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0061344F crt_store_dword665A88_return_address
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Genuine runtime scalar setter, KEEP library flag. Cdecl one rawDWORD. Call61342C returns ADDRESS665A88; store argument there, forward that pointer inEAX. No
// argument validation, conversion, lock, allocation or neighboring-global write; EDI unchanged by hotpatch MOV EDI,EDI. Fresh getter native proves the fixed address; runtime timezone
// caller supplies classification context without assuming this numeric field's authored name.
int *__cdecl crt_store_dword665A88_return_address(int a1)
{
  int *result; // eax

  result = crt_address_of_00665a88();
  *result = a1;
  return result;
}

