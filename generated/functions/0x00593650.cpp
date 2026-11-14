// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00593650 rf_vfile_rename_loose_source_with_same_directory_prefix
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, command-line option ownership, loose lookup return semantics, VPP location, stream flags/status and file-attribute paths): Thiscall VFile, new basename/text, optional old filename, resolver context (RET12). Nonnull old filename re-resolves, false result returns-4; NULL uses existing fields. Packed member+264 nonzero returns-3. Unbounded-copies source path into256-byte local, finds last BACKSLASH and writes NUL there WITHOUT no-separator guard; builds new path via unbounded sprintf(other256,"%s\%s",directory,newName). CRT rename failure returns-99999; success copies destination to receiver+5 and returns0. No new-name separator/traversal validation, root-id change, lookup-cache update, attribute clearing or open-stream close.
int __thiscall rf_vfile_rename_loose_source_with_same_directory_prefix(int this, const char *a2, char *String2, int a4)
{
  char v5; // dl
  _BYTE *v6; // [esp+8h] [ebp-224h]
  char *v7; // [esp+Ch] [ebp-220h]
  char v8; // [esp+13h] [ebp-219h]
  char *v9; // [esp+18h] [ebp-214h]
  char *v10; // [esp+1Ch] [ebp-210h]
  char Str[256]; // [esp+24h] [ebp-208h] BYREF
  char Buffer[256]; // [esp+124h] [ebp-108h] BYREF
  char *last_char_wrapper; // [esp+228h] [ebp-4h]

  if ( String2 && !rf_vfile_resolve_open_source(this, String2, a4) )
    return -4;
  if ( *(_DWORD *)(this + 264) )
    return -3;
  v10 = (char *)(this + 5);
  v9 = Str;
  do
  {
    v8 = *v10;
    *v9++ = *v10++;
  }
  while ( v8 );
  last_char_wrapper = rf_cstring_find_last_char_wrapper(Str, 92);
  *last_char_wrapper = 0;
  sprintf(Buffer, "%s\\%s", Str, a2);
  if ( rename((const char *)(this + 5), Buffer) )
    return -99999;
  v7 = Buffer;
  v6 = (_BYTE *)(this + 5);
  do
  {
    v5 = *v7;
    *v6++ = *v7++;
  }
  while ( v5 );
  return 0;
}

