// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005EFC00 rf_ui_button_replace_tooltip_record
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): Arguments text,xOffset,yOffset,font. Auxiliary sentinel at+292/+296. If head!=sentinel performs attempted unlink using REPEATED loads of object+292 after pointer writes;does NOT retain old node or free it. Original sequence is head.prev.next=head.next;head.next.prev=head.prev;head.next=0;head.prev=0,where every head is reloaded. For a well-formed single-record list first write sets head=sentinel,third sets sentinel.next=0,and fourth writes through address4. Multi-record lists can corrupt links. No iteration (constant-zero backedge). Then allocates288-byte record without NULL guard:owner+8=this,unbounded text+12,font+268,palette+272=0x1CF7608,offsets276/280,tag284=-1;appends via current tail296. Returns0. This is original behavior,not a safe generic replacement routine.
int __thiscall rf_ui_button_replace_tooltip_record(_DWORD *this, char *a2, int a3, int a4, int a5)
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

