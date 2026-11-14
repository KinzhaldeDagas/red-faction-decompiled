// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005A0160 rf_binary_stream_read_line_skip_crlf_run
// UNREALRED VERIFIED [binary-fields-20261029]: Thiscall stream,destination,IGNORED length argument,minimum version. Immediately destination[0]=0; below minimum returns0. Reads bytes until NUL/error,CR13 or LF10,stores UNBOUNDED line and adds NUL. Then consumes ALL consecutive CR/LF bytes,so empty separator lines are skipped. Reads first following nonseparator and seeks backward1 relative byte if nonzero. Returns stored line length,not status. No capacity enforcement,seek-result handling or CR/LF preservation.
int __thiscall rf_binary_stream_read_line_skip_crlf_run(int *this, _BYTE *a2, int a3, int a4)
{
  char char8_versioned; // [esp+7h] [ebp-5h]
  int v7; // [esp+8h] [ebp-4h]

  *a2 = 0;
  if ( !rf_binary_stream_version_at_least(this, a4) )
    return 0;
  v7 = 0;
  char8_versioned = rf_binary_stream_read_char8_versioned(this, 0, 0);
  while ( char8_versioned && char8_versioned != 13 && char8_versioned != 10 )
  {
    a2[v7] = char8_versioned;
    char8_versioned = rf_binary_stream_read_char8_versioned(this, 0, 0);
    ++v7;
  }
  a2[v7] = 0;
  while ( char8_versioned == 13 || char8_versioned == 10 )
    char8_versioned = rf_binary_stream_read_char8_versioned(this, 0, 0);
  if ( char8_versioned )
    rf_vfile_seek(this, -1, 1);
  return v7;
}

