// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00611AFB ___sbh_free_block
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): H=20byte regionheader:
// aggregateclass0..31maskDWORD0,class32..63maskDWORD4,uncommittedgroupmaskDWORD8,1MiBreservationptr12,Rmetadataptr16. Rsize41C4h:
// cachedgroupDWORD0,BYTE[64]nonempty-groupcounts+4,hiClassMasksDWORD[32]+44h,loClassMasksDWORD[32]+C4h,G[g]=R+144h+204h*g. GcountDWORD0;binsentinel(k)=G+8*k,itsnext+4/prev+8.
// FreeblockB has sizetagDWORD0,next4,prev8,matchingfooterB+size-4;user=B+4,allocatedtags=size+1. ForVALIDpositivealignedspans,class=min((size
// SAR4)-1,63);classbit80000000h>>(k&31),hiifk<32elselo. Groupmaskusesbit80000000h>>g.
// Unlinksolebinnode(next==prev):cleargroupclassbit,decrementRcount[k]BYTE,clearHaggregatebitiffcounterbecomes0.
// InsertionatbinHEADwiresnext/prev;iffpreviouslyemptysetgroupbit,incrementRcount[k],setHbitiffoldcounter0. CounterscountGROUPShavingthatclass,NOTfreeblocks. Cdecl(H,user),VOID
// (correctedfalsepointerreturn;all3free/realloccallersdiscardEAX). Computeg=UNSIGNED(user-H.base)>>15,B=user-4,size=*B-1. If(size&1)!=0
// skipALLmutation:ordinaryalready-freeevenrawtagtakes thisexit. Onlyonebitguard,noNULL/range/alignment/tag/footerconsistencyvalidation. Capturepreviousfooter=B-4,nexttag=B+size.
// IfnexttagEVEN,unlinknextfreeblockwithmaskaccounting,addnextsize.
// IfpreviousfooterEVEN,prevB=B-prevSize,coalesce;retainprevlistpositionWITHOUTunlink/reinsertiffprevclass==mergedclass,otherwiseunlinkprevwithaccountingandinsertmergedatnewbinhead.
// Busy previousalwaysinsertnewfreeblock. WriteEVENsizeheader/footer,thenG.allocatedCount--. Nonzero->finish;EAXoftenGpointerbutnotcontractresult.
// Countbecomes0:ifpriorpendingheader2021850exists,VirtualFree(prior.base+(pendingIndexDWORD2021F58<<15),8000h,MEM_DECOMMIT4000h),IGNORERESULT;restorepriorH.uncommittedbit,priorR.lo[pendingIndex]=0,decrementpriorR.count63BYTE,if0clearpriorH.lo
// mask1(class63).
// IfpriorH.uncommitted==FFFFFFFFh,VirtualFree(prior.base,0,MEM_RELEASE8000h),HeapFree(prior.R),bothresultsIGNORED;_memcpy_0(priorH,priorH+20,base+20*used-priorH-20)compactsheaderarray,used--,ifCURRENT
// H liesAFTERremovedheaderadjustH-=20,resetglobalrover2021F50=headerbase. FinallycacheCURRENTadjustedHastheONEpendingemptyheaderandgaspendingindex.
// NewemptygroupremainsCOMMITTEDuntilanothergroupempties; allocationreusecanremovecache.
// Noownlock,payloadzeroing,APIerrorhandling,metadatarollbackorerrno;allpointer/list/countstateassumedvalid.
void __cdecl __sbh_free_block(_DWORD *a1, void *a2)
{
  int v2; // eax
  int *v3; // esi
  unsigned int v4; // edi
  int v5; // ecx
  char *v6; // ebx
  unsigned int v7; // edx
  _BYTE *v8; // ecx
  unsigned int v9; // ebx
  bool v10; // zf
  _BYTE *v11; // ecx
  unsigned int v12; // ebx
  unsigned int v13; // edx
  unsigned int v14; // ebx
  int v15; // ecx
  unsigned int v16; // esi
  unsigned int v17; // esi
  _DWORD *v18; // ecx
  int v19; // ebx
  LPVOID *v20; // eax
  _DWORD *v21; // [esp+8h] [ebp-10h]
  int v22; // [esp+Ch] [ebp-Ch]
  int v23; // [esp+10h] [ebp-8h]
  int v24; // [esp+14h] [ebp-4h]
  char *v25; // [esp+24h] [ebp+Ch]
  int *v26; // [esp+24h] [ebp+Ch]
  char v27; // [esp+27h] [ebp+Fh]

  v2 = a1[4];
  v3 = (int *)((char *)a2 - 4);
  v4 = ((unsigned int)a2 - a1[3]) >> 15;
  v21 = (_DWORD *)(516 * v4 + v2 + 324);
  v5 = *((_DWORD *)a2 - 1) - 1;
  v24 = v5;
  if ( (v5 & 1) == 0 )
  {
    v6 = (char *)v3 + v5;
    v22 = *(int *)((char *)v3 + v5);
    v23 = *((_DWORD *)a2 - 2);
    v25 = (char *)v3 + v5;
    if ( (v22 & 1) == 0 )
    {
      v7 = (v22 >> 4) - 1;
      if ( v7 > 0x3F )
        v7 = 63;
      if ( *((_DWORD *)v6 + 1) == *((_DWORD *)v6 + 2) )
      {
        if ( v7 >= 0x20 )
        {
          v11 = (_BYTE *)(v7 + v2 + 4);
          v12 = ~(0x80000000 >> (v7 - 32));
          *(_DWORD *)(v2 + 4 * v4 + 196) &= v12;
          v10 = (*v11)-- == 1;
          if ( v10 )
            a1[1] &= v12;
        }
        else
        {
          v8 = (_BYTE *)(v7 + v2 + 4);
          v9 = ~(0x80000000 >> v7);
          *(_DWORD *)(v2 + 4 * v4 + 68) &= v9;
          v10 = (*v8)-- == 1;
          if ( v10 )
            *a1 &= v9;
        }
        v6 = v25;
      }
      v5 = v22 + v24;
      *(_DWORD *)(*((_DWORD *)v6 + 2) + 4) = *((_DWORD *)v6 + 1);
      *(_DWORD *)(*((_DWORD *)v25 + 1) + 8) = *((_DWORD *)v25 + 2);
      v24 += v22;
    }
    v13 = (v5 >> 4) - 1;
    if ( v13 > 0x3F )
      v13 = 63;
    if ( (v23 & 1) != 0 )
    {
      v14 = (unsigned int)a1;
    }
    else
    {
      v26 = (int *)((char *)v3 - v23);
      v14 = (v23 >> 4) - 1;
      if ( v14 > 0x3F )
        v14 = 63;
      v15 = v23 + v5;
      v13 = (v15 >> 4) - 1;
      v24 = v15;
      if ( v13 > 0x3F )
        v13 = 63;
      if ( v14 != v13 )
      {
        if ( v26[1] == v26[2] )
        {
          if ( v14 >= 0x20 )
          {
            v17 = ~(0x80000000 >> (v14 - 32));
            *(_DWORD *)(v2 + 4 * v4 + 196) &= v17;
            v10 = (*(_BYTE *)(v14 + v2 + 4))-- == 1;
            if ( v10 )
              a1[1] &= v17;
          }
          else
          {
            v16 = ~(0x80000000 >> v14);
            *(_DWORD *)(v2 + 4 * v4 + 68) &= v16;
            v10 = (*(_BYTE *)(v14 + v2 + 4))-- == 1;
            if ( v10 )
              *a1 &= v16;
          }
        }
        *(_DWORD *)(v26[2] + 4) = v26[1];
        *(_DWORD *)(v26[1] + 8) = v26[2];
      }
      v3 = v26;
    }
    if ( (v23 & 1) != 0 || v14 != v13 )
    {
      v18 = &v21[2 * v13];
      v19 = v18[1];
      v3[2] = (int)v18;
      v3[1] = v19;
      v18[1] = v3;
      *(_DWORD *)(v3[1] + 8) = v3;
      if ( v3[1] == v3[2] )
      {
        v27 = *(_BYTE *)(v13 + v2 + 4);
        *(_BYTE *)(v13 + v2 + 4) = v27 + 1;
        if ( v13 >= 0x20 )
        {
          if ( !v27 )
            a1[1] |= 0x80000000 >> (v13 - 32);
          *(_DWORD *)(v2 + 4 * v4 + 196) |= 0x80000000 >> (v13 - 32);
        }
        else
        {
          if ( !v27 )
            *a1 |= 0x80000000 >> v13;
          *(_DWORD *)(v2 + 4 * v4 + 68) |= 0x80000000 >> v13;
        }
      }
    }
    *v3 = v24;
    *(int *)((char *)v3 + v24 - 4) = v24;
    v10 = (*v21)-- == 1;
    if ( v10 )
    {
      if ( unk_2021850 )
      {
        VirtualFree((LPVOID)(*((_DWORD *)unk_2021850 + 3) + (*(_DWORD *)byte_2021F58 << 15)), 0x8000u, 0x4000u);
        *((_DWORD *)unk_2021850 + 2) |= 0x80000000 >> byte_2021F58[0];
        *(_DWORD *)(*((_DWORD *)unk_2021850 + 4) + 4 * *(_DWORD *)byte_2021F58 + 196) = 0;
        --*(_BYTE *)(*((_DWORD *)unk_2021850 + 4) + 67);
        v20 = (LPVOID *)unk_2021850;
        if ( !*(_BYTE *)(*((_DWORD *)unk_2021850 + 4) + 67) )
        {
          *((_DWORD *)unk_2021850 + 1) &= ~1u;
          v20 = (LPVOID *)unk_2021850;
        }
        if ( v20[2] == (LPVOID)-1 )
        {
          VirtualFree(v20[3], 0, 0x8000u);
          HeapFree(MEMORY[0x2021854], 0, *((LPVOID *)unk_2021850 + 4));
          memcpy_0(
            unk_2021850,
            (char *)unk_2021850 + 20,
            (size_t)MEMORY[0x2021F48] + 20 * unk_2021F44 - (_DWORD)unk_2021850 - 20);
          --unk_2021F44;
          if ( a1 > unk_2021850 )
            a1 -= 5;
          unk_2021F50 = MEMORY[0x2021F48];
        }
      }
      unk_2021850 = a1;
      *(_DWORD *)byte_2021F58 = v4;
    }
  }
}

