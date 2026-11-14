// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0061F373 ___convertcp
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review):
// Cdecl(UINTsourceCP,UINTdestCP,constchar*source,int*inoutLength,char*optionalDest,intdestCapacity),pointer/NULL. DereferenceinoutLengthBEFORECPcomparison,noNULLguard.
// IdenticalCPreturnsNULLwithoutcopy/OSquery/outputchange. DifferentCP:ifGetCPInfoBOTHsuccess/MaxCharSizeEXACT1,UTF16tempunitcount=originalbytecount
// (strlen+1if-1),setSBCSfastflag;otherwiseMultiByteToWideChar(sourceCP,1,source,originalcount,NULL,0)query. Requirepositiveunits<=7FFFFFF0,allocate2*units+8
// taggedscratch,<=1024stack/headerCCCC,largerheapmalloc/headerDDDD,data+8;NULL->NULL. Zero2*unitsbytes,actualMultiByteToWideCharflags1/originalcount,capacityunits;0->freea/NULL.
// OptionalDestnonNULL:WideCharToMultiByte(destCP,0,temp,ORIGINALunits,dest,rawcapacity,NULL,NULL);nonzero->returndest,zeroNULL;NEVERupdateinoutLengthonthisbranch.
// OptionalDestNULL:SBCSfastflagretainsunitsasoutputcapacity;othercasesQUERYWideCharToMultiByte(destCP,0,temp,units,NULL,0,NULL,NULL),thenOVERWRITEunitvariablewithreturnedOUTPUTBYTErequirement.
// Allocatecalloc_crt(1,currentcount);finalWideCharToMultiBytepassesSAMEcurrentcountasBOTHUTF16INPUTUNITCOUNTandoutputBYTEcapacity. This
// isnotindependentcorrectunittracking:outputbytes!=originalUTF16unitscantruncateinputorreadpastinitialized/allocatedtemporary.
// FinalAPI0freesownedoutput/NULL;nonzeroandORIGINALlength!=-1 ->*inoutLength=actualreturnedbytes;original-1stays-1. FreeaUTF16scratchnormally,callerownsnonnullallocatedoutput. No
// substitutionreport,ownerrno mapping,NULappend,rangevalidationofdestcapacityorunwind-finallycleanup;temporaryheaderallocationguarddoesnotguardoverwrittenfinalunitcount.
void *__cdecl __convertcp(UINT CodePage, UINT a2, const CHAR *a3, int *a4, CHAR *a5, int a6)
{
  int v6; // esi
  bool v7; // cc
  unsigned int v8; // eax
  void *v9; // esp
  WCHAR *v10; // eax
  LPSTR v12; // ebx
  void *v13; // eax
  int v14; // eax
  _DWORD v15[3]; // [esp+0h] [ebp-40h] BYREF
  LPSTR v16; // [esp+Ch] [ebp-34h]
  int *v17; // [esp+10h] [ebp-30h]
  int v18; // [esp+14h] [ebp-2Ch]
  LPCCH lpMultiByteStr; // [esp+18h] [ebp-28h]
  int cbMultiByte; // [esp+1Ch] [ebp-24h]
  void *Block; // [esp+20h] [ebp-20h]
  LPWSTR lpWideCharStr; // [esp+24h] [ebp-1Ch]
  struct _cpinfo CPInfo; // [esp+28h] [ebp-18h] BYREF

  lpMultiByteStr = a3;
  v17 = a4;
  cbMultiByte = *a4;
  v16 = a5;
  Block = nullptr;
  v18 = 0;
  if ( CodePage != a2 )
  {
    if ( GetCPInfo(CodePage, &CPInfo) && CPInfo.MaxCharSize == 1 && GetCPInfo(a2, &CPInfo) && CPInfo.MaxCharSize == 1 )
    {
      v6 = cbMultiByte;
      v18 = 1;
      if ( cbMultiByte == -1 )
        v6 = strlen(lpMultiByteStr) + 1;
      v7 = v6 <= 0;
    }
    else
    {
      v6 = MultiByteToWideChar(CodePage, 1u, lpMultiByteStr, cbMultiByte, nullptr, 0);
      v7 = v6 <= 0;
      if ( !v6 )
        return nullptr;
    }
    if ( v7 || (unsigned int)v6 > 0x7FFFFFF0 )
    {
      lpWideCharStr = nullptr;
LABEL_21:
      if ( lpWideCharStr )
      {
        memset(lpWideCharStr, 0, 2 * v6);
        if ( MultiByteToWideChar(CodePage, 1u, lpMultiByteStr, cbMultiByte, lpWideCharStr, v6) )
        {
          v12 = v16;
          if ( v16 )
          {
            if ( WideCharToMultiByte(a2, 0, lpWideCharStr, v6, v16, a6, nullptr, nullptr) )
              Block = v12;
          }
          else if ( v18 || (v6 = WideCharToMultiByte(a2, 0, lpWideCharStr, v6, nullptr, 0, nullptr, nullptr)) != 0 )
          {
            v13 = _calloc_crt(1u, v6);
            Block = v13;
            if ( v13 )
            {
              v14 = WideCharToMultiByte(a2, 0, lpWideCharStr, v6, (LPSTR)v13, v6, nullptr, nullptr);
              if ( v14 )
              {
                if ( cbMultiByte != -1 )
                  *v17 = v14;
              }
              else
              {
                free(Block);
                Block = nullptr;
              }
            }
          }
        }
        _freea(lpWideCharStr);
        return Block;
      }
      return nullptr;
    }
    v8 = 2 * v6 + 8;
    if ( v8 > 0x400 )
    {
      v10 = (WCHAR *)malloc(2 * v6 + 8);
      if ( v10 )
      {
        *(_DWORD *)v10 = 56797;
        goto LABEL_18;
      }
    }
    else
    {
      v9 = alloca(v8);
      v10 = (WCHAR *)v15;
      if ( v15 )
      {
        v15[0] = 52428;
LABEL_18:
        v10 += 4;
      }
    }
    lpWideCharStr = v10;
    goto LABEL_21;
  }
  return Block;
}

