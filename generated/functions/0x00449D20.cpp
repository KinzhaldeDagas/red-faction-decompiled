// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00449D20 rf_geomod_operation_node132_construct_noop
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, queue/history ownership, smoke lifetime, cutter registry, native region constraints and corrected stack/AL ABI): 
// Thiscall132-byte node constructor, returns receiver. Invokes no-op operation100 constructor at+8. Thus initializes neither links0/4, operation8..107, nor six smoke slots108..131.
// History append and execution-queue append share this body but assign different ownership to trailing slots. No allocation or destructor registration here.
char *__thiscall rf_geomod_operation_node132_construct_noop(char *this)
{
  rf_geomod_operation_init(this + 8);
  return this;
}

