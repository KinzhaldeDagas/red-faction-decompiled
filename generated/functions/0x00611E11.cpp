// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00611E11 ___sbh_alloc_new_region
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): H=20byte regionheader:
// aggregateclass0..31maskDWORD0,class32..63maskDWORD4,uncommittedgroupmaskDWORD8,1MiBreservationptr12,Rmetadataptr16. Rsize41C4h:
// cachedgroupDWORD0,BYTE[64]nonempty-groupcounts+4,hiClassMasksDWORD[32]+44h,loClassMasksDWORD[32]+C4h,G[g]=R+144h+204h*g. GcountDWORD0;binsentinel(k)=G+8*k,itsnext+4/prev+8.
// FreeblockB has sizetagDWORD0,next4,prev8,matchingfooterB+size-4;user=B+4,allocatedtags=size+1. ForVALIDpositivealignedspans,class=min((size
// SAR4)-1,63);classbit80000000h>>(k&31),hiifk<32elselo. Groupmaskusesbit80000000h>>g. Noargs,newheaderpointer/NULL. GlobalsHarray2021F48,used2021F44,capacity2021F54.
// ONLYused==capacitygrowsarraywithHeapReAlloc(heap2021854,flags0,oldBase,20*(capacity+16));failureNULLpreservesbase/capacity.
// Successcapacity+=16,publishnewbase,re-readused,chooseH=base+20*used. Nooverflow/used>capacityvalidation.
// HeapAlloc(heap,HEAP_ZERO_MEMORY8,41C4h),storeH.Rimmediately;NULL->returnNULL.
// VirtualAlloc(NULL,100000h,MEM_RESERVE2000h,PAGE_READWRITE4),storeH.base;NULL->HeapFreeR/NULL,leavingfreedRpointerinUNUSEDheaderentry.
// FullsuccessH.uncommitted=-1,H.hi/lo0,used++,R.cachedgroup=-1,returnH;noactualpagecommit. Headerarraygrowthremainscommittedonlaterfailure.
// ThisbodydoesNOTrebaseglobalrover2021F50,pendingemptyheader2021850,orcaller-heldHpointerwhenHeapReAllocmovesarray. Noownlock,errno,newhandlerortransaction.
char *__sbh_alloc_new_region()
{
  int v0; // esi
  void *v1; // eax
  char *v3; // esi
  LPVOID v4; // eax
  LPVOID v5; // eax

  v0 = unk_2021F44;
  if ( unk_2021F44 == unk_2021F54 )
  {
    v1 = HeapReAlloc(MEMORY[0x2021854], 0, MEMORY[0x2021F48], 20 * (unk_2021F54 + 16));
    if ( !v1 )
      return nullptr;
    unk_2021F54 += 16;
    v0 = unk_2021F44;
    MEMORY[0x2021F48] = v1;
  }
  v3 = (char *)MEMORY[0x2021F48] + 20 * v0;
  v4 = HeapAlloc(MEMORY[0x2021854], 8u, 0x41C4u);
  *((_DWORD *)v3 + 4) = v4;
  if ( !v4 )
    return nullptr;
  v5 = VirtualAlloc(nullptr, 0x100000u, 0x2000u, 4u);
  *((_DWORD *)v3 + 3) = v5;
  if ( !v5 )
  {
    HeapFree(MEMORY[0x2021854], 0, *((LPVOID *)v3 + 4));
    return nullptr;
  }
  *((_DWORD *)v3 + 2) = -1;
  *(_DWORD *)v3 = 0;
  *((_DWORD *)v3 + 1) = 0;
  ++unk_2021F44;
  **((_DWORD **)v3 + 4) = -1;
  return v3;
}

