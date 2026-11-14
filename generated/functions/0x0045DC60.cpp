// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0045DC60 rf_rfstring_array8_append_owned
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, multiplayer level catalog/control call chains, native header/string ABI, original setup tables, slider
// arithmetic, callback stack reuse and RFString array ownership): Thiscall arrayECX {countDWORD0,capacity4,data8},OWNED8-byte RFString by-value stack arg,RET8. Only count==capacity
// triggers grow45E020(newCap=capacity?2*capacity:16);no count>capacity/overflow or grow-result guard. Save old count,increment count BEFORE assigning incoming string to
// data+8*oldCount,then destroy owned argument and return old index. Exception cleanup owns argument destruction;no duplicate check or rollback of already incremented count in this
// body. Existing8-byte argument represented by two DWORD slots.
int __thiscall rf_rfstring_array8_append_owned(_DWORD *this, int a2, int a3)
{
  int v4; // [esp+4h] [ebp-1Ch]
  int v6; // [esp+10h] [ebp-10h]

  if ( *this == *(this + 1) )
  {
    if ( *(this + 1) )
      v4 = 2 * *(this + 1);
    else
      v4 = 16;
    rf_rfstring_array8_reallocate_capacity(this, v4);
  }
  v6 = (*this)++;
  rf_string_assign_from_object((_DWORD *)(*(this + 2) + 8 * v6), (int)&a2);
  rf_string_destroy_buffer(&a2);
  return v6;
}

