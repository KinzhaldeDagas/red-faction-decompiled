// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00611FC9 ___sbh_resize_block
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): H=20byte regionheader:
// aggregateclass0..31maskDWORD0,class32..63maskDWORD4,uncommittedgroupmaskDWORD8,1MiBreservationptr12,Rmetadataptr16. Rsize41C4h:
// cachedgroupDWORD0,BYTE[64]nonempty-groupcounts+4,hiClassMasksDWORD[32]+44h,loClassMasksDWORD[32]+C4h,G[g]=R+144h+204h*g. GcountDWORD0;binsentinel(k)=G+8*k,itsnext+4/prev+8.
// FreeblockB has sizetagDWORD0,next4,prev8,matchingfooterB+size-4;user=B+4,allocatedtags=size+1. ForVALIDpositivealignedspans,class=min((size
// SAR4)-1,63);classbit80000000h>>(k&31),hiifk<32elselo. Groupmaskusesbit80000000h>>g.
// Unlinksolebinnode(next==prev):cleargroupclassbit,decrementRcount[k]BYTE,clearHaggregatebitiffcounterbecomes0.
// InsertionatbinHEADwiresnext/prev;iffpreviouslyemptysetgroupbit,incrementRcount[k],setHbitiffoldcounter0. CounterscountGROUPShavingthatclass,NOTfreeblocks.
// Cdecl(H,user,unsignedrawNewSize),intinplaceBoolean. g=UNSIGNED(user-H.base)>>15,wanted=(rawSize+23)&FFFFFFF0h modulo32;old=*DWORD(user-4)-1.
// Comparewanted/oldSIGNEDthenreadNEXTboundarytagatuser+old-4BEFOREtakingtheconditionalbranch,evenequalsize. Allwanted/old/sumcomparisonsareSIGNED32. Equal->1withoutwrites.
// Grow:requireNEXTtagEVENandwanted<=old+nextSizeelse0BEFOREmutation. Unlinknextwithaccounting;remainder=old+nextSize-wanted.
// SIGNEDremainder>0->createfreeB=user+wanted-4,insertnewbinhead/writefreeheaderfooter;otherwiseNOremainderentry. Writebusywanted+1atuser-4anduser+wanted-8,return1.
// Nevercoalescepreviousblockormoveallocation.
// Shrink:IMMEDIATELYwritebusynewheader/footer,makefreeB=user+wanted-4,size=old-wanted;ifthecapturednexttagEVENunlinkitwithaccountingandmergeitsbytes;ALWAYSinsertresultfreeatbinhead/writeEVENheader/footer,return1.
// NoGallocationcount/pendingemptycacheupdates,payloadcopy/clear,ownlock,VirtualAlloc,HeapAlloc,newhandlerorerrno.
// NoownNULL/header/group/allocatedtag/sizeoverflowguard;callerrestrictssmallrequests,corrupt/overflowinputsarenotnormalized.
int __cdecl __sbh_resize_block(_DWORD *a1, void *a2, unsigned int a3)
{
  int v3; // eax
  unsigned int v4; // edx
  signed int v5; // esi
  int v6; // ecx
  int *v7; // edi
  int v8; // ebx
  unsigned int v9; // ecx
  unsigned int v10; // ebx
  _BYTE *v11; // ecx
  int v12; // ebx
  bool v13; // zf
  unsigned int v14; // ebx
  _BYTE *v15; // ecx
  int v16; // ebx
  unsigned int v17; // edi
  char *v18; // ecx
  _DWORD *v19; // eax
  char v20; // cl
  _DWORD *v21; // edx
  int *v22; // eax
  int v24; // ecx
  signed int *v25; // ebx
  unsigned int v26; // esi
  unsigned int v27; // esi
  unsigned int v28; // ebx
  _BYTE *v29; // esi
  int v30; // ebx
  _BYTE *v31; // ecx
  unsigned int v32; // ebx
  unsigned int v33; // ecx
  signed int v34; // edi
  _DWORD *v35; // eax
  char v36; // cl
  int v37; // [esp+Ch] [ebp-Ch]
  int v38; // [esp+10h] [ebp-8h]
  int v39; // [esp+14h] [ebp-4h]
  int v40; // [esp+14h] [ebp-4h]
  signed int *v41; // [esp+24h] [ebp+Ch]
  char v42; // [esp+27h] [ebp+Fh]
  unsigned int v43; // [esp+28h] [ebp+10h]
  unsigned int v44; // [esp+28h] [ebp+10h]
  signed int v45; // [esp+28h] [ebp+10h]
  char v46; // [esp+2Bh] [ebp+13h]

  v3 = a1[4];
  v4 = ((unsigned int)a2 - a1[3]) >> 15;
  v37 = 516 * v4 + v3 + 324;
  v5 = (a3 + 23) & 0xFFFFFFF0;
  v6 = *((_DWORD *)a2 - 1) - 1;
  v7 = (int *)((char *)a2 + v6 - 4);
  v8 = *v7;
  v43 = v6;
  v39 = *v7;
  if ( v5 <= v6 )
  {
    if ( v5 < v6 )
    {
      v45 = v6 - v5;
      v24 = v5 + 1;
      *((_DWORD *)a2 - 1) = v5 + 1;
      v25 = (signed int *)((char *)a2 + v5 - 4);
      v26 = (v45 >> 4) - 1;
      v41 = v25;
      *(v25 - 1) = v24;
      if ( v26 > 0x3F )
        v26 = 63;
      if ( (v39 & 1) == 0 )
      {
        v27 = (v39 >> 4) - 1;
        if ( v27 > 0x3F )
          v27 = 63;
        if ( v7[1] == v7[2] )
        {
          if ( v27 >= 0x20 )
          {
            v31 = (_BYTE *)(v27 + v3 + 4);
            v32 = ~(0x80000000 >> (v27 - 32));
            *(_DWORD *)(v3 + 4 * v4 + 196) &= v32;
            v13 = (*v31)-- == 1;
            if ( v13 )
              a1[1] &= v32;
          }
          else
          {
            v28 = 0x80000000 >> v27;
            v29 = (_BYTE *)(v27 + v3 + 4);
            v30 = ~v28;
            *(_DWORD *)(v3 + 4 * v4 + 68) &= v30;
            v13 = (*v29)-- == 1;
            if ( v13 )
              *a1 &= v30;
          }
          v25 = v41;
        }
        *(_DWORD *)(v7[2] + 4) = v7[1];
        *(_DWORD *)(v7[1] + 8) = v7[2];
        v45 += v39;
        v26 = (v45 >> 4) - 1;
        if ( v26 > 0x3F )
          v26 = 63;
      }
      v33 = v37 + 8 * v26;
      v34 = *(_DWORD *)(v33 + 4);
      v25[2] = v33;
      v25[1] = v34;
      *(_DWORD *)(v33 + 4) = v25;
      *(_DWORD *)(v25[1] + 8) = v25;
      if ( v25[1] == v25[2] )
      {
        v42 = *(_BYTE *)(v26 + v3 + 4);
        *(_BYTE *)(v26 + v3 + 4) = v42 + 1;
        if ( v26 >= 0x20 )
        {
          if ( !v42 )
            a1[1] |= 0x80000000 >> (v26 - 32);
          v35 = (_DWORD *)(v3 + 4 * v4 + 196);
          v36 = v26 - 32;
        }
        else
        {
          if ( !v42 )
            *a1 |= 0x80000000 >> v26;
          v35 = (_DWORD *)(v3 + 4 * v4 + 68);
          v36 = v26;
        }
        *v35 |= 0x80000000 >> v36;
      }
      *v25 = v45;
      *(signed int *)((char *)v25 + v45 - 4) = v45;
    }
  }
  else
  {
    if ( (v8 & 1) != 0 || v5 > v6 + v8 )
      return 0;
    v9 = (v39 >> 4) - 1;
    v38 = v9;
    if ( v9 > 0x3F )
    {
      v9 = 63;
      v38 = 63;
    }
    if ( v7[1] == v7[2] )
    {
      if ( v9 >= 0x20 )
      {
        v14 = 0x80000000 >> (v9 - 32);
        v15 = (_BYTE *)(v38 + v3 + 4);
        v16 = ~v14;
        *(_DWORD *)(v3 + 4 * v4 + 196) &= v16;
        v13 = (*v15)-- == 1;
        if ( v13 )
          a1[1] &= v16;
      }
      else
      {
        v10 = 0x80000000 >> v9;
        v11 = (_BYTE *)(v38 + v3 + 4);
        v12 = ~v10;
        *(_DWORD *)(v3 + 4 * v4 + 68) &= v12;
        v13 = (*v11)-- == 1;
        if ( v13 )
          *a1 &= v12;
      }
    }
    *(_DWORD *)(v7[2] + 4) = v7[1];
    *(_DWORD *)(v7[1] + 8) = v7[2];
    v40 = v43 - v5 + v39;
    if ( v40 <= 0 )
    {
      v21 = a2;
    }
    else
    {
      v17 = (v40 >> 4) - 1;
      v18 = (char *)a2 + v5 - 4;
      if ( v17 > 0x3F )
        v17 = 63;
      v44 = v37 + 8 * v17;
      *(_DWORD *)((char *)a2 + v5) = *(_DWORD *)(v44 + 4);
      *((_DWORD *)v18 + 2) = v44;
      *(_DWORD *)(v44 + 4) = v18;
      *(_DWORD *)(*(_DWORD *)((char *)a2 + v5) + 8) = (char *)a2 + v5 - 4;
      if ( *(_DWORD *)((char *)a2 + v5) == *(_DWORD *)((char *)a2 + v5 + 4) )
      {
        v46 = *(_BYTE *)(v17 + v3 + 4);
        *(_BYTE *)(v17 + v3 + 4) = v46 + 1;
        if ( v17 >= 0x20 )
        {
          if ( !v46 )
            a1[1] |= 0x80000000 >> (v17 - 32);
          v19 = (_DWORD *)(v3 + 4 * v4 + 196);
          v20 = v17 - 32;
        }
        else
        {
          if ( !v46 )
            *a1 |= 0x80000000 >> v17;
          v19 = (_DWORD *)(v3 + 4 * v4 + 68);
          v20 = v17;
        }
        *v19 |= 0x80000000 >> v20;
      }
      v21 = a2;
      v22 = (int *)((char *)a2 + v5 - 4);
      *v22 = v40;
      *(int *)((char *)v22 + v40 - 4) = v40;
    }
    *(v21 - 1) = v5 + 1;
    *(_DWORD *)((char *)v21 + v5 - 8) = v5 + 1;
  }
  return 1;
}

