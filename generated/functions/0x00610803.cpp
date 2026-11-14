// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00610803 _write_char
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Native32-bit FILE offsets: ptr0,cnt4,base8,flags12,fd16,charbuf20,bufsiz24,tmpname28. Internal registers ECX FILE,ALcharacter,EAXrawinput,ESI
// count/errorDWORDpointer. Syntheticstringflag0x40 with baseNULL onlyincrements*count,NOoutput/cntdecrement/EAXassignment. OtherwiseDEC FILEcnt wrapped;nonnegative
// storeAL/ptr++,zeroextendALtoEAX;negative SIGN-EXTEND AL beforeflsbuf. Result-1 sets*count=-1;otherwiseincrementcount with32-bitwrap. No earlyreject whenincomingcount==-1, no
// ownerrno/lock/NULL/returnnormalization oncount-only path. EAXis char/helperresidue,notcounterpointerguarantee.
int __usercall write_char@<eax>(FILE *File@<ecx>, int result@<eax>, _DWORD *a3@<esi>)
{
  bool v3; // sf

  if ( ((File->_flag & 0x40) == 0 || File->_base)
    && ((v3 = File->_cnt - 1 < 0, --File->_cnt, v3)
      ? (result = _flsbuf((char)result, File))
      : (*File->_ptr = result, ++File->_ptr, result = (unsigned __int8)result),
        result == -1) )
  {
    *a3 = -1;
  }
  else
  {
    ++*a3;
  }
  return result;
}

