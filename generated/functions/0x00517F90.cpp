// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00517F90 rf_pointer_array_append_unique
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, room destruction/reconstruction,shared-vertex portal-side voting,detail references and intrusive list edge cases,original ECX/stack flow and PE bytes): Thiscall12-byte DWORD-array header(count0,capacity4,backing8),DWORD value,RET4. Call51EAF0 raw equality search; if signed result>=0 return first existing index without mutation,otherwise forward556340 append result (oldcount index). Value0 and arbitrary integer identifiers are accepted; values are never dereferenced and existing duplicates are not removed. No sorting,validation ofcount/capacity/storage,allocation failure handling or pointed-object ownership transfer; append helper grows only on count==capacity. Used for unique candidate faces/portal-room owners as well as AI integer history.
int __thiscall rf_pointer_array_append_unique(_DWORD *this, int a2)
{
  int index; // [esp+4h] [ebp-4h]

  index = rf_pointer_array_find_index(this, a2);
  if ( index >= 0 )
    return index;
  else
    return rf_pointer_array_append_dword(this, a2);
}

