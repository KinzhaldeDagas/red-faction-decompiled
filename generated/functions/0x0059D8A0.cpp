// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0059D8A0 rf_format_float_fixed_cstring
// UNREALRED VERIFIED [string-pool-stream-20261028]: Arguments destination,IGNORED capacity,float value,signed precision. Promotes float to double for sprintf percent-dot-star-f into32-byte local,then unbounded copy including NUL to destination,returns destination. No precision or output-size bound; overflow can occur in LOCAL buffer before destination copy. No scientific-format fallback or numeric validation.
_BYTE *__cdecl rf_format_float_fixed_cstring(_BYTE *a1, int a2, float a3, int a4)
{
  char v4; // dl
  _BYTE *v6; // [esp+10h] [ebp-2Ch]
  char *v7; // [esp+14h] [ebp-28h]
  char Buffer[32]; // [esp+18h] [ebp-24h] BYREF

  sprintf(Buffer, "%.*f", a4, a3);
  v7 = Buffer;
  v6 = a1;
  do
  {
    v4 = *v7;
    *v6++ = *v7++;
  }
  while ( v4 );
  return a1;
}

