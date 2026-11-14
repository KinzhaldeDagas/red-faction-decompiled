// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0061F527 ?x_ismbbtype_l@@YAHPAUlocaleinfo_struct@@IHH@Z
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Cdecl(optional locale,raw character slot,int
// ctypeMask,raw mbMask slot). Construct LocaleUpdate, truncate character and mbMask each to unsigned low8. If BYTE[mbinfo+29+character]&mbMask nonzero return1 immediately; else when
// ctypeMask!=0 read WORD[classTable+2*character]&ctypeMask, normalize any nonzero to1; zero mask/result ->0. Thus Boolean OR of two different classification tables, with
// short-circuiting and full32-bit ctype mask but byte mb mask. No own errno/invalid handler, lead-byte expansion or pointer validation. All own normal returns after locale
// construction clear threadData+0x70 mask0x2 only if local update-object byte+12 is nonzero; nested supplied-locale objects do not acquire another pin. There is no SEH/finally
// cleanup in this body if a helper throws.
int __cdecl x_ismbbtype_l(struct localeinfo_struct *a1, char a2, int a3, char a4)
{
  int result; // eax
  _DWORD v5[2]; // [esp+0h] [ebp-10h] BYREF
  int v6; // [esp+8h] [ebp-8h]
  char v7; // [esp+Ch] [ebp-4h]

  _LocaleUpdate::_LocaleUpdate((_LocaleUpdate *)v5, a1);
  if ( ((unsigned __int8)a4 & *(_BYTE *)(v5[1] + (unsigned __int8)a2 + 29)) != 0
    || (!a3
      ? (result = 0)
      : (result = (unsigned __int16)(a3 & *(_WORD *)(*(_DWORD *)(v5[0] + 200) + 2 * (unsigned __int8)a2))),
        result) )
  {
    result = 1;
  }
  if ( v7 )
    *(_DWORD *)(v6 + 112) &= ~2u;
  return result;
}

