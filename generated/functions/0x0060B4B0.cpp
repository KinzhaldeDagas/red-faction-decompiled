// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060B4B0 _strtol
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Cdecl(const text*,char**end,int radix), signed32
// return. Call strtoxl(locale,text,end,radix,flags0); LIVE global2021B8C==0 selects address665A78 static locale-info object, nonzero selects literalNULL (delegate acquires current
// locale). Reclaim20 forwarded stack bytes; forward raw EAX as signed int. No own validation, parse/whitespace/base logic, locale snapshot, errno assignment, lock or result
// normalization; all conversion/end-pointer/range behavior belongs to reviewed helper.
int __cdecl strtol(const char *String, char **EndPtr, int Radix)
{
  if ( unk_2021B8C )
    return strtoxl(nullptr, String, (const char **)EndPtr, Radix, 0);
  else
    return strtoxl((struct localeinfo_struct *)&off_665A78, String, (const char **)EndPtr, Radix, 0);
}

