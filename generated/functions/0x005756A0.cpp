// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005756A0 rf_bitmap_type_from_filename_extension
// UNREALRED VERIFIED [bitmap-loading-20261028]: Uses last dot and case-insensitive extension comparison: pcx->1,tga->2,vbm->5,vaf->4,m2v->6. No dot plus full name USERBMAP yields3. Other/no extension0. Strings are inline bytes at0x640E5C..6C, not pointers despite off_ labels; verified against PE bytes. Does not inspect file contents or strip directory components; null input unguarded.
int __cdecl rf_bitmap_type_from_filename_extension(char *Str)
{
  char *String1; // [esp+0h] [ebp-4h]
  char *String1a; // [esp+0h] [ebp-4h]

  String1 = strrchr(Str, 46);
  if ( String1 )
  {
    String1a = String1 + 1;
    if ( !_stricmp(String1a, off_640E5C) )
    {
      return 1;
    }
    else if ( !_stricmp(String1a, off_640E60) )
    {
      return 2;
    }
    else if ( !_stricmp(String1a, off_640E64) )
    {
      return 5;
    }
    else if ( !_stricmp(String1a, off_640E68) )
    {
      return 4;
    }
    else if ( !_stricmp(String1a, off_640E6C) )
    {
      return 6;
    }
    else
    {
      return 0;
    }
  }
  else if ( !_stricmp(Str, "USERBMAP") )
  {
    return 3;
  }
  else
  {
    return 0;
  }
}

