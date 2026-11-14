// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005F0F30 rf_ui_base_destroy_auxiliary_records
// UNREALRED VERIFIED [ui-properties-20261029]: Thiscall ui_base. While doubly linked auxiliary-record head+292 is not sentinel this+292,unlinks first record(next0,previous4),zeros those links,calls0x5F1460(record,1). After empty sets live BYTE+4=0;returns sentinel address. Does not free base object itself,unlink gadget ownership or reset rectangle/callback. No corrupted-list guard.
int __thiscall rf_ui_base_destroy_auxiliary_records(int this)
{
  int result; // eax
  _DWORD **v3; // [esp+10h] [ebp-4h]

  while ( 1 )
  {
    result = this + 292;
    if ( *(_DWORD *)(this + 292) == this + 292 )
      break;
    v3 = *(_DWORD ***)(this + 292);
    *v3[1] = *v3;
    (*v3)[1] = v3[1];
    *v3 = nullptr;
    v3[1] = nullptr;
    if ( v3 )
      rf_ui_auxiliary_record_scalar_delete(v3, 1);
  }
  *(_BYTE *)(this + 4) = 0;
  return result;
}

