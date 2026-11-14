// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0061E23E ___free_lc_time
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Cdecl(timeObject**pointer),void. NULLobjectpointer
// ->return. Free43containedpointers,exactindexorder1..6,0,8..13,7,14..42;eachpassedrawtofree,includingNULL.
// DoesNOTfreeobjectitself,checkrefcount+180,guarddefaulttimeADDRESS664C60,clearfields,detectduplicatepointersoracquirelock.
// Callerfreetlocinfochecksref/staticidentitythenfreesouterobjectseparately. Fieldsat172/176/180notfreedbythisbody;partialfreesremainifdelegatethrows.
void __cdecl __free_lc_time(void **a1)
{
  if ( a1 )
  {
    free(a1[1]);
    free(a1[2]);
    free(a1[3]);
    free(a1[4]);
    free(a1[5]);
    free(a1[6]);
    free(*a1);
    free(a1[8]);
    free(a1[9]);
    free(a1[10]);
    free(a1[11]);
    free(a1[12]);
    free(a1[13]);
    free(a1[7]);
    free(a1[14]);
    free(a1[15]);
    free(a1[16]);
    free(a1[17]);
    free(a1[18]);
    free(a1[19]);
    free(a1[20]);
    free(a1[21]);
    free(a1[22]);
    free(a1[23]);
    free(a1[24]);
    free(a1[25]);
    free(a1[26]);
    free(a1[27]);
    free(a1[28]);
    free(a1[29]);
    free(a1[30]);
    free(a1[31]);
    free(a1[32]);
    free(a1[33]);
    free(a1[34]);
    free(a1[35]);
    free(a1[36]);
    free(a1[37]);
    free(a1[38]);
    free(a1[39]);
    free(a1[40]);
    free(a1[41]);
    free(a1[42]);
  }
}

