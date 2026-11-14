// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060B79C _IsRootUNCName
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Internal ESI char* input, no incoming stack
// argument; preserves ESI, normalized boolean in EAX. strlen(input), no own NULL guard. Require length>=5, first TWO bytes each independently slash or backslash (mixed accepted),
// third byte nonseparator. Scan nonempty server to first separator, require nonempty share after it. Scan share to NUL/separator; accept NUL or ONE trailing separator immediately
// followed by NUL, reject further components/doubled trailing separators. No name/case/drive validation, locale or allocation. Native PUSH ESI supplies strlen argument despite
// misleading uninitialized decompiler temporary.
BOOL __usercall IsRootUNCName@<eax>(_BYTE *a1@<esi>)
{
  char v1; // al
  char v2; // al
  _BYTE *v3; // eax
  char v4; // cl
  char *v5; // eax
  char v6; // cl
  const char *v8; // [esp+0h] [ebp-4h]

  if ( strlen(v8) < 5 || *a1 != 92 && *a1 != 47 )
    return 0;
  v1 = a1[1];
  if ( v1 != 92 && v1 != 47 )
    return 0;
  v2 = a1[2];
  if ( v2 == 92 )
    return 0;
  if ( v2 == 47 )
    return 0;
  v3 = a1 + 3;
  v4 = a1[3];
  if ( !v4 )
    return 0;
  do
  {
    if ( v4 == 92 )
      break;
    if ( v4 == 47 )
      break;
    v4 = *++v3;
  }
  while ( *v3 );
  if ( !*v3 )
    return 0;
  v5 = v3 + 1;
  if ( !*v5 )
    return 0;
  v6 = *v5;
  do
  {
    if ( v6 == 92 )
      break;
    if ( v6 == 47 )
      break;
    v6 = *++v5;
  }
  while ( *v5 );
  return !*v5 || !v5[1];
}

