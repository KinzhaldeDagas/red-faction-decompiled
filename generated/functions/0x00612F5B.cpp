// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00612F5B ___freetlocinfo
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Locale root offsets:
// rootrefLONG0,lconvRefPtr176,numericRefPtr180,monetaryRefPtr184,lconvPtr188,ctypeRefPtr192,biasedCtypePtr196,biasedLowerPtr204,biasedUpperPtr208,timePtr212. Six categoryrecords
// at72+16*i contain narrowNamePtr0,wideNamePtr4,narrowRefPtr8,wideRefPtr12; narrow static C-name identity ADDRESS665990. Cdecl(root),void;NOrootNULLguard/rootrefcountcheck/ownlock.
// LconvcleanupONLYif lconvPtrnonNULL,notADDRESS66607C,lconvRefPtrnonNULLand*refEXACT0. Underthatgate,monRefnonNULLzero ->freemonRef thenfree_lconv_mon(lconv);numRefnonNULLzero
// ->freenumRef thenfree_lconv_num(lconv);finallyfreelconvRefandlconvobjectEVENifsubrefsnonzero. CtyperefnonNULLzero
// ->free(ctypePtr-254),free(lowerPtr-128),free(upperPtr-128),freectyperef;nosubpointerNULLguardsbeforebiasedsubtraction. timePtr mustnonNULL: ifnotADDRESS664C60
// andtime+180EXACT0,free_lc_time(time)thenfreetimeobject. Sixcategoryslots: ifnarrowName!=static665990
// andnarrowRefnonNULLwithcount0,freenarrowRef;wideName!=NULLandwideRefnonNULLcount0 ->freewideRef. Namesarenotseparatelyfreedhere;refallocationownscombinedstorage.
// FinallyALWAYSfreeroot. No componentdecrements,pointerclearing,negative-countacceptance,duplicate-pointerchecks,defaultrootguardorrollback. Caller
// mustperformrefreleaseandprotectstaticroot665998beforecalling.
void __cdecl __freetlocinfo(char *Block)
{
  _UNKNOWN **v2; // eax
  _DWORD *v3; // eax
  _DWORD *v4; // eax
  _DWORD *v5; // eax
  _DWORD *v6; // eax
  int v7; // eax
  void **v8; // edi
  _DWORD *v9; // eax
  int Blocka; // [esp+14h] [ebp+8h]

  v2 = *((_UNKNOWN ***)Block + 47);
  if ( v2 )
  {
    if ( v2 != &off_66607C )
    {
      v3 = *((_DWORD **)Block + 44);
      if ( v3 )
      {
        if ( !*v3 )
        {
          v4 = *((_DWORD **)Block + 46);
          if ( v4 && !*v4 )
          {
            free(*((void **)Block + 46));
            __free_lconv_mon(*((void ***)Block + 47));
          }
          v5 = *((_DWORD **)Block + 45);
          if ( v5 && !*v5 )
          {
            free(*((void **)Block + 45));
            __free_lconv_num(*((void ***)Block + 47));
          }
          free(*((void **)Block + 44));
          free(*((void **)Block + 47));
        }
      }
    }
  }
  v6 = *((_DWORD **)Block + 48);
  if ( v6 && !*v6 )
  {
    free((void *)(*((_DWORD *)Block + 49) - 254));
    free((void *)(*((_DWORD *)Block + 51) - 128));
    free((void *)(*((_DWORD *)Block + 52) - 128));
    free(*((void **)Block + 48));
  }
  v7 = *((_DWORD *)Block + 53);
  if ( (_UNKNOWN ***)v7 != off_664C60 && !*(_DWORD *)(v7 + 180) )
  {
    __free_lc_time(*((void ***)Block + 53));
    free(*((void **)Block + 53));
  }
  v8 = (void **)(Block + 80);
  Blocka = 6;
  do
  {
    if ( *(v8 - 2) != &unk_665990 && *v8 && !*(_DWORD *)*v8 )
      free(*v8);
    if ( *(v8 - 1) )
    {
      v9 = v8[1];
      if ( v9 )
      {
        if ( !*v9 )
          free(v8[1]);
      }
    }
    v8 += 4;
    --Blocka;
  }
  while ( Blocka );
  free(Block);
}

