// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0059D7C0 rf_format_signed_decimal_cstring
// UNREALRED VERIFIED [string-pool-stream-20261028]: Arguments destination,IGNORED capacity,signed integer. sprintf32-byte local with percent-d,then unbounded copy including NUL to destination,returns destination. No grouping,padding,base selection or locale-independent conversion logic beyond CRT formatting.
_BYTE *__cdecl rf_format_signed_decimal_cstring(_BYTE *a1, int a2, int a3)
{
  char v3; // dl
  _BYTE *v5; // [esp+8h] [ebp-2Ch]
  char *v6; // [esp+Ch] [ebp-28h]
  char Buffer[32]; // [esp+10h] [ebp-24h] BYREF

  sprintf(Buffer, "%d", a3);
  v6 = Buffer;
  v5 = a1;
  do
  {
    v3 = *v6;
    *v5++ = *v6++;
  }
  while ( v3 );
  return a1;
}

