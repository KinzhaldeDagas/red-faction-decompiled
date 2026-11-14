// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060615E ??2@YAPAXI@Z
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Cdecl(size_t
// rawSize),operatornewreturnsnonNULLmallocpointerorentersC++throwpath. Firstmalloc(rawSize);NULL->callnewh(rawSize),nonzerohandlerresultRETRYsameSizeunboundedly,zero->throwsetup.
// Noownsize0normalization,upperbound,errnoassignmentorlock;malloc/newhandlersemanticsdelegated.
// Throwsetup:ifglobal2021348bit0clear,SETBITBEFOREconstructingstaticbad_allocat202133C,thenatexit(crt_static_bad_alloc_destroy_0202133c),registrationresultIGNORED.
// Noatomicinit/rollback;ctorfailurecanleaveflagset. Copyconstruct12bytestackexceptionfromstaticobject,callCxxThrowException(stackObject,ThrowInfo65E6EC),noownpost-callreturn/cleanup.
// OriginalPEThrowInfoattrs0/destructor60610F/catcharray65E6FCcount2;catchrecords65E708/65E724names .?AVbad_alloc@std@@ and
// .?AVexception@std@@,eachsize12andPMD{0,-1,0},corroboratebad_allocidentity/exceptionbase.
// DoesnotreturnNULLafterhandlerdeclines;ESIusedonlythrowpath,normalmallocreturndoesnotmodifyit.
void *__cdecl operator new(size_t Size)
{
  void *result; // eax
  _BYTE pExceptionObject[12]; // [esp+0h] [ebp-Ch] BYREF

  while ( 1 )
  {
    result = malloc(Size);
    if ( result )
      break;
    if ( !_callnewh(Size) )
    {
      if ( (dword_2021348 & 1) == 0 )
      {
        dword_2021348 |= 1u;
        std::bad_alloc::bad_alloc((std::bad_alloc *)unk_202133C);
        atexit(crt_static_bad_alloc_destroy_0202133c);
      }
      crt_bad_alloc_copy_construct((std::exception *)pExceptionObject, (struct std::exception *)unk_202133C);
      _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI2_AVbad_alloc_std__);
    }
  }
  return result;
}

