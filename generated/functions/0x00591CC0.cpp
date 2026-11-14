// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00591CC0 rf_command_line_capture_option_following_argument
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, command-line option ownership, loose lookup return semantics, VPP location, stream flags/status and file-attribute paths): Cdecl option pointer and token index. Marks option token consumed at1BA1D4C+8*index. If option byte+21 needs argument, considers immediately next token only. Out-of-count next token silently leaves prior value. Next token starting minus formats diagnostic via unbounded sprintf into260-byte LOCAL buffer, returns low byte formatter count without printing/fatal here and without consuming next token. Nonempty acceptable token allocates strlen+1, unbounded-copies into option+16, marks argument consumed; does NOT delete old value before replacement. Empty token leaves previous value and argument unconsumed. AL return incidental, not reliable success. No index/NULL/allocation checks.
char __cdecl rf_command_line_capture_option_following_argument(int a1, int a2)
{
  char result; // al
  char v3; // [esp+3h] [ebp-131h]
  char *v4; // [esp+8h] [ebp-12Ch]
  char *v5; // [esp+Ch] [ebp-128h]
  char *v7; // [esp+18h] [ebp-11Ch]
  char *v8; // [esp+1Ch] [ebp-118h]
  int v9; // [esp+24h] [ebp-110h]
  char Buffer[260]; // [esp+2Ch] [ebp-108h] BYREF

  result = a2;
  byte_1BA1D4C[8 * a2] = 1;
  if ( *(_BYTE *)(a1 + 21) )
  {
    result = a2 + 1;
    v9 = a2 + 1;
    if ( a2 + 1 < dword_1BA1EDC )
    {
      if ( *(_BYTE *)dword_1BA1D48[2 * v9] == 45 )
      {
        return sprintf(
                 Buffer,
                 "Command line parameter %s requires argument, but next argument appears to be option (%s)\n",
                 (const char *)dword_1BA1D48[2 * a2],
                 (const char *)dword_1BA1D48[2 * v9]);
      }
      else
      {
        v8 = (char *)dword_1BA1D48[2 * v9];
        v7 = v8 + 1;
        do
          result = *v8;
        while ( *v8++ );
        if ( v8 - v7 > 0 )
        {
          *(_DWORD *)(a1 + 16) = operator new(v8 - v7 + 1);
          v5 = (char *)dword_1BA1D48[2 * v9];
          v4 = *(char **)(a1 + 16);
          do
          {
            v3 = *v5;
            *v4 = *v5;
            result = (_BYTE)v5++ + 1;
            ++v4;
          }
          while ( v3 );
          byte_1BA1D4C[8 * v9] = 1;
        }
      }
    }
  }
  return result;
}

