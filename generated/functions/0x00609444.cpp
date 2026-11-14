// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00609444 _tolower
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Cdecl(int C). LIVE global2021B8C0:
// unsigned(C-65)<=25 =>return C+32; every other32-bit input returned unchanged, including EOF/high bytes. Nonzero global forwards to tolower_l(C,NULLlocale), retaining its different
// out-of-range handling. No own locale update, errno or invalid-handler call.
int __cdecl tolower(int C)
{
  int result; // eax

  if ( unk_2021B8C )
    return _tolower_l(C, nullptr);
  result = C;
  if ( (unsigned int)(C - 65) <= 0x19 )
    return C + 32;
  return result;
}

