// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00483EC0 rf_geomod_debris_work_measure
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, geometry-operation phases, terrain/debris ownership, saved replay, native x87 gates and localized level-text lifecycle): 
// Cdecl44-byte work record pointer; reads solid at+8, computes binary32 AABB extents (X,Y,Z)=solid.max84-solid.min72. Zeros major-axis vector+24, then sets one positive unit axis;
// stores maximum extent E at+40 and aspect ratio A=max/min at+36 for finite ordered valid bounds. These offsets matter: subdivider tests A>3 OR E/A>10, so the second quotient
// approximates minimum extent for ordinary positive finite boxes; preserve E divided by stored F32(A) with the native x87 comparison rather than recomputing minimum extent. No
// zero-denominator, reversed bounds, finite or NULL guard.
// Exact native branch comparator GE(a,b) is ordered a>=b OR unordered, from TEST AH,5/JP. If GE(Y,X): if GE(Z,Y), select Z,E=Z,A=F32(Z/X); otherwise select
// Y,E=Y,A=F32(Y/(GE(Z,X)?X:Z)). Else: if GE(Z,X), select Z,E=Z,A=F32(Z/Y); otherwise select X,E=X,A=F32(X/(GE(Z,Y)?Y:Z)). Ties among maximal axes prefer Z, then Y, then X. All
// divisions store FLOAT+36. NaN follows this branch tree rather than a generic finite max/min implementation; no record link/position/solid ownership change.
void __cdecl rf_geomod_debris_work_measure(int a1)
{
  double v1; // st7
  double v2; // st7
  float out_vector; // [esp+0h] [ebp-Ch] BYREF
  float v4; // [esp+4h] [ebp-8h]
  float v5; // [esp+8h] [ebp-4h]

  rf_vector_subtract((const float *)(*(_DWORD *)(a1 + 8) + 84), &out_vector, (const float *)(*(_DWORD *)(a1 + 8) + 72));
  rf_vector3_zero_return_destination((float *)(a1 + 24));
  if ( v4 >= (double)out_vector )
  {
    if ( v5 >= (double)v4 )
    {
      *(float *)(a1 + 40) = v5;
      *(float *)(a1 + 32) = 1.0;
      *(float *)(a1 + 36) = v5 / out_vector;
    }
    else
    {
      *(float *)(a1 + 40) = v4;
      *(float *)(a1 + 28) = 1.0;
      if ( v5 >= (double)out_vector )
        v2 = v4 / out_vector;
      else
        v2 = v4 / v5;
      *(float *)(a1 + 36) = v2;
    }
  }
  else if ( v5 >= (double)out_vector )
  {
    *(float *)(a1 + 40) = v5;
    *(float *)(a1 + 32) = 1.0;
    *(float *)(a1 + 36) = v5 / v4;
  }
  else
  {
    *(float *)(a1 + 40) = out_vector;
    *(float *)(a1 + 24) = 1.0;
    if ( v5 >= (double)v4 )
      v1 = out_vector / v4;
    else
      v1 = out_vector / v5;
    *(float *)(a1 + 36) = v1;
  }
}

