// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005A0080 rf_binary_stream_read_nul_string_to_buffer
// UNREALRED VERIFIED [binary-fields-20261029]: Thiscall stream,destination,max characters,minimum version,optional fallback. Max=-1 becomes65535. Allowed version repeatedly reads char8(min0,default0) until NUL/error; stores only while storedCount<max but CONTINUES consuming/discarding beyond limit,then writes NUL at storedCount. Thus destination needs max+1 bytes for nonnegative max. Other negative max stores no characters but still consumes. Version absent with fallback copies entire fallback INCLUDING NUL without applying max; null fallback leaves destination unchanged. Return incidental low byte,not stored length. No explicit error return or rollback.
char __thiscall rf_binary_stream_read_nul_string_to_buffer(int *this, char *a2, int a3, int a4, char *a5)
{
  char result; // al
  char v6; // dl
  char *v7; // [esp+8h] [ebp-14h]
  char *v8; // [esp+Ch] [ebp-10h]
  int v10; // [esp+14h] [ebp-8h]
  int v11; // [esp+18h] [ebp-4h]

  if ( a3 == -1 )
    a3 = 0xFFFF;
  result = rf_binary_stream_version_at_least(this, a4);
  if ( result )
  {
    v11 = 0;
    v10 = -1;
    while ( v10 )
    {
      result = rf_binary_stream_read_char8_versioned(this, 0, 0);
      v10 = result;
      if ( result )
      {
        result = v11;
        if ( v11 < a3 )
        {
          a2[v11] = v10;
          result = ++v11;
        }
      }
    }
    a2[v11] = 0;
  }
  else if ( a5 )
  {
    v8 = a5;
    v7 = a2;
    do
    {
      v6 = *v8;
      *v7 = *v8;
      result = (_BYTE)v8++ + 1;
      ++v7;
    }
    while ( v6 );
  }
  return result;
}

