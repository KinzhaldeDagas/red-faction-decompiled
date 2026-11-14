// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00416F90 rf_clutter_skin_array_append_value108
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, clutter registry grammar/default retention,108-byte skin ownership, allocator cookies, native stack aliases and original flag-table strings): ECX header(count0,capacity4,base8) plus108-byte skin record BY VALUE (27 consecutive stackDWORDs),RET108. Corrects saved first stack argument from char to full DWORD while retaining27-slot ABI;first word is RFString extent,not an8-bit scalar. If EXACT count==capacity,grows2*capacity or16 whenzero via4171A0;no >=/doubling overflow validation. Saves oldindex,increments count BEFORE assigning108-byte record into base+108*index via417140. Destroys BY-VALUE argument through416DB0 on normal exit and native unwind;returnsoldindexEAX. Parent parser explicitly copy-constructs108-byte stackargument;ownership is not a shallow pointer or caller-popped payload. No pointer/capacity/active
// texture-count guard,copy rollback or companion glare update.
int __thiscall rf_clutter_skin_array_append_value108(
        _DWORD *array,
        int word0,
        int word1,
        int word2,
        int word3,
        int word4,
        int word5,
        int word6,
        int word7,
        int word8,
        int word9,
        int word10,
        int word11,
        int word12,
        int word13,
        int word14,
        int word15,
        int word16,
        int word17,
        int word18,
        int word19,
        int word20,
        int word21,
        int word22,
        int word23,
        int word24,
        int word25,
        int word26)
{
  int v29; // [esp+4h] [ebp-1Ch]
  int v31; // [esp+10h] [ebp-10h]

  if ( *array == *(array + 1) )
  {
    if ( *(array + 1) )
      v29 = 2 * *(array + 1);
    else
      v29 = 16;
    rf_clutter_skin_array_reallocate_capacity(array, v29);
  }
  v31 = (*array)++;
  rf_clutter_skin108_assign((_DWORD *)(*(array + 2) + 108 * v31), (int)&word0);
  rf_clutter_skin108_destroy_strings((char *)&word0);
  return v31;
}

