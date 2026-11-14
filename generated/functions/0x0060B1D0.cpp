// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060B1D0 _longjmp
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Noreturn cdecl(jmp_buf pointer,int Value), native
// nonlocal restore/JMP,not indirect CALL of saved PC. Allocate80-byte stack EXCEPTION_RECORD; initialize ONLY first five DWORDs {code80000026,flags0,nestedRecord0,address0,nParams0};
// remaining information slots not initialized here. EBX=buffer,load EBP=buffer[0] saved frame immediately,ESI=buffer[6] saved registration. If saved registration!=current FS:0 call
// imported RtlUnwind(savedRegistration,own60B21E,&partialException,NULL),with EBX/ESI saved around OS unwind; restore them at local target. This happens even for savedRegistration0
// when it differs from FS. If registration0 skip all local-unwind/version probing. Otherwise stdcall rt_probe_read4(buffer+20h). Probe false OR DWORD+20h!=56433230h
// ->local_unwind2(live EBP=saved frame,registration,buffer[7] level),reclaim8. Matching format ->load raw callback+24h; NULL skips legacy unwind entirely; nonNULL push buffer,CALL
// callback,NO caller pop (expected callee cleanup4). Signature read is not integrity/size validation: first buffer fields read BEFORE probe,only one DWORD probed; callback/other
// fields/restore target unvalidated. Then NLG_Notify(EAX=buffer[5] savedPC,EBP=savedFrame,stack code0),RET4 preserves destination. Set EDX=buffer base,restore
// EBX=buffer[1],EDI=buffer[2],ESI=buffer[3]. Read original Value via CURRENT ESP+5Ch (works only if delegates honor stack cleanup); unsigned CMP Value,1 /ADC EAX,0 maps ONLY zero
// to1,all nonzero incl negatives unchanged. Set ESP=buffer[4] savedESP,ADD ESP4 skips saved return slot,JMP DWORDbuffer[5]. EBP restored earlier and assumed preserved by delegates;
// EDX clobbered,ECX/flags not restored,x87/MXCSR/XMM not restored by own code. No cookie,buffer lifetime/NULL/whole-size/security/target/bounds validation,object freeing,own
// catch/rollback or return to longjmp caller. Incoming exception/registration and cleanup semantics belong to OS/verified unwind helpers; original code80000026 is deliberate unwind
// marker.
void __cdecl __noreturn longjmp(jmp_buf Buf, int Value)
{
  int *__attribute__((__org_typedef(jmp_buf))) v2; // ebx
  void *v3; // ebp
  _DWORD *v4; // esi
  void (__stdcall *v5)(int *__attribute__((__org_typedef(jmp_buf)))); // eax
  EXCEPTION_RECORD ExceptionRecord; // [esp+0h] [ebp-50h] BYREF

  v2 = Buf;
  ExceptionRecord.ExceptionCode = -2147483610;
  memset(&ExceptionRecord.ExceptionFlags, 0, 16);
  v3 = (void *)*Buf;
  v4 = (_DWORD *)Buf[6];
  if ( v4 != (_DWORD *)__readfsdword(0) )
  {
    RtlUnwind(v4, &lj_return, &ExceptionRecord, nullptr);
    v2 = Buf;
  }
  if ( v4 )
  {
    if ( _rt_probe_read4(v2 + 8) && v2[8] == 1447244336 )
    {
      v5 = (void (__stdcall *)(int *__attribute__((__org_typedef(jmp_buf)))))v2[9];
      if ( v5 )
        v5(v2);
    }
    else
    {
      _local_unwind2(v3, v4, v2[7]);
    }
  }
  _NLG_Notify(v2[5], (int)v3, 0);
  ((void (*)(void))v2[5])();
}

