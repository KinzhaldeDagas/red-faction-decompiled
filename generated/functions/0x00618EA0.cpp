// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00618EA0 __fltin2
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Cdecl(outputRecord*,textPointer,UNUSED
// rawLength,UNUSED arg3,UNUSED arg4,LocaleUpdate*), returns outputRecord. Corrected second/sixth pointer types. Parser call
// strgtold12_l(local12byteValue,&localEnd,text,0,0,0,0,localeUpdate), eight caller-popped slots. Raw input arguments at+16/+20/+24 are NEVER READ; apparent length is NOT a bound. If
// parserFlags mask4, SKIP binary64 converter, status512, force local result bits0. Otherwise ALWAYS convert local12-byte value to binary64; set status128 iff parserFlags mask2 OR
// converter result1; independently OR256 iff parserFlags mask1 OR converter result2 (both can coexist). Output writes ONLY DWORD0 status, DWORD4 endPointer-text modulo32, DWORD16/20
// raw binary64; bytes8..15 untouched. No string/record NULL validation, length restriction, full-consumption check, own locale acquisition/cleanup or own errno assignment. Parser and
// converter semantics delegated; cookie checked while preserving record EAX.
_DWORD *__cdecl _fltin2(_DWORD *a1, char *a2, int a3, int a4, int a5, _LocaleUpdate *a6)
{
  int v6; // ebx
  int v7; // eax
  char *v9; // [esp+Ch] [ebp-24h] BYREF
  char *v10; // [esp+10h] [ebp-20h]
  unsigned int v11; // [esp+14h] [ebp-1Ch] BYREF
  int v12; // [esp+18h] [ebp-18h]
  int v13; // [esp+1Ch] [ebp-14h]
  unsigned __int8 v14[12]; // [esp+20h] [ebp-10h] BYREF

  v10 = a2;
  v6 = 0;
  v13 = __strgtold12_l(v14, &v9, a2, 0, 0, 0, 0, a6);
  if ( (v13 & 4) != 0 )
  {
    v6 = 512;
    v11 = 0;
    v12 = 0;
  }
  else
  {
    v7 = crt_ld12_to_binary64(v14, &v11);
    if ( (v13 & 2) != 0 || v7 == 1 )
      v6 = 128;
    if ( (v13 & 1) != 0 || v7 == 2 )
      v6 |= 0x100u;
  }
  a1[1] = v9 - v10;
  a1[4] = v11;
  a1[5] = v12;
  *a1 = v6;
  return a1;
}

