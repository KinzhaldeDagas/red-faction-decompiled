// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0059DA00 rf_format_vector3_fixed_cstring
// UNREALRED VERIFIED [string-pool-stream-20261028]: Arguments destination,IGNORED capacity,3-float vector pointer,signed precision. sprintf into260-byte local with format < percent-dot-star-f, percent-dot-star-f, percent-dot-star-f >,same precision for all3 promoted floats. Unbounded NUL-inclusive copy to destination,returns destination. No precision bound,null check,vector normalization or local/destination capacity enforcement.
_BYTE *__cdecl rf_format_vector3_fixed_cstring(_BYTE *a1, int a2, float *a3, int a4)
{
  char v5; // [esp+23h] [ebp-115h]
  _BYTE *v6; // [esp+28h] [ebp-110h]
  char *v7; // [esp+2Ch] [ebp-10Ch]
  char Buffer[260]; // [esp+30h] [ebp-108h] BYREF

  sprintf(Buffer, "< %.*f, %.*f, %.*f >", a4, *a3, a4, a3[1], a4, a3[2]);
  v7 = Buffer;
  v6 = a1;
  do
  {
    v5 = *v7;
    *v6++ = *v7++;
  }
  while ( v5 );
  return a1;
}

