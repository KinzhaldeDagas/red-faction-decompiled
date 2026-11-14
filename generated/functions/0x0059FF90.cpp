// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0059FF90 rf_binary_stream_read_u16_string_to_buffer
// UNREALRED VERIFIED [binary-fields-20261029]: Thiscall stream,destination,Count,minimum version,optional fallback C string. Count=-1 becomes65535. Allowed version reads unsigned16 length(default0); zero writes destination[0]=0. Nonzero length<Count reads full length then writes NUL at length. Length>=Count reads Count-1 bytes,writes NUL at Count-1,then discards remaining declared bytes via byte reader,even after error. Count<=0 not safely rejected. Version absent with nonnull fallback calls strncpy(destination,fallback,Count),which may leave no NUL; null fallback leaves destination unchanged. No consistent result/count; raw length is not checked against available file bytes.
__int16 __thiscall rf_binary_stream_read_u16_string_to_buffer(
        int *this,
        char *Destination,
        int Count,
        int a4,
        char *Source)
{
  signed int v5; // eax
  signed int i; // [esp+4h] [ebp-8h]
  size_t Size; // [esp+8h] [ebp-4h]

  if ( Count == -1 )
    Count = 0xFFFF;
  LOWORD(v5) = rf_binary_stream_version_at_least(this, a4);
  if ( (_BYTE)v5 )
  {
    LOWORD(v5) = rf_binary_stream_read_uint16_versioned(this, 0, 0);
    Size = (unsigned __int16)v5;
    if ( (_WORD)v5 )
    {
      if ( (unsigned __int16)v5 >= Count )
      {
        rf_vfile_read_buffered_bytes_versioned(this, Destination, Count - 1, 0, 0);
        Destination[Count - 1] = 0;
        for ( i = 0; ; ++i )
        {
          v5 = Size - (Count - 1);
          if ( i >= v5 )
            break;
          rf_binary_stream_read_char8_versioned(this, 0, 0);
        }
      }
      else
      {
        rf_vfile_read_buffered_bytes_versioned(this, Destination, (unsigned __int16)v5, 0, 0);
        Destination[Size] = 0;
        LOWORD(v5) = Size + (_WORD)Destination;
      }
    }
    else
    {
      *Destination = 0;
    }
  }
  else if ( Source )
  {
    LOWORD(v5) = (unsigned __int16)strncpy(Destination, Source, Count);
  }
  return v5;
}

