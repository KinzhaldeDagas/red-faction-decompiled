// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0051A710 rf_qsort_vertex_pointer_compare_x
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, solid clone side effects, UV frame mapping, debug geometry, vector aliasing and by-value ABI): cdecl qsort comparator takes pointers to vertex pointers and compares only vertex X floats. Finite inputs return-1 if firstX<secondX,0 equal,1 greater; equal-X order unspecified by qsort. No Y/Z tie-break, pointer checks or explicit NaN total ordering.
int __cdecl rf_qsort_vertex_pointer_compare_x(float **a1, float **a2)
{
  float v3; // [esp+0h] [ebp-8h]
  float v4; // [esp+4h] [ebp-4h]

  v3 = **a1;
  v4 = **a2;
  if ( v4 <= (double)v3 )
    return v4 != v3;
  else
    return -1;
}

