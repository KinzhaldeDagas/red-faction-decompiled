// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004F0330 rf_command_line_copy_enabled_archive_basename
// UNREALRED VERIFIED [save-validation-20261028]: Checks enabled boolean option at0x88E478 and nonnull/nonempty string0x88E488. On success optionally copies full C string to caller output without capacity argument and returns1; otherwise optionally clears output first byte and returns0. Archive caller appends .vpp; exact command-line spelling is not established by this body.
int __cdecl rf_command_line_copy_enabled_archive_basename(_BYTE *a1)
{
  char v2; // cl
  _BYTE *v3; // [esp+8h] [ebp-18h]
  char *v4; // [esp+Ch] [ebp-14h]

  if ( rf_command_line_bool_option_is_enabled(unk_88E478) )
  {
    if ( unk_88E488 && strlen(unk_88E488) )
    {
      if ( a1 )
      {
        v4 = (char *)unk_88E488;
        v3 = a1;
        do
        {
          v2 = *v4;
          *v3++ = *v4++;
        }
        while ( v2 );
      }
      return 1;
    }
    else
    {
      if ( a1 )
        *a1 = 0;
      return 0;
    }
  }
  else
  {
    if ( a1 )
      *a1 = 0;
    return 0;
  }
}

