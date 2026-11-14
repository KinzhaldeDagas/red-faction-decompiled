// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0043E1D0 rf_blood_surface_marks_remove_in_aabb
// UNREALRED VERIFIED [runtime-snapshots-blood-glass-20261028] For each active mark whose position+0x14 passes rf_aabb_contains_point_inclusive(min,max), unlink active ring and append free ring. Save next traversal pointer before removal. Input first argument has no shown role in predicate; no texture release or geometry face deletion here.
int __cdecl rf_blood_surface_marks_remove_in_aabb(int a1, float *a2, float *a3)
{
  int result; // eax
  int v4; // [esp+0h] [ebp-Ch]
  int i; // [esp+8h] [ebp-4h]

  result = dword_6E6254;
  for ( i = dword_6E6254; i; i = v4 )
  {
    if ( *(_DWORD *)(i + 76) == dword_6E6254 )
      v4 = 0;
    else
      v4 = *(_DWORD *)(i + 76);
    result = rf_aabb_contains_point_inclusive((float *)(i + 20), a2, a3);
    if ( (_BYTE)result )
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
        result = i;
        *(_DWORD *)(unk_6E6228 + 80) = i;
      }
      else
      {
        *(_DWORD *)(i + 76) = i;
        result = i;
        *(_DWORD *)(i + 80) = i;
        unk_6E6228 = i;
      }
      continue;
    }
  }
  return result;
}

