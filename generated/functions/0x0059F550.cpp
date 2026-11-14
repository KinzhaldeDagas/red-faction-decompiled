// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0059F550 rf_vpackfile_enumerate_member_names_by_extensions
// UNREALRED VERIFIED [binary-fields-20261029]: cdecl extension-list text,allocated-name-buffer output,count output,optional archive-name filter. Splits comma-separated input by locating commas but copies exactly FIRST3 bytes of each token into4-byte NUL-terminated slots in68-byte local; no token length/count checks,whitespace trimming or leading-dot removal. Allocates128KiB with malloc,scans mounted archives in order (176-byte archive records),then24-byte member records,finds last dot in member name and compares extension case-insensitively to tokens. Optional archive filter is case-insensitive exact name. Appends matching member C strings including NUL into allocated buffer,increments count,adds final NUL,sets outputs,returns1. No128KiB capacity/malloc check,deduplication,sorting or lookup-precedence filtering. Caller owns malloc buffer; even zero matches returns allocated empty buffer.
int __cdecl rf_vpackfile_enumerate_member_names_by_extensions(char *a1, _DWORD *a2, _DWORD *a3, char *String1)
{
  char *v4; // ecx
  char *v5; // edx
  char v7; // [esp+13h] [ebp-85h]
  _BYTE *v8; // [esp+18h] [ebp-80h]
  char *v9; // [esp+1Ch] [ebp-7Ch]
  int k; // [esp+20h] [ebp-78h]
  char v11; // [esp+27h] [ebp-71h]
  int v12; // [esp+28h] [ebp-70h]
  char *last_char_wrapper; // [esp+2Ch] [ebp-6Ch]
  int j; // [esp+30h] [ebp-68h]
  char *String2; // [esp+34h] [ebp-64h]
  char v16[68]; // [esp+38h] [ebp-60h] BYREF
  _BYTE *v17; // [esp+80h] [ebp-18h]
  int v18; // [esp+84h] [ebp-14h]
  int v19; // [esp+88h] [ebp-10h]
  char *Str; // [esp+8Ch] [ebp-Ch]
  int v21; // [esp+90h] [ebp-8h]
  int i; // [esp+94h] [ebp-4h]

  v19 = 0;
  v17 = nullptr;
  v21 = 0;
  v18 = 0;
  Str = a1;
  *a3 = 0;
  *a2 = 0;
  do
  {
    v4 = &v16[4 * v18];
    v5 = Str;
    *(_WORD *)v4 = *(_WORD *)Str;
    v4[2] = v5[2];
    v16[4 * v18++ + 3] = 0;
    Str = rf_cstring_find_first_character(Str, 44);
    if ( Str )
      ++Str;
  }
  while ( Str );
  v17 = malloc(0x20000u);
  for ( i = 0; i < rf_vpackfile_count; ++i )
  {
    String2 = &rf_vpackfiles[176 * i];
    if ( !String1 || !_stricmp(String1, String2) )
    {
      for ( j = 0; j < *((_DWORD *)String2 + 41); ++j )
      {
        v12 = *((_DWORD *)String2 + 42) + 24 * j;
        last_char_wrapper = rf_cstring_find_last_char_wrapper(*(char **)(v12 + 4), 46);
        if ( last_char_wrapper )
        {
          v11 = 0;
          for ( k = 0; k < v18; ++k )
          {
            if ( !_stricmp(last_char_wrapper + 1, &v16[4 * k]) )
            {
              v11 = 1;
              break;
            }
          }
          if ( v11 )
          {
            v9 = *(char **)(v12 + 4);
            v8 = &v17[v19];
            do
            {
              v7 = *v9;
              *v8++ = *v9++;
            }
            while ( v7 );
            v19 += strlen(*(const char **)(v12 + 4)) + 1;
            ++v21;
          }
        }
      }
    }
  }
  v17[v19] = 0;
  *a2 = v17;
  *a3 = v21;
  return 1;
}

