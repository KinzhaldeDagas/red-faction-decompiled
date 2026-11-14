// IDA pseudocode evidence; not yet portable or build-ready.
// 0x006122AA ___sbh_alloc_block
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): H=20byte regionheader:
// aggregateclass0..31maskDWORD0,class32..63maskDWORD4,uncommittedgroupmaskDWORD8,1MiBreservationptr12,Rmetadataptr16. Rsize41C4h:
// cachedgroupDWORD0,BYTE[64]nonempty-groupcounts+4,hiClassMasksDWORD[32]+44h,loClassMasksDWORD[32]+C4h,G[g]=R+144h+204h*g. GcountDWORD0;binsentinel(k)=G+8*k,itsnext+4/prev+8.
// FreeblockB has sizetagDWORD0,next4,prev8,matchingfooterB+size-4;user=B+4,allocatedtags=size+1. ForVALIDpositivealignedspans,class=min((size
// SAR4)-1,63);classbit80000000h>>(k&31),hiifk<32elselo. Groupmaskusesbit80000000h>>g.
// Unlinksolebinnode(next==prev):cleargroupclassbit,decrementRcount[k]BYTE,clearHaggregatebitiffcounterbecomes0.
// InsertionatbinHEADwiresnext/prev;iffpreviouslyemptysetgroupbit,incrementRcount[k],setHbitiffoldcounter0. CounterscountGROUPShavingthatclass,NOTfreeblocks.
// Cdecl(rawrequestDWORD),userpointer/NULL. wanted=(request+23)&FFFFFFF0h modulo32;SIGNEDk=(wanted SAR4)-1. Ifk<32
// hiWanted=FFFFFFFFh>>k,loWanted=FFFFFFFFh;elsehiWanted0,loWanted=FFFFFFFFh>>(k-32). Nativevariable shiftsmaskcounttoLOW5bits,NOk<=63/overflow/requestlimitvalidation.
// Scanheaderrover2021F50toend(base2021F48+20*used),thenbasetoroverforFIRSTHwhoseaggregatebitsintersectwantedmasks.
// Ifnone,searchuncommittedgroupmasknonzerointhatsamerover/wraporder;none->alloc_new_region;failureNULL.
// Selectednewgroup:callalloc_new_group(H),storeitsreturninR.cachedgroupEVEN-1;failureNULLwithoutrollbackofnewregion/headergrowth. PublishroverHafternewgroupsuccess/existingclasshit.
// PreferR.cachedgroupif!=-1anditsclassmasksfit;elseLINEARscanfromg0without32bounduntilgroupfits,assumingaggregateinvariants. SelectFIRSTMSBofeligiblehi-maskelseeligiblelo-mask+32
// (smallesteligibleclass),takebinHEADfreeB. remainder=B.size-wanted;remClass=(remainder SAR4)-1,SIGNEDclamp>63to63.
// IfremClass==selectedClass,KEEPfreeBlinkedandupdateitsEVENremainderheader/footer.
// OtherwiseunlinkoldBwithaccounting;nonzeroremainderinsertSAMEBatremainderclasshead/writefreeheaderfooter;zero->nofreeentry.
// AllocatefromHIGHEND:busyHeader=B+remainder,busytagswanted+1atheader/end,returnheader+4.
// IncrementG.allocatedCount;iffold0ANDH==pendingempty2021850ANDg==pendingIndex2021F58,clearpendingheader(globalindexleftunchanged). FinallyR.cachedgroup=g.
// Noownlock,payloadinitialization,errno,validitychecks,listsearchbeyondclassheadortransaction. Correctnessassumescaller-validatedsmallrequestandconsistentserializedmasks;
// zero/corruptmasksorsizescanlooporindexoutsideintendedmetadata.
_DWORD *__cdecl __sbh_alloc_block(int a1)
{
  char *v1; // eax
  int v2; // ecx
  unsigned int v3; // esi
  char *i; // ebx
  _DWORD *v6; // eax
  int v7; // edx
  int v8; // edx
  _DWORD *j; // ecx
  int v10; // edi
  int v11; // ecx
  int *v12; // edx
  int v13; // ecx
  int v14; // esi
  unsigned int v15; // ebx
  _BYTE *v16; // edi
  bool v17; // zf
  unsigned int v18; // ebx
  _BYTE *v19; // edi
  int v20; // ebx
  _DWORD *v21; // ecx
  int v22; // edi
  _DWORD *v23; // edx
  int v24; // ecx
  int v25; // [esp+Ch] [ebp-14h]
  int v26; // [esp+Ch] [ebp-14h]
  signed int v27; // [esp+10h] [ebp-10h]
  _DWORD *v28; // [esp+14h] [ebp-Ch]
  unsigned int v29; // [esp+18h] [ebp-8h]
  int v30; // [esp+18h] [ebp-8h]
  int v31; // [esp+1Ch] [ebp-4h]
  char *v32; // [esp+28h] [ebp+8h]
  char v33; // [esp+2Bh] [ebp+Bh]

  v1 = (char *)MEMORY[0x2021F48] + 20 * unk_2021F44;
  v27 = (a1 + 23) & 0xFFFFFFF0;
  v2 = (v27 >> 4) - 1;
  if ( v2 >= 32 )
  {
    v3 = 0;
    v29 = 0xFFFFFFFF >> ((v27 >> 4) - 33);
  }
  else
  {
    v3 = 0xFFFFFFFF >> v2;
    v29 = -1;
  }
  for ( i = (char *)unk_2021F50; ; i += 20 )
  {
    v32 = i;
    if ( i >= v1 || v3 & *(_DWORD *)i | v29 & *((_DWORD *)i + 1) )
      break;
  }
  if ( i == v1 )
  {
    for ( i = (char *)MEMORY[0x2021F48]; ; i += 20 )
    {
      v32 = i;
      if ( (unsigned int)i >= unk_2021F50 || v3 & *(_DWORD *)i | v29 & *((_DWORD *)i + 1) )
        break;
    }
    if ( i == (char *)unk_2021F50 )
    {
      while ( i < v1 && !*((_DWORD *)i + 2) )
      {
        i += 20;
        v32 = i;
      }
      if ( i == v1 )
      {
        for ( i = (char *)MEMORY[0x2021F48]; ; i += 20 )
        {
          v32 = i;
          if ( (unsigned int)i >= unk_2021F50 || *((_DWORD *)i + 2) )
            break;
        }
        if ( i == (char *)unk_2021F50 )
        {
          i = __sbh_alloc_new_region();
          v32 = i;
          if ( !i )
            return nullptr;
        }
      }
      **((_DWORD **)i + 4) = __sbh_alloc_new_group(i);
      if ( **((_DWORD **)i + 4) == -1 )
        return nullptr;
    }
  }
  unk_2021F50 = i;
  v6 = *((_DWORD **)i + 4);
  v7 = *v6;
  v31 = *v6;
  if ( *v6 == -1 || !(v3 & v6[v7 + 17] | v29 & v6[v7 + 49]) )
  {
    v31 = 0;
    v8 = v6[49];
    for ( j = v6 + 17; !(v3 & *j | v29 & v8); ++j )
    {
      ++v31;
      v8 = j[33];
    }
    v7 = v31;
  }
  v28 = &v6[129 * v7 + 81];
  v10 = 0;
  v11 = v3 & v6[v7 + 17];
  if ( !v11 )
  {
    v11 = v29 & v6[v7 + 49];
    v10 = 32;
  }
  while ( v11 >= 0 )
  {
    v11 *= 2;
    ++v10;
  }
  v12 = (int *)v28[2 * v10 + 1];
  v13 = *v12 - v27;
  v14 = (v13 >> 4) - 1;
  v30 = v13;
  if ( v14 > 63 )
    v14 = 63;
  if ( v14 == v10 )
    goto LABEL_57;
  if ( v12[1] != v12[2] )
    goto LABEL_47;
  if ( v10 >= 32 )
  {
    v18 = 0x80000000 >> (v10 - 32);
    v19 = (char *)v6 + v10 + 4;
    v20 = ~v18;
    v6[v31 + 49] &= v20;
    v17 = (*v19)-- == 1;
    v26 = v20;
    if ( v17 )
    {
      i = v32;
      *((_DWORD *)v32 + 1) &= v26;
      goto LABEL_47;
    }
  }
  else
  {
    v15 = 0x80000000 >> v10;
    v16 = (char *)v6 + v10 + 4;
    v25 = ~v15;
    v6[v31 + 17] &= ~v15;
    v17 = (*v16)-- == 1;
    if ( v17 )
    {
      i = v32;
      *(_DWORD *)v32 &= v25;
      goto LABEL_47;
    }
  }
  i = v32;
LABEL_47:
  *(_DWORD *)(v12[2] + 4) = v12[1];
  *(_DWORD *)(v12[1] + 8) = v12[2];
  if ( v13 )
  {
    v21 = &v28[2 * v14];
    v22 = v21[1];
    v12[2] = (int)v21;
    v12[1] = v22;
    v21[1] = v12;
    *(_DWORD *)(v12[1] + 8) = v12;
    if ( v12[1] == v12[2] )
    {
      v33 = *((_BYTE *)v6 + v14 + 4);
      *((_BYTE *)v6 + v14 + 4) = v33 + 1;
      if ( v14 >= 32 )
      {
        if ( !v33 )
          *((_DWORD *)i + 1) |= 0x80000000 >> (v14 - 32);
        v6[v31 + 49] |= 0x80000000 >> (v14 - 32);
      }
      else
      {
        if ( !v33 )
          *(_DWORD *)i |= 0x80000000 >> v14;
        v6[v31 + 17] |= 0x80000000 >> v14;
      }
    }
    v13 = v30;
LABEL_57:
    if ( v13 )
    {
      *v12 = v13;
      *(int *)((char *)v12 + v13 - 4) = v13;
    }
    goto LABEL_60;
  }
  v13 = 0;
LABEL_60:
  v23 = (int *)((char *)v12 + v13);
  *v23 = v27 + 1;
  *(_DWORD *)((char *)v23 + v27 - 4) = v27 + 1;
  v24 = (*v28)++;
  if ( !v24 && i == unk_2021850 && v31 == *(_DWORD *)byte_2021F58 )
    unk_2021850 = nullptr;
  *v6 = v31;
  return v23 + 1;
}

