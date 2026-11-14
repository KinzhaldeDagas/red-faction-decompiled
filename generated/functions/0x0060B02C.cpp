// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060B02C _toupper
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Cdecl(int C). LIVE global2021B8C0:
// unsigned(C-97)<=25 =>return C-32; all other32-bit values unchanged. Nonzero global calls toupper_l(C,NULLlocale). ASCII range test uses wrapped subtraction and unsigned comparison;
// no byte cast, table read, own errno or invalid handler in fast path.
int __cdecl toupper(int C)
{
  int result; // eax

  if ( unk_2021B8C )
    return _toupper_l(C, nullptr);
  result = C;
  if ( (unsigned int)(C - 97) <= 0x19 )
    return C - 32;
  return result;
}

