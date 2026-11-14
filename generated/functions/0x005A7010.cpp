// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005A7010 rf_text_list_add_text_entry
// UNREALRED VERIFIED [list-selection-20261029]: Arguments text,font,first indent,later indent,line gap. Flag0x400 allocates60-byte base entry storing borrowed text;otherwise allocates316-byte buffered entry,virtual setter copies max254 characters or substitutes long-text placeholder. Sets style+56=0x1CF7614,font+40,indents+28/+32,gap+36;layouts entry with callback Y=-scrollY. Nonempty list with positive height cap+676 attempts front eviction before insertion;removal helper recomputes height without not-yet-linked new entry,so final extent is not strictly guaranteed capped. Flag0x40 finds first case-insensitively greater text and inserts before;equal text remains after existing equals. Otherwise appends using doubly linked sentinel+724. Recomputes all Y/extents,synchronizes scrollbar ranges. Flag0x80 directly sets scrollY=new bottom-innerHeight without scrollbar-position sync/clamp. Returns
// new entry. No allocation failure,source/callback or membership guards.
int *__thiscall rf_text_list_add_text_entry(int *this, int a2, int a3, int a4, int a5, int a6)
{
  int v6; // esi
  int *v8; // [esp+8h] [ebp-34h]
  int *v9; // [esp+Ch] [ebp-30h]
  _DWORD *v11; // [esp+14h] [ebp-28h]
  _DWORD *v12; // [esp+1Ch] [ebp-20h]
  int v13; // [esp+24h] [ebp-18h]
  int i; // [esp+24h] [ebp-18h]
  int v15; // [esp+28h] [ebp-14h]
  int *v16; // [esp+2Ch] [ebp-10h]

  v15 = 0;
  if ( (*(this + 157) & 0x400) != 0 )
  {
    v12 = operator new(0x3Cu);
    if ( v12 )
      v9 = rf_text_entry_construct(v12);
    else
      v9 = nullptr;
    v16 = v9;
    (*(void (__thiscall **)(int *, int))*v16)(v16, a2);
  }
  else
  {
    v11 = operator new(0x13Cu);
    if ( v11 )
      v8 = rf_text_entry_buffered_construct(v11);
    else
      v8 = nullptr;
    v16 = v8;
    (*(void (__thiscall **)(int *, int))*v16)(v16, a2);
  }
  v16[14] = (int)&unk_1CF7614;
  v16[10] = a3;
  v16[7] = a4;
  v16[8] = a5;
  v16[9] = a6;
  rf_text_list_layout_block((int)this, v16, -*(this + 178));
  if ( (int *)*(this + 183) == this + 181 )
  {
    v16[4] = 0;
    *(this + 171) = v16[6];
  }
  else
  {
    if ( *(this + 169) > 0 )
    {
      *(this + 171) += v16[6] + *(this + 179);
      while ( (int *)*(this + 183) != this + 181 && *(this + 171) > *(this + 169) )
      {
        v13 = *(this + 183);
        *(this + 171) -= *(this + 179) + *(_DWORD *)(v13 + 24);
        rf_text_list_remove_entry(this, v13);
      }
    }
    if ( (*(this + 157) & 0x40) != 0 )
    {
      for ( i = *(this + 183); (int *)i != this + 181; i = *(_DWORD *)(i + 8) )
      {
        if ( _stricmp((const char *)v16[12], *(const char **)(i + 48)) < 0 )
        {
          v15 = i;
          break;
        }
      }
    }
  }
  if ( v15 )
  {
    *(_DWORD *)(*(_DWORD *)(v15 + 12) + 8) = v16;
    v16[3] = *(_DWORD *)(v15 + 12);
    *(_DWORD *)(v15 + 12) = v16;
    v16[2] = v15;
  }
  else
  {
    v16[3] = *(this + 184);
    v16[2] = (int)(this + 181);
    *(_DWORD *)(*(this + 184) + 8) = v16;
    *(this + 184) = (int)v16;
  }
  rf_text_list_recompute_block_positions_and_extent(this);
  rf_text_list_sync_vertical_scrollbar_extent(this);
  rf_text_list_sync_horizontal_scrollbar_extent(this);
  if ( (*(this + 157) & 0x80) != 0 )
  {
    v6 = v16[6] + v16[4];
    *(this + 178) = v6 - rf_text_list_inner_height(this);
  }
  return v16;
}

