// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00607118 ?_store_num@@YAXHHPAPADPAII@Z
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Mixed ABI EAX=signed value,EDX=unsigned
// width,ECX=remainingCounter*,EDI=outputPointerSlot*,ONE caller-popped stack DWORD alternateFlag. VOID; no NUL append, pointer validation, errno, allocation or sign formatting. Fixed
// mode flag0: if unsigned width>=remaining, set remaining0 WITHOUT output writes/advance. Else emit EXACT width digits RIGHT-TO-LEFT using SIGNED IDIV10/remainder+ASCII0,
// zero-padding positive short values and discarding higher digits if value too wide; advance output by width/decrement remaining by width. Width0 with remaining>0 does nothing.
// Negative values use signed negative remainders directly, no abs/minus, so non-digit bytes possible. Alternate mode any nonzero flag IGNORES width. If remaining>1, do at least one
// signed division/emission of low digit, advance/decrement, repeat only while quotient>0 AND remaining>1; reserve one byte but NEVER set failure when value has more digits. Reverse
// emitted bytes in place using DO-WHILE swap. Truncated positive value retains least-significant digits, reversed into normal order (e.g12345 with remaining4 emits345,remaining1),
// caller can treat it as success. Crucially if initial remaining<=1, emit NOTHING yet STILL execute reversal once: swap byte at current output with byte at output-1, leave
// output/count unchanged. No guard for this preceding-byte access. Caller-facing counters do not distinguish this path or truncation; ESI/EBX preserved, EDI register unchanged while
// pointed slot updated.
void __usercall _store_num(int a1@<eax>, unsigned int a2@<edx>, unsigned int *a3@<ecx>, char **a4@<edi>, int a5)
{
  char *v5; // esi
  int v6; // et2
  char *v7; // eax
  char *v8; // esi
  char v9; // cl
  int v10; // esi
  int v11; // et2
  int v12; // [esp+8h] [ebp-4h]

  v12 = 0;
  if ( a5 )
  {
    v5 = *a4;
    if ( *a3 > 1 )
    {
      do
      {
        v6 = a1 % 10;
        a1 /= 10;
        *v5++ = v6 + 48;
        --*a3;
      }
      while ( a1 > 0 && *a3 > 1 );
    }
    v7 = *a4;
    *a4 = v5;
    v8 = v5 - 1;
    do
    {
      v9 = *v8;
      *v8-- = *v7;
      *v7++ = v9;
    }
    while ( v7 < v8 );
  }
  else if ( a2 >= *a3 )
  {
    *a3 = 0;
  }
  else
  {
    v10 = a2 - 1;
    if ( a2 )
    {
      do
      {
        v11 = a1 % 10;
        a1 /= 10;
        ++v12;
        (*a4)[v10--] = v11 + 48;
      }
      while ( v10 != -1 );
    }
    *a4 += v12;
    *a3 -= v12;
  }
}

