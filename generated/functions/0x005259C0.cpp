// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005259C0 rf_face_partition_decal_polygons_flag8
// UNREALRED VERIFIED [decal-face-links-20261028]: Traverses face polygon chain+76 via next+1328; parent decal pointer+1316 flags+80 mask8 chooses output1, otherwise output2. Each output uses mandatory count pointer as capacity and writes only while current_count<capacity; scans full chain even after outputs full. Replaces both counts with actual written values, returns flag8 count. Context argument2 unused. Negative capacities produce0 writes; no null pointer or alias protection.
int __cdecl rf_face_partition_decal_polygons_flag8(int a1, int a2, int a3, int *a4, int a5, int *a6)
{
  int v7; // [esp+0h] [ebp-1Ch]
  int v8; // [esp+8h] [ebp-14h]
  int v9; // [esp+Ch] [ebp-10h]
  int v10; // [esp+10h] [ebp-Ch]
  int v11; // [esp+14h] [ebp-8h]
  int i; // [esp+18h] [ebp-4h]

  v11 = 0;
  v8 = 0;
  v10 = *a4;
  v9 = *a6;
  for ( i = *(_DWORD *)(a1 + 76); i; i = v7 )
  {
    v7 = *(_DWORD *)(i + 1328);
    if ( (*(_DWORD *)(*(_DWORD *)(i + 1316) + 80) & 8) != 0 )
    {
      if ( v11 < v10 )
        *(_DWORD *)(a3 + 4 * v11++) = i;
    }
    else if ( v8 < v9 )
    {
      *(_DWORD *)(a5 + 4 * v8++) = i;
    }
  }
  *a4 = v11;
  *a6 = v8;
  return v11;
}

