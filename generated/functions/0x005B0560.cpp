// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005B0560 rf_ui_window_append_tooltip_record
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, UI window construction/navigation/parsing/drawing/cleanup, exact flag and list operations, original stack ABI and call sites): Thiscall window,5 stack args text,a,x,y,finalValue,RET20. Allocates288-byte record and immediately dereferences it without NULL guard. Stores owner+8,unbounded NUL text copy at12(capacity256 before field268),finalValue at268,default style pointer1CF7608 at272,x276,y280,a284. Appends into base auxiliary sentinel at window+292 using previous pointer296: record.previous4=old previous,record.next0=sentinel,oldPrevious.next0=record,window.previous296=record. Returns allocation pointer. No string bound,field initialization beyond listed stores,coordinate validation or allocation rollback.
char *__thiscall rf_ui_window_append_tooltip_record(_DWORD *this, char *a2, int a3, int a4, int a5, int a6)
{
  char v6; // al
  _BYTE *v8; // [esp+8h] [ebp-14h]
  char *v11; // [esp+14h] [ebp-8h]
  _DWORD *v12; // [esp+18h] [ebp-4h]

  v11 = (char *)operator new(0x120u);
  v12 = v11 != nullptr ? (_DWORD *)v11 : nullptr;
  v12[2] = this;
  v8 = v12 + 3;
  do
  {
    v6 = *a2;
    *v8++ = *a2++;
  }
  while ( v6 );
  *(v11 != nullptr ? (_DWORD *)(v11 + 268) : (_DWORD *)268) = a6;
  *(v11 != nullptr ? (_DWORD *)(v11 + 272) : (_DWORD *)272) = byte_1CF7608;
  *(v11 != nullptr ? (_DWORD *)(v11 + 276) : (_DWORD *)276) = a4;
  *(v11 != nullptr ? (_DWORD *)(v11 + 280) : (_DWORD *)280) = a5;
  *(v11 != nullptr ? (_DWORD *)(v11 + 284) : (_DWORD *)284) = a3;
  *(v11 != nullptr ? (_DWORD *)(v11 + 4) : (_DWORD *)4) = *(this + 74);
  *v12 = this + 73;
  *(_DWORD *)*(this + 74) = v12;
  *(this + 74) = v12;
  return v11 != nullptr ? v11 : nullptr;
}

