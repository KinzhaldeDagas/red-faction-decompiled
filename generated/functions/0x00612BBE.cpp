// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00612BBE __setmbcp_nolock
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Multibyte record layout:
// refcountLONG+0,codepageDWORD+4,multibyteFlagDWORD+8,LCIDDWORD+12,sixWORDdata+16..27,classBYTE[257]+28 (character c at+29+c),caseMapBYTE[256]+285,totalallocation544
// with3trailingpaddingbytes. Cdecl(rawselector,record),0/-1;NONULLguard/lock/directerrno. ResolveviaESI-getSystemCP. Resolved0 ->setSBCS/success. Searchfive48byterecordsat665898
// forFULLDWORDcodepage932/936/949/950/1361 BEFOREOSvalidation. Builtin: clear257classbytes,forfour8byterangepairgroupsORmasks665894={1,2,4,8} acrossinclusivebytes
// untilzeroendpoint/start;setcodepage,flag1,CPtoLCID,copyallsixWORDsfromrecord+4;callsetSBUpLow,return0 regardlessmappinghelperfailures. ECXstaticrecordoffset andEDX
// usedaslivevaluesacrossCPtoLCID arepreservedbynativecallee,notuninitializedlocals. Nonbuiltin: rejectFULLvalue65000/65001 thenIsValidCodePage(ZEROEXTENDlow16bits)false ->-1
// WITHOUTmodifyingrecord. GetCPInfousesFULLresolvedDWORD. APItrue clearsclass,setsCP/LCID0;MaxCharSize<=1 flag0. Larger:leadOSrangesOR4,EVERYbyte1..254OR8
// (not0/255),setLCIDviaCPtoLCID,flag1 frompreservedEDX; zeroall6WORDs,callsetSBUpLow,return0. GetCPInfofalse ->setSBCS/successONLYifglobal2021B70nonzero
// fromspecialselectorresolution;otherwise-1,recordunchanged. No UTF8/UTF7support,rangecapacityguards,refcountchangesortransaction aroundsetSBUpLow.
int __cdecl _setmbcp_nolock(int a1, _DWORD *a2)
{
  UINT SystemCP; // edi
  unsigned int i; // eax
  BYTE *v5; // esi
  BYTE v6; // cl
  unsigned int j; // eax
  _BYTE *v8; // esi
  unsigned int v9; // eax
  unsigned int v10; // edi
  _WORD *v11; // eax
  int v12; // ecx
  _WORD *v13; // ecx
  int v14; // edx
  char *v15; // eax
  int v16; // ecx
  int v17; // edx
  unsigned int v18; // [esp+Ch] [ebp-20h]
  int v19; // [esp+10h] [ebp-1Ch]
  _BYTE *v20; // [esp+10h] [ebp-1Ch]
  struct _cpinfo CPInfo; // [esp+14h] [ebp-18h] BYREF
  UINT v22; // [esp+34h] [ebp+8h]

  SystemCP = getSystemCP(a1);
  v22 = SystemCP;
  if ( SystemCP )
  {
    v19 = 0;
    for ( i = 0; i < 60; i += 12 )
    {
      if ( dword_665898[i] == SystemCP )
      {
        memset(a2 + 7, 0, 0x101u);
        v18 = 0;
        v8 = (char *)&unk_6658A8 + 48 * v19;
        v20 = v8;
        do
        {
          while ( *v8 )
          {
            LOBYTE(v9) = v8[1];
            if ( !(_BYTE)v9 )
              break;
            v10 = (unsigned __int8)*v8;
            v9 = (unsigned __int8)v9;
            while ( v10 <= v9 )
            {
              *((_BYTE *)a2 + v10 + 29) |= byte_665894[v18];
              v9 = (unsigned __int8)v8[1];
              ++v10;
            }
            SystemCP = v22;
            v8 += 2;
          }
          ++v18;
          v8 = v20 + 8;
          v20 += 8;
        }
        while ( v18 < 4 );
        a2[1] = SystemCP;
        a2[2] = 1;
        a2[3] = CPtoLCID(SystemCP);
        v11 = a2 + 4;
        v13 = (_WORD *)((char *)&unk_66589C + v12);
        v14 = 6;
        do
        {
          *v11++ = *v13++;
          --v14;
        }
        while ( v14 );
LABEL_26:
        setSBUpLow((int)a2);
        return 0;
      }
      ++v19;
    }
    if ( SystemCP == 65000 || SystemCP == 65001 || !IsValidCodePage((unsigned __int16)SystemCP) )
      return -1;
    if ( GetCPInfo(SystemCP, &CPInfo) )
    {
      memset(a2 + 7, 0, 0x101u);
      a2[1] = SystemCP;
      a2[3] = 0;
      if ( CPInfo.MaxCharSize <= 1 )
      {
        a2[2] = 0;
      }
      else
      {
        if ( CPInfo.LeadByte[0] )
        {
          v5 = &CPInfo.LeadByte[1];
          do
          {
            v6 = *v5;
            if ( !*v5 )
              break;
            for ( j = *(v5 - 1); j <= v6; ++j )
              *((_BYTE *)a2 + j + 29) |= 4u;
            v5 += 2;
          }
          while ( *(v5 - 1) );
        }
        v15 = (char *)a2 + 30;
        v16 = 254;
        do
        {
          *v15++ |= 8u;
          --v16;
        }
        while ( v16 );
        a2[3] = CPtoLCID(a2[1]);
        a2[2] = v17;
      }
      a2[4] = 0;
      a2[5] = 0;
      a2[6] = 0;
      goto LABEL_26;
    }
    if ( !unk_2021B70 )
      return -1;
  }
  setSBCS(a2);
  return 0;
}

