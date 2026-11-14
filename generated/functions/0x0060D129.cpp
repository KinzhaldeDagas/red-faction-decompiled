// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060D129 __forcdecpt_l
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): LocaleUpdate607051 is constructed before own
// validation; normal return clears thread DWORD+112 mask2 iff its cleanup BYTE+12 is set. Decimal separator uses ONLY first byte of localeInfo+188 -> lconv -> decimal_point. No own
// SEH/finally for exceptions escaping helpers. Cdecl(mutable formattedString,locale), insert decimal separator in place with no size argument. Initially compare tolower(SIGNED first
// byte) with 'e'; if different increment pointer once, then continue advancing while isdigit(UNSIGNED current byte) nonzero. This intentionally skips an initial sign/first character,
// rather than scanning all characters for a point. At stopping pointer, tolower(SIGNED byte)=='x' advances another TWO bytes. Replace byte at selected pointer with decimal separator
// and rotate displaced bytes right until displaced NUL is written; loop reads one byte beyond the original NUL. No existing-point check, NULL/empty/malformed input guard, capacity
// check or status result. Existing AL/EAX return is incidental and can become locale-thread pointer on cleanup; retain stored type without claiming a meaningful char return. Assumes
// valid formatted input and spare byte.
char __cdecl _forcdecpt_l(char *a1, struct localeinfo_struct *a2)
{
  char *v2; // esi
  bool i; // zf
  char result; // al
  char *v5; // esi
  char v6; // cl
  int v8; // [esp+4h] [ebp-10h] BYREF
  int v9; // [esp+Ch] [ebp-8h]
  char v10; // [esp+10h] [ebp-4h]

  _LocaleUpdate::_LocaleUpdate((_LocaleUpdate *)&v8, a2);
  v2 = a1;
  for ( i = tolower(*a1) == 101; !i; i = isdigit((unsigned __int8)*v2) == 0 )
    ++v2;
  if ( tolower(*v2) == 120 )
    v2 += 2;
  result = *v2;
  *v2 = ***(_BYTE ***)(v8 + 188);
  v5 = v2 + 1;
  do
  {
    v6 = *v5;
    *v5 = result;
    result = v6;
  }
  while ( *v5++ );
  if ( v10 )
  {
    result = v9;
    *(_DWORD *)(v9 + 112) &= ~2u;
  }
  return result;
}

