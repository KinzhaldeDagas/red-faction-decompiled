// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004F6960 rf_vector_canonicalize_exact_unit_axis
// UNREALRED VERIFIED [save-validation-20261028]: Mutates vec3: if abs(x)==1, clears y,z; else if abs(y)==1, clears x,z; else if abs(z)==1, clears x,y. X then Y then Z priority. Other vectors are unchanged; does not perform general normalization.
void __cdecl rf_vector_canonicalize_exact_unit_axis(float *a1)
{
  float v1; // [esp+0h] [ebp-Ch]
  float v2; // [esp+4h] [ebp-8h]
  float v3; // [esp+8h] [ebp-4h]

  v3 = fabs(*a1);
  if ( v3 == 1.0 )
  {
    a1[1] = 0.0;
    a1[2] = 0.0;
  }
  else
  {
    v2 = fabs(a1[1]);
    if ( v2 == 1.0 )
    {
      *a1 = 0.0;
      a1[2] = 0.0;
    }
    else
    {
      v1 = fabs(a1[2]);
      if ( v1 == 1.0 )
      {
        *a1 = 0.0;
        a1[1] = 0.0;
      }
    }
  }
}

