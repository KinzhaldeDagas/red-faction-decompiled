// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00620B05 _copy_environ
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Internal EAX=source char**, returns new char**/NULL.
// NULLsource ->NULL. Count entries,calloc_crt(count+1,4); NULL ->amsg_exit(9) fatal path, no normal graceful fallback. Each entry strdup independently, result stored WITHOUT checking
// for NULL; continue later entries even after strdup failure, so returned array may have interiorNULL and later live allocations. Final NULL slot appended. Source untouched; caller
// owns duplicated array/strings. No lock, rollback, partial strdup cleanup or count overflow precheck.
char **__usercall copy_environ@<eax>(const char **a1@<eax>)
{
  char **result; // eax
  const char **v3; // ecx
  char **v4; // esi
  char **v5; // [esp+4h] [ebp-4h]

  result = nullptr;
  v3 = a1;
  if ( a1 )
  {
    if ( *a1 )
    {
      do
      {
        ++v3;
        result = (char **)((char *)result + 1);
      }
      while ( *v3 );
    }
    v4 = (char **)_calloc_crt((size_t)result + 1, 4u);
    v5 = v4;
    if ( !v4 )
      _amsg_exit(9);
    while ( *a1 )
      *v4++ = _strdup(*a1++);
    *v4 = nullptr;
    return v5;
  }
  return result;
}

