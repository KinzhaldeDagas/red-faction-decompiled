// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00613460 crt_store_dword665A80_return_address
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Genuine runtime scalar setter, KEEP library flag. One cdecl rawDWORD. Getter613432 returns ADDRESS665A80, which receives argument unchanged; return address
// inEAX, not new value/success. No range/sign/unit validation, lock, allocation or adjacent state update. Fresh getter is MOV EAX,665A80/RET and existing caller is runtime timezone
// setup; retain numeric field identity.
int *__cdecl crt_store_dword665A80_return_address(int a1)
{
  int *result; // eax

  result = crt_address_of_00665a80();
  *result = a1;
  return result;
}

