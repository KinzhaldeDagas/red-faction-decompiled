// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00611ACB ___sbh_find_block
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review):
// Cdecl(constvoid*address),returns20byteHEADERpointer/NULL (refinedpointertypes).
// ReadheaderarraybaseDWORD2021F48,usedcount2021F44;computeEND=base+20*countmodulo32,walkheadersby20whileUNSIGNEDptr<END.
// FirstheaderwhereUNSIGNED(address-H.reservationBase12)<100000hreturnsH.
// ThischecksONLYmembershipinreserved1MiBaddressrange,notcommittedgroup,exactpayloadstart,alignment,allocatedtagorNULLaddressvalidity. NomatchingheaderNULL.
// Noownlock,allocation,errnooroverflowguard;headerarraycount/baseassumedvalid.
_DWORD *__cdecl __sbh_find_block(const void *a1)
{
  _DWORD *result; // eax

  for ( result = MEMORY[0x2021F48]; result < (_DWORD *)((char *)MEMORY[0x2021F48] + 20 * unk_2021F44); result += 5 )
  {
    if ( (char *)a1 - result[3] < (char *)0x100000 )
      return result;
  }
  return nullptr;
}

