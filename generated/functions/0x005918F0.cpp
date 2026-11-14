// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005918F0 rf_command_line_tokenize_in_place_with_quote_grouping
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, tokenizer ownership/quote rules, native hook contracts, observer registration, startup signaling and thread-exit/calling-convention paths): Cdecl mutable string and skip-first-logical-token byte. Clears50 global token pointer slots and consumed bytes, WITHOUT deleting prior token allocations or resetting global count1BA1EDC. Uses strtok with delimiters SPACE/TAB only, mutating source and sharing CRT tokenizer state. Copies tokens into unbounded local scratch; while quote-group flag set, joins subsequent tokens with single space. Toggles grouping ONLY when current token contains exactly ONE double quote (first quote==last quote); tokens with2+ quotes do not toggle, even odd3+. Preserves all quote/backslash bytes, no escape processing or quote stripping. When group closes, first completed group can be skipped once;
// otherwise allocates/copies scratch to token[count] and increments count with NO50-entry guard. Unterminated final group silently discarded. Reparse can leak cleared tokens and append beyond stale count. Index50 aliases globals: pointer store hits registry-init storage1BA1ED8; consumed-byte store hits LOW BYTE of count1BA1EDC. At count50 this resets count to0 before copy destination is reloaded591B97, so copy reloads token0 pointer instead of newly allocated slot50, then count increments to1. With normal first-pass token0 this overwrites that allocation; after reparse has cleared slot0 it instead reloads NULL. Normal return is final strtok NULL, not number of tokens.
char *__cdecl rf_command_line_tokenize_in_place_with_quote_grouping(char *String, char a2)
{
  char *result; // eax
  char *last_char_wrapper; // eax
  char v4; // [esp+Bh] [ebp-269h]
  _BYTE *v5; // [esp+10h] [ebp-264h]
  char *v6; // [esp+14h] [ebp-260h]
  char *v8; // [esp+2Ch] [ebp-248h]
  char *v9; // [esp+40h] [ebp-234h]
  char v10; // [esp+47h] [ebp-22Dh]
  _WORD *v11; // [esp+48h] [ebp-22Ch]
  char v12; // [esp+4Fh] [ebp-225h]
  char *v13; // [esp+54h] [ebp-220h]
  char *v14; // [esp+58h] [ebp-21Ch]
  char *first_character; // [esp+60h] [ebp-214h] BYREF
  char v16; // [esp+64h] [ebp-210h] BYREF
  _BYTE v17[3]; // [esp+65h] [ebp-20Fh] BYREF
  bool v18; // [esp+26Bh] [ebp-9h]
  int i; // [esp+26Ch] [ebp-8h]
  char *Str; // [esp+270h] [ebp-4h]

  v18 = 0;
  for ( i = 0; i < 50; ++i )
  {
    dword_1BA1D48[2 * i] = 0;
    byte_1BA1D4C[8 * i] = 0;
  }
  v16 = 0;
  result = strtok(String, " \t");
  for ( Str = result; Str; Str = result )
  {
    if ( v18 )
    {
      v11 = (_WORD *)((char *)&first_character + 3);
      do
      {
        v10 = *((_BYTE *)v11 + 1);
        v11 = (_WORD *)((char *)v11 + 1);
      }
      while ( v10 );
      *v11 = 32;
      v9 = &Str[strlen(Str) + 1];
      v8 = (char *)&first_character + 3;
      while ( *++v8 )
        ;
      qmemcpy(v8, Str, v9 - Str);
    }
    else
    {
      v14 = Str;
      v13 = &v16;
      do
      {
        v12 = *v14;
        *v13++ = *v14++;
      }
      while ( v12 );
    }
    first_character = rf_cstring_find_first_character(Str, 34);
    if ( first_character )
    {
      last_char_wrapper = rf_cstring_find_last_char_wrapper(Str, 34);
      if ( first_character == last_char_wrapper )
        v18 = !v18;
    }
    if ( !v18 )
    {
      if ( a2 )
      {
        a2 = 0;
      }
      else
      {
        dword_1BA1D48[2 * dword_1BA1EDC] = (int)operator new(&v17[strlen(&v16)] - v17 + 1);
        byte_1BA1D4C[8 * dword_1BA1EDC] = 0;
        v6 = &v16;
        v5 = (_BYTE *)dword_1BA1D48[2 * dword_1BA1EDC];
        do
        {
          v4 = *v6;
          *v5++ = *v6++;
        }
        while ( v4 );
        ++dword_1BA1EDC;
        v16 = 0;
      }
    }
    result = strtok(nullptr, " \t");
  }
  return result;
}

