// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005213F0 rf_world_decal_recycle_unprotected
// UNREALRED VERIFIED [resource-pools-20261028]: Traverses active circular list0xA7051C via next+224 saving successor. Skips flags+80 mask0x400. For others decrements counters0xA70630/34 when masks0x100/0x200, releases attached polygons through0x5215D0, clears flags, unlinks active record and inserts into circular free list0xA70620, decrementing active count0xA70624. No operator-delete of fixed record. Raw1/0x400 snapshot exclusions are separate policies.
int rf_world_decal_recycle_unprotected()
{
  int result; // eax
  int v1; // [esp+0h] [ebp-Ch]
  _DWORD *i; // [esp+8h] [ebp-4h]

  result = unk_A7051C;
  for ( i = (_DWORD *)unk_A7051C; i; i = (_DWORD *)v1 )
  {
    if ( i[56] == unk_A7051C )
      v1 = 0;
    else
      v1 = i[56];
    if ( (i[20] & 0x400) == 0 )
    {
      if ( (i[20] & 0x100) != 0 )
        --unk_A70630;
      if ( (i[20] & 0x200) != 0 )
        --unk_A70634;
      rf_world_decal_release_attached_polygons((int)i);
      i[20] = 0;
      if ( (_DWORD *)unk_A7051C == i )
      {
        if ( (_DWORD *)i[56] == i )
        {
          i[56] = 0;
          i[57] = 0;
          unk_A7051C = 0;
LABEL_16:
          if ( unk_A70620 )
          {
            i[57] = *(_DWORD *)(unk_A70620 + 228);
            i[56] = unk_A70620;
            *(_DWORD *)(*(_DWORD *)(unk_A70620 + 228) + 224) = i;
            *(_DWORD *)(unk_A70620 + 228) = i;
          }
          else
          {
            i[56] = i;
            i[57] = i;
            unk_A70620 = i;
          }
          --unk_A70624;
          goto LABEL_20;
        }
        unk_A7051C = i[56];
      }
      *(_DWORD *)(i[57] + 224) = i[56];
      *(_DWORD *)(i[56] + 228) = i[57];
      i[56] = 0;
      i[57] = 0;
      goto LABEL_16;
    }
LABEL_20:
    result = v1;
  }
  return result;
}

