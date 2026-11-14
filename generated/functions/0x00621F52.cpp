// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00621F52 __strdup
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Cdecl(source), returns newly allocated duplicate or
// NULL. NULL source returnsNULL without errno/invalid-handler call. Otherwise strlen(source)+1 computed with unchecked32-bit increment, malloc that byte count; NULL allocation
// returnsNULL, allocator error policy delegated. Successful allocation calls strcpy_s(newBuffer,lengthPlus1,source); any nonzero status invokes Watson(NULL,NULL,NULL,0,0). If Watson
// unexpectedly returns, return same allocation; no free or NULL remap. Success transfers allocation pointer to caller. Source is scanned twice and not snapshotted, no own
// length-overflow/overlap check or rollback on copy failure.
char *__cdecl _strdup(const char *Source)
{
  size_t v2; // esi
  char *v3; // eax
  char *v4; // edi

  if ( !Source )
    return nullptr;
  v2 = strlen(Source) + 1;
  v3 = (char *)malloc(v2);
  v4 = v3;
  if ( !v3 )
    return nullptr;
  if ( strcpy_s(v3, v2, Source) )
    _invoke_watson(nullptr, nullptr, nullptr, 0, 0);
  return v4;
}

