// IDA pseudocode evidence; not yet portable or build-ready.
// 0x006092FF _isprint
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Cdecl(raw int C), printable classification. If LIVE
// global2021B8C==0 read WORD[*(DWORD665A60)+2*C] and AND0x157; no local locale object and no input-range/byte-truncation guard. Nonzero global calls __isprint_l(C,NULLlocale) and
// returns delegate result. Preserve raw mask value, not Boolean. PE-initial665A60 points655470 with preceding zero WORD for C=-1; this is an initial table snapshot, not a promise
// that runtime pointer cannot change. No own errno/invalid handler or allocation.
int __cdecl isprint(int C)
{
  if ( unk_2021B8C )
    return _isprint_l(C, nullptr);
  else
    return off_665A60[C] & 0x157;
}

