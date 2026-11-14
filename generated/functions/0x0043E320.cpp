// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0043E320 rf_blood_surface_marks_remove_in_sphere
// UNREALRED VERIFIED [runtime-snapshots-blood-glass-20261028] For each active mark compare squared distance(position+0x14,input center) STRICTLY less than input radius squared. Admitted mark moves active=>free ring. Boundary equality not removed, and squaring makes negative radius same comparison magnitude. Assembly stores x87 distance result before comparison; inferred pseudocode temporaries can misleadingly appear to reuse prior value.
int __cdecl rf_blood_surface_marks_remove_in_sphere(float *a1, float a2)
{
  int result; // eax
  int v3; // [esp+0h] [ebp-14h]
  float v4; // [esp+8h] [ebp-Ch]
  float v5; // [esp+Ch] [ebp-8h]
  int i; // [esp+10h] [ebp-4h]

  result = dword_6E6254;
  for ( i = dword_6E6254; i; i = v3 )
  {
    if ( *(_DWORD *)(i + 76) == dword_6E6254 )
      v3 = 0;
    else
      v3 = *(_DWORD *)(i + 76);
    v5 = rf_vector_distance_squared((const float *)(i + 20), a1);
    v4 = a2 * a2;
    if ( v4 > (double)v5 )
    {
      if ( dword_6E6254 == i )
      {
        if ( *(_DWORD *)(i + 76) == i )
        {
          *(_DWORD *)(i + 76) = 0;
          *(_DWORD *)(i + 80) = 0;
          dword_6E6254 = 0;
          goto LABEL_12;
        }
        dword_6E6254 = *(_DWORD *)(i + 76);
      }
      *(_DWORD *)(*(_DWORD *)(i + 80) + 76) = *(_DWORD *)(i + 76);
      *(_DWORD *)(*(_DWORD *)(i + 76) + 80) = *(_DWORD *)(i + 80);
      *(_DWORD *)(i + 76) = 0;
      *(_DWORD *)(i + 80) = 0;
LABEL_12:
      if ( unk_6E6228 )
      {
        *(_DWORD *)(i + 80) = *(_DWORD *)(unk_6E6228 + 80);
        *(_DWORD *)(i + 76) = unk_6E6228;
        *(_DWORD *)(*(_DWORD *)(unk_6E6228 + 80) + 76) = i;
        *(_DWORD *)(unk_6E6228 + 80) = i;
      }
      else
      {
        *(_DWORD *)(i + 76) = i;
        *(_DWORD *)(i + 80) = i;
        unk_6E6228 = i;
      }
    }
    result = v3;
  }
  return result;
}

