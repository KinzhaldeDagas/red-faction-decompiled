// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060D296 __shift
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Internal registers EAX sourceCString, EDI signed/raw byte displacement. Displacement0 returns original sourceEAX with no memory read. Otherwise
// strlen(source)+1 with32 wrap, call memcpy_0(dest=source+displacement wrapped,source,lengthIncludingNUL). ADD16 reclaims three copy slots PLUS old strlen argument; return copy
// delegateEAX, restore callerESI. No allocation/capacity/delta/overlap validation; delegated copy owns overlap behavior, not inferred from old memcpy label.
const char *__usercall _shift@<eax>(const char *result@<eax>, int a2@<edi>)
{
  const char *v2; // esi
  size_t v3; // eax

  v2 = result;
  if ( a2 )
  {
    v3 = strlen(result);
    return (const char *)memcpy_0((void *)&v2[a2], v2, v3 + 1);
  }
  return result;
}

