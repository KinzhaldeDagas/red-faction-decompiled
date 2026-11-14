// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060C0A6 ?_strlwr_s_l_stat@@YAHPADIPAUlocaleinfo_struct@@@Z
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Invalid(E) means errnoE plus
// invalid_parameter(NULL,NULL,NULL,0,0); stated returns require callbackreturn. Cdecl(char*buffer,unsignedcapacity,NONNULLlocaleinfo*),errno-style0/E;
// noownlocaleconstruction/NULLlocalevalidation. NULLbuffer invalid22. strnlen(buffer,capacity)>=capacity FIRSTbuffer[0]=0 theninvalid22,INCLUDINGcapacity0write.
// LocaleRoot=localeinfo.firstpointer;LCID=root+20. LCID0:inplaceASCIIA..Z->a..z,otherbytesunchanged,return0.
// OtherLCID:crtLCMapStringA(locale,LCID,100h,buffer,-1,NULL,0,rootCP+4,1)sizequery. Return0->errno42/42,bufferretained. Unsignedcapacity<required ->buffer[0]=0,invalid34/34. Positive
// required<=FFFFFFE0 allocate required+8taggedscratch:total<=1024stack/headerCCCC,largerheapmalloc/headerDDDD,data+8;invalidsize/allocationNULL->errno12/12. ScratchNOTinitialized.
// SecondlowercaseMapsameinputNULterminated/capacityrequired;ANYnonzeroresult ->strcpy_s(buffer,capacity,scratch),returnthatstatus;zero->errno42/42.
// freeascratchnormally,cookiecheckedallnormalreturns. No exactrequired/writtencheck, explicitNULcheck,owntransactionorunwindfree.
// Verifiedstathelpercanreturnpositivequerycountwithoutwritingoutput,so thiscaller maythenreaduninitializedscratchthroughstrcpy_s.
errno_t __cdecl _strlwr_s_l_stat(char *Destination, rsize_t SizeInBytes, struct localeinfo_struct *a3)
{
  int *v3; // eax
  errno_t v4; // esi
  LCID v5; // ecx
  char *i; // ecx
  char v7; // al
  int v9; // eax
  char *v10; // ecx
  int v11; // eax
  void *v12; // esp
  _DWORD *v13; // eax
  int v14; // [esp-4h] [ebp-1Ch]
  _DWORD v15[3]; // [esp+0h] [ebp-18h] BYREF
  char *cchDest; // [esp+Ch] [ebp-Ch]
  void *Memory; // [esp+10h] [ebp-8h]

  if ( !Destination )
    goto LABEL_2;
  if ( strnlen(Destination, SizeInBytes) >= SizeInBytes )
  {
    *Destination = 0;
LABEL_2:
    v3 = _errno();
    v14 = 22;
LABEL_3:
    v4 = v14;
    *v3 = v14;
    _invalid_parameter(nullptr, nullptr, nullptr, 0, 0);
    return v4;
  }
  v5 = *(_DWORD *)(*(_DWORD *)a3 + 20);
  if ( v5 )
  {
    v9 = __crtLCMapStringA(a3, v5, 0x100u, Destination, -1, nullptr, 0, *(_DWORD *)(*(_DWORD *)a3 + 4), 1);
    v10 = (char *)v9;
    cchDest = (char *)v9;
    if ( !v9 )
    {
      *_errno() = 42;
      return *_errno();
    }
    if ( SizeInBytes < v9 )
    {
      *Destination = 0;
      v3 = _errno();
      v14 = 34;
      goto LABEL_3;
    }
    if ( v9 <= 0 || !(0xFFFFFFE0 / v9) )
    {
      Memory = nullptr;
      goto LABEL_28;
    }
    v11 = v9 + 8;
    if ( (unsigned int)(v10 + 8) > 0x400 )
    {
      v13 = malloc((size_t)(v10 + 8));
      if ( v13 )
      {
        *v13 = 56797;
        goto LABEL_25;
      }
    }
    else
    {
      v12 = alloca(v11);
      v13 = v15;
      if ( v15 )
      {
        v15[0] = 52428;
LABEL_25:
        v13 += 2;
      }
    }
    v10 = cchDest;
    Memory = v13;
LABEL_28:
    if ( Memory )
    {
      if ( __crtLCMapStringA(
             a3,
             *(_DWORD *)(*(_DWORD *)a3 + 20),
             0x100u,
             Destination,
             -1,
             (char *)Memory,
             (int)v10,
             *(_DWORD *)(*(_DWORD *)a3 + 4),
             1) )
      {
        v4 = strcpy_s(Destination, SizeInBytes, (const char *)Memory);
      }
      else
      {
        *_errno() = 42;
        v4 = 42;
      }
      _freea(Memory);
      return v4;
    }
    *_errno() = 12;
    return *_errno();
  }
  for ( i = Destination; *i; ++i )
  {
    v7 = *i;
    if ( *i >= 65 && v7 <= 90 )
      *i = v7 + 32;
  }
  return 0;
}

