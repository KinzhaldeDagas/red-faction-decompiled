// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0061D011 __fptostr
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Decimal record layout from native accesses:16 bytes
// {int sign at0 (45 means negative),int decimalPoint at4,int conversionStatus at8,char* digits at12}. Cdecl(output,unsigned capacity,int requestedDigits,record*), return0/22/34. Load
// record.digits BEFORE output validation. NULL output or capacity0 -> errno22,invalid_parameter5zeros,22. Otherwise clear output[0]; require unsigned
// capacity>max(requestedDigits,0)+1 (modulo32), else errno34/invalid34. Write leading spare '0'; if requestedDigits>0 copy exactly that many source bytes, advance source only while
// nonNUL, pad exhausted source with '0'; NUL terminate. If remaining signed count>=0 (zero after positive copy,0 for zero request) AND SIGNED source byte>='5', increment retained
// decimal with carry backward over '9'. Negative requested count skips rounding, emits empty string after spare removal. If spare became '1', keep it and increment
// record.decimalPoint; else strlen(afterSpare)+1 and overlapping memcpy_0 shift left. No source-digit validation, record/input NULL guard, source length bound, sign emission or own
// locale. Carry uses half-up first-discarded-byte criterion, no sticky or ties-to-even logic; output can contain requestedDigits+1 digits after carry.
int __cdecl _fptostr(char *a1, unsigned int a2, int a3, _DWORD *a4)
{
  _DWORD *v4; // ecx
  char *v5; // edi
  int v6; // esi
  int v8; // edx
  int v9; // eax
  char *v10; // eax
  char v11; // cl
  size_t v12; // eax

  v4 = a4;
  v5 = (char *)a4[3];
  if ( !a1 || !a2 )
  {
    v6 = 22;
    *_errno() = 22;
LABEL_3:
    _invalid_parameter(nullptr, nullptr, nullptr, 0, 0);
    return v6;
  }
  v8 = a3;
  *a1 = 0;
  if ( a3 <= 0 )
    v9 = 0;
  else
    v9 = a3;
  if ( a2 <= v9 + 1 )
  {
    *_errno() = 34;
    v6 = 34;
    goto LABEL_3;
  }
  *a1 = 48;
  v10 = a1 + 1;
  if ( a3 > 0 )
  {
    do
    {
      v11 = *v5;
      if ( *v5 )
        ++v5;
      else
        v11 = 48;
      *v10++ = v11;
      --v8;
    }
    while ( v8 > 0 );
    v4 = a4;
  }
  *v10 = 0;
  if ( v8 >= 0 && *v5 >= 53 )
  {
    while ( *--v10 == 57 )
      *v10 = 48;
    ++*v10;
  }
  if ( *a1 == 49 )
  {
    ++v4[1];
  }
  else
  {
    v12 = strlen(a1 + 1);
    memcpy_0(a1, a1 + 1, v12 + 1);
  }
  return 0;
}

