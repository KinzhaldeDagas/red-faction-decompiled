// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060D23A __fassign_l
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Cdecl(isDouble,destination,textPointer,locale),
// returns destination in EAX (corrected third argument from int to char*). Any nonzero isDouble calls verified parse_string_to_binary64_locale into local8 bytes and copies both raw
// DWORDs to destination; zero calls binary32 parser into local copy of first stack parameter and copies one DWORD. BOTH parser status returns ignored; always copy produced raw
// representation if helper returns. No NULL/length/alignment validation, own locale snapshot, errno assignment, range/status propagation or x87 load/store. Parser conversion/error
// semantics delegated.
int *__cdecl _fassign_l(int a1, int *a2, char *a3, struct localeinfo_struct *a4)
{
  int *result; // eax
  int v5[2]; // [esp+0h] [ebp-8h] BYREF

  if ( a1 )
  {
    crt_parse_string_to_binary64_locale((int)v5, a3, a4);
    result = a2;
    *a2 = v5[0];
    result[1] = v5[1];
  }
  else
  {
    crt_parse_string_to_binary32_locale((int)&a1, a3, a4);
    result = a2;
    *a2 = a1;
  }
  return result;
}

