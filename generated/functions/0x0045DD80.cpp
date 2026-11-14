// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0045DD80 rf_two_rfstring_array16_append_owned
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, multiplayer level catalog/control call chains, native header/string ABI, original setup tables, slider
// arithmetic, callback stack reuse and RFString array ownership): Thiscall arrayECX {count0,capacity4,data8},OWNED16-byte two-RFString record by-value at four DWORD stack
// slots,RET16. count==capacity only ->grow45E160(capacity?2*capacity:16);no count>capacity/overflow/result guard. Save old count,increment count BEFORE assigning record into
// data+16*oldCount via45DFF0,then destroy both input RFStrings using two_rfstring_prefix_destroy and return old index. SEH cleanup destroys owned input on unwind. No dedup/sort or
// count rollback here;not a4-byte pointer-array append. Used for master and filtered level records.
int __thiscall rf_two_rfstring_array16_append_owned(_DWORD *this, int a2, int a3, int a4, int a5)
{
  int v6; // [esp+4h] [ebp-1Ch]
  int v8; // [esp+10h] [ebp-10h]

  if ( *this == *(this + 1) )
  {
    if ( *(this + 1) )
      v6 = 2 * *(this + 1);
    else
      v6 = 16;
    rf_two_rfstring_array16_reallocate_capacity(this, v6);
  }
  v8 = (*this)++;
  rf_two_rfstring_assign_from_object((_DWORD *)(*(this + 2) + 16 * v8), (int)&a2);
  rf_two_rfstring_prefix_destroy((char *)&a2);
  return v8;
}

