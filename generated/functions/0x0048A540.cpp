// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0048A540 sub_48A540
// UNREALRED VERIFIED [moving-shadow-receiver-retirement-20261027] Type-9 retirement called by rf_object_delete_dispatch at 0x4B7469: removes geometry registration records from 0x704600, destroys and clears solid pointer +0x294, then unlinks the live projected-shadow/collision owner by previous+0x28C = next and next+0x290 = previous, clearing both owner links. A host shadow cache must invalidate on instance removal and must not retain the freed solid geometry or identify a replacement solely by reused authored UID.
_DWORD *__cdecl sub_48A540(_DWORD *a1)
{
  _DWORD *v2; // [esp+4h] [ebp-18h]
  char *v3; // [esp+Ch] [ebp-10h]
  _DWORD *Block; // [esp+14h] [ebp-8h]
  int v5; // [esp+18h] [ebp-4h]

  v5 = a1[165];
  if ( !v5 )
    goto LABEL_18;
  for ( Block = dword_704600; Block; Block = v2 )
  {
    if ( (_DWORD *)*Block == dword_704600 )
      v2 = nullptr;
    else
      v2 = (_DWORD *)*Block;
    if ( Block[2] == v5 )
    {
      if ( dword_704600 == Block )
      {
        if ( (_DWORD *)*Block == Block )
        {
          *Block = 0;
          Block[1] = 0;
          dword_704600 = nullptr;
LABEL_13:
          free(Block);
          continue;
        }
        dword_704600 = (_DWORD *)*Block;
      }
      *(_DWORD *)Block[1] = *Block;
      *(_DWORD *)(*Block + 4) = Block[1];
      *Block = 0;
      Block[1] = 0;
      goto LABEL_13;
    }
  }
  v3 = (char *)a1[165];
  if ( v3 )
    rf_solid_destroy(v3, 1);
  a1[165] = 0;
LABEL_18:
  *(_DWORD *)(a1[164] + 652) = a1[163];
  *(_DWORD *)(a1[163] + 656) = a1[164];
  a1[163] = 0;
  a1[164] = 0;
  return a1;
}

