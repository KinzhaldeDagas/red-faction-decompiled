// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00612DA3 __setmbcp
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Multibyte record layout:
// refcountLONG+0,codepageDWORD+4,multibyteFlagDWORD+8,LCIDDWORD+12,sixWORDdata+16..27,classBYTE[257]+28 (character c at+29+c),caseMapBYTE[256]+285,totalallocation544
// with3trailingpaddingbytes. Cdecl(codepageSelector),status0/-1. getptd,updatetmbcinfo,resolvegetSystemCP; ifresolved==currentrecord.codepage return0withoutallocation/tableupdates.
// malloc_crt544;NULLreturnsinitial-1,errnolefttodelegate. Copy544bytescurrentPTDrecord,newrefcount0,callsetmbcp_nolock(RESOLVEDcp,new). ThisSECONDgetSystemCP
// normallyresetsspecialselectorflag2021B70=0,soOSGetCPInfofailuredoesnotretainpublicsentinelfallback. Failure-1 freesnew(unlessstatic665468),errno22/-1;
// anyotherhypotheticalnonzerostatusretainsallocationandreturnsstatus. SuccessdecrementoldPTDrecordatomic,freeifzeroandnotstatic;publishnewPTD+104,incrementnewref.
// IfPTDmask+112bit2set ORglobal66598Cbit1set,return0withoutglobalpublish.
// Otherwiselock13/armEH4scope65ED00;copyCP/flag/LCIDtogglobals2021B80/84/88,copyONLYFIRST5of6WORDsto2021B74,257classbytes665688,256casemap665790.
// Decrementoldglobalmb/freeifzeroandnotstatic,publishglobalnew,incrementnewref,finallyunlock13normal/unwindvia612F04. PTDreplacementhappensBEFOREglobal-lockwindow;
// old/currentpointersassumednonNULL. No original-selectorretention, invalidcallback, rollbackofpartialcopies/refcountsorallocation-finallyoutsideglobalpublishwindow.
int __cdecl _setmbcp(int CodePage)
{
  DWORD *v1; // edi
  DWORD v2; // ebx
  _DWORD *v3; // eax
  _DWORD *v4; // ebx
  int v5; // eax
  int i; // eax
  int j; // eax
  int k; // eax
  int v10; // [esp+14h] [ebp-20h]
  UINT CodePagea; // [esp+3Ch] [ebp+8h]

  v10 = -1;
  v1 = _getptd();
  __updatetmbcinfo();
  v2 = v1[26];
  CodePagea = getSystemCP(CodePage);
  if ( CodePagea == *(_DWORD *)(v2 + 4) )
    return 0;
  v3 = _malloc_crt(0x220u);
  v4 = v3;
  if ( v3 )
  {
    qmemcpy(v3, (const void *)v1[26], 0x220u);
    *v3 = 0;
    v5 = _setmbcp_nolock(CodePagea, v3);
    v10 = v5;
    if ( v5 )
    {
      if ( v5 == -1 )
      {
        if ( v4 != (_DWORD *)&unk_665468 )
          free(v4);
        *_errno() = 22;
      }
    }
    else
    {
      if ( !InterlockedDecrement((volatile LONG *)v1[26]) && (_UNKNOWN *)v1[26] != &unk_665468 )
        free((void *)v1[26]);
      v1[26] = (DWORD)v4;
      InterlockedIncrement(v4);
      if ( (v1[28] & 2) == 0 && (dword_66598C & 1) == 0 )
      {
        _lock(13);
        unk_2021B80 = v4[1];
        unk_2021B84 = v4[2];
        unk_2021B88 = v4[3];
        for ( i = 0; i < 5; ++i )
          word_2021B74[i] = *((_WORD *)v4 + i + 8);
        for ( j = 0; j < 257; ++j )
          byte_665688[j] = *((_BYTE *)v4 + j + 28);
        for ( k = 0; k < 256; ++k )
          byte_665790[k] = *((_BYTE *)v4 + k + 285);
        if ( !InterlockedDecrement(lpAddend) && lpAddend != (volatile LONG *)&unk_665468 )
          free((void *)lpAddend);
        lpAddend = v4;
        InterlockedIncrement(v4);
        _unlock(13);
      }
    }
  }
  return v10;
}

