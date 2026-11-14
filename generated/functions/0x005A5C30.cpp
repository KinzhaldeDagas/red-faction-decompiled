// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005A5C30 rf_text_list_recompute_block_positions_and_extent
// UNREALRED VERIFIED [text-layout-20261029]: Walks doubly linked block list: sentinel=list+724,first pointer+732,next block+8. Resets content width+680,height+684. For each node,maximizes width from block+20,sets block topY+16=current height,adds inter-block gap list+716 plus block height+24. Caps content width to configured+672 when nonzero and exceeded. Finally subtracts one gap even on EMPTY list,so empty height=-gap. Returns this. No rewrap,dirty clear,scroll clamping or cycle validation.
_DWORD *__thiscall rf_text_list_recompute_block_positions_and_extent(_DWORD *this)
{
  _DWORD *i; // [esp+4h] [ebp-4h]

  *(this + 171) = 0;
  *(this + 170) = 0;
  for ( i = (_DWORD *)*(this + 183); i != this + 181; i = (_DWORD *)i[2] )
  {
    if ( i[5] > *(this + 170) )
      *(this + 170) = i[5];
    i[4] = *(this + 171);
    *(this + 171) += *(this + 179) + i[6];
  }
  if ( *(this + 168) && *(this + 170) > *(this + 168) )
    *(this + 170) = *(this + 168);
  *(this + 171) -= *(this + 179);
  return this;
}

