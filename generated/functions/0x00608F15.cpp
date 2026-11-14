// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00608F15 _strtok
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Cdecl(optional writable string, delimiter string),
// returns token pointer into original string or NULL. Calls getptd first, builds zeroed 32-byte bitmap from delimiter bytes INCLUDING delimiter NUL. NonNULL string starts a new scan;
// NULL uses threadData DWORD+0x18 as saved cursor, without checking that cursor. Skip leading delimiters until NUL or nonmember; mark token start, then scan to NUL or next delimiter.
// A found nonzero delimiter is overwritten with NUL and cursor advances one byte; at natural end cursor remains at terminator. Always store cursor back at threadData+0x18. Return
// token iff final cursor differs from start; delimiter-only/empty input returns NULL. Consecutive delimiters do not produce empty tokens. Delimiter map rebuilt on each call, so later
// calls may use different delimiters. Security-cookie epilogue; no own input validation, allocation or cross-thread global cursor.
char *__cdecl strtok(char *String, const char *Delimiter)
{
  char v3; // dl
  char *v4; // edx
  char *v5; // ebx
  DWORD *v7; // [esp+10h] [ebp-28h]
  _BYTE v8[32]; // [esp+14h] [ebp-24h] BYREF

  v7 = _getptd();
  memset(v8, 0, sizeof(v8));
  do
  {
    v3 = *Delimiter;
    v8[*(unsigned __int8 *)Delimiter >> 3] |= 1 << (*Delimiter & 7);
    ++Delimiter;
  }
  while ( v3 );
  v4 = String;
  if ( !String )
    v4 = (char *)v7[6];
  while ( ((unsigned __int8)(1 << (*v4 & 7)) & v8[(unsigned __int8)*v4 >> 3]) != 0 && *v4 )
    ++v4;
  v5 = v4;
  while ( *v4 )
  {
    if ( ((unsigned __int8)(1 << (*v4 & 7)) & v8[(unsigned __int8)*v4 >> 3]) != 0 )
    {
      *v4++ = 0;
      break;
    }
    ++v4;
  }
  v7[6] = (DWORD)v4;
  return v4 != v5 ? v5 : nullptr;
}

