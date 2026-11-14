// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060598B __cfltcvt_init_0
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Noargs raw floating-conversion table initializer.
// Write exact ten UNENCODED callback pointers at665060..665084:
// cfltcvt60DBE1,cropzeros60D2C8,fassign60D27C,forcdecpt60D2B5,positive60D21E,cfltcvt60DBE1,cfltcvt_l60DB59,fassign_l60D23A,cropzeros_l60D19C,forcdecpt_l60D129. EAX returns raw
// cfltcvt pointer. No once guard, lock, encoding or call through any slot. Repeated invocation overwrites slots with raw addresses even if another initializer previously encoded
// them; encoding performed separately by initp_misc_cfltcvt_tab, not here.
int (__cdecl *_cfltcvt_init_0())(int, int, int, int, size_t Size, int)
{
  off_665060[0] = (int (*)())_cfltcvt;
  off_665064[0] = (int (*)())_cropzeros;
  off_665068[0] = (int (*)())_fassign;
  off_66506C[0] = (int (*)())_forcdecpt;
  off_665070[0] = (int (*)())_positive;
  off_665074[0] = (int (*)())_cfltcvt;
  off_665078[0] = (int (*)())_cfltcvt_l;
  off_66507C[0] = (int (*)())_fassign_l;
  off_665080[0] = (int (*)())_cropzeros_l;
  off_665084 = (int (*)())_forcdecpt_l;
  return (int (__cdecl *)(int, int, int, int, size_t, int))_cfltcvt;
}

