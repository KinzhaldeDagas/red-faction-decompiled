// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0059D920 rf_format_byte_count_cstring
// UNREALRED VERIFIED [string-pool-stream-20261028]: Arguments destination,IGNORED capacity,signed byte count. Values<999 (including negatives) format percent-d bytes. Otherwise rounds bytes/1024 to float; if that value>=999.989990234375,divides float by1024 again and formats2-decimal MB,else2-decimal KB. Copies64-byte local including NUL unbounded to destination,returns destination. Labels KB/MB use binary1024 division; no GB branch or locale-independent decimal separator.
_BYTE *__cdecl rf_format_byte_count_cstring(_BYTE *a1, int a2, int a3)
{
  char v4; // [esp+Bh] [ebp-55h]
  _BYTE *v5; // [esp+10h] [ebp-50h]
  char *v6; // [esp+14h] [ebp-4Ch]
  char Buffer[64]; // [esp+18h] [ebp-48h] BYREF
  float v8; // [esp+5Ch] [ebp-4h]

  if ( a3 >= 999 )
  {
    v8 = (double)a3 / 1024.0;
    if ( v8 >= 999.989990234375 )
    {
      v8 = v8 / 1024.0;
      sprintf(Buffer, "%.2f MB", v8);
    }
    else
    {
      sprintf(Buffer, "%.2f KB", v8);
    }
  }
  else
  {
    sprintf(Buffer, "%d bytes", a3);
  }
  v6 = Buffer;
  v5 = a1;
  do
  {
    v4 = *v6;
    *v5++ = *v6++;
  }
  while ( v4 );
  return a1;
}

