// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00520450 rf_world_group_render_entries_by_plane
// UNREALRED VERIFIED [room-render-20261028]: Clears global ungrouped count0x940A40 and plane-group count0x940A44. For each input packet with plane pointer+28 nonnull, creates8200-byte group at0x941A48+8200*index: root pointer+0,up to2048 member pointers+4,count+8196. Adds EVERY no-plane input whose center packet+4 is on opposite plane side from camera using0x5206C0<0,marks packet groupedbyte+22=1. Same packet may belong to multiple plane groups. Remaining no-plane/unmarked entries go0x92EA38. Shell-sorts group pointers0xA41E48 by root distance+40 DESCENDING. Does not sort no-plane list here,draw or reset incoming grouped bytes; submit path clears them. Matrix argument unused; no explicit group/member output-capacity guards.
int __cdecl rf_world_group_render_entries_by_plane(float *a1, int a2, int a3, int a4)
{
  int result; // eax
  int v5; // [esp+4h] [ebp-18h]
  int ii; // [esp+8h] [ebp-14h]
  int m; // [esp+Ch] [ebp-10h]
  int j; // [esp+10h] [ebp-Ch]
  _DWORD *v9; // [esp+14h] [ebp-8h]
  int i; // [esp+18h] [ebp-4h]
  int k; // [esp+18h] [ebp-4h]
  int n; // [esp+18h] [ebp-4h]

  dword_940A40 = 0;
  unk_940A44[0] = 0;
  for ( i = 0; i < a4; ++i )
  {
    if ( *(_DWORD *)(*(_DWORD *)(a3 + 4 * i) + 28) )
    {
      v9 = (_DWORD *)((char *)&unk_941A48 + 8200 * unk_940A44[0]);
      *(_DWORD *)&byte_98967F[4 * unk_940A44[0] + 755657] = v9;
      *v9 = *(_DWORD *)(a3 + 4 * i);
      v9[2049] = 0;
      for ( j = 0; j < a4; ++j )
      {
        if ( !*(_DWORD *)(*(_DWORD *)(a3 + 4 * j) + 28)
          && rf_render_entry_compare_camera_plane_side(
               *(float **)(*(_DWORD *)(a3 + 4 * i) + 28),
               *(_DWORD *)(a3 + 4 * j),
               a1) < 0 )
        {
          v9[++v9[2049]] = *(_DWORD *)(a3 + 4 * j);
          *(_BYTE *)(*(_DWORD *)(a3 + 4 * j) + 22) = 1;
        }
      }
      ++unk_940A44[0];
    }
  }
  for ( k = 0; k < a4; ++k )
  {
    if ( !*(_DWORD *)(*(_DWORD *)(a3 + 4 * k) + 28) && !*(_BYTE *)(*(_DWORD *)(a3 + 4 * k) + 22) )
      unk_92EA38[dword_940A40++] = *(_DWORD *)(a3 + 4 * k);
  }
  result = unk_940A44[0] / 2;
  for ( m = unk_940A44[0] / 2; m > 0; m /= 2 )
  {
    for ( n = m; n < unk_940A44[0]; ++n )
    {
      for ( ii = n - m;
            ii >= 0
         && *(float *)(**(_DWORD **)&byte_98967F[4 * m + 755657 + 4 * ii] + 40) > (double)*(float *)(**(_DWORD **)&byte_98967F[4 * ii + 755657] + 40);
            ii -= m )
      {
        v5 = *(_DWORD *)&byte_98967F[4 * ii + 755657];
        *(_DWORD *)&byte_98967F[4 * ii + 755657] = *(_DWORD *)&byte_98967F[4 * m + 755657 + 4 * ii];
        *(_DWORD *)&byte_98967F[4 * m + 755657 + 4 * ii] = v5;
      }
    }
    result = m / 2;
  }
  return result;
}

