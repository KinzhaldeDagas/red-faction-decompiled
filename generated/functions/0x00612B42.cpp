// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00612B42 ?getSystemCP@@YAHH@Z
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Internal ESI=rawsignedselector,UINT EAX,plainRET.
// Construct stack_LocaleUpdate(NULL),resetglobal2021B70=0. Selector-2 setsflag1/GetOEMCP;-3 flag1/GetACP;-4 flag1/readlocaleRoot+4 (FIRSTDWORDpointerofupdateobject);
// otherselectorsreturnedbitsexactly,including0andothernegativevalues. OnEVERYnormalreturn ifupdate.cleanupBYTE12!=0 clearPTD+112bit2;otherwiseleavepinuntouched. No validation,
// allocation, errno mapping or exception-finallypinrelease inthisbody; temporarylocaleconstructor ownsrefresh/pinsemantics.
UINT __usercall getSystemCP@<eax>(int a1@<esi>)
{
  UINT result; // eax
  int v2; // [esp+4h] [ebp-10h] BYREF
  int v3; // [esp+Ch] [ebp-8h]
  char v4; // [esp+10h] [ebp-4h]

  _LocaleUpdate::_LocaleUpdate((_LocaleUpdate *)&v2, nullptr);
  unk_2021B70 = 0;
  switch ( a1 )
  {
    case -2:
      unk_2021B70 = 1;
      result = GetOEMCP();
      goto LABEL_3;
    case -3:
      unk_2021B70 = 1;
      result = GetACP();
      goto LABEL_3;
    case -4:
      result = *(_DWORD *)(v2 + 4);
      unk_2021B70 = 1;
LABEL_3:
      if ( v4 )
        *(_DWORD *)(v3 + 112) &= ~2u;
      return result;
  }
  if ( v4 )
    *(_DWORD *)(v3 + 112) &= ~2u;
  return a1;
}

