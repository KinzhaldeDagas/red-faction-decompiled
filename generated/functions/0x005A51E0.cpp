// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005A51E0 rf_hermite3_set_points_and_tangents
// UNREALRED VERIFIED [character-pipeline-20261029]: Thiscall object. Arguments signed count,point pointer array,tangent pointer array. Stores count DWORD+72; for each i<count,copies nonnull point into vector slot i (byte12*i),nonnull tangent into slot i+3 (byte36+12*i). Null entries leave existing values. No count<=3 guard,so larger counts overlap arrays and can overwrite count/adjacent fields. Negative count stores negative value,no copies,returns0; positive returns count. No allocation.
int __thiscall rf_hermite3_set_points_and_tangents(float *this, int a2, int a3, int a4)
{
  int result; // eax
  float v6[3]; // [esp+4h] [ebp-1Ch] BYREF
  float copy_result[3]; // [esp+10h] [ebp-10h] BYREF
  int i; // [esp+1Ch] [ebp-4h]

  *((_DWORD *)this + 18) = a2;
  for ( i = 0; ; ++i )
  {
    result = i;
    if ( i >= a2 )
      break;
    if ( *(_DWORD *)(a3 + 4 * i) )
      rf_vector_copy(this + 3 * i, copy_result, *(const float **)(a3 + 4 * i));
    if ( *(_DWORD *)(a4 + 4 * i) )
      rf_vector_copy(this + 3 * i + 9, v6, *(const float **)(a4 + 4 * i));
  }
  return result;
}

