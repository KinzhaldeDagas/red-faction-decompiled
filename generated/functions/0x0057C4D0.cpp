// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0057C4D0 rf_path_copy_basename_after_backslash
// UNREALRED VERIFIED [vpp-streaming] Copies only the suffix after the final backslash, or the whole input when no backslash exists. Virtual-file lookup uses this basename canonicalization.
_BYTE *__cdecl rf_path_copy_basename_after_backslash(_BYTE *a1, char *Str)
{
  char v2; // cl
  _BYTE *result; // eax
  char v4; // cl
  _BYTE *v5; // [esp+8h] [ebp-30h]
  char *v6; // [esp+Ch] [ebp-2Ch]
  _BYTE *v7; // [esp+28h] [ebp-10h]
  char *v8; // [esp+2Ch] [ebp-Ch]
  char *v9; // [esp+34h] [ebp-4h]

  v9 = strrchr(Str, 92);
  if ( v9 )
  {
    strlen(v9 + 1);
    v6 = v9 + 1;
    v5 = a1;
    do
    {
      v4 = *v6;
      *v5 = *v6++;
      result = ++v5;
    }
    while ( v4 );
  }
  else
  {
    v8 = Str;
    v7 = a1;
    do
    {
      v2 = *v8;
      *v7 = *v8++;
      result = ++v7;
    }
    while ( v2 );
  }
  return result;
}

