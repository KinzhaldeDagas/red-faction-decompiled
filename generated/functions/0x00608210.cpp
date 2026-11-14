// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00608210 _swap
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Register bytewise swap: EAX left pointer,ECX right pointer,EDX raw count copiedESI. Equal pointers or count0 skips. Otherwise sequentially read both bytes,
// store swapped, decrement count and advance BOTH pointers until wrapped count0. Returns advanced leftEAX; rightECX also advances. No signed-negative rejection, overlap/range/NULL
// guard, block allocation or temporary whole-range copy. ESI/EBX preserved; negative count may execute huge wrapped loop.
char *__usercall swap@<eax>(char *result@<eax>, int a2@<edx>, char *a3@<ecx>)
{
  int v3; // esi
  char v4; // dl

  v3 = a2;
  if ( result != a3 && a2 )
  {
    do
    {
      v4 = *result;
      *result = *a3;
      --v3;
      *a3 = v4;
      ++result;
      ++a3;
    }
    while ( v3 );
  }
  return result;
}

