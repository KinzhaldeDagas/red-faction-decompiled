// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0061290B ?setSBUpLow@@YAXPAUthreadmbcinfostruct@@@Z
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Multibyte record layout:
// refcountLONG+0,codepageDWORD+4,multibyteFlagDWORD+8,LCIDDWORD+12,sixWORDdata+16..27,classBYTE[257]+28 (character c at+29+c),caseMapBYTE[256]+285,totalallocation544
// with3trailingpaddingbytes. Internal ESI=record pointer,void,preservesESI,securitycookie; noNULLguard/ownlock. GetCPInfo(record.codepage). Success:
// buildbytearray0..255,replacebyte0withspace andall inclusiveOSleadbyterangeswithspace. Call crtGetStringTypeA(NULL,1,array,256,WORDtypes,cp,LCID,0),then
// crtLCMapStringA(NULL,LCID,100h,array,256,lowerBYTEbuffer,256,cp,0),then200h upperBYTEbuffer. ALLTHREE returnstatusesIGNORED,stacktype/mapbuffersnotpreinitialized: laterreads
// mayconsumeuninitializeddataonfailure. Loopc0..255: iftypes[c]&1 ORclass[c+1]10h andcaseMap[c]=lower[c];else if&2 OR20h/mapupper[c];else map0. DoesNOTclearoldclass10/20bits;
// uppertestwinswhenbothflags. IfGetCPInfofails skipallmappinghelpers,useASCIIA..Z OR10h/mapc+32,a..z OR20h/mapc-32,allothersmap0,againretainoldclassbits.
// CPINFOlead-rangescanstopsatstartbyte0,notexplicitarraylengthguard; invertedrangesnotfilled. Lifted WCHAR[128]scratchbuffersactuallyreadas256BYTEShere. No directerrno/rollback or
// dynamic allocation.
void __usercall setSBUpLow(int a1@<esi>)
{
  unsigned int i; // eax
  BYTE v2; // al
  BYTE *v3; // ebx
  unsigned int v4; // ecx
  unsigned int v5; // eax
  BYTE *v6; // ebx
  int v7; // eax
  WORD v8; // cx
  char v9; // cl
  unsigned int v10; // ecx
  _BYTE *v11; // eax
  char v12; // dl
  int v13; // [esp+8h] [ebp-51Ch]
  struct _cpinfo CPInfo; // [esp+Ch] [ebp-518h] BYREF
  WORD CharType[256]; // [esp+20h] [ebp-504h] BYREF
  char v16[256]; // [esp+220h] [ebp-304h] BYREF
  char DestStr[256]; // [esp+320h] [ebp-204h] BYREF
  CHAR MultiByteStr[256]; // [esp+420h] [ebp-104h] BYREF

  if ( GetCPInfo(*(_DWORD *)(a1 + 4), &CPInfo) )
  {
    for ( i = 0; i < 0x100; ++i )
      MultiByteStr[i] = i;
    v2 = CPInfo.LeadByte[0];
    MultiByteStr[0] = 32;
    if ( CPInfo.LeadByte[0] )
    {
      v3 = &CPInfo.LeadByte[1];
      do
      {
        v4 = v2;
        v5 = *v3;
        if ( v4 <= v5 )
          memset(&MultiByteStr[v4], 32, v5 - v4 + 1);
        v6 = v3 + 1;
        v2 = *v6;
        v3 = v6 + 1;
      }
      while ( v2 );
    }
    __crtGetStringTypeA(nullptr, 1u, MultiByteStr, 256, CharType, *(_DWORD *)(a1 + 4), *(_DWORD *)(a1 + 12), 0);
    __crtLCMapStringA(nullptr, *(_DWORD *)(a1 + 12), 0x100u, MultiByteStr, 256, DestStr, 256, *(_DWORD *)(a1 + 4), 0);
    __crtLCMapStringA(nullptr, *(_DWORD *)(a1 + 12), 0x200u, MultiByteStr, 256, v16, 256, *(_DWORD *)(a1 + 4), 0);
    v7 = 0;
    while ( 1 )
    {
      v8 = CharType[v7];
      if ( (v8 & 1) != 0 )
      {
        *(_BYTE *)(a1 + v7 + 29) |= 0x10u;
        v9 = DestStr[v7];
      }
      else
      {
        if ( (v8 & 2) == 0 )
        {
          *(_BYTE *)(a1 + v7 + 285) = 0;
          goto LABEL_16;
        }
        *(_BYTE *)(a1 + v7 + 29) |= 0x20u;
        v9 = v16[v7];
      }
      *(_BYTE *)(a1 + v7 + 285) = v9;
LABEL_16:
      if ( (unsigned int)++v7 >= 0x100 )
        return;
    }
  }
  v10 = 0;
  v13 = -97 - (a1 + 285);
  do
  {
    v11 = (_BYTE *)(a1 + v10 + 285);
    if ( (unsigned int)&v11[v13 + 32] <= 0x19 )
    {
      *(_BYTE *)(a1 + v10 + 29) |= 0x10u;
      v12 = v10 + 32;
LABEL_23:
      *v11 = v12;
      goto LABEL_25;
    }
    if ( (unsigned int)&v11[v13] <= 0x19 )
    {
      *(_BYTE *)(a1 + v10 + 29) |= 0x20u;
      v12 = v10 - 32;
      goto LABEL_23;
    }
    *v11 = 0;
LABEL_25:
    ++v10;
  }
  while ( v10 < 0x100 );
}

