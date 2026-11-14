// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005BB510 rf_rfa_load_raw_file
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, animation-clip pool, raw-buffer callers, key sampling branches and interpolation helpers): Cdecl filename,optional caller buffer. Gets/creates clip; already-nonNULL raw pointer returns0 without read. Copies stored name unbounded into1024-byte stack buffer, truncates at FIRST dot anywhere, appends .rfa. Append scan starts at Str-1 and increments into Str; odd &v13+3 pseudocode is stack-layout artifact. Opens virtual stream mode1; failure formats diagnostic into256-byte local (no display call), destructs stream,returns0,leaves registry name. Success stores file size+104; external buffer stores pointer and ownership0, otherwise allocates exact size via operator new[] and ownership1. Reads full advertised size, IGNORES read return, closes/destructs stream,returns stored size. No header/signature/version/offset validation,
// rebasing, external capacity check or partial-read rollback.
int __cdecl rf_rfa_load_raw_file(const char *a1, void *a2)
{
  int size; // eax
  void *v4; // eax
  char *v6; // [esp+Ch] [ebp-650h]
  char v7; // [esp+13h] [ebp-649h]
  char *v8; // [esp+18h] [ebp-644h]
  char *v9; // [esp+1Ch] [ebp-640h]
  int v10; // [esp+20h] [ebp-63Ch]
  char Buffer[256]; // [esp+28h] [ebp-634h] BYREF
  int self[71]; // [esp+128h] [ebp-534h] BYREF
  char *v13; // [esp+244h] [ebp-418h] BYREF
  char Str[1024]; // [esp+248h] [ebp-414h] BYREF
  char *first_character; // [esp+64Ch] [ebp-10h]
  int v16; // [esp+658h] [ebp-4h]

  v13 = rf_animation_clip_pool_get_or_create((char *)a1);
  if ( *((_DWORD *)v13 + 30) )
    return 0;
  rf_vfile_construct_unopened(self);
  v16 = 0;
  v9 = v13;
  v8 = Str;
  do
  {
    v7 = *v9;
    *v8++ = *v9++;
  }
  while ( v7 );
  first_character = rf_cstring_find_first_character(Str, 46);
  if ( first_character )
    *first_character = 0;
  v6 = (char *)&v13 + 3;
  while ( *++v6 )
    ;
  strcpy(v6, ".rfa");
  if ( rf_vfile_open_with_extension_cache_control_paths(self, Str, 1, byte_98967F) >= 0 )
  {
    size = rf_vfile_get_size((int)self, nullptr, (int)byte_98967F);
    *((_DWORD *)v13 + 26) = size;
    if ( a2 )
    {
      *((_DWORD *)v13 + 30) = a2;
      v13[108] = 0;
    }
    else
    {
      v4 = operator new[](*((_DWORD *)v13 + 26));
      *((_DWORD *)v13 + 30) = v4;
      v13[108] = 1;
    }
    rf_vfile_read_buffered_bytes_versioned(self, *((char **)v13 + 30), *((_DWORD *)v13 + 26), 0, 0);
    rf_vfile_close_stdio_or_vpp(self);
    v10 = *((_DWORD *)v13 + 26);
    v16 = -1;
    rf_vfile_destruct_close_if_open(self);
    return v10;
  }
  else
  {
    sprintf(Buffer, "Unable to load %s as an animation file.  File probably doesn't exist.", Str);
    v16 = -1;
    rf_vfile_destruct_close_if_open(self);
    return 0;
  }
}

