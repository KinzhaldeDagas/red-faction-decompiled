// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005264C0 rf_geometry_free_context_circular_blocks
// UNREALRED VERIFIED [level-lifecycle-20261028]: If context pointer0xD035F0 nonnull, traverses circular doubly-linked heap block list held in its first dword, saves next before unlink, adjusts head when necessary, clears block links and free()s every block. Singleton clears context head to0. Does not free context object or clear globals0xD035EC/0xD035F0; null-context return register incidental.
_DWORD *rf_geometry_free_context_circular_blocks()
{
  _DWORD *result; // eax
  _DWORD *v1; // [esp+0h] [ebp-Ch]
  _DWORD *Block; // [esp+8h] [ebp-4h]

  if ( dword_D035F0 )
  {
    result = dword_D035F0;
    for ( Block = (_DWORD *)*dword_D035F0; ; Block = v1 )
    {
      if ( !Block )
        return result;
      if ( *Block == *dword_D035F0 )
        v1 = nullptr;
      else
        v1 = (_DWORD *)*Block;
      if ( (_DWORD *)*dword_D035F0 == Block )
      {
        if ( (_DWORD *)*Block == Block )
        {
          *Block = 0;
          Block[1] = 0;
          *dword_D035F0 = 0;
          goto LABEL_12;
        }
        *dword_D035F0 = *Block;
      }
      *(_DWORD *)Block[1] = *Block;
      *(_DWORD *)(*Block + 4) = Block[1];
      *Block = 0;
      Block[1] = 0;
LABEL_12:
      free(Block);
      result = v1;
    }
  }
  return result;
}

