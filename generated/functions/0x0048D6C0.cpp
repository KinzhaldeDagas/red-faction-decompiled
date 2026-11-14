// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0048D6C0 rf_ban_pattern_text_is_valid
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, ban-list validation and wildcard matching, native text-reader capacity and list ownership, multiplayer process initialization and character-cache ABI): 
// Cdecl Cstring, full EAX Boolean; noNULL guard before strlen. Rejects unsigned length>255, copies including NUL into local260-byte buffer. Starts strtok with '.' (so delimiter runs
// collapse). Numeric token must contain only ASCII digits according to48D5E0 and atoi result must signed-range0..255; no explicit decimal-overflow handling. Counts numeric
// components. After numeric component3, calls strtok(NULL,EMPTY delimiter at639337), taking entire remaining suffix as fourth token; other numeric steps use '.'. After fourth numeric
// rejects any further token; exhausted stream valid only count==4.
// A token starting '*' requires token length EXACT1, then strtok(NULL,EMPTY delimiter at639336) must returnNULL and preceding numeric count must be nonzero. Bare '*' invalid;
// terminal wildcard after positive prefix accepted. Original639336/337 bytes are BOTH NUL. Does not canonicalize original text, store list entry or call matcher. Because initial
// strtok skips repeated dots, this is not a strict lexical dotted-quad parser; preserve exact delimiter-switch behavior.
BOOL __cdecl rf_ban_pattern_text_is_valid(const char *a1)
{
  char v2; // [esp+13h] [ebp-135h]
  char *v3; // [esp+18h] [ebp-130h]
  const char *v4; // [esp+1Ch] [ebp-12Ch]
  char String[260]; // [esp+38h] [ebp-110h] BYREF
  int v6; // [esp+140h] [ebp-8h]
  char *v7; // [esp+144h] [ebp-4h]

  if ( strlen(a1) > 0xFF )
    return 0;
  v4 = a1;
  v3 = String;
  do
  {
    v2 = *v4;
    *v3++ = *v4++;
  }
  while ( v2 );
  v7 = strtok(String, ".");
  if ( !v7 )
    return 0;
  v6 = 0;
  while ( *v7 != 42 )
  {
    if ( rf_cstring_contains_non_decimal_digit(v7) )
      return 0;
    if ( (unsigned int)atoi(v7) >= 0x100 )
      return 0;
    if ( ++v6 == 3 )
      v7 = strtok(nullptr, &byte_639337);
    else
      v7 = strtok(nullptr, ".");
    if ( v6 == 4 && v7 )
      return 0;
    if ( !v7 )
      return v6 == 4;
  }
  if ( strlen(v7) > 1 )
    return 0;
  if ( strtok(nullptr, &byte_639336) )
    return 0;
  return v6 != 0;
}

