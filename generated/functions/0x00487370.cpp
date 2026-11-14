// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00487370 sub_487370
// UNREALRED VERIFIED [ai-authored-startup-20261028] Authored waypoint traversal method parser: exact case-insensitive Loop returns1, Ping Pong returns2, every other string returns0. No trimming or alternate aliases observed.
int __cdecl sub_487370(char *String1)
{
  int v2; // [esp+0h] [ebp-4h]

  v2 = 0;
  if ( !_stricmp(String1, "Loop") )
    return 1;
  if ( !_stricmp(String1, "Ping Pong") )
    return 2;
  return v2;
}

