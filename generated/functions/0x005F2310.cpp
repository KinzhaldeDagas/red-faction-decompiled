// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005F2310 rf_ui_checkbox_replace_tooltip_record
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): Args text,xOffset,yOffset,font. Same original repeated-head unlink defect as button helper0x5EFC00:if head292!=sentinel(this+292),writes head.prev.next=head.next,then head.next.prev=head.prev,then head.next=0,head.prev=0,with fresh head reloads after writes. No retained node,no free,constant-zero backedge. For a well-formed sole record first update makes head=sentinel,third clears sentinel.next/object.head,fourth writes DWORD[4]=0. Then allocates288-byte tooltip without NULL guard;owner8=this,unbounded text12,font268,palette272=0x1CF7608,offsets276/280,tag284=-1;appends via tail296;returns0. Existing list corruption is original behavior,not fixed.
int __thiscall rf_ui_checkbox_replace_tooltip_record(_DWORD *this, char *a2, int a3, int a4, int a5)
{
  char v5; // al
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
  v7 = v11 + 3;
  do
  {
    v5 = *a2;
    *v7++ = *a2++;
  }
  while ( v5 );
  *(v10 != nullptr ? (_DWORD *)(v10 + 268) : (_DWORD *)268) = a5;
  *(v10 != nullptr ? (_DWORD *)(v10 + 272) : (_DWORD *)272) = byte_1CF7608;
  *(v10 != nullptr ? (_DWORD *)(v10 + 276) : (_DWORD *)276) = a3;
  *(v10 != nullptr ? (_DWORD *)(v10 + 280) : (_DWORD *)280) = a4;
  *(v10 != nullptr ? (_DWORD *)(v10 + 284) : (_DWORD *)284) = -1;
  *(v10 != nullptr ? (_DWORD *)(v10 + 4) : (_DWORD *)4) = *(this + 74);
  *v11 = this + 73;
  *(_DWORD *)*(this + 74) = v11;
  *(this + 74) = v11;
  return 0;
}

