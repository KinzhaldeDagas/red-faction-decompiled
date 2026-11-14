// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00605F36 __ftol2
// UNREALRED VERIFIED [nonworld-byte-rgb-20260903]: x87 fallback used by __ftol2_sse; compensates the current x87 integer conversion result using the fractional remainder to implement truncation toward zero.
unsigned int __usercall _ftol2@<eax>(double a1@<st0>)
{
  int v1; // edx
  unsigned int result; // eax
  float v3; // [esp+0h] [ebp-20h]
  int v4; // [esp+18h] [ebp-8h]

  *(float *)&v4 = a1;
  v1 = v4;
  result = (__int64)a1;
  if ( result || (v1 = (unsigned __int64)(__int64)a1 >> 32, (v1 & 0x7FFFFFFF) != 0) )
  {
    if ( v1 >= 0 )
    {
      v3 = a1 - (double)(__int64)a1;
      result -= __CFADD__(LODWORD(v3), 0x7FFFFFFF);
    }
    else
    {
      return (__PAIR64__(result, -(float)(a1 - (double)(__int64)a1)) + 0x7FFFFFFF) >> 32;
    }
  }
  return result;
}

