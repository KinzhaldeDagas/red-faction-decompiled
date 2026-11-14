// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005A6BF0 rf_text_list_replace_tooltip_record
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): Args text,xOffset,yOffset,font. Same repeated-head unlink defect as checkbox/button/inputbox helpers:auxiliary sentinel292/296,head read anew after each write;attempted head.prev.next=head.next,head.next.prev=head.prev,head.next=0,head.prev=0. Sole existing record makes first update head=sentinel,third clears object.head,then fourth writes DWORD[4]=0. No retained old node,no free,no actual iteration(constant-zero backedge);multiple records can corrupt links. Then allocates288-byte record unchecked;owner8=this,text12 unbounded,font268,palette272=0x1CF7608,offsets276/280,tag284=-1;append via tail296;returns0. Font/palette/offset/tag metadata initialized BEFORE text copy,so oversized text can overwrite those fields.
int __thiscall rf_text_list_replace_tooltip_record(_DWORD *this, char *a2, int a3, int a4, int a5)
{
  char v5; // dl
  _BYTE *v7; // [esp+8h] [ebp-14h]
  char *v10; // [esp+14h] [ebp-8h]
  _DWORD *v11; // [esp+18h] [ebp-4h]

  if ( (_DWORD *)*(this + 73) != this + 73 )
  {
    **(_DWORD **)(*(this + 73) + 4) = *(_DWORD *)*(this + 73);
    *(_DWORD *)(*(_DWORD *)*(this + 73) + 4) = *(_DWORD *)(*(this + 73) + 4);
    *(_DWORD *)*(this + 73) = 0;
    *(_DWORD *)(*(this + 73) + 4) = 0;
  }
  v10 = (char *)operator new(0x120u);
  v11 = v10 != nullptr ? (_DWORD *)v10 : nullptr;
  v11[2] = this;
  v11[67] = a5;
  v11[68] = &unk_1CF7608;
  v11[69] = a3;
  v11[70] = a4;
  v11[71] = -1;
  v7 = v11 + 3;
  do
  {
    v5 = *a2;
    *v7++ = *a2++;
  }
  while ( v5 );
  *(v10 != nullptr ? (_DWORD *)(v10 + 4) : (_DWORD *)4) = *(this + 74);
  *v11 = this + 73;
  *(_DWORD *)*(this + 74) = v11;
  *(this + 74) = v11;
  return 0;
}

