// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005A4930 rf_bezier20_set_control_points
// UNREALRED VERIFIED [character-pipeline-20261029]: Thiscall object containing20 embedded vectors at+0..239 and count DWORD+240. Arguments signed count,array of vector pointers. Stores count,then for i<count copies pointed vector to12*i ONLY if pointer nonnull; null entries leave existing coordinates. No count<=20,pointer-array bound or allocation guard; excessive count can overwrite count/adjacent fields. Count<=0 performs no copies and returns0; positive returns loop count.
int __thiscall rf_bezier20_set_control_points(float *this, int a2, int a3)
{
  int result; // eax
  float copy_result[3]; // [esp+4h] [ebp-10h] BYREF
  int i; // [esp+10h] [ebp-4h]

  *((_DWORD *)this + 60) = a2;
  for ( i = 0; ; ++i )
  {
    result = i;
    if ( i >= a2 )
      break;
    if ( *(_DWORD *)(a3 + 4 * i) )
      rf_vector_copy(this + 3 * i, copy_result, *(const float **)(a3 + 4 * i));
  }
  return result;
}

