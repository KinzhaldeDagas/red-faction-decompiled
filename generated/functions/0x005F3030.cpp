// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005F3030 rf_ui_container_append_region_tooltip
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): Args text,regionID,xOffset,yOffset,font. Allocates288-byte tooltip record without NULL guard;owner8=this,unbounded text copy12,font268,palette272=0x1CF7608,offsets276/280,tag284=regionID. Appends to auxiliary doubly linked sentinel292/296. Unlike button/checkbox replacement helpers,does NOT remove an old record and supports multiple region tags. Returns new record pointer;no validation or duplicate-tag check.
char *__thiscall rf_ui_container_append_region_tooltip(_DWORD *this, char *a2, int a3, int a4, int a5, int a6)
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

