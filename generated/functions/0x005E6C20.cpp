// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005E6C20 rf_image_error_message_by_packed_string_index
// UNREALRED VERIFIED [image-headers-20261028]: Starts at packed NUL-separated string table whose first string is No error. Advances code times by strlen(current)+1 and returns resulting pointer. No error-code range or table-end check; if(!pointer) after advancement does not detect terminal empty string or overrun. Negative code causes long decrementing traversal. Returns borrowed static pointer; no allocation.
const char *__cdecl rf_image_error_message_by_packed_string_index(int a1)
{
  const char *i; // [esp+10h] [ebp-4h]

  for ( i = aNoError_0; a1--; i += strlen(i) + 1 )
  {
    if ( !i )
      return nullptr;
  }
  return i;
}

