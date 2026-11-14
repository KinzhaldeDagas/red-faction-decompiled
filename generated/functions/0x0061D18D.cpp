// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0061D18D __fltout2
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Decimal record layout from native accesses:16 bytes
// {int sign at0 (45 means negative),int decimalPoint at4,int conversionStatus at8,char* digits at12}. Cdecl(double value,record*,digitBuffer,unsigned capacity), returns record
// pointer; corrected two misleading int parameters to ONE by-value binary64 occupying8 bytes (total20 caller-popped bytes unchanged). dtold(local10byteExtended,&stackDouble);
// allocate12-byte outgoing slot, copy EXACT10 extended bytes using two MOVSD+MOVSW, leave upper2 padding uninitialized. I10_OUTPUT(packedExtended12byteSlot,17,0,&localOutput) returns
// status ->record+8. Sign-extend local signed BYTE+2 to record.sign, signed WORD+0 to record.decimalPoint. strcpy_s(digitBuffer,capacity,localOutput+4); failure Watson5zeros (no own
// recovery). Publish record.digits=digitBuffer, return record; cookie checked. No own NULL/capacity/input-class validation, errno assignment or floating arithmetic; extended
// conversion and decimal-generation policy delegated, I10 status is recorded rather than used to skip copy.
_DWORD *__cdecl _fltout2(double a1, _DWORD *a2, char *a3, rsize_t SizeInBytes)
{
  _DWORD *v4; // ebx
  char *Destination; // [esp+Ch] [ebp-30h]
  __int16 v7; // [esp+10h] [ebp-2Ch] BYREF
  char v8; // [esp+12h] [ebp-2Ah]
  char Source[24]; // [esp+14h] [ebp-28h] BYREF
  unsigned __int64 v10; // [esp+2Ch] [ebp-10h] BYREF
  unsigned __int16 v11; // [esp+34h] [ebp-8h]

  v4 = a2;
  Destination = a3;
  __dtold((int *)&v10, (int *)&a1);
  v4[2] = _I10_OUTPUT(v10, v11, 17, 0, &v7);
  *v4 = v8;
  v4[1] = v7;
  if ( strcpy_s(Destination, SizeInBytes, Source) )
    _invoke_watson(nullptr, nullptr, nullptr, 0, 0);
  v4[3] = Destination;
  return v4;
}

