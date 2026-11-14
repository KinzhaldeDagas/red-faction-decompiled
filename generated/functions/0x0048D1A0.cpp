// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0048D1A0 rf_ban_pattern_matches_ipv4_text
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, ban-list validation and wildcard matching, native text-reader capacity and list ownership, multiplayer process initialization and character-cache ABI): 
// Cdecl(pattern Cstring,address Cstring), full EAX Boolean. NULL either returns0. Initializes two4-int arrays to-1; copies pattern UNBOUNDED into local128-byte buffer, tokenizes with
// strtok delimiter '.'. Converts tokens via atoi until no token or token FIRST character '*'; no maximum-four bound while storing. Requires at least one parsed pattern component.
// Reuses same buffer for unbounded address copy and similarly parses address; requires exactly FOUR converted address tokens before stop. No digit/octet-range validation here, no
// wildcard-token-length check, no input mutation but global strtok state is changed.
// Compares first four slots in order. First pattern slot equal-1 returns(index>0), otherwise unequal address slot returns0; all four equal returns1. Thus omitted suffix is wildcard
// even without literal '*',and atoi result-1 also acts as wildcard sentinel. Leading wildcard fails because parsed count0. Extra tokens can overrun arrays BEFORE count validation;
// supplied address normally comes from inet_ntoa. This matcher does not call separate pattern validator48D6C0.
BOOL __cdecl rf_ban_pattern_matches_ipv4_text(char *a1, char *a2)
{
  char v3; // al
  int v4; // eax
  char v5; // al
  int v6; // eax
  char *v7; // [esp+8h] [ebp-C8h]
  char *v8; // [esp+Ch] [ebp-C4h]
  char *v9; // [esp+18h] [ebp-B8h]
  char *v10; // [esp+1Ch] [ebp-B4h]
  char String[128]; // [esp+20h] [ebp-B0h] BYREF
  _DWORD v12[4]; // [esp+A4h] [ebp-2Ch] BYREF
  int i; // [esp+B4h] [ebp-1Ch]
  _DWORD v14[4]; // [esp+B8h] [ebp-18h] BYREF
  int v15; // [esp+C8h] [ebp-8h]
  char *v16; // [esp+CCh] [ebp-4h]

  memset(v14, 255, sizeof(v14));
  memset(v12, 255, sizeof(v12));
  if ( !a1 || !a2 )
    return 0;
  v10 = a1;
  v9 = String;
  do
  {
    v3 = *v10;
    *v9++ = *v10++;
  }
  while ( v3 );
  v16 = strtok(String, ".");
  if ( !v16 )
    return 0;
  v15 = 0;
  do
  {
    if ( *v16 == 42 )
      break;
    v4 = atoi(v16);
    v14[v15++] = v4;
    v16 = strtok(nullptr, ".");
  }
  while ( v16 );
  if ( v15 <= 0 )
    return 0;
  v8 = a2;
  v7 = String;
  do
  {
    v5 = *v8;
    *v7++ = *v8++;
  }
  while ( v5 );
  v16 = strtok(String, ".");
  if ( !v16 )
    return 0;
  v15 = 0;
  do
  {
    if ( *v16 == 42 )
      break;
    v6 = atoi(v16);
    v12[v15++] = v6;
    v16 = strtok(nullptr, ".");
  }
  while ( v16 );
  if ( v15 != 4 )
    return 0;
  for ( i = 0; i < 4; ++i )
  {
    if ( v14[i] == -1 )
      return i > 0;
    if ( v14[i] != v12[i] )
      return 0;
  }
  return 1;
}

