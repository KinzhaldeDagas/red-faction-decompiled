// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005A08B0 rf_binary_stream_write_u16_length_string
// UNREALRED VERIFIED [binary-fields-20261029]: Thiscall stream,optional C string,explicit signed length. Null string forces length0. Negative length computes strlen; nonnegative uses exact supplied length. Writes low16 length through WORD writer0x5A0640,then if length nonzero sends FULL original length bytes through raw writer,WITHOUT NUL. Length>65535 therefore truncates prefix but not body. No capacity/string-length validation or check of prefix-write result; lower stream status may skip body. Returns last helper incidental result.
int __thiscall rf_binary_stream_write_u16_length_string(void *stream, const char *buffer, int length)
{
  int result; // eax

  if ( !buffer )
    length = 0;
  if ( length < 0 )
    length = strlen(buffer);
  result = rf_binary_stream_write_word_host_order(stream, length);
  if ( length )
    return (int)rf_vfile_write_bytes_with_optional_feedback(stream, (void *)buffer, length);
  return result;
}

