// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0052EE70 rf_geomod_face_boolean_class_set
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, Boolean stage dispatch and workspace ownership,class bits/action table,transforms and room-return ABI,original ECX/stack flow and PE bytes): ThiscallmetadataDWORDpointer,value RET4. ClearONLYmask0x70000000 usingAND8FFFFFFF,thenOR low32(value<<28) WITHOUT inputmask/clamp. ReturnresultingfullflagsEAX. Value8 setsbit31;value16shiftsallbitsawayproducingclass0 whileexistingbit31persists. Normal0..7modifiesclassbits,preservingoldsignbit. Doesnotvalidateactiontablebounds.
int __thiscall rf_geomod_face_boolean_class_set(int *this, int a2)
{
  int result; // eax

  *this &= 0x8FFFFFFF;
  result = *this | (a2 << 28);
  *this = result;
  return result;
}

