// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00611EC1 ___sbh_alloc_new_group
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): H=20byte regionheader:
// aggregateclass0..31maskDWORD0,class32..63maskDWORD4,uncommittedgroupmaskDWORD8,1MiBreservationptr12,Rmetadataptr16. Rsize41C4h:
// cachedgroupDWORD0,BYTE[64]nonempty-groupcounts+4,hiClassMasksDWORD[32]+44h,loClassMasksDWORD[32]+C4h,G[g]=R+144h+204h*g. GcountDWORD0;binsentinel(k)=G+8*k,itsnext+4/prev+8.
// FreeblockB has sizetagDWORD0,next4,prev8,matchingfooterB+size-4;user=B+4,allocatedtags=size+1. ForVALIDpositivealignedspans,class=min((size
// SAR4)-1,63);classbit80000000h>>(k&31),hiifk<32elselo. Groupmaskusesbit80000000h>>g. Cdecl(H),intgroupindex/-1.
// RequireNONZEROuncommittedmaskbycaller;shiftmaskleftuntilsignbitset,countgfrom0. Mask0hasNOtermination/32iterationguardandloopsforever.
// Preinitializebins0..62next/prevtoselfBEFOREOScommit;bin63connectedlater. DoesNOTresetG.allocatedCount (validlifecyclealready0).
// VirtualAlloc(H.base+(g<<15),8000h,MEM_COMMIT1000h,READWRITE4);NULL->-1,leavingpreinitializedlinksbutnotchangingavailability/classmasks.
// SuccessinitializeEIGHT4KiBpages:atpage+8andpage+FFChbusy-1sentinels;freeB=page+Ch,sizeFF0h,matchingfooterpage+FF8h;next/prevchainbetweenpagestride1000h. First8pagebytesuntouched.
// Connectbin63sentinelG+1F8h.next=firstpage+Ch,prev=lastpage+Ch,repairendlinks.
// R.hi[g]=0,R.lo[g]=1;incrementR.count[63]BYTE,ifold0ORH.lowithmask1(class63);clearH.uncommittedgroupbit,returng. Class63contains8freepageblocksbutgroupcountincrementsonce.
// Noownlock,header/regionvalidation,errnoorrollbackafterwrites.
int __cdecl __sbh_alloc_new_group(_DWORD *a1)
{
  int v1; // eax
  int v2; // esi
  int v3; // ebx
  int v4; // eax
  int v5; // edx
  _DWORD *v6; // edi
  _DWORD *v8; // edx
  _DWORD *v9; // eax
  int v10; // ecx

  v1 = a1[2];
  v2 = a1[4];
  v3 = 0;
  while ( v1 >= 0 )
  {
    v1 *= 2;
    ++v3;
  }
  v4 = 516 * v3 + v2 + 324;
  v5 = 63;
  do
  {
    *(_DWORD *)(v4 + 8) = v4;
    *(_DWORD *)(v4 + 4) = v4;
    v4 += 8;
    --v5;
  }
  while ( v5 );
  v6 = (_DWORD *)(a1[3] + (v3 << 15));
  if ( !VirtualAlloc(v6, 0x8000u, 0x1000u, 4u) )
    return -1;
  v8 = v6 + 7168;
  if ( v6 < v6 + 7168 )
  {
    v9 = v6 + 4;
    v10 = 8;
    do
    {
      *(v9 - 2) = -1;
      v9[1019] = -1;
      *v9 = v9 + 1023;
      *(v9 - 1) = 4080;
      v9[1] = v9 - 1025;
      v9[1018] = 4080;
      v9 += 1024;
      --v10;
    }
    while ( v10 );
    v8 = v6 + 7168;
  }
  *(_DWORD *)(516 * v3 + v2 + 832) = v6 + 3;
  v6[5] = 516 * v3 + v2 + 828;
  *(_DWORD *)(516 * v3 + v2 + 836) = v8 + 3;
  v8[4] = 516 * v3 + v2 + 828;
  *(_DWORD *)(v2 + 4 * v3 + 68) = 0;
  *(_DWORD *)(v2 + 4 * v3 + 196) = 1;
  if ( (*(_BYTE *)(v2 + 67))++ == 0 )
    a1[1] |= 1u;
  a1[2] &= ~(0x80000000 >> v3);
  return v3;
}

