// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005A0590 rf_binary_stream_write_bool_equal_one
// UNREALRED VERIFIED [binary-fields-20261029]: Thiscall stream,input BYTE. Writes1 ONLY when low8 input equals1,otherwise writes0 (nonzero values2..255 become false). Sends local1-byte boolean through raw writer0x5A0990. Returns lower writer incidental result; no independent status check.
int *__thiscall rf_binary_stream_write_bool_equal_one(_DWORD *this, char a2)
{
  bool Buffer; // [esp+7h] [ebp-5h] BYREF

  Buffer = a2 == 1;
  return rf_vfile_write_bytes_with_optional_feedback(this, &Buffer, 1u);
}

